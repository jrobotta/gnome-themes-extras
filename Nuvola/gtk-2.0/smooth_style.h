#include <gtk/gtkstyle.h>
#include "utils/misc_functions.h"

typedef struct _SmoothStyle SmoothStyle;
typedef struct _SmoothStyleClass SmoothStyleClass;

#if GTK2
extern GType smooth_type_style;
extern GtkStyleClass *style_parent_class;

#define SMOOTH_TYPE_STYLE              smooth_type_style
#define SMOOTH_STYLE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), SMOOTH_TYPE_STYLE, SmoothStyle))
#define SMOOTH_STYLE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), SMOOTH_TYPE_STYLE, SmoothStyleClass))
#define SMOOTH_IS_STYLE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), SMOOTH_TYPE_STYLE))
#define SMOOTH_IS_STYLE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), SMOOTH_TYPE_STYLE))
#define SMOOTH_STYLE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), SMOOTH_TYPE_STYLE, SmoothStyleClass))
#endif

struct _SmoothStyle
{
  #if GTK2
  GtkStyle parent_instance;
  #endif
};

struct _SmoothStyleClass
{
  #if GTK2
  GtkStyleClass parent_class;
  #endif
};

#if GTK2
void smooth_style_register_type (GTypeModule *module);
#endif

#if GTK2
extern GMemChunk	  *	smooth_style_data_chunk;
#endif
