#ifndef MISC_FUNCTIONS_H
#define MISC_FUNCTIONS_H

#include <gtk/gtk.h>

#include <gdk-pixbuf/gdk-pixbuf.h>

#include "draw_fill.h"
#include "draw_grips.h"
#include "draw_arrows.h"

#include <math.h>
#include <string.h>

#define DETAIL(xx) ((detail) && (!strcmp(xx, detail)))
#define FUZZY_COMPARE(i, j, fudge) ((i>j)?(i - j <= fudge):(j - i <= fudge))

#if GTK_CHECK_VERSION(2, 0, 0)
#define GTK2		1
#else
#define GTK1		1 
#endif

#ifdef GTK2

#define xthickness(style) (((GtkStyle *)style)->xthickness)
#define ythickness(style) (((GtkStyle *)style)->ythickness)

#define gdk_window_get_size(window, width, height) (gdk_drawable_get_size (window, width, height))
#define gdk_pixbuf_unref(pixbuf) (g_object_unref(pixbuf))
#define gdk_pixmap_unref(pixmap) (g_object_unref(pixmap))
#define gdk_pixbuf_ref(pixbuf) (g_object_ref(pixbuf))
#define gdk_pixmap_ref(pixmap) (g_object_ref(pixmap))
#define gdk_gc_destroy(gc) (g_object_ref(gc))

typedef const gchar		detail_char;

#endif

#ifdef GTK1

#define xthickness(style) (((GtkStyle *)style)->klass->xthickness)
#define ythickness(style) (((GtkStyle *)style)->klass->ythickness)
#define g_ascii_strncasecmp(str1, str2, len) (g_strncasecmp(str1, str2, len))

typedef gchar			detail_char;

#endif

#define NO_CHECK	1
#define FAST_CHECK	2
#define SLOPPY_CHECK	3
#define CLEAN_CHECK	4
#define X_CHECK		5
#define BLOCK_CHECK	6
#define CIRCLE_CHECK	7
#define DIAMOND_CHECK   8
#define XPM_CHECK	9

#define NO_OPTION	1
#define CIRCLE_OPTION	2
#define DIAMOND_OPTION	3
#define SQUARE_OPTION	4
#define XPM_OPTION	5

#define NO_EDGE		1
#define LINE_EDGE	2
#define GRADIENT_EDGE	3
#define XPM_EDGE	4

void
get_tab_status (GtkNotebook *notebook,
		int          x,
		int          y, 
		int         *position, 
		int         *selected);

gboolean
sanitize_parameters(GtkStyle * style,
  	            GdkWindow * window,
	            gint * width,
	            gint * height);
		    
void
reverse_engineer_stepper_box (GtkWidget    *range,
			      GtkArrowType  arrow_type,
			      gint         *x,
			      gint         *y,
			      gint         *width,
			      gint         *height);

void
reverse_engineer_spin_button (GtkWidget    *widget,
			      GtkArrowType  arrow_type,
			      gint         *x,
			      gint         *y,
			      gint         *width,
			      gint         *height);

void
reverse_engineer_arrow_box (GtkWidget    *widget,
                            const gchar * detail,
			    GtkArrowType  arrow_type,
			    gint         *x,
			    gint         *y,
			    gint         *width,
			    gint         *height);
			    
gboolean
rounded_extension_points(gint x,
                         gint y, 
			 gint width, 
			 gint height,
			 GtkPositionType position,
			 GdkPoint points[8]);


void
rounded_box_points(gint x,
                   gint y, 
  	           gint width, 
		   gint height,
		   GdkPoint points[13],
		   gboolean large);

void
draw_default_triangle(GtkStyle * style,
	              GdkWindow * window,
	              GtkStateType state_type,
	              GtkShadowType shadow_type,
	              GdkRectangle * area,
	              GtkWidget * widget,
	              const gchar * detail,
		      gint x,
		      gint y,
		      gint width,
		      gint height);	

void
do_draw_shadow_with_gap(GdkWindow * window,
                        GdkRectangle * area,
			GdkGC * tl_gc,
			GdkGC * br_gc,
			gint x,
			gint y,
			gint width,
			gint height,
			GtkPositionType gap_side, 
			gint gap_pos,
			gint gap_size,
			gboolean topleft_overlap);

void
do_draw_bevel_with_gap(GdkWindow * window,
                       GdkRectangle * area,
		       GdkGC * tl_gc,
		       GdkGC * br_gc,
		       gint x,
		       gint y,
		       gint width,
		       gint height,
		       gint thickness,
		       GtkPositionType gap_side, 
		       gint gap_pos,
		       gint gap_size);

void
do_draw_option_shadow(GdkWindow * window,
	       GdkRectangle * area,
               GdkGC * tl_gc,
               GdkGC * br_gc,
	       gint x,
	       gint y,
	       gint width,
	       gint height);
	       
void
do_draw_option_bevel(GdkWindow * window,
                       GdkRectangle * area,
		       GdkGC * tl_gc,
		       GdkGC * br_gc,
		       gint x,
		       gint y,
		       gint width,
		       gint height,
		       gint thickness);

void
draw_check_mark(GdkWindow * window,
                GdkGC * gc,
		GdkRectangle * area,
		gint x,
		gint y,
		gint width,
		gint height,
		gint check_style);

gboolean 
TranslateCheckStyleName (gchar * str, gint *retval);

gboolean 
TranslateEdgeStyleName (gchar * str, gint *retval);

#endif /* MISC_FUNCTIONS_H */
