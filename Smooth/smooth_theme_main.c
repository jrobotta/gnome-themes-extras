#include <gmodule.h>
#include "smooth_rc_style.h"
#include "smooth_style.h"

#if GTK1
#include "gtk1/gtk1_patches.h"

extern GtkStyleClass smooth_default_class;

void
smooth_style_duplicate (GtkStyle * dest, GtkStyle * src)
{
  SmoothRcStyle *dest_data = NEW_THEME_DATA(dest); 
  
  dest_data->refcount = 1;
  dest->klass = &smooth_default_class;
  smooth_rc_style_init(dest_data);
  SET_THEME_DATA(dest, dest_data);
}

void
smooth_style_realize (GtkStyle * style)
{
}

void
smooth_style_unrealize (GtkStyle * style)
{
}

static void
theme_data_ref (SmoothRcStyle * theme_data)
{
  if (theme_data) theme_data->refcount++;
}

static void
theme_data_unref (SmoothRcStyle * theme_data)
{
  if (theme_data) theme_data->refcount--;
  if ((theme_data) && (theme_data->refcount == 0)) {
    g_free (theme_data);
    theme_data = NULL;
  }  
}

static void
smooth_rc_style_destroy (GtkRcStyle * rc_style)
{
  theme_data_unref (SMOOTH_RC_DATA(rc_style));
}

static void
smooth_style_destroy (GtkStyle * style)
{
  theme_data_unref (THEME_DATA(style));
}

static void
smooth_rc_style_to_style(GtkStyle * style, 
                         GtkRcStyle * rc_style)
{
  SmoothRcStyle *data = SMOOTH_RC_DATA(rc_style);

  style->klass = &smooth_default_class;
  style->engine_data = data;
  
  if (data->xthickness >= 0)
  style->klass->xthickness = data->xthickness;

  if (data->ythickness >= 0)
  style->klass->ythickness = data->ythickness;
  
  theme_data_ref (data);
}

static void
theme_set_background (GtkStyle * style,
		      GdkWindow * window, 
		      GtkStateType state_type)
{
  GdkPixmap *pixmap;
  gint parent_relative;

  g_return_if_fail (style != NULL);
  g_return_if_fail (window != NULL);

  if (style->bg_pixmap[state_type]) {
    if (style->bg_pixmap[state_type] == (GdkPixmap *) GDK_PARENT_RELATIVE) {
      pixmap = NULL;
      parent_relative = TRUE;
    } else {
      pixmap = style->bg_pixmap[state_type];
      parent_relative = FALSE;
    }

    gdk_window_set_back_pixmap (window, pixmap, parent_relative);
  } else {
    gdk_window_set_background (window, &style->bg[state_type]);
  }
}

G_MODULE_EXPORT void
theme_init (GtkThemeEngine * engine)
{
  engine->parse_rc_style = smooth_rc_style_parse;
  engine->merge_rc_style = smooth_rc_style_merge;
  engine->rc_style_to_style = smooth_rc_style_to_style;
  engine->duplicate_style = smooth_style_duplicate;
  engine->realize_style = smooth_style_realize;
  engine->unrealize_style = smooth_style_unrealize;
  engine->destroy_rc_style = smooth_rc_style_destroy;
  engine->destroy_style = smooth_style_destroy;
  engine->set_background = theme_set_background;

  patches_install();
}

G_MODULE_EXPORT void
theme_exit (void)
{
  patches_uninstall();
}
#endif

#if GTK2
G_MODULE_EXPORT void
theme_init (GTypeModule *module)
{
  smooth_rc_style_register_type (module);
  smooth_style_register_type (module);
  gtk_rc_reparse_all;
}

G_MODULE_EXPORT void
theme_exit (void)
{
}

G_MODULE_EXPORT GtkRcStyle *
theme_create_rc_style (void)
{
  void *ptr;
  
  ptr = GTK_RC_STYLE (g_object_new (SMOOTH_TYPE_RC_STYLE, NULL));  
  return (GtkRcStyle *)ptr;
}
#endif

/* The following function will be called by GTK+ when the module
 * is loaded and checks to see if we are compatible with the
 * version of GTK+ that loads us.
*/
G_MODULE_EXPORT const gchar *g_module_check_init (GModule * module);

const gchar *

g_module_check_init (GModule * module)
{
  return gtk_check_version (GTK_MAJOR_VERSION,
			    GTK_MINOR_VERSION,
			    GTK_MICRO_VERSION - GTK_INTERFACE_AGE);
}
