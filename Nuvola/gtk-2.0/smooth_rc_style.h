#include <gtk/gtk.h>
#include "utils/misc_functions.h"

#define SMOOTH_LINE_NONE		1
#define SMOOTH_LINE_FLAT		2
#define SMOOTH_LINE_THIN		3
#define SMOOTH_LINE_BEVELED		4
#define SMOOTH_LINE_STANDARD		5
#define SMOOTH_LINE_SMOOTHED		6
#define SMOOTH_LINE_COLD		7
#define SMOOTH_LINE_WIN32		8
#define SMOOTH_LINE_SMOOTHBEVEL		9

#define SMOOTH_SOLID_FILL		1
#define SMOOTH_GRADIENT_FILL		2
#define SMOOTH_SHADE_GRADIENT_FILL	3
#define SMOOTH_PIXBUF_FILL		4

#define SMOOTH_NORMAL_TABS		1
#define SMOOTH_ROUND_TABS		2
#define SMOOTH_TRIANGLE_TABS		3
#define SMOOTH_XPM_TABS			4

#define NO_EDGE		1
#define LINE_EDGE	2
#define GRADIENT_EDGE	3
#define XPM_EDGE	4

#define DEFAULT_CHECKSTYLE		FAST_CHECK
#define DEFAULT_GRADIENT		TRUE
#define DEFAULT_HGRADIENTDIRECTION	GDK_GRADIENT_HORIZONTAL
#define DEFAULT_VGRADIENTDIRECTION	GDK_GRADIENT_VERTICAL
#define DEFAULT_FILLSTYLE		SMOOTH_SOLID_FILL
#define DEFAULT_EDGESTYLE		LINE_EDGE
#define DEFAULT_LINETHICKNESS		2
#define DEFAULT_LINESTYLE		SMOOTH_LINE_STANDARD
#define DEFAULT_TABSTYLE		SMOOTH_NORMAL_TABS
#define DEFAULT_GRIPSTYLE		FIXEDLINES_IN_GRIP
#define DEFAULT_ARROWSTYLE		ARROW_STYLE_THINICE
#define DEFAULT_SOLIDARROW		FALSE
#define DEFAULT_ETCHEDARROW		FALSE
#define DEFAULT_GRIPCOUNT		3
#define DEFAULT_GRIPSPACING		2
#define DEFAULT_OPTIONSTYLE		CIRCLE_OPTION
#define DEFAULT_REAL_SLIDERS		FALSE
#define DEFAULT_RESIZE_GRIP		TRUE
#define DEFAULT_TROUGH_SHOW_VALUE	FALSE
#define DEFAULT_GRIPOVERLAP		FALSE


typedef struct _SmoothRcStyle SmoothRcStyle;

#if GTK1
typedef struct _SmoothRcProperty SmoothRcProperty;
#endif

#if GTK2
typedef struct _SmoothRcStyleClass SmoothRcStyleClass;
#endif

typedef struct _smooth_line_style smooth_line_style;
typedef struct _smooth_fill_style smooth_fill_style;

typedef struct _smooth_part_style smooth_part_style;

typedef struct _smooth_edge_style smooth_edge_style;

typedef struct _smooth_bg_style smooth_bg_style;
typedef struct _smooth_grip_style smooth_grip_style;
typedef struct _smooth_check_style smooth_check_style;
typedef struct _smooth_option_style smooth_option_style;
typedef struct _smooth_arrow_style smooth_arrow_style;
typedef struct _smooth_trough_style smooth_trough_style;

typedef gboolean (*SmoothTranslateEnumFunc) (gchar * str, gint *retval);

#define THEME_PART(part)                 ((smooth_part_style *) (part))

#if GTK2
extern GType smooth_type_rc_style;

#define SMOOTH_TYPE_RC_STYLE              smooth_type_rc_style
#define SMOOTH_RC_STYLE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), SMOOTH_TYPE_RC_STYLE, SmoothRcStyle))
#define SMOOTH_RC_STYLE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), SMOOTH_TYPE_RC_STYLE, SmoothRcStyleClass))
#define SMOOTH_IS_RC_STYLE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), SMOOTH_TYPE_RC_STYLE))
#define SMOOTH_IS_RC_STYLE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), SMOOTH_TYPE_RC_STYLE))
#define SMOOTH_RC_STYLE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), SMOOTH_TYPE_RC_STYLE, SmoothRcStyleClass))
#define SMOOTH_RC_DATA(rc_style)          (SMOOTH_RC_STYLE (rc_style))

#define THEME_DATA(style)                 (SMOOTH_RC_STYLE (style->rc_style))
#define NEW_THEME_DATA(rc_style)          (SMOOTH_RC_STYLE (rc_style))
#define SET_THEME_DATA(rc_style, data)    (SMOOTH_RC_DATA (rc_style))
#endif

#if GTK1
#define SMOOTH_RC_DATA(rc_style)          ((SmoothRcStyle *) ((rc_style)->engine_data))

#define THEME_DATA(style)                 ((SmoothRcStyle *) ((style)->engine_data))
#define NEW_THEME_DATA(rc_style)          ((SmoothRcStyle *) (g_new0 (SmoothRcStyle, 1)))
#define SET_THEME_DATA(rc_style, data)    (rc_style->engine_data=data)

#define PANED_HANDLE_SIZE(style)(THEME_DATA(style)->paned_handle_size)
#endif

#define REAL_SLIDERS(style)(THEME_DATA(style)->real_sliders)
#define RESIZE_GRIP(style)(THEME_DATA(style)->resize_grip)
#define DO_CHECK_LINE_THICKNESS(line,thickness)(((line==SMOOTH_LINE_BEVELED) || (line==SMOOTH_LINE_FLAT) || (line==SMOOTH_LINE_NONE))?thickness:2)

#define PART_STYLE(part)(THEME_PART(part)->style)
#define PART_XPADDING(part)(THEME_PART(part)->ypadding)
#define PART_YPADDING(part)(THEME_PART(part)->xpadding)

#define LINE_STYLE(style, part)(((part) && THEME_PART(part)->use_line)?THEME_PART(part)->line.style:THEME_DATA(style)->line.style)
#define LINE_THICKNESS(style, part) (((part) && THEME_PART(part)->use_line)?DO_CHECK_LINE_THICKNESS(THEME_PART(part)->line.style, THEME_PART(part)->line.thickness):DO_CHECK_LINE_THICKNESS(THEME_DATA(style)->line.style, THEME_DATA(style)->line.thickness))

#define EDGE_PART(style)(&THEME_DATA(style)->edge)
#define BACKGROUND_PART(style)(&THEME_DATA(style)->background)

#define EDGE_LINE_STYLE(style, part)((((part) && THEME_PART(part)->edge.use_line))?THEME_PART(part)->edge.line.style:(EDGE_PART(style)->use_line?EDGE_PART(style)->line.style:LINE_STYLE(style, part)))
#define EDGE_LINE_THICKNESS(style, part) ((((part) && THEME_PART(part)->edge.use_line))?DO_CHECK_LINE_THICKNESS(THEME_PART(part)->edge.line.style, THEME_PART(part)->edge.line.thickness):(EDGE_PART(style)->use_line?DO_CHECK_LINE_THICKNESS(EDGE_PART(style)->line.style, EDGE_PART(style)->line.thickness):LINE_THICKNESS(style, part)))

#define GRIP_PART(style)(&THEME_DATA(style)->grip)
#define GRIP_COUNT(style)(GRIP_PART(style)->count)
#define GRIP_SPACING(style)(GRIP_PART(style)->spacing)
#define GRIP_OVERLAP_TOOLBAR(style)(GRIP_PART(style)->overlap)

#define CHECK_PART(style)(&THEME_DATA(style)->check)
#define CHECK_MOTIF(style)(CHECK_PART(style)->motif)

#define OPTION_PART(style)(&THEME_DATA(style)->option)
#define OPTION_MOTIF(style)(THEME_DATA(style)->option.motif)

#define TROUGH_PART(style)(&THEME_DATA(style)->trough)
#define TROUGH_SHOW_VALUE(style) (THEME_DATA(style)->trough.show_value)
#define PROGRESS_PART(style)(&THEME_DATA(style)->progress)

/* macros for retrieving fill/background properties */
#define FILL_STYLE(style, part) (((part) && THEME_PART(part)->use_fill)?THEME_PART(part)->fill.style:THEME_DATA(style)->fill.style)
#define FILL_GRADIENT_DIRECTION(style, part, orientation) (((part) && THEME_PART(part)->use_fill)?THEME_PART(part)->fill.gradient_direction[orientation]:THEME_DATA(style)->fill.gradient_direction[orientation])
#define FILL_QUADRATIC_GRADIENT(style, part) (((part) && THEME_PART(part)->use_fill)?THEME_PART(part)->fill.quadratic_gradient:THEME_DATA(style)->fill.quadratic_gradient)
#define FILL_SHADE1_VALUE(style, part) (((part) && THEME_PART(part)->use_fill)?THEME_PART(part)->fill.shade1:THEME_DATA(style)->fill.shade1)
#define FILL_SHADE2_VALUE(style, part) (((part) && THEME_PART(part)->use_fill)?THEME_PART(part)->fill.shade2:THEME_DATA(style)->fill.shade2)
#define FILL_COLOR1(style, part, state) (((part) && THEME_PART(part)->use_fill)?((THEME_PART(part)->fill.use_color1[state])?THEME_PART(part)->fill.color1[state]:((THEME_DATA(style)->fill.use_color1[state])?THEME_DATA(style)->fill.color1[state]:style->bg[state])):((THEME_DATA(style)->fill.use_color1[state])?THEME_DATA(style)->fill.color1[state]:style->bg[state]))
#define FILL_COLOR2(style, part, state) (((part) && THEME_PART(part)->use_fill)?((THEME_PART(part)->fill.use_color2[state])?THEME_PART(part)->fill.color2[state]:((THEME_DATA(style)->fill.use_color2[state])?THEME_DATA(style)->fill.color2[state]:style->bg[state])):((THEME_DATA(style)->fill.use_color2[state])?THEME_DATA(style)->fill.color2[state]:style->bg[state]))
#define FILL_FILE_NAME(style, part, state) (((part) && THEME_PART(part)->use_fill)?((THEME_PART(part)->fill.file_name[state])?THEME_PART(part)->fill.file_name[state]:((THEME_DATA(style)->fill.file_name[state])?THEME_DATA(style)->fill.file_name[state]:NULL)):((THEME_DATA(style)->fill.file_name[state])?THEME_DATA(style)->fill.file_name[state]:NULL))

#define ARROW_STYLE(style)(THEME_DATA(style)->arrow.style)
#define SOLID_ARROW(style)(THEME_DATA(style)->arrow.solid)
#define ETCHED_ARROW(style)(THEME_DATA(style)->arrow.etched)
#define ARROW_XPADDING(part)(THEME_DATA(style)->arrow.ypadding)
#define ARROW_YPADDING(part)(THEME_DATA(style)->arrow.xpadding)

struct _smooth_line_style {
  gint style;
  gint thickness;
};

struct _smooth_fill_style {
  gint style;//none/flat/gradient/shaded

  gint gradient_direction[2];//horizontal/vertical/fdiagonal/bdiagonal
  gint quadratic_gradient;

  gfloat shade1;//0.0/2.5
  gfloat shade2;//0.0/2.5

  gboolean use_color1[5];//GtkStateType
  gboolean use_color2[5];//GtkStateType

  GdkColor color1[5];//GtkStateType
  GdkColor color2[5];//GtkStateType

  gchar * file_name[5];//GtkStateType
};

struct _smooth_edge_style {
  gint style;

  smooth_line_style line;
  smooth_fill_style fill;
  gboolean use_line;
};

struct _smooth_part_style {
  gint style;

  smooth_edge_style edge;
  smooth_line_style line;
  smooth_fill_style fill;
  gboolean use_line;
  gboolean use_fill;

  gchar * file_name;
  GdkPixmap * part;

  gint xpadding;
  gint ypadding;
};

struct _smooth_bg_style {
  smooth_part_style part;
};

struct _smooth_grip_style {
  smooth_part_style part;

  gint count;
  gint spacing;
  gboolean overlap;
};

struct _smooth_check_style {
  smooth_part_style part;
  gboolean motif;  
};

struct _smooth_option_style {
  smooth_part_style part;
  gboolean motif;  
};

struct _smooth_arrow_style {
  gint style;
  gboolean solid;
  gboolean etched;

  gint xpadding;
  gint ypadding;

  /*smooth_part_style part;
  gint border;
  gint fill;*/
};

struct _smooth_trough_style {
  smooth_part_style part;
  gboolean show_value;
};


struct _SmoothRcStyle
{
  #if GTK2
  GtkRcStyle parent_instance;
  #endif

  #if GTK1
  gint			  refcount;
  #endif
  
  gboolean		  real_sliders;
  gboolean		  resize_grip;
  
  smooth_fill_style	  fill;
  smooth_line_style	  line;
  smooth_edge_style	  edge;
  smooth_bg_style	  background;

  smooth_trough_style     trough;

  smooth_part_style       progress;

  smooth_grip_style	  grip;
  smooth_check_style	  check;
  smooth_option_style	  option;
  smooth_arrow_style      arrow;
  gint			  tab_style;
  #if GTK1
  gint			  xthickness;
  gint			  ythickness;

  guint16		  paned_handle_size;
  #endif
};

void smooth_rc_style_init (SmoothRcStyle *style);

#if GTK2
struct _SmoothRcStyleClass
{
  GtkRcStyleClass parent_class;
};

void smooth_rc_style_register_type (GTypeModule *module);
#endif

#if GTK1
void
smooth_rc_style_merge (GtkRcStyle * dest,
                       GtkRcStyle * src);
		       
guint 
smooth_rc_style_parse (GScanner * scanner, 
                       GtkRcStyle * rc_style);

struct _SmoothRcProperty
{
  gchar * class_name;
  gchar * property_name;
  GtkArg value;
};
#endif
