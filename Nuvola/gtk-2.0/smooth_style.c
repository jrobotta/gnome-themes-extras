/*******************************************************************************************
 * Smooth theme for gtk, based on the ThinIce, CleanIce, XFCE, EnGradient, IceGradient, XFCE, 
 *                                    Xenophilia, Wonderland/Bluecurve, & LighthouseBlue GTK+ Engines
 *
 * Author: Andrew Johnson <aj_genius@hotmail.com>
 *
 * A nice simple engine, designed to be clean, smooth and highly configurable. It is based
 * initially upon EnGradient, but highly modified to include some of the best features from 
 * many other (some popular) engines. While very little of this code is initially my own,
 * it is been so highly modified it at times might apear to be.
 *
 *******************************************************************************************
 *   
 * EnGradient Header -->
 * 
 * My gradient engine for gtk+.  slightly modified from the IceGradient theme,
 * to include checkboxes, scrollbars, arrows, and a few other things from the
 * Mac2 theme engine, in order to make it look like a standard toolkit.  Almost
 * no code in this theme is my own.  It is mostly the IceGradient theme, with
 * large chunks of the Mac2 theme (by Ken Lynch <kenny@lynch42.freeserve.co.uk>)
 *   
 *   IceGradient theme for gtk, hacked over ThinIce by Tim Gerla and Tomas Ögren ThinIce,
 *     which is based on raster's Motif theme and the Metal theme.
 *     Authors: Tim Gerla <timg@means.net>
 *              Tomas Ögren <stric@ing.umu.se>
 *              JM Perez <jose.perez@upcnet.es>
 *   
 * <-- EnGradient Header
 *   
 *******************************************************************************************   
 *   
 * IceGradient Header -->
 *   
 * IceGradient theme for gtk, hacked over ThinIce by Tim Gerla and Tomas Ögren ThinIce,
 *   which is based on raster's Motif theme and the Metal theme.
 *   Authors: Tim Gerla <timg@means.net>
 *            Tomas Ögren <stric@ing.umu.se>
 *            JM Perez <jose.perez@upcnet.es>
 *   
 * <-- IceGradient Header
 *   
 *******************************************************************************************    
 *   
 * CleanIce Header -->
 *
 * CleanIce theme for gtk, based on the ThinIce, Clean and Cleanice GTK+ Engines
 *   Author: Bastien Nocera <hadess@hadess.net>
 *   Cleanice original author:  Rodney Dawes <dobez@fnmail.com>
 *   ThinIce Authors: Tim Gerla <timg@means.net>
 *   	  Tomas Ögren <stric@ing.umu.se>
 *   Clean Author: dengen40@yahoo.com
 *
 * <-- CleanIce Header
 *
 *******************************************************************************************/

#include <gtk/gtk.h>

#include "smooth_style.h"
#include "smooth_rc_style.h"

#include "utils/misc_functions.h"

#include <math.h>

#include <gtk/gtk.h>

#define IS_HANDLE_BOX_ITEM(object) ((widget) && (widget->parent) && GTK_IS_HANDLE_BOX(gtk_widget_get_parent (widget)))

#if GTK1
extern GtkStyleClass smooth_default_class;

#define IS_BONOBO_DOCK_ITEM(object) (TRUE)

#endif

#if GTK2
static GtkStyleClass *parent_class = NULL;

#define IS_BONOBO_DOCK_ITEM(object) ((widget) && (widget->parent) && (GTK_IS_HANDLE_BOX(gtk_widget_get_parent (widget)) || (g_type_name(G_OBJECT_TYPE(widget->parent))) && (!strcmp("BonoboDockItem", g_type_name(G_OBJECT_TYPE(widget->parent))))))

#endif

#define ROUND_CORNERS	0

static void 
draw_slider_grip(GtkStyle * style,
                       GdkWindow * window,
		       GtkStateType state_type,
		       GtkShadowType shadow_type,
		       GdkRectangle * area,
		       GtkWidget * widget,
		       detail_char * detail,
		       gint x,
		       gint y,
		       gint width,
		       gint height,
		       GtkOrientation orientation);

static void
draw_handle(GtkStyle * style,
	    GdkWindow * window,
	    GtkStateType state_type,
	    GtkShadowType shadow_type,
	    GdkRectangle * area,
	    GtkWidget * widget,
	    detail_char * detail,
	    gint x,
	    gint y,
	    gint width,
	    gint height,
	    GtkOrientation orientation);

static GdkGC *
new_color_gc (GtkStyle * style, GdkColor * color)
{
  GdkGCValues gc_values;
  
  gdk_colormap_alloc_color (style->colormap, color,
			    FALSE, TRUE);

  gc_values.foreground = *color;

  return gtk_gc_get (style->depth, style->colormap,
		     &gc_values, GDK_GC_FOREGROUND);
}


static double shades[] = {1.065, 0.963, 0.896, 0.85, 0.768, 0.665, 0.4, 0.205, 0.112};

static GdkGC *
shaded_color (GtkStyle * style, GtkStateType state_type, gdouble shade_value)
{
  GdkColor color;
  
  shade (&style->bg[state_type], &color, shade_value);

  return new_color_gc (style, &color);

}

#define LIGHTNESS_MULT  1.2//1.1
#define DARKNESS_MULT   0.666667 //0.5
static void
lighttone_color(GdkColor * color, GtkStyle * style, GtkStateType state)
{
  shade (&style->bg[state], color, LIGHTNESS_MULT);
}

static void
darktone_color(GdkColor * color, GtkStyle * style, GtkStateType state)
{
  shade (&style->bg[state], color, DARKNESS_MULT);
}

static void
midtone_color(GdkColor * color, GtkStyle * style, GtkStateType state)
{
  GdkColor dark_color, light_color;
  
  shade (&style->bg[state], &light_color, LIGHTNESS_MULT);
  shade (&style->bg[state], &dark_color, DARKNESS_MULT);

  color->red = (light_color.red + dark_color.red) / 2;
  color->green = (light_color.green + dark_color.green) / 2;
  color->blue = (light_color.blue + dark_color.blue) / 2;
}

static GdkGC *
lighttone_gc(GtkStyle * style, GtkStateType state)
{
  GdkGC * light_gc=style->light_gc[state];
  light_gc = shaded_color (style, state, LIGHTNESS_MULT);  
  return light_gc;
}

static GdkGC *
darktone_gc(GtkStyle * style, GtkStateType state)
{
  GdkGC * dark_gc=dark_gc=style->dark_gc[state];
  dark_gc = shaded_color (style, state, DARKNESS_MULT);  
  return dark_gc;
}

static GdkGC *
midtone_gc(GtkStyle * style, GtkStateType state)
{
  GdkGC * dark_gc=NULL, * light_gc=NULL, * mid_gc=style->mid_gc[state];
  GdkColor dark_color, light_color, mid_color;

  shade (&style->bg[state], &light_color, LIGHTNESS_MULT);
  shade (&style->bg[state], &dark_color, DARKNESS_MULT);

  mid_color.red = (light_color.red + dark_color.red) / 2;
  mid_color.green = (light_color.green + dark_color.green) / 2;
  mid_color.blue = (light_color.blue + dark_color.blue) / 2;
  mid_gc = new_color_gc(style, &mid_color);
  return mid_gc;
}

static GdkGC *
middarktone_gc(GtkStyle * style, GtkStateType state)
{
  GdkGC * dark_gc=NULL, * mid_gc=style->mid_gc[state];
  GdkColor dark_color,  mid_color;

  shade (&style->bg[state], &dark_color, DARKNESS_MULT);

  mid_color.red = (style->bg[state].red + dark_color.red) / 2;
  mid_color.green = (style->bg[state].green + dark_color.green) / 2;
  mid_color.blue = (style->bg[state].blue + dark_color.blue) / 2;
  mid_gc = new_color_gc(style, &mid_color);
  return mid_gc;
}

static GdkGC *
midlighttone_gc(GtkStyle * style, GtkStateType state)
{
  GdkGC * * light_gc=NULL, * mid_gc=style->mid_gc[state];
  GdkColor  light_color, mid_color;

  shade (&style->bg[state], &light_color, LIGHTNESS_MULT);

  mid_color.red = (light_color.red + style->bg[state].red) / 2;
  mid_color.green = (light_color.green + style->bg[state].green) / 2;
  mid_color.blue = (light_color.blue + style->bg[state].blue) / 2;
  mid_gc = new_color_gc(style, &mid_color);
  return mid_gc;
}

static GdkBitmap *
arc_clip_mask(gint width,
	      gint height)
{
  GdkBitmap *result;
  GdkGC *gc;
  GdkColor color;

  result = (GdkBitmap *)gdk_pixmap_new(NULL, width, height, 1);
  gc = gdk_gc_new(result);
	
  color.pixel = 0;
  gdk_gc_set_foreground(gc, &color);

  gdk_draw_rectangle(result, gc, TRUE, 0, 0, width, height);
  gdk_draw_rectangle(result, gc, FALSE, 0, 0, width, height);

  color.pixel = 1;
  gdk_gc_set_foreground(gc, &color);

  gdk_draw_arc(result, gc, TRUE, 0, 0, width, height, 0, 360*64);
  gdk_draw_arc(result, gc, FALSE, 0, 0, width, height, 0, 360*64);

  gdk_gc_destroy(gc);

  return result;
}

static GdkBitmap *
round_box_clip_mask(gint width,
		    gint height)
{
  GdkBitmap *result;
  GdkGC *gc;
  GdkColor color;
  GdkPoint	 points[13];

  result = (GdkBitmap *)gdk_pixmap_new(NULL, width, height, 1);
  gc = gdk_gc_new(result);
	
  color.pixel = 0;
  gdk_gc_set_foreground(gc, &color);

  gdk_draw_rectangle(result, gc, TRUE, 0, 0, width, height);
  gdk_draw_rectangle(result, gc, FALSE, 0, 0, width, height);

  color.pixel = 1;
  gdk_gc_set_foreground(gc, &color);

  rounded_box_points(1, 1, width-2, height-2,points, TRUE);

  gdk_draw_polygon(result, gc, TRUE, points, 12);
  gdk_draw_polygon(result, gc, FALSE, points, 12);

  gdk_gc_destroy(gc);

  return result;
}

#define FLAT_FILL_BACKGROUND(style, window, state_type, area, widget, part, x, y, width, height) (fill_background(style, window, state_type, GTK_SHADOW_NONE, area, NULL, widget, part, x, y, width, height, FALSE, FALSE, GTK_ORIENTATION_VERTICAL,FALSE))		
#define gradient_fill_background(style, window, state_type, area, widget, part, x, y, width, height, invert, orientation) (fill_background(style, window, state_type, GTK_SHADOW_NONE, area, NULL, widget, part, x, y, width, height, TRUE, invert, orientation,FALSE))

/* This function is based on a similar routine from IceGradient */
static void 
fill_background(GtkStyle * style,
  	        GdkWindow * window,
	        GtkStateType state_type,
		GtkShadowType shadow_type,
	        GdkRectangle * area,
	        GdkRegion * rgn,
 	        GtkWidget * widget,
		smooth_part_style * part,
	        gint x,
	        gint y,
	        gint width,
	        gint height,
		gboolean use_gradient,  
	        gboolean invert,
		GtkOrientation orientation,
		gboolean arc_fill)
{
  GdkRectangle clip_area;
  GdkBitmap * clip_mask = NULL;
  gint fill_style;
  
  g_return_if_fail(sanitize_parameters(style, window, &width, &height));
  
  if (!part) part = THEME_PART(BACKGROUND_PART(style));
  
  fill_style = FILL_STYLE(style, part);  

  clip_area.x = x;
  clip_area.y = y;
  clip_area.width = width;
  clip_area.height = height;
  	
  if (fill_style == SMOOTH_PIXBUF_FILL) {
    if (!FILL_FILE_NAME(style, part, state_type)) 
      fill_style = SMOOTH_SOLID_FILL;
  } else {
    if (!use_gradient) 
       fill_style = SMOOTH_SOLID_FILL;
  }

  switch (fill_style) {
    case SMOOTH_PIXBUF_FILL : 
      { 
        GdkGC *gc = gdk_gc_new(window);
	GdkGCValues gc_values;

        gdk_gc_get_values(style->bg_gc[state_type], &gc_values);
	gdk_gc_set_function(gc, GDK_COPY);
        gdk_gc_set_line_attributes(gc, 1, GDK_LINE_SOLID, gc_values.cap_style, gc_values.join_style);
        
        if (!arc_fill) {
	  #if ROUND_CORNERS
  	  gdk_gc_set_clip_rectangle(gc, NULL);
	  arc_fill = TRUE;
	  clip_mask = round_box_clip_mask(width, height);
	  gdk_gc_set_clip_origin(gc, x, y);	  
          gdk_gc_set_clip_mask(gc, clip_mask);
          #else
	  if (rgn) {
	    arc_fill = TRUE;
	    gdk_gc_set_clip_region(gc, rgn);
	  } else 
	    if (area) gdk_gc_set_clip_rectangle(gc, area);
	  #endif
	} 
	else {
  	  gdk_gc_set_clip_rectangle(gc, NULL);
          clip_mask = arc_clip_mask(clip_area.width+1, clip_area.height+1);
	  gdk_gc_set_clip_origin(gc, clip_area.x, clip_area.y);	  
          gdk_gc_set_clip_mask(gc, clip_mask);
        }
	         
        gdk_tile_pixbuf_fill (window, gc, FILL_FILE_NAME(style, part, state_type), area, x, y, width, height, arc_fill);
	
        gdk_gc_set_clip_mask(gc, NULL);
        gdk_gc_set_clip_rectangle(gc, NULL);
        gdk_gc_destroy(gc);
      }
      break;
    case SMOOTH_GRADIENT_FILL : 
    case SMOOTH_SHADE_GRADIENT_FILL : 
      {
        GdkGC *gc = gdk_gc_new(window);
	GdkGCValues gc_values;
        gint direction=FILL_GRADIENT_DIRECTION(style, part, orientation);
        gboolean quadratic=FILL_QUADRATIC_GRADIENT(style, part);
       
        gdk_gc_get_values(style->bg_gc[state_type], &gc_values);
	gdk_gc_set_function(gc, GDK_COPY);
        gdk_gc_set_line_attributes(gc, 1, GDK_LINE_SOLID, gc_values.cap_style, gc_values.join_style);
        
        if (!arc_fill) {
	  #if ROUND_CORNERS
  	  gdk_gc_set_clip_rectangle(gc, NULL);
	  arc_fill = TRUE;
	  clip_mask = round_box_clip_mask(width, height);
	  gdk_gc_set_clip_origin(gc, x, y);	  
          gdk_gc_set_clip_mask(gc, clip_mask);
          #else
	  if (rgn) {
	    arc_fill = TRUE;
	    gdk_gc_set_clip_region(gc, rgn);
	  } else 
	    if (area) gdk_gc_set_clip_rectangle(gc, area);
	  #endif
	} 
	else
          if (arc_fill) {
  	    gdk_gc_set_clip_rectangle(gc, NULL);
            clip_mask = arc_clip_mask(clip_area.width+1, clip_area.height+1);
	    gdk_gc_set_clip_origin(gc, clip_area.x, clip_area.y);	  
            gdk_gc_set_clip_mask(gc, clip_mask);
          }
	  
	if (fill_style == SMOOTH_GRADIENT_FILL) {
          GdkColor color1=FILL_COLOR1(style, part, state_type), color2=FILL_COLOR2(style, part, state_type);

          gdk_draw_gradient(window, gc, style->colormap, area, x, y, width, height, color1, color2, direction, quadratic, arc_fill);
        } else {
          gfloat shade2=FILL_SHADE2_VALUE(style, part), shade1=FILL_SHADE1_VALUE(style, part); 
  
          gdk_draw_shaded_gradient(window, gc, style->colormap, area, x, y, width, height, style->bg[state_type], shade2, shade1, direction, quadratic, arc_fill);
        }
        gdk_gc_set_clip_mask(gc, NULL);
        gdk_gc_set_clip_rectangle(gc, NULL);
        gdk_gc_destroy(gc);
      }
      break;
    default :
      if ((!style->bg_pixmap[state_type]) || (arc_fill) || (rgn)) {
        GdkGC *gc = ((!(OPTION_MOTIF(style))) && (shadow_type!=GTK_SHADOW_NONE))?style->base_gc[state_type]:style->bg_gc[state_type];

        if (area) gdk_gc_set_clip_rectangle(gc, area);
	if (rgn) gdk_gc_set_clip_region(gc, rgn);

        if (!arc_fill) {
         gdk_draw_rectangle(window, gc, TRUE, x, y, width, height); 
	} 
	else 
	{
  	  gdk_draw_arc(window, gc, TRUE, x, y, width, height, 0, 360 * 64);
          gdk_draw_arc(window, gc, FALSE, x, y, width, height, 0, 360 * 64);
        }

        gdk_gc_set_clip_region(gc, NULL);
        gdk_gc_set_clip_rectangle(gc, NULL);
      } else
         gtk_style_apply_default_background(style, window, widget && !GTK_WIDGET_NO_WINDOW(widget),
                                          state_type, area, x, y, width, height);
  }
  if (clip_mask) {
    #if GTK1
    gdk_bitmap_unref(clip_mask);
    #endif
    
    #if GTK2
    g_object_unref(clip_mask);
    #endif
 } 
}


static void
draw_line_shadow_with_gap(GtkStyle * style,
                          GdkWindow * window,
			  GtkStateType state_type,
			  GtkShadowType shadow_type,
			  GdkRectangle * area,
			  GtkWidget * widget,
			  detail_char * detail,
			  smooth_part_style * part,
			  gint x,
			  gint y,
			  gint width,
			  gint height,
			  GtkPositionType gap_side,
			  gint gap_pos,
			  gint gap_size)
{
  GdkGC              *gc1 = NULL;
  GdkGC              *gc2 = NULL;
  GdkGC              *gc3 = NULL;
  GdkGC              *gc4 = NULL;
  GdkGC              *shade = NULL;
  GdkGC              *dark, *light, *mid, *middark, *midlight;
  gboolean 	     line_overlap = FALSE;

  if ((EDGE_LINE_STYLE(style, part)==SMOOTH_LINE_WIN32) && DETAIL("buttondefault")) {
    shade = shaded_color (style, state_type, shades[8]);
    do_draw_shadow_with_gap(window, area, shade, shade, x, y, width, height, gap_side, gap_pos, gap_size, TRUE);
    if (shade) gtk_gc_release (shade);
    return;
  }
  
  if (EDGE_LINE_STYLE(style, part)==SMOOTH_LINE_NONE) return;
  
  if (shadow_type == GTK_SHADOW_NONE) return;

  dark = darktone_gc(style, state_type);
  if (EDGE_LINE_STYLE(style, part)==SMOOTH_LINE_FLAT) {
    gc1 = dark;
    if DETAIL("SMOOTH_DRAW_OPTION")
      do_draw_option_shadow(window, area, gc1, gc1, x, y, width, height);
    else
      do_draw_shadow_with_gap(window, area, gc1, gc1, x, y, width, height, gap_side, gap_pos, gap_size, TRUE);
    if (dark) gtk_gc_release (dark);
    return;
  }   
    
  light = lighttone_gc(style, state_type);
  mid = midtone_gc(style, state_type);

  midlight = midlighttone_gc(style, state_type);
  middark = middarktone_gc(style, state_type);
  
  switch (shadow_type)
    {
    case GTK_SHADOW_ETCHED_IN:
      gc1 = light;
      gc2 = dark;
      if DETAIL("SMOOTH_DRAW_OPTION") {
        do_draw_option_shadow(window, area, gc2, gc1, x, y, width, height);
        do_draw_option_shadow(window, area, gc1, gc2, x+1, y+1, width-2, height-2);
      } else {
        do_draw_shadow_with_gap(window, area, gc2, gc1, x, y, width, height, gap_side, gap_pos+1, gap_size-1, TRUE);
        do_draw_shadow_with_gap(window, area, gc1, gc2, x+1, y+1, width-2, height-2, gap_side, gap_pos, gap_size-2, TRUE);
      }
      break;
    case GTK_SHADOW_ETCHED_OUT:
      gc1 = dark;
      gc2 = light;
      if DETAIL("SMOOTH_DRAW_OPTION") {
        do_draw_option_shadow(window, area, gc2, gc1, x, y, width, height);
        do_draw_option_shadow(window, area, gc1, gc2, x+1, y+1, width-2, height-2);
      } else {
        do_draw_shadow_with_gap(window, area, gc2, gc1, x, y, width, height, gap_side, gap_pos+1, gap_size-1, TRUE);
        do_draw_shadow_with_gap(window, area, gc1, gc2, x+1, y+1, width-2, height-2, gap_side, gap_pos, gap_size-2, TRUE);
      }
      break;
    case GTK_SHADOW_IN:
      if (EDGE_LINE_STYLE(style, part)==SMOOTH_LINE_BEVELED) {
        gc1 = light;
        gc2 = dark;
        if DETAIL("SMOOTH_DRAW_OPTION")
          do_draw_option_bevel(window, area, gc2, gc1, x, y, width, height, EDGE_LINE_THICKNESS(style, part));
        else
	  do_draw_bevel_with_gap(window, area, gc2, gc1, x, y, width, height, EDGE_LINE_THICKNESS(style, part), gap_side, gap_pos, gap_size);
      } else
        if (EDGE_LINE_STYLE(style, part)==SMOOTH_LINE_THIN) {
          gc1 = light;
          gc2 = dark;
          if DETAIL("SMOOTH_DRAW_OPTION")
            do_draw_option_shadow(window, area, gc2, gc1, x, y, width, height);
          else
	    do_draw_shadow_with_gap(window, area, gc2, gc1, x, y, width, height, gap_side, gap_pos, gap_size, TRUE);
      } else
        if ((EDGE_LINE_STYLE(style, part)==SMOOTH_LINE_WIN32) && DETAIL ("button") && (widget) && GTK_WIDGET_HAS_DEFAULT(widget)) {
          do_draw_shadow_with_gap(window, area, dark, dark, x, y, width, height, gap_side, gap_pos, gap_size, TRUE);
      } else {
        switch (EDGE_LINE_STYLE(style, part))
	{
	  case SMOOTH_LINE_SMOOTHED :
            gc1 = middark;
            gc2 = dark;
            gc3 = light;
            gc4 = midlight;
	    line_overlap = FALSE;
            break;
	  case SMOOTH_LINE_COLD :
            if (DETAIL ("button") || DETAIL ("togglebutton") || DETAIL ("optionmenu") || 
	        DETAIL ("slider") || DETAIL ("vscrollbar") || DETAIL ("hscrollbar"))
	    { 
              shade = shaded_color (style, state_type, shades[6]);
              gc2 = mid;
              gc4 = light;
	    } else {
              shade = shaded_color (style, state_type, shades[5]);
              gc2 = style->bg_gc[state_type];
              gc4 = style->bg_gc[state_type];
            }
            gc1 = shade;
            gc3 = shade;
	    line_overlap = FALSE;
            break;
	  case SMOOTH_LINE_WIN32 :
            shade = shaded_color (style, state_type, shades[8]);
            gc1 = dark;
            gc2 = shade;
            gc3 = light;
            gc4 = style->bg_gc[state_type];
	    line_overlap = TRUE;
            break;
          default :
            gc1 = dark;
            gc2 = style->black_gc;
            gc3 = light;
            gc4 = mid;
	    line_overlap = FALSE;
	    break;
	} 
        if DETAIL("SMOOTH_DRAW_OPTION") {
          do_draw_option_shadow(window, area, gc1, gc3, x, y, width, height);
          do_draw_option_shadow(window, area, gc2, gc4, x+1, y+1, width-2, height-2);
        } else {
          do_draw_shadow_with_gap(window, area, gc1, gc3, x, y, width, height, gap_side, gap_pos+1, gap_size-1, line_overlap);
          do_draw_shadow_with_gap(window, area, gc2, gc4, x+1, y+1, width-2, height-2, gap_side, gap_pos, gap_size, line_overlap);
	}  
      } 	
      break;
    case GTK_SHADOW_OUT:
      if (EDGE_LINE_STYLE(style, part)==SMOOTH_LINE_BEVELED) {
        gc1 = dark;
        gc2 = light;
        if DETAIL("SMOOTH_DRAW_OPTION")
          do_draw_option_bevel(window, area, gc2, gc1, x, y, width, height, EDGE_LINE_THICKNESS(style, part));
        else
          do_draw_bevel_with_gap(window, area, gc2, gc1, x, y, width, height, EDGE_LINE_THICKNESS(style, part), gap_side, gap_pos, gap_size);
      } else
        if (EDGE_LINE_STYLE(style, part)==SMOOTH_LINE_THIN) {
          gc1 = dark;
          gc2 = light;
          if DETAIL("SMOOTH_DRAW_OPTION")
            do_draw_option_shadow(window, area, gc2, gc1, x, y, width, height);
          else
            do_draw_shadow_with_gap(window, area, gc2, gc1, x, y, width, height, gap_side, gap_pos, gap_size, TRUE);
      } else {
        switch (EDGE_LINE_STYLE(style, part)) 
	{
	  case SMOOTH_LINE_SMOOTHED :
            gc1 = mid;
            gc2 = light;
            gc3 = dark;
            gc4 = mid;
	    line_overlap = TRUE;
            break;
	  case SMOOTH_LINE_SMOOTHBEVEL :
            gc1 = midlight;
            gc2 = light;
            gc3 = dark;
            gc4 = middark;
	    line_overlap = TRUE;
            break;
	  case SMOOTH_LINE_COLD :
            shade = shaded_color (style, state_type, shades[6]);
            gc1 = shade;
            gc2 = light;
            gc3 = shade;
            gc4 = mid;
	    line_overlap = TRUE;
            break;
	  case SMOOTH_LINE_WIN32 :
            shade = shaded_color (style, state_type, shades[8]);
            gc1 = light;
            gc2 = style->bg_gc[state_type];
            gc3 = shade;
            gc4 = dark;
	    line_overlap = FALSE;
            break;
          default :
            gc1 = mid;
            gc2 = light;
            gc3 = style->black_gc;
            gc4 = dark;
	    line_overlap = TRUE;
	    break;
	} 
        if DETAIL("SMOOTH_DRAW_OPTION") {
          do_draw_option_shadow(window, area, gc1, gc3, x, y, width, height);
          do_draw_option_shadow(window, area, gc2, gc4, x+1, y+1, width-2, height-2);
        } else {
          do_draw_shadow_with_gap(window, area, gc1, gc3, x, y, width, height, gap_side, gap_pos+1, gap_size-1, line_overlap);
          do_draw_shadow_with_gap(window, area, gc2, gc4, x+1, y+1, width-2, height-2, gap_side, gap_pos+1, gap_size-1, line_overlap);
	}  
      } 	
      break;
    }
  if (shade) {
    gtk_gc_release (shade);
  }  
  if (dark) gtk_gc_release (dark);
  if (mid) gtk_gc_release (mid);
  if (light) gtk_gc_release (light);
  if (middark) gtk_gc_release (middark);
  if (midlight) gtk_gc_release (midlight);
}

static void 
draw_grip(GtkStyle * style,
          GdkWindow * window,
          GtkStateType state_type,
	  GdkRectangle * area,
	  gint x,
	  gint y,
	  gint width,
	  gint height,
	  GtkOrientation orientation)
{
  gint	x2, y2;
  GdkGC * light_gc, * dark_gc, * mid_gc;
  GdkGC              *dark, *light, *mid;
  GdkRectangle dest;
  smooth_grip_style * grip = GRIP_PART(style);
  
  dark = darktone_gc(style, state_type);
  light = lighttone_gc(style, state_type);
  mid = midtone_gc(style, state_type);

  dest.x = x + EDGE_LINE_THICKNESS(style, grip);
  dest.y = y + EDGE_LINE_THICKNESS(style, grip);
  dest.width = width - 2*EDGE_LINE_THICKNESS(style, grip);
  dest.height = height - 2*EDGE_LINE_THICKNESS(style, grip);

  if (LINE_STYLE(style, grip) == SMOOTH_LINE_NONE) return;
  if (LINE_STYLE(style, grip) == SMOOTH_LINE_FLAT){
    light_gc=style->fg_gc[state_type];
    dark_gc=style->bg_gc[state_type];
  } else {
    light_gc=light;
    dark_gc=dark;
  } 

  switch PART_STYLE(grip)
  {
    case NO_GRIP:
      break;
    case BARS_IN_GRIP :
    case BARS_OUT_GRIP :
       dest.x = x + 2;
       dest.y = y + 2;
       dest.width = width - 4;
       dest.height = height - 4;

      do_draw_lines(window, &dest, light, dark, mid, x, y, width, height, orientation, (PART_STYLE(grip)==BARS_IN_GRIP));
      break; 
    case LINES_IN_GRIP :
    case LINES_OUT_GRIP :
      do_draw_lines(window, &dest, light, dark, mid, x, y, width, height, orientation, (PART_STYLE(grip)==LINES_IN_GRIP));
      break; 
    case FIXEDLINES_IN_GRIP :
    case FIXEDLINES_OUT_GRIP :
      do_draw_fixed_midlines(window, &dest, light_gc, dark_gc, x, y, width, height, orientation, GRIP_COUNT(style), GRIP_SPACING(style), (PART_STYLE(grip)==FIXEDLINES_OUT_GRIP), FALSE, FALSE);
      break; 
    case SLASHES_GRIP :
      x = dest.x;
      y = dest.y;
      width = dest.width;
      height = dest.height;
      do_draw_fixed_midlines(window, &dest, light_gc, dark_gc, x, y, width, height, orientation, GRIP_COUNT(style), GRIP_SPACING(style), FALSE, TRUE, FALSE);
      break; 
    case DOTS_IN_GRIP :
    case DOTS_OUT_GRIP :
    case SMALLDOTS_IN_GRIP :
    case SMALLDOTS_OUT_GRIP :
      {
        gboolean small = ((PART_STYLE(grip) == SMALLDOTS_IN_GRIP) || (PART_STYLE(grip) == SMALLDOTS_OUT_GRIP));
	if (LINE_STYLE(style, grip) == SMOOTH_LINE_FLAT){
          dark_gc=style->fg_gc[state_type];
        } else {
          if ((PART_STYLE(grip) == DOTS_IN_GRIP) || (PART_STYLE(grip) == SMALLDOTS_IN_GRIP)) {
            light_gc=style->dark_gc[state_type];
            dark_gc=style->light_gc[state_type];
          } else {
            if (orientation == GTK_ORIENTATION_HORIZONTAL)
	      y -= 1;
            else
  	      x -= 1;
          }      
        } 
        do_draw_fixed_dots(window, &dest, light_gc, dark_gc, mid, x, y, width, height, orientation, GRIP_COUNT(style), GRIP_SPACING(style), small);
      }
      break; 
    case MAC_BUDS_IN_GRIP :
    case MAC_BUDS_OUT_GRIP : 
    case NS_BUDS_IN_GRIP :
    case NS_BUDS_OUT_GRIP : 
      {
        gboolean in = ((PART_STYLE(grip) == MAC_BUDS_IN_GRIP) || (PART_STYLE(grip) == NS_BUDS_IN_GRIP));
        gboolean ns = ((PART_STYLE(grip) == NS_BUDS_OUT_GRIP) || (PART_STYLE(grip) == NS_BUDS_IN_GRIP));
       
        if (!in) {
          light_gc = style->white_gc;
          mid_gc = mid;
        } else {
          light_gc = dark;
          mid_gc = mid;
          dark_gc = light;
        }
   
        do_draw_buds(window, area, light_gc, dark_gc, mid_gc, x, y, width, height, orientation, ns);
      }
      break; 
    default:
      break; 
  }

  if (dark) gtk_gc_release (dark);
  if (light) gtk_gc_release (light);
  if (mid) gtk_gc_release (mid);
}

static void
draw_hline(GtkStyle * style,
	   GdkWindow * window,
	   GtkStateType state_type,
	   GdkRectangle * area,
	   GtkWidget * widget,
	   detail_char * detail,
	   gint x1,
	   gint x2,
	   gint y)
{
  gint                thickness_light;
  gint                thickness_dark;
  gint                i;
  GdkGC * gc1, * gc2;
  
  g_return_if_fail(sanitize_parameters(style, window, NULL, NULL));

  thickness_light = ythickness(style) / 2;
  thickness_dark = ythickness(style) - thickness_light;

  if (LINE_STYLE(style,NULL) == SMOOTH_LINE_NONE) return;
  if (LINE_STYLE(style,NULL) == SMOOTH_LINE_FLAT) 
  {
    gc1 = style->fg_gc[state_type];
    gc2 = style->bg_gc[state_type];
  } else {
    gc1 = style->light_gc[state_type];
    gc2 = style->dark_gc[state_type];
  }

  if (area)
  {
    gdk_gc_set_clip_rectangle(gc1, area);
    gdk_gc_set_clip_rectangle(gc2, area);
  }
 
  for (i = 0; i < thickness_dark; i++)
  {
    gdk_draw_line(window, gc1, x2 - i, y + i, x2, y + i);
    gdk_draw_line(window, gc2, x1, y + i, x2 - i, y + i);
  }

  y += thickness_dark;
  for (i = 0; i < thickness_light; i++)
  {
    gdk_draw_line(window, gc2, x1, y + i, x1 + thickness_light - i - 1, y + i);
    gdk_draw_line(window, gc1, x1 + thickness_light - i - 1, y + i, x2, y + i);
  }

  if (area)
  {
    gdk_gc_set_clip_rectangle(gc1, NULL);
    gdk_gc_set_clip_rectangle(gc2, NULL);
  }
}

static void
draw_vline(GtkStyle * style,
	   GdkWindow * window,
	   GtkStateType state_type,
	   GdkRectangle * area,
	   GtkWidget * widget,
	   detail_char * detail,
	   gint y1,
	   gint y2,
	   gint x)
{
  gint                thickness_light;
  gint                thickness_dark;
  gint                i;
  GdkGC * gc1, * gc2;

  g_return_if_fail(sanitize_parameters(style, window, NULL, NULL));

  thickness_light = xthickness(style) / 2;
  thickness_dark = xthickness(style) - thickness_light;

  if (LINE_STYLE(style,NULL) == SMOOTH_LINE_NONE) return;
  if (LINE_STYLE(style,NULL) == SMOOTH_LINE_FLAT) 
  {
    gc1 = style->fg_gc[state_type];
    gc2 = style->bg_gc[state_type];
  } else {
    gc1 = style->light_gc[state_type];
    gc2 = style->dark_gc[state_type];
  }
  
  if (area)
  {
    gdk_gc_set_clip_rectangle(gc1, area);
    gdk_gc_set_clip_rectangle(gc2, area);
  }
  
  for (i = 0; i < thickness_dark; i++)
  {
    gdk_draw_line(window, gc1, x + i, y2 - i, x + i, y2);
    gdk_draw_line(window, gc2, x + i, y1, x + i, y2 - i);
  }

  x += thickness_dark;
  for (i = 0; i < thickness_light; i++)
  {
    gdk_draw_line(window, gc2, x + i, y1, x + i, y1 + thickness_light - i - 1);
    gdk_draw_line(window, gc1, x + i, y1 + thickness_light - i - 1, x + i, y2);
  }
  if (area)
  {
    gdk_gc_set_clip_rectangle(gc1, NULL);
    gdk_gc_set_clip_rectangle(gc2, NULL);
  }
}

static void
draw_shadow(GtkStyle * style,
	    GdkWindow * window,
	    GtkStateType state_type,
	    GtkShadowType shadow_type,
	    GdkRectangle * area,
	    GtkWidget * widget,
	    detail_char * detail,
	    gint x,
	    gint y,
	    gint width,
	    gint height)
{
  g_return_if_fail(sanitize_parameters(style, window, &width, &height));

  #if ROUND_CORNERS
    draw_round_shadow(style, window, state_type, shadow_type, area, widget, detail, x, y, width, height);
  #else
    draw_line_shadow_with_gap(style, window, state_type, shadow_type, area, widget, detail, NULL, x, y, width, height, 0, 0, 0);
  #endif  
}

static void
draw_polygon(GtkStyle * style,
	     GdkWindow * window,
	     GtkStateType state_type,
	     GtkShadowType shadow_type,
	     GdkRectangle * area,
	     GtkWidget * widget,
	     detail_char * detail,
	     GdkPoint * points,
	     gint npoints,
	     gint fill)
{
  static const gdouble pi_over_4 = M_PI_4;
  static const gdouble pi_3_over_4 = M_PI_4 * 3;

  GdkGC              *gc1;
  GdkGC              *gc2;
  GdkGC              *gc3;
  GdkGC              *gc4;
  gdouble             angle;
  gint                xadjust;
  gint                yadjust;
  gint                i;

  g_return_if_fail(sanitize_parameters(style, window, NULL, NULL));
  g_return_if_fail(points != NULL);

  switch (shadow_type)
    {
    case GTK_SHADOW_IN:
      gc1 = style->light_gc[state_type];
      gc2 = style->dark_gc[state_type];
      gc3 = style->light_gc[state_type];
      gc4 = style->dark_gc[state_type];
      break;
    case GTK_SHADOW_ETCHED_IN:
      gc1 = style->light_gc[state_type];
      gc2 = style->dark_gc[state_type];
      gc3 = style->dark_gc[state_type];
      gc4 = style->light_gc[state_type];
      break;
    case GTK_SHADOW_OUT:
      gc1 = style->dark_gc[state_type];
      gc2 = style->light_gc[state_type];
      gc3 = style->dark_gc[state_type];
      gc4 = style->light_gc[state_type];
      break;
    case GTK_SHADOW_ETCHED_OUT:
      gc1 = style->dark_gc[state_type];
      gc2 = style->light_gc[state_type];
      gc3 = style->light_gc[state_type];
      gc4 = style->dark_gc[state_type];
      break;
    default:
      return;
    }

  if (area)
    {
      gdk_gc_set_clip_rectangle(gc1, area);
      gdk_gc_set_clip_rectangle(gc2, area);
      gdk_gc_set_clip_rectangle(gc3, area);
      gdk_gc_set_clip_rectangle(gc4, area);
    }

  if (fill)
    gdk_draw_polygon(window, style->bg_gc[state_type], TRUE, points, npoints);

  npoints--;

  for (i = 0; i < npoints; i++)
    {
      if ((points[i].x == points[i + 1].x) &&
	  (points[i].y == points[i + 1].y))
	{
	  angle = 0;
	}
      else
	{
	  angle = atan2(points[i + 1].y - points[i].y,
			points[i + 1].x - points[i].x);
	}

      if ((angle > -pi_3_over_4) && (angle < pi_over_4))
	{
	  if (angle > -pi_over_4)
	    {
	      xadjust = 0;
	      yadjust = 1;
	    }
	  else
	    {
	      xadjust = 1;
	      yadjust = 0;
	    }

	  gdk_draw_line(window, gc1,
			points[i].x - xadjust, points[i].y - yadjust,
			points[i + 1].x - xadjust, points[i + 1].y - yadjust);
	  gdk_draw_line(window, gc3,
			points[i].x, points[i].y,
			points[i + 1].x, points[i + 1].y);
	}
      else
	{
	  if ((angle < -pi_3_over_4) || (angle > pi_3_over_4))
	    {
	      xadjust = 0;
	      yadjust = 1;
	    }
	  else
	    {
	      xadjust = 1;
	      yadjust = 0;
	    }

	  gdk_draw_line(window, gc4,
			points[i].x + xadjust, points[i].y + yadjust,
			points[i + 1].x + xadjust, points[i + 1].y + yadjust);
	  gdk_draw_line(window, gc2,
			points[i].x, points[i].y,
			points[i + 1].x, points[i + 1].y);
	}
    }
  if (area)
    {
      gdk_gc_set_clip_rectangle(gc1, NULL);
      gdk_gc_set_clip_rectangle(gc2, NULL);
      gdk_gc_set_clip_rectangle(gc3, NULL);
      gdk_gc_set_clip_rectangle(gc4, NULL);
    }
}

static void
draw_arrow(GtkStyle * style,
	   GdkWindow * window,
	   GtkStateType state_type,
	   GtkShadowType shadow_type,
	   GdkRectangle * area,
	   GtkWidget * widget,
	   detail_char * detail,
	   GtkArrowType arrow_type,
	   gint fill,
	   gint x,
	   gint y,
	   gint width,
	   gint height)
{
  gint alternate;
  
  g_return_if_fail(sanitize_parameters(style, window, &width, &height));
  
  #if GTK1 /* GTK2 does this automatically */
    if (DETAIL ("hscrollbar") || DETAIL ("vscrollbar") || 
        DETAIL("spinbutton_up") || DETAIL("spinbutton_down"))
    {	 
      gtk_paint_box(style, window, state_type, shadow_type, area, widget, detail, x, y, width, height);
    }  
  #endif
  
  reverse_engineer_arrow_box (widget, detail, arrow_type, &x, &y, &width, &height);
  
  alternate = ARROW_STYLE(style);
  
  x+=ARROW_XPADDING(style); 
  y+=ARROW_YPADDING(style); 
  width-=2*ARROW_XPADDING(style); 
  height-=2*ARROW_YPADDING(style);
  
  if (ETCHED_ARROW(style)) {
    do_draw_arrow(window, area, arrow_type, style->light_gc[state_type], style->light_gc[state_type], x+1, y+1, width, height, alternate);
    do_draw_arrow(window, area, arrow_type, style->dark_gc[state_type], style->dark_gc[state_type], x, y, width, height, alternate);
  } else  {   
    gboolean solid = SOLID_ARROW(style);
    GdkGC * fill_gc = style->fg_gc[state_type];

    if (!solid)
      fill_gc = style->base_gc[state_type];

    do_draw_arrow(window, area, arrow_type, fill_gc, style->fg_gc[state_type], x, y, width, height, alternate); 
  }
}

static void
draw_diamond(GtkStyle * style,
	     GdkWindow * window,
	     GtkStateType state_type,
	     GtkShadowType shadow_type,
	     GdkRectangle * area,
	     GtkWidget * widget,
	     detail_char * detail,
	     gint x,
	     gint y,
	     gint width,
	     gint height)
{
  gint                half_width;
  gint                half_height;

  g_return_if_fail(sanitize_parameters(style, window, &width, &height));

  half_width = width / 2;
  half_height = height / 2;

  if (area)
    {
      gdk_gc_set_clip_rectangle(style->light_gc[state_type], area);
      gdk_gc_set_clip_rectangle(style->bg_gc[state_type], area);
      gdk_gc_set_clip_rectangle(style->dark_gc[state_type], area);
      gdk_gc_set_clip_rectangle(style->black_gc, area);
    }
  switch (shadow_type)
    {
    case GTK_SHADOW_IN:
      gdk_draw_line(window, style->light_gc[state_type],
		    x + 2, y + half_height,
		    x + half_width, y + height - 2);
      gdk_draw_line(window, style->light_gc[state_type],
		    x + half_width, y + height - 2,
		    x + width - 2, y + half_height);
      gdk_draw_line(window, style->light_gc[state_type],
		    x + 1, y + half_height,
		    x + half_width, y + height - 1);
      gdk_draw_line(window, style->light_gc[state_type],
		    x + half_width, y + height - 1,
		    x + width - 1, y + half_height);
      gdk_draw_line(window, style->light_gc[state_type],
		    x, y + half_height,
		    x + half_width, y + height);
      gdk_draw_line(window, style->light_gc[state_type],
		    x + half_width, y + height,
		    x + width, y + half_height);

      gdk_draw_line(window, style->dark_gc[state_type],
		    x + 2, y + half_height,
		    x + half_width, y + 2);
      gdk_draw_line(window, style->dark_gc[state_type],
		    x + half_width, y + 2,
		    x + width - 2, y + half_height);
      gdk_draw_line(window, style->dark_gc[state_type],
		    x + 1, y + half_height,
		    x + half_width, y + 1);
      gdk_draw_line(window, style->dark_gc[state_type],
		    x + half_width, y + 1,
		    x + width - 1, y + half_height);
      gdk_draw_line(window, style->dark_gc[state_type],
		    x, y + half_height,
		    x + half_width, y);
      gdk_draw_line(window, style->dark_gc[state_type],
		    x + half_width, y,
		    x + width, y + half_height);
      break;
    case GTK_SHADOW_OUT:
      gdk_draw_line(window, style->dark_gc[state_type],
		    x + 2, y + half_height,
		    x + half_width, y + height - 2);
      gdk_draw_line(window, style->dark_gc[state_type],
		    x + half_width, y + height - 2,
		    x + width - 2, y + half_height);
      gdk_draw_line(window, style->dark_gc[state_type],
		    x + 1, y + half_height,
		    x + half_width, y + height - 1);
      gdk_draw_line(window, style->dark_gc[state_type],
		    x + half_width, y + height - 1,
		    x + width - 1, y + half_height);
      gdk_draw_line(window, style->dark_gc[state_type],
		    x, y + half_height,
		    x + half_width, y + height);
      gdk_draw_line(window, style->dark_gc[state_type],
		    x + half_width, y + height,
		    x + width, y + half_height);

      gdk_draw_line(window, style->light_gc[state_type],
		    x + 2, y + half_height,
		    x + half_width, y + 2);
      gdk_draw_line(window, style->light_gc[state_type],
		    x + half_width, y + 2,
		    x + width - 2, y + half_height);
      gdk_draw_line(window, style->light_gc[state_type],
		    x + 1, y + half_height,
		    x + half_width, y + 1);
      gdk_draw_line(window, style->light_gc[state_type],
		    x + half_width, y + 1,
		    x + width - 1, y + half_height);
      gdk_draw_line(window, style->light_gc[state_type],
		    x, y + half_height,
		    x + half_width, y);
      gdk_draw_line(window, style->light_gc[state_type],
		    x + half_width, y,
		    x + width, y + half_height);
      break;
    default:
      break;
    }
  if (area)
    {
      gdk_gc_set_clip_rectangle(style->light_gc[state_type], NULL);
      gdk_gc_set_clip_rectangle(style->bg_gc[state_type], NULL);
      gdk_gc_set_clip_rectangle(style->dark_gc[state_type], NULL);
      gdk_gc_set_clip_rectangle(style->black_gc, NULL);
    }
}

static void
draw_oval(GtkStyle * style,
	  GdkWindow * window,
	  GtkStateType state_type,
	  GtkShadowType shadow_type,
	  GdkRectangle * area,
	  GtkWidget * widget,
	  detail_char * detail,
	  gint x,
	  gint y,
	  gint width,
	  gint height)
{
  g_return_if_fail(style != NULL);
  g_return_if_fail(window != NULL);
}

static void
draw_box(GtkStyle * style,
	 GdkWindow * window,
	 GtkStateType state_type,
	 GtkShadowType shadow_type,
	 GdkRectangle * area,
	 GtkWidget * widget,
	 detail_char * detail,
	 gint x,
	 gint y,
	 gint width,
	 gint height)
{
  GtkOrientation      orientation;
  
  g_return_if_fail(sanitize_parameters(style, window, &width, &height));

  orientation = GTK_ORIENTATION_HORIZONTAL;
  if (height > width)
    orientation = GTK_ORIENTATION_VERTICAL;

#ifdef DEBUG
     printf("%p %s %i %i state_type = %d (%d)\n", detail, detail, width, height, state_type, orientation);
#endif

  #if GTK1
    if (GTK_IS_PANED(widget)) {
      gint mouse_x, mouse_y;
          		
      gdk_window_get_pointer (window, &mouse_x, &mouse_y, NULL);
      
      if ((PANED_HANDLE_SIZE(style) > 2) && (GTK_PANED(widget)->handle_size != PANED_HANDLE_SIZE(style))) {
        gtk_paned_set_gutter_size(GTK_PANED(widget), PANED_HANDLE_SIZE(style));
        gtk_paned_set_handle_size(GTK_PANED(widget), PANED_HANDLE_SIZE(style));
      }	else {
        if GTK_IS_VPANED(widget) {
          orientation = GTK_ORIENTATION_HORIZONTAL;
	  y -= 3;
	  height += 6;
        } else {
          orientation = GTK_ORIENTATION_VERTICAL;
	  x -= 3;
	  width += 6;
        }
      	/*
        if (mouse_x >= x && mouse_x < x + width && mouse_y >= y && mouse_y < y + height)
          state_type = GTK_STATE_PRELIGHT;
         */
        gtk_paint_handle(style, window, state_type, GTK_SHADOW_NONE, area, widget, detail, x, y, width, height, orientation);    
      }	
    } else 
  #endif
    if (DETAIL("buttondefault")) {
        gradient_fill_background(style, window, state_type, area, widget, NULL, x, y, width, height, shadow_type == GTK_SHADOW_IN, GTK_ORIENTATION_HORIZONTAL);
        gtk_paint_shadow(style, window, state_type, shadow_type, area, widget,
                detail, x, y, width, height);
    } else if (DETAIL("togglebutton")) {
        gradient_fill_background(style, window, state_type, area, widget, NULL, x, y, width, height, shadow_type == GTK_SHADOW_IN, GTK_ORIENTATION_HORIZONTAL);
        gtk_paint_shadow(style, window, state_type, shadow_type, area, widget,
                detail, x, y, width, height);
    } else if (DETAIL("button")) {
	gradient_fill_background(style, window, state_type, area, widget, NULL, x, y, width, height, shadow_type == GTK_SHADOW_IN, GTK_ORIENTATION_HORIZONTAL);

        /* Paint a triangle here instead of in "buttondefault"
           which is drawn _behind_ the current button */
        draw_default_triangle(style, window, state_type, shadow_type, area, widget, detail, x, y, width, height);

        gtk_paint_shadow(style, window, state_type, shadow_type, area, widget,
                detail, x, y, width, height);
    } else if (DETAIL("handlebox_bin")) {
        FLAT_FILL_BACKGROUND(style, window, state_type, area, widget, NULL, x, y, width, height);
    } else if (DETAIL ("hscrollbar") || DETAIL ("vscrollbar"))
    {
      orientation = (GTK_IS_VSCROLLBAR(widget))?GTK_ORIENTATION_VERTICAL:GTK_ORIENTATION_HORIZONTAL;
      
      gradient_fill_background(style, window, state_type, area, widget, NULL, x, y, width, height, shadow_type == GTK_SHADOW_IN, orientation);
     
      gtk_paint_shadow(style, window, state_type, shadow_type, area, widget,
               detail, x, y, width, height);
    } else if (DETAIL("menubar")) {
        gint thick = 0;
	gboolean toolbar_overlap = (GRIP_OVERLAP_TOOLBAR(style) && IS_BONOBO_DOCK_ITEM(widget));
	if (toolbar_overlap)
	  thick = EDGE_LINE_THICKNESS(style, NULL);
 
        gradient_fill_background(style, window, state_type, area, widget, NULL, -thick, y, x+width+thick, height, TRUE, GTK_ORIENTATION_HORIZONTAL);
	if (toolbar_overlap)
          draw_line_shadow_with_gap(style, window, state_type, shadow_type, area, widget, detail, NULL, x-thick, y, x+width+thick, height, GTK_POS_LEFT, 0, height);
        else
	  gtk_paint_shadow(style, window, state_type, shadow_type, area, widget,detail, x, y, width, height);
    } else if (DETAIL("toolbar")) {
	gboolean toolbar_overlap = (GRIP_OVERLAP_TOOLBAR(style) && (IS_BONOBO_DOCK_ITEM(widget)));

        gboolean horiz=(orientation==GTK_ORIENTATION_HORIZONTAL);
	gboolean vert=(!horiz);
	gint hthick = 0, vthick = 0;
	
	if (toolbar_overlap) {
	  if (horiz)
	    hthick = EDGE_LINE_THICKNESS(style, NULL);
	  else
	    vthick = EDGE_LINE_THICKNESS(style, NULL);  
        }

        FLAT_FILL_BACKGROUND(style, window, state_type, area, widget, NULL, x, y, width, height);
	  
	gradient_fill_background(style, window, state_type, area, widget, NULL, x-hthick, y-vthick, width+hthick, height+vthick, TRUE, orientation);
	if (toolbar_overlap)
          draw_line_shadow_with_gap(style, window, state_type, shadow_type, area, widget, detail, NULL, x-hthick, y-vthick, width+hthick, height+vthick, horiz?GTK_POS_LEFT:GTK_POS_TOP, 0, vert?width:height);
        else
          gtk_paint_shadow(style, window, state_type, shadow_type, area, widget,detail, x-hthick, y-vthick, width+hthick, height+vthick);
    } else if (DETAIL("menuitem")) {
	if ((shadow_type == GTK_SHADOW_NONE) && (EDGE_LINE_STYLE(style, NULL) != SMOOTH_LINE_NONE))
	  shadow_type = GTK_SHADOW_OUT;
	gradient_fill_background(style, window, state_type, area, widget, NULL, x, y, width, height, shadow_type == GTK_SHADOW_IN, GTK_ORIENTATION_HORIZONTAL);
        gtk_paint_shadow(style, window, state_type, shadow_type, area, widget,detail, x, y, width, height);
    } else if (DETAIL("optionmenutab")) {
        gradient_fill_background(style, window, state_type, area, widget, NULL, x, y, width, height, shadow_type == GTK_SHADOW_IN, GTK_ORIENTATION_HORIZONTAL);
        gtk_paint_shadow(style, window, state_type, shadow_type, area, widget,detail, x, y, width, height);	
    } else if (DETAIL("slider")) {
        orientation = (GTK_IS_VSCROLLBAR(widget))?GTK_ORIENTATION_VERTICAL:GTK_ORIENTATION_HORIZONTAL;

	gradient_fill_background(style, window, state_type, area, widget, NULL, x, y, width, height, shadow_type == GTK_SHADOW_IN, orientation);
        gtk_paint_shadow(style, window, state_type, shadow_type, area, widget,
          detail, x, y, width, height);
        draw_slider_grip(style, window, state_type, shadow_type, area, widget, detail, x, y, width, height, orientation);
    } else if (DETAIL("trough")) {
        if (GTK_IS_SCALE (widget) && REAL_SLIDERS(style)) {
          FLAT_FILL_BACKGROUND(style, window, GTK_STATE_NORMAL, area, widget, NULL, x, y, width, height);
          if GTK_IS_HSCALE (widget) {
	    draw_hline (style, window, state_type, area, widget, detail,
	   	        x, x + width, y + (height / 2));
          } else {
	    draw_vline (style, window, state_type, area, widget, detail,
		        y, y + height, x + (width / 2));
          }
        } else {
  	  smooth_part_style * trough = THEME_PART(TROUGH_PART(style));
	  if (GTK_IS_PROGRESS_BAR(widget)) {
  	    switch (GTK_PROGRESS_BAR(widget)->orientation) {
	      case GTK_PROGRESS_LEFT_TO_RIGHT:
              case GTK_PROGRESS_RIGHT_TO_LEFT:
                orientation = GTK_ORIENTATION_HORIZONTAL;
	        break;
	      case GTK_PROGRESS_BOTTOM_TO_TOP:
              case GTK_PROGRESS_TOP_TO_BOTTOM:
                orientation = GTK_ORIENTATION_VERTICAL;
                break;
	    }
	  } else {
  	    if (GTK_IS_SCROLLBAR(widget))
             orientation = (GTK_IS_VSCROLLBAR(widget))?GTK_ORIENTATION_VERTICAL:GTK_ORIENTATION_HORIZONTAL;
	  }    
	  gradient_fill_background(style, window, state_type, area, widget, trough, 
	                           x+PART_XPADDING(trough), y+PART_YPADDING(trough), 
	                           width-PART_XPADDING(trough)*2, height-PART_YPADDING(trough)*2, 
	                           shadow_type == GTK_SHADOW_IN, orientation);

          if (GTK_IS_SCALE(widget) && TROUGH_SHOW_VALUE(style)) {	    
	    GtkAdjustment * adjustment = gtk_range_get_adjustment(GTK_RANGE(widget));
	    gfloat value = 0;
            #if GTK1
              value = adjustment->value;
	    #endif
  
            #if GTK2
              value = gtk_range_get_value(GTK_RANGE(widget));
            #endif
	    
	    if (orientation == GTK_ORIENTATION_HORIZONTAL) {
              gint w=0;           
              
	      w = (width-PART_XPADDING(trough)*2)*((value- adjustment->lower) / (adjustment->upper - adjustment->lower));
	      w = MAX (2, w);
	      w = MIN(w, width-PART_XPADDING(trough)*2);              
              
	      gradient_fill_background(style, window, GTK_STATE_SELECTED, area, widget, trough, 
	                               x+PART_XPADDING(trough), y+PART_YPADDING(trough), 
	                               w, height-PART_YPADDING(trough)*2, 
	                               shadow_type == GTK_SHADOW_IN, orientation);
            } else {
              gint h;           
              
	      h = (height-PART_YPADDING(trough)*2)*(1-(value - adjustment->lower) / (adjustment->upper - adjustment->lower));
              h = MAX (2, h);
              h = MIN(h, height-PART_YPADDING(trough)*2);
	      
              gradient_fill_background(style, window, GTK_STATE_SELECTED, area, widget, trough, 
	                               x+PART_XPADDING(trough), y+height-PART_YPADDING(trough)-h, 
	                               width-PART_XPADDING(trough)*2, h,
	                               shadow_type == GTK_SHADOW_IN, orientation);
            }
          }
	  
          draw_line_shadow_with_gap(style, window, GTK_STATE_NORMAL, shadow_type, area, widget, detail,
	                            trough, x+PART_XPADDING(trough), y+PART_YPADDING(trough), 
	                            width-PART_XPADDING(trough)*2, height-PART_YPADDING(trough)*2, 
				    0, 0, 0);
      }
    } else if (DETAIL("bar")) {
      if (GTK_IS_PROGRESS_BAR(widget)) {
 	smooth_part_style * progress = PROGRESS_PART(style);
 	switch (GTK_PROGRESS_BAR(widget)->orientation) {
	  case GTK_PROGRESS_LEFT_TO_RIGHT:
          case GTK_PROGRESS_RIGHT_TO_LEFT:
            orientation = GTK_ORIENTATION_HORIZONTAL;
	    break;
	  case GTK_PROGRESS_BOTTOM_TO_TOP:
          case GTK_PROGRESS_TOP_TO_BOTTOM:
            orientation = GTK_ORIENTATION_VERTICAL;
            break;
        }
        gradient_fill_background(style, window, state_type, area, widget, progress, 
	                         x+PART_XPADDING(progress), y+PART_YPADDING(progress), 
	                         width-PART_XPADDING(progress)*2, height-PART_YPADDING(progress)*2, 
	                         shadow_type == GTK_SHADOW_IN, orientation);
        draw_line_shadow_with_gap(style, window, state_type, shadow_type, area, widget, detail,
                                  progress, x+PART_XPADDING(progress), y+PART_YPADDING(progress), 
	                          width-PART_XPADDING(progress)*2, height-PART_YPADDING(progress)*2, 
	    		          0, 0, 0);
      } else {
         gradient_fill_background(style, window, state_type, area, widget, NULL, x, y, width, height, shadow_type == GTK_SHADOW_IN, orientation);
         gtk_paint_shadow(style, window, state_type, shadow_type, area, widget,
               detail, x, y, width, height);
      }
    } else if (DETAIL("hruler") || DETAIL("vruler")) {
        orientation = (GTK_IS_VRULER(widget))?GTK_ORIENTATION_VERTICAL:GTK_ORIENTATION_HORIZONTAL;
        gradient_fill_background(style, window, state_type, area, widget, NULL, x, y, width, height, shadow_type == GTK_SHADOW_IN, orientation);
        gtk_paint_shadow(style, window, state_type, shadow_type, area, widget,
          detail, x, y, width, height);
    } else if (DETAIL("spinbutton_up") || DETAIL("spinbutton_down")) {
      gradient_fill_background(style, window, state_type, area, widget, NULL, x, y, width, height, shadow_type == GTK_SHADOW_IN, GTK_ORIENTATION_HORIZONTAL);
      gtk_paint_shadow(style, window, state_type, shadow_type, area, widget,
                       detail, x, y, width, height);
    } else if (DETAIL("optionmenu")) {
        gradient_fill_background(style, window, state_type, area, widget, NULL, x, y, width, height, shadow_type == GTK_SHADOW_IN, orientation);
        gtk_paint_shadow(style, window, state_type, shadow_type, area, widget,detail, x, y, width, height);
        draw_vline (style, window, state_type,
		area, widget, detail,
		y + ythickness(style) + 1,
		y + height - ythickness(style) - 2,
		x + width - 19 - xthickness(style));
    } else if (DETAIL("metacity")) {
        gradient_fill_background(style, window, state_type, area, widget, NULL, x, y, width, height, shadow_type == GTK_SHADOW_IN, GTK_ORIENTATION_HORIZONTAL);
        gtk_paint_shadow(style, window, state_type, shadow_type, area, widget,
          detail, x, y, width, height);      
    } else {
        FLAT_FILL_BACKGROUND(style, window, state_type, area, widget, NULL, x, y, width, height);
        gtk_paint_shadow(style, window, state_type, shadow_type, area, widget,
                detail, x, y, width, height);
    }
}

static void
draw_check(GtkStyle * style,
	   GdkWindow * window,
	   GtkStateType state_type,
	   GtkShadowType shadow_type,
	   GdkRectangle * area,
	   GtkWidget * widget,
	   detail_char * detail,
	   gint x,
	   gint y,
	   gint width,
	   gint height)
{  
  smooth_check_style * check;
  g_return_if_fail(sanitize_parameters(style, window, &width, &height));

  check = CHECK_PART(style);
  
  if GTK_IS_CHECK_MENU_ITEM(widget) {
    x -= 2;
    y -= 2;
    width += 4;
    height += 4;
  }
  
  #if GTK1
    if (widget) state_type = GTK_WIDGET_STATE(widget);
  #endif

  if (!((GTK_IS_CHECK_MENU_ITEM(widget) && (EDGE_LINE_STYLE(style, check) == SMOOTH_LINE_NONE)))) {
    if ((shadow_type == GTK_SHADOW_IN) && (EDGE_LINE_STYLE(style, check) == SMOOTH_LINE_BEVELED) &&
       (PART_STYLE(check) == NO_CHECK))
    {
      state_type = GTK_STATE_ACTIVE;
    }   
    if (CHECK_MOTIF(style)) 
      gradient_fill_background(style, window, state_type, area, widget, THEME_PART(check), x, y, width, height, FALSE, GTK_ORIENTATION_HORIZONTAL);
    else
      gdk_draw_rectangle(window, style->base_gc[state_type], TRUE, x, y, width, height);		     
  }


  if (shadow_type == GTK_SHADOW_IN)
  {
     gint thick = EDGE_LINE_THICKNESS(style, check);
     if (EDGE_LINE_STYLE(style, check) == SMOOTH_LINE_COLD) thick = 1;

     #if GTK2
     if (PART_STYLE(check) == SLOPPY_CHECK) /* default theme style */
        parent_class->draw_check (style, window, state_type, GTK_SHADOW_IN, area, widget, "check", x+thick, y+thick, width-thick*2, height-thick*2);
     else				 
     #endif
       draw_check_mark(window, style->text_gc[state_type], area, x+thick, y+thick, width-thick*2, height-thick*2, PART_STYLE(check));
  }

  if (!CHECK_MOTIF(style))
    shadow_type = GTK_SHADOW_IN;
  
  if (THEME_PART(check)->use_line || THEME_PART(check)->edge.use_line)
    draw_line_shadow_with_gap(style, window, state_type, shadow_type, area, widget, detail, THEME_PART(check), x, y, width, height, 0, 0, 0);
  else  
    gtk_paint_shadow(style, window, state_type, shadow_type, area, widget, detail, x, y, width, height);
}

static void
draw_option(GtkStyle * style,
            GdkWindow * window,
            GtkStateType state_type,
            GtkShadowType shadow_type,
            GdkRectangle * area,
            GtkWidget * widget,
            detail_char *detail,
            gint x,
            gint y,
            gint width,
            gint height)
{
  smooth_option_style * option;
  smooth_line_style * line_style;
  
  g_return_if_fail(sanitize_parameters(style, window, &width, &height));

  #if GTK1
    if (widget) state_type = GTK_WIDGET_STATE(widget);
  #endif

  option = OPTION_PART(style);
  if (THEME_PART(option)->use_line) 
    line_style = &THEME_PART(option)->line;
  else if (EDGE_PART(style)->use_line) 
    line_style = &EDGE_PART(style)->line;
  else  
    line_style = &THEME_DATA(style)->line;

    if (((shadow_type == GTK_SHADOW_IN) || (!OPTION_MOTIF(style))) && (PART_STYLE(option) == NO_OPTION))
      state_type = GTK_STATE_ACTIVE;

    if (line_style->style != SMOOTH_LINE_NONE) {
    
      if ((line_style->style != SMOOTH_LINE_BEVELED) && (line_style->style != SMOOTH_LINE_THIN))
        {x++; y++; width-=2; height-=2;}     

      fill_background(style, window, state_type, shadow_type, area, NULL, widget, THEME_PART(option), x, y, width, height, (OPTION_MOTIF(style)), TRUE, GTK_ORIENTATION_VERTICAL, TRUE);
     
      if ((line_style->style != SMOOTH_LINE_BEVELED) && (line_style->style != SMOOTH_LINE_THIN))
        {x--; y--; width+=2; height+=2;}

      draw_line_shadow_with_gap(style, window, state_type, OPTION_MOTIF(style)?shadow_type:GTK_SHADOW_IN, area, widget, "SMOOTH_DRAW_OPTION", NULL, x, y, width, height, 0, 0, 0);
  
      if ((line_style->style != SMOOTH_LINE_BEVELED) && (line_style->style != SMOOTH_LINE_THIN))
         {x+=2; y+=2; width-=3; height-=3;}
      else
         {x++; y++; width-=2; height-=2;}   
    }
    
    if ((shadow_type == GTK_SHADOW_IN) && (PART_STYLE(option) != NO_OPTION)) {
      
      if (area)
	 gdk_gc_set_clip_rectangle(style->text_gc[state_type], area);
      
      if ((line_style->style != SMOOTH_LINE_FLAT) && (line_style->style != SMOOTH_LINE_NONE))
      {
	gdk_draw_arc (window, style->text_gc[state_type], TRUE,
		      x + width / 4,
		      y + height / 4,
		      width / 2, height / 2,
		      0, 360 * 64); 
	gdk_draw_arc (window, style->text_gc[state_type], FALSE,
		      x + width / 4,
		      y + height / 4,
		      width / 2, height / 2,
		      0, 360 * 64); 
      }
      else		      
      { 	
	gdk_draw_arc (window, style->text_gc[state_type], TRUE,
		      x + width / 4,
		      y + height / 4,
		      width / 2, height / 2,
		      0, 360 * 64); 
	gdk_draw_arc (window, style->text_gc[state_type], FALSE,
		      x + width / 4,
		      y + height / 4,
		      width / 2, height / 2,
		      0, 360 * 64); 
      }		      

      if (area)
        gdk_gc_set_clip_rectangle(style->text_gc[state_type], NULL);
    }    
}

static void
draw_shadow_gap (GtkStyle * style, 
                 GdkWindow * window, 
		 GtkStateType state_type, 
		 GtkShadowType shadow_type, 
		 GdkRectangle * area, 
		 GtkWidget * widget, 
		 detail_char * detail, 
		 gint x, 
		 gint y, 
		 gint width, 
		 gint height, 
		 GtkPositionType gap_side, 
		 gint gap_x, 
		 gint gap_width)
{
  g_return_if_fail(sanitize_parameters(style, window, &width, &height));
  
  FLAT_FILL_BACKGROUND(style, window, state_type, area, widget, NULL, x, y, width, height);

  draw_line_shadow_with_gap(style, window, state_type, shadow_type, area, widget, detail, NULL, x, y, width, height, gap_side, gap_x, gap_width);
}

static void
draw_box_gap (GtkStyle * style, 
              GdkWindow * window, 
	      GtkStateType state_type, 
	      GtkShadowType shadow_type, 
	      GdkRectangle * area, 
	      GtkWidget * widget, 
	      detail_char * detail, 
	      gint x, 
	      gint y, 
	      gint width, 
	      gint height, 
	      GtkPositionType gap_side, 
	      gint gap_x, 
	      gint gap_width)
{
  g_return_if_fail(sanitize_parameters(style, window, &width, &height));
  
  FLAT_FILL_BACKGROUND(style, window, state_type, area, widget, NULL, x, y, width, height);

  draw_line_shadow_with_gap(style, window, state_type, shadow_type, area, widget, detail, NULL, x, y, width, height, gap_side, gap_x-1, gap_width+1);
}

/* This routine is mostly based on the Xenophilia draw_extension & draw_polygon
 * routines, though the LighthouseBlue draw_extension routine, & the XFCE
 * draw_shadow routine were also useful resources.
 */
static void
draw_extension(GtkStyle * style,
	       GdkWindow * window,
	       GtkStateType state_type,
	       GtkShadowType shadow_type,
	       GdkRectangle * area,
	       GtkWidget * widget,
	       detail_char * detail,
	       gint x,
	       gint y,
	       gint width,
	       gint height,
	       GtkPositionType gap_side)
{
  GtkStateType parent_state;
  GdkPoint	 points[8];
  GdkRectangle tab_area, draw_area;
  GtkStyle	 *parent_style;
  gint		 x2, y2;
  gboolean	 triangular;
  gint 		 orientation=0, position=1, selected=0;
  GtkNotebook *notebook=NULL;
  GdkGC              *shade = NULL;
  GdkGC              *dark=NULL, *light=NULL, *mid=NULL, *midlight=NULL, *middark=NULL;
  gint thick=0;      
  GdkRectangle        rect;
  SmoothRcStyle *data = NULL;
  smooth_part_style * tab;

  g_return_if_fail(sanitize_parameters(style, window, &width, &height));
    
#ifdef DEBUG
  printf("draw_tab(%d,%d,%d,%d) (detail = '%s')\n", x, y, width, height, detail?detail:"<null>");
#endif
  data = THEME_DATA(style); 

  g_return_if_fail (style != NULL);
  g_return_if_fail (window != NULL);

  tab_area.x = x;
  tab_area.y = y;
  tab_area.width = width;
  tab_area.height = height;
	
  if (area) {
    gdk_rectangle_intersect (&tab_area, area, &draw_area);
    area = &draw_area;
  } else {
    area = &tab_area;
  }
	
  x2 = x + width - 1;
  y2 = y + height - 1;
	
  if (GTK_IS_NOTEBOOK(widget)) {
    notebook = GTK_NOTEBOOK(widget);
    orientation = notebook->tab_pos;
    get_tab_status (notebook, x, y, &position, &selected);
  }  

  
  tab = NULL;
  thick = EDGE_LINE_THICKNESS(style, tab);
  
  switch (data->tab_style)
    {
    case SMOOTH_NORMAL_TABS:
      goto square;
      break;
    case SMOOTH_ROUND_TABS:
      if (rounded_extension_points(x, y, width, height, gap_side, points)) 
        goto draw;	    
      else
        return;

      break;   	
    case SMOOTH_TRIANGLE_TABS:
	if (   detail 
		&& !g_strcasecmp(detail, "tab")
		&& (gap_side == GTK_POS_BOTTOM || gap_side == GTK_POS_TOP)
		&& widget
		&& GTK_IS_NOTEBOOK(widget))
	{
		gint i, h, t;
		
		t = height - 5 + 2;
		i = t / 3;
		if (!(i > 0))
			goto square;
		
		if (notebook->tab_hborder == 2) {
			gtk_notebook_set_tab_hborder (notebook, i + 2);
			goto square;
		}
		
    
		triangular = TRUE;
		h = i*3 + 5;
		if (gap_side == GTK_POS_BOTTOM) {
			y2 = y + h;
			
			points[0].x = x2;		points[0].y = y2;
			points[1].x = x2-i;		points[1].y = y+4;
			points[2].x = x2-i-2;	points[2].y = y+2;
			points[3].x = x2-i-5;	points[3].y = y;
			points[4].x = x+i+5;	points[4].y = y;
			points[5].x = x+i+2;	points[5].y = y+2;
			points[6].x = x+i;		points[6].y = y+4;
			points[7].x = x;		points[7].y = y2;
		} else {
			y -= (h - height);
			
			points[0].x = x;		points[0].y = y;
			points[1].x = x+i;		points[1].y = y2-4;
			points[2].x = x+i+2;	points[2].y = y2-2;
			points[3].x = x+i+5;	points[3].y = y2;
			points[4].x = x2-i-5;	points[4].y = y2;
			points[5].x = x2-i-2;	points[5].y = y2-2;
			points[6].x = x2-i;		points[6].y = y2-4;
			points[7].x = x2;		points[7].y = y;	
		}
		goto draw;
	} else goto square;
      break;
    }
    
    square: {
       gint c1=0, c2=1;
       switch (gap_side) {
          case GTK_POS_BOTTOM:
            y2 += 1;
            points[0].x = x2;		points[0].y = y2;
	    points[1].x = x2;		points[1].y = y+c2;
	    points[2].x = x2-c1;	points[2].y = y+c1;
	    points[3].x = x2-c2;	points[3].y = y;
	    points[4].x = x+c2;		points[4].y = y;
	    points[5].x = x+c1;		points[5].y = y+c1;
	    points[6].x = x;		points[6].y = y+c2;
	    points[7].x = x;		points[7].y = y2;
	    break;
	
          case GTK_POS_TOP:
	    points[0].x = x;		points[0].y = y;
	    points[1].x = x;		points[1].y = y2-c2;
	    points[2].x = x+c1;		points[2].y = y2-c1;
	    points[3].x = x+c2;		points[3].y = y2;
	    points[4].x = x2-c2;	points[4].y = y2;
	    points[5].x = x2-c1;	points[5].y = y2-c1;
	    points[6].x = x2;		points[6].y = y2-c2;
	    points[7].x = x2;		points[7].y = y;
	    break;
    
          case GTK_POS_RIGHT:
            points[0].y = y;		points[0].x = x2;
	    points[1].y = y;		points[1].x = x+c2;
	    points[2].y = y+c1;		points[2].x = x+c1;
	    points[3].y = y+c2;		points[3].x = x;
	    points[4].y = y2-c2;	points[4].x = x;
	    points[5].y = y2-c1;	points[5].x = x+c1;
	    points[6].y = y2;		points[6].x = x+c2;
	    points[7].y = y2;		points[7].x = x2;
	    break;
			
          case GTK_POS_LEFT:
            points[0].y = y2;		points[0].x = x;
            points[1].y = y2;		points[1].x = x2-c2;
	    points[2].y = y2-c1;	points[2].x = x2-c1;
	    points[3].y = y2-c2;	points[3].x = x2;
	    points[4].y = y+c2;		points[4].x = x2;
	    points[5].y = y+c1;		points[5].x = x2-c1;
	    points[6].y = y;		points[6].x = x2-c2;
	    points[7].y = y;		points[7].x = x;
	    break;
         
	  default:
            return;
       }
    }		
    draw :	
	
        dark = darktone_gc(style, state_type);
        light = lighttone_gc(style, state_type);
        mid = midtone_gc(style, state_type);

	parent_style = style;
	parent_state = GTK_STATE_NORMAL;
	if (widget) {
		if (widget->state == GTK_STATE_INSENSITIVE)
			state_type = GTK_STATE_INSENSITIVE;
		
		if (widget->parent) {
			parent_style = widget->parent->style;
			parent_state = widget->parent->state;
		}
	}
	
	/* draw inner shadow line(s)  */	
	{
	  GdkGC		*gc[3], *use_gc=NULL, *mid_gc=NULL, *bg_gc=style->bg_gc[state_type];
	  gdouble		angle;
	  gint		j,i, x1,y1, x2,y2, xt, yt, mx=0,my=0, sign, thickness;
	
          fill_background(parent_style, window, parent_state, GTK_SHADOW_NONE, area, NULL, widget, NULL, x, y, width, height, FALSE, FALSE, GTK_ORIENTATION_VERTICAL,FALSE);
	  
          switch (EDGE_LINE_STYLE(style, tab)) {
	    case SMOOTH_LINE_NONE : return;

            case SMOOTH_LINE_THIN :
              gc[0] = light;
              gc[1] = light;
              gc[2] = dark;
              gc[3] = dark;
	      thickness = 0;
              break;
	    
            case SMOOTH_LINE_BEVELED :
              gc[0] = light;
              gc[1] = light;
              gc[2] = dark;
              gc[3] = dark;
	      thickness = EDGE_LINE_THICKNESS(style, tab) - 1;
              break;
	    
            case SMOOTH_LINE_FLAT :
              gc[0] = style->fg_gc[state_type];
              gc[1] = style->fg_gc[state_type];
              gc[2] = style->fg_gc[state_type];
              gc[3] = style->fg_gc[state_type];
              thickness = 0;
              break;

            case SMOOTH_LINE_SMOOTHED :
              gc[0] = mid;
              gc[1] = light;
              gc[2] = mid;
              gc[3] = dark;
              thickness = 1;
              break;

            case SMOOTH_LINE_COLD :
              shade = shaded_color (style, state_type, shades[6]);
              gc[0] = shade;
              gc[1] = light;
              gc[2] = mid;
              gc[3] = shade;
              thickness = 1;
	      break;

            case SMOOTH_LINE_WIN32 :
              shade = shaded_color (style, state_type, shades[8]);
              gc[0] = light;
              gc[1] = style->bg_gc[state_type];
              gc[2] = dark;
              gc[3] = shade;
              thickness = 1;
              break;

            case SMOOTH_LINE_SMOOTHBEVEL :
              midlight = midlighttone_gc(style, state_type);
              middark = middarktone_gc(style, state_type);
  
              gc[0] = midlight;
              gc[1] = light;
              gc[2] = middark;
              gc[3] = dark;
              thickness = 1;
              break;
	    
            default :			 
              gc[0] = mid;
              gc[1] = light;
              gc[2] = dark;
              gc[3] = style->black_gc;
              thickness = 1;
          }
          {
            GdkRegion *cliprgn = gdk_region_polygon(points, 8, GDK_EVEN_ODD_RULE);
            fill_background(style, window, state_type, GTK_SHADOW_NONE, NULL, cliprgn, widget, NULL, x, y, width, height, FALSE, FALSE, GTK_ORIENTATION_VERTICAL,FALSE);
	    gdk_gc_set_clip_region (bg_gc, NULL);
            gdk_region_destroy(cliprgn);
	  }

          if (!(selected)) gdk_draw_line (window, bg_gc, points[0].x, points[0].y, points[7].x, points[7].y);

	  sign = 0;
	  for (i = thickness; i >= 0; --i) {
	    for (j = 0; j < 7; ++j) {
		x1	= points[j].x;
		y1	= points[j].y;
		x2	= points[j+1].x;
		y2	= points[j+1].y;
			
		if ((x1 == x2) && (y1 == y2)) {
		  angle = 0;
		} else {
		  angle = atan2 (y2 - y1, x2 - x1);
		}
			
		if ((angle > - (M_PI_4 * 3) - 0.0625) && (angle < M_PI_4 - 0.0625)) {
		  if (i!=1) {
		    use_gc = gc[3];
		  } else {
		    use_gc = gc[2];
		  } 
		  mid_gc = use_gc;
		  if (angle > -M_PI_4) {
   	            y1  -= i;
		    y2 -= i;
		  } else {
		    x1  -= i;
		    x2 -= i;
		  }
		  if (sign != 0) {
		    sign = 0;
  		    mx = x1 + i;
  		    if (i!=1) {
		      mid_gc = gc[3];
		    } else {
		      mid_gc = gc[2];
		    } 
		  }
		} else {
		  if (i!=1) {
		    use_gc = gc[0];
		  } else {
     		    use_gc = gc[1];
		  }  
		  mid_gc = use_gc;
		  if ((angle < -(M_PI_4 * 3)) || (angle > (M_PI_4 * 3))) {
   	            y1  += i;
		    y2 += i;
		  } else {
		    x1  += i;
		    x2 += i;
		  }
		  if (sign != 1) {
		    sign = 1;
  		    mx = x1 - i;
  		    if (i!=1) {
		      mid_gc = gc[0];
		    } else {
		      mid_gc = gc[1];
		    } 
		  }
	        }
	        my = y1;
		if (use_gc) {
	  	  if (y2 < y1) {
		    xt = x1; x1 = x2; x2 = xt;
		    yt = y1; y1 = y2; y2 = yt;
	          }
	          gdk_draw_line (window, use_gc, x1, y1, x2, y2);
	        }
		
		if ((j > 0) && (mid_gc) && (mid_gc != use_gc))
		  gdk_draw_point (window, mid_gc, mx, my);
            }
	  }  
	}  
  if (shade) gtk_gc_release (shade);
  if (mid) gtk_gc_release (mid);
  if (light) gtk_gc_release (light);
  if (dark) gtk_gc_release (dark);
  if (middark) gtk_gc_release (middark);
  if (midlight) gtk_gc_release (midlight);
}

static void 
draw_slider_grip(GtkStyle * style,
                       GdkWindow * window,
		       GtkStateType state_type,
		       GtkShadowType shadow_type,
		       GdkRectangle * area,
		       GtkWidget * widget,
		       detail_char * detail,
		       gint x,
		       gint y,
		       gint width,
		       gint height,
		       GtkOrientation orientation)
{
  gboolean BAIL = FALSE;
  smooth_grip_style *grip = GRIP_PART(style);
#ifdef DEBUG
  printf("Slider Grip... x,y=%d,%d width = %d, height = %d (%d)\n",x,y,width,height, state_type);
#endif
 
 switch (PART_STYLE(grip))
   {
   case NO_GRIP:
     break;
   case BARS_IN_GRIP:
   case BARS_OUT_GRIP:
      {
      gint w, h;
		
      w = width;
      h = height;
      if (orientation == GTK_ORIENTATION_VERTICAL) {
	h = MIN(height, width + height/7);
	y = y + (height - h)/2;
	orientation = GTK_ORIENTATION_HORIZONTAL; 
      } else {
	w = MIN(width, width/7 + height);
	x = x + (width - w)/2;
	orientation = GTK_ORIENTATION_VERTICAL;
      }
		
      width = w;
      height = h;
     } 
      /* too small no bars */
     if ((width <= 13) && (height <= 11))
       BAIL = TRUE;

     break;
   case LINES_IN_GRIP:
   case LINES_OUT_GRIP:
      {
      gint w, h;
		
      w = width;
      h = height;
      if (orientation == GTK_ORIENTATION_VERTICAL) {
	h = MIN(height, width + height/7);
	y = y + (height - h)/2;
      } else {
	w = MIN(width, width/7 + height);
	x = x + (width - w)/2;
      }
		
      width = w;
      height = h;
     } 
      /* too small no lines */
     if ((width <= 13) && (height <= 11))
       BAIL = TRUE;

     break;

   case FIXEDLINES_IN_GRIP:
   case FIXEDLINES_OUT_GRIP:
       /* too small no midlines */
      if ((width <= 13) && (height <= 13))
         BAIL = TRUE;
	
     break;
   case SLASHES_GRIP:
      if ((width <= 7) && (height <= 7))
         BAIL = TRUE;

     break;
   case DOTS_IN_GRIP:
   case DOTS_OUT_GRIP:
   case SMALLDOTS_IN_GRIP :
   case SMALLDOTS_OUT_GRIP :
      if ((width <= 7) && (height <= 7))
         BAIL = TRUE;

      break;
   case MAC_BUDS_IN_GRIP:
   case MAC_BUDS_OUT_GRIP:
   case NS_BUDS_IN_GRIP:
   case NS_BUDS_OUT_GRIP:
     {
       gboolean ns = ((PART_STYLE(grip) == NS_BUDS_OUT_GRIP) || (PART_STYLE(grip) == NS_BUDS_IN_GRIP));
       gint w = width, h = height;

       if (orientation == GTK_ORIENTATION_VERTICAL) {
         h = MIN(height, width + height/7);
         y = y + (height - h)/2;
       } else {
         w = MIN(width, width/7 + height);
         x = x + (width - w)/2;
       }

       #if GTK1
       x += 1 + (gint)(ns);
       y += 1 + (gint)(ns);
       width = w - 3;
       height = h - 3;
       #endif

       #if GTK2
       x += 2 + (gint)(ns);
       y += 3 + (gint)(ns);
       width = w - 4;
       height = h - 6;
       #endif
      
        /* too small no buds */
       if ((width <= 13) && (height <= 11))
         BAIL = TRUE;
     }
     break;
   default :
     BAIL = TRUE;
   }	  
   if (!BAIL)
     draw_grip(style, window, state_type, area, x+PART_XPADDING(grip), y+PART_YPADDING(grip), width-PART_XPADDING(grip)*2, height-PART_YPADDING(grip)*2, orientation);      
}

static void
draw_slider(GtkStyle * style,
	    GdkWindow * window,
	    GtkStateType state_type,
	    GtkShadowType shadow_type,
	    GdkRectangle * area,
	    GtkWidget * widget,
	    detail_char * detail,
	    gint x,
	    gint y,
	    gint width,
	    gint height,
	    GtkOrientation orientation)
{
  GdkGC *light_gc, *dark_gc;
  SmoothRcStyle *data = NULL;
  smooth_grip_style  *grip;

  g_return_if_fail(sanitize_parameters(style, window, &width, &height));

  data = THEME_DATA(style);
  grip = GRIP_PART(style);

  light_gc = style->light_gc[state_type];
  dark_gc = style->dark_gc[state_type];

#ifdef DEBUG
  printf("draw_slider(%s, %d, %d, %d)\n", detail, x, y, orientation);
#endif

  gradient_fill_background(style, window, state_type, area, widget, THEME_PART(grip), x, y, width, height, shadow_type == GTK_SHADOW_IN, orientation);
     
  if ((THEME_PART(grip)->use_line || THEME_PART(grip)->edge.use_line))
    draw_line_shadow_with_gap(style, window, state_type, shadow_type, area, widget, detail, THEME_PART(grip), x, y, width, height, 0, 0, 0);
  else  
    gtk_paint_shadow(style, window, state_type, shadow_type, area, widget, detail, x, y, width, height);

  draw_slider_grip(style, window, state_type, shadow_type, area, widget, detail, x, y, width, height, orientation);
}

static void
draw_handle(GtkStyle * style,
	    GdkWindow * window,
	    GtkStateType state_type,
	    GtkShadowType shadow_type,
	    GdkRectangle * area,
	    GtkWidget * widget,
	    detail_char * detail,
	    gint x,
	    gint y,
	    gint width,
	    gint height,
	    GtkOrientation orientation)
{
    GdkGC              *light_gc, *dark_gc;
    GdkRectangle        dest;
    smooth_grip_style  *grip;
    gint ax=x, ay=y, aw=width, ah=height;
    gboolean toolbar_overlap = (GRIP_OVERLAP_TOOLBAR(style) && (DETAIL("dockitem")));
    #if GTK2
    gboolean horiz=(DETAIL("handlebox") || (DETAIL("dockitem") && !IS_HANDLE_BOX_ITEM(widget)))?(orientation==GTK_ORIENTATION_HORIZONTAL):(orientation==GTK_ORIENTATION_VERTICAL);
    gint gap_size=(!horiz)?y+height:x+width;
    #endif
    #if GTK1
    gboolean horiz=(width<height);
    gint gap_size=(horiz)?y+height:x+width;
    #endif    
    gboolean vert=(!horiz);
    g_return_if_fail(sanitize_parameters(style, window, &width, &height));

    aw=width; ah=height;
     
    grip = GRIP_PART(style);
    
    if (!GTK_IS_PANED(widget)) {
      gint thick = 0;
      if (toolbar_overlap)
	thick = EDGE_LINE_THICKNESS(style, NULL)*2;
      gradient_fill_background(style, window, state_type, area, widget, THEME_PART(grip), x, y, width+thick*horiz, height+thick*vert, shadow_type == GTK_SHADOW_IN, orientation);
    } else  {
      FLAT_FILL_BACKGROUND(style, window, state_type, area, widget, THEME_PART(grip), x, y, width, height);
    }
    switch (PART_STYLE(grip)) {
      case NO_GRIP:
        break;
      case BARS_IN_GRIP :
      case BARS_OUT_GRIP :
        {
          gint w=width, h=height;
		
          if (vert) {
	     if (DETAIL("handlebox")) {
              h+=1;
              gap_size=x+width;
	     }else
	     if (DETAIL("dockitem")) {
	        #if GTK2
	        w+=1;
	        h = MIN(height+1, width + height/7);
   	        y = y + (height - h)/2;
	        orientation = GTK_ORIENTATION_HORIZONTAL;
	        if (!toolbar_overlap) y -=1;
   	        #endif
	        #if GTK1
	        h+=1;
	        orientation = GTK_ORIENTATION_HORIZONTAL;
   	        #endif
             } else 
	     {
               h+=1;
	       y-=1;
	       w = MIN(width+1, width/7 + height);
   	       x = x + (width - w)/2;
	     }
          } else {
	     if (DETAIL("handlebox")) {
              w+=1;
              gap_size=y+height;
              orientation = GTK_ORIENTATION_VERTICAL;
	     }else
	     if (DETAIL("dockitem")) {
	     #if GTK2
               h+=1;
	       w = MIN(width+1, width/7 + height);
   	       x = x + (width - w)/2;
	       orientation = GTK_ORIENTATION_VERTICAL;
               if (!toolbar_overlap) x -=1;
	     #endif
	     #if GTK1
               w+=1;
	       orientation = GTK_ORIENTATION_VERTICAL;
   	     #endif
	     } else {
               w+=1;
	       x-=1;
	       h = MIN(height+1, width + height/7);
   	       y = y + (height - h)/2;
	     }
          }
		
          width = w;
          height = h;
        }
	break;
      case LINES_IN_GRIP :
      case LINES_OUT_GRIP :
        {
          gint w=width, h=height;
		
          if (vert) {
	     w+=1;
	     h = MIN(height+1, width + height/7);
	     y = y + (height - h)/2;
             if ((GTK_IS_PANED(widget)) || (GTK_IS_RANGE(widget))) orientation = GTK_ORIENTATION_HORIZONTAL;
	     if (!GRIP_OVERLAP_TOOLBAR(style) && DETAIL("dockitem")) y -=1;
          } else {
	     w = MIN(width+1, width/7 + height);
	     x = x + (width - w)/2;
	     if ((GTK_IS_PANED(widget)) || (GTK_IS_RANGE(widget))) orientation = GTK_ORIENTATION_VERTICAL;
	     if (!GRIP_OVERLAP_TOOLBAR(style) && DETAIL("dockitem")) x -=1;
          }
		
          if (DETAIL("dockitem") || DETAIL("handlebox"))
	    orientation = GTK_ORIENTATION_VERTICAL;
          break;

          width = w;
          height = h;
        }
	break;
      case SLASHES_GRIP:
	#if GTK1
	x -= 2;
	y -= 2;
	width += 4;
	height += 4;	
	#endif
	break;
      case DOTS_OUT_GRIP:
      case DOTS_IN_GRIP:
      case SMALLDOTS_IN_GRIP :
      case SMALLDOTS_OUT_GRIP :
        if (DETAIL("dockitem") || DETAIL("handlebox"))
	  orientation = GTK_ORIENTATION_VERTICAL;
        break;
      case FIXEDLINES_OUT_GRIP:
      case FIXEDLINES_IN_GRIP:
        if (DETAIL("dockitem") || DETAIL("handlebox"))
	  orientation = GTK_ORIENTATION_VERTICAL;
        break;
      case MAC_BUDS_IN_GRIP:
      case MAC_BUDS_OUT_GRIP:
      case NS_BUDS_IN_GRIP:
      case NS_BUDS_OUT_GRIP:
	x += 3;
	y += 3;
	width -= 4;
	height -= 6;
        orientation = GTK_ORIENTATION_VERTICAL;
        break;
     }

    draw_grip(style, window, state_type, area, x+PART_XPADDING(grip), y+PART_YPADDING(grip), width-PART_XPADDING(grip)*2, height-PART_YPADDING(grip)*2, orientation);      

    switch (PART_STYLE(grip)) {
      case BARS_IN_GRIP :
      case BARS_OUT_GRIP :
      case LINES_IN_GRIP :
      case LINES_OUT_GRIP :
        x=ax; 
	y=ay; 
	width=aw; 
	height=ah;
	break;
	
      case SLASHES_GRIP:
	#if GTK1
	x += 2;
	y += 2;
	width -= 4;
	height -= 4;	
	#endif
	break;
	
      case MAC_BUDS_IN_GRIP:
      case MAC_BUDS_OUT_GRIP:
      case NS_BUDS_IN_GRIP:
      case NS_BUDS_OUT_GRIP:
        x -= 3;
        y -= 3;
	width += 4;
	height += 6;
	break;
    }

  if ((THEME_PART(grip)->use_line || THEME_PART(grip)->edge.use_line)) {
    gint thick = 0;

    if (toolbar_overlap)
      thick = EDGE_LINE_THICKNESS(style, grip)*2;
    else
      gap_size = 0;    

    draw_line_shadow_with_gap(style, window, state_type, shadow_type, area, widget, detail, THEME_PART(grip), x, y, width+horiz*thick, height+vert*thick, vert?GTK_POS_BOTTOM:GTK_POS_RIGHT, 0, gap_size);
  } else  {
    gint thick = 0;

    if (toolbar_overlap)
      thick = EDGE_LINE_THICKNESS(style, NULL)*2;
    else
      gap_size = 0;    
      
    draw_line_shadow_with_gap(style, window, state_type, shadow_type, area, widget, detail, NULL, x, y, width+horiz*thick, height+vert*thick, vert?GTK_POS_BOTTOM:GTK_POS_RIGHT, 0, gap_size);
  }
}

#ifdef GTK2
static void make_square(gint * value1, gint * value2) 
{ 
  if (*value1 < *value2) 
    *value2 = *value1;
}

static void make_square_offset(gint * value1, gint * value2, gint * value3) 
{ 
  if (*value1 < *value2) 
  {
    *value3 += (*value1 - *value2);
    *value2 = *value1;
  }
}
   
static void
draw_resize_grip (GtkStyle       *style,
                              GdkWindow      *window,
                              GtkStateType    state_type,
                              GdkRectangle   *area,
                              GtkWidget      *widget,
                              const gchar    *detail,
                              GdkWindowEdge   edge,
                              gint            x,
                              gint            y,
                              gint            width,
                              gint            height)
{
  g_return_if_fail (GTK_IS_STYLE (style));
  g_return_if_fail (window != NULL);
  
  if (widget && GTK_IS_STATUSBAR(widget) && !RESIZE_GRIP(style)) {
    gtk_statusbar_set_has_resize_grip(GTK_STATUSBAR(widget), FALSE);
    return;
  }
    
  if (area)
    {
      gdk_gc_set_clip_rectangle (style->light_gc[state_type], area);
      gdk_gc_set_clip_rectangle (style->dark_gc[state_type], area);
      gdk_gc_set_clip_rectangle (style->bg_gc[state_type], area);
    }
  
  switch (edge)
    {
    case GDK_WINDOW_EDGE_WEST:
    case GDK_WINDOW_EDGE_EAST:
      {
	gint xi;

        if (edge==GDK_WINDOW_EDGE_WEST) 
          make_square(&height, &width); 
        else 
          make_square_offset(&height, &width, &x);
	
	xi = x;

	while (xi < x + width)
	  {
	    gdk_draw_line (window,
			   style->light_gc[state_type],
			   xi, y,
			   xi, y + height);

	    xi++;
	    gdk_draw_line (window,
			   style->dark_gc[state_type],
			   xi, y,
			   xi, y + height);

	    xi += 2;
	  }
      }
      break;
    case GDK_WINDOW_EDGE_NORTH:
    case GDK_WINDOW_EDGE_SOUTH:
      {
	gint yi;

        if (edge==GDK_WINDOW_EDGE_NORTH) 
          make_square(&width, &height); 
        else 
          make_square_offset(&width, &height, &y);

	yi = y;

	while (yi < y + height)
	  {
	    gdk_draw_line (window,
			   style->light_gc[state_type],
			   x, yi,
			   x + width, yi);

	    yi++;
	    gdk_draw_line (window,
			   style->dark_gc[state_type],
			   x, yi,
			   x + width, yi);

	    yi+= 2;
	  }
      }
      break;
    case GDK_WINDOW_EDGE_NORTH_WEST:
      {
	gint xi, yi;

        make_square(&width, &height);
        make_square(&height, &width);
	
	xi = x + width;
	yi = y + height;

	while (xi > x + 3)
	  {
	    gdk_draw_line (window,
			   style->dark_gc[state_type],
			   xi, y,
			   x, yi);

	    --xi;
	    --yi;

	    gdk_draw_line (window,
			   style->dark_gc[state_type],
			   xi, y,
			   x, yi);

	    --xi;
	    --yi;

	    gdk_draw_line (window,
			   style->light_gc[state_type],
			   xi, y,
			   x, yi);

	    xi -= 3;
	    yi -= 3;
	    
	  }
      }
      break;
    case GDK_WINDOW_EDGE_NORTH_EAST:
      {
        gint xi, yi;

        make_square(&width, &height);
        make_square_offset(&height, &width, &x);

        xi = x;
        yi = y + height;

        while (xi < (x + width - 3))
          {
            gdk_draw_line (window,
                           style->light_gc[state_type],
                           xi, y,
                           x + width, yi);                           

            ++xi;
            --yi;
            
            gdk_draw_line (window,
                           style->dark_gc[state_type],
                           xi, y,
                           x + width, yi);                           

            ++xi;
            --yi;
            
            gdk_draw_line (window,
                           style->dark_gc[state_type],
                           xi, y,
                           x + width, yi);

            xi += 3;
            yi -= 3;
          }
      }
      break;
    case GDK_WINDOW_EDGE_SOUTH_WEST:
      {
	gint xi, yi;

        make_square_offset(&width, &height, &y);
        make_square(&height, &width);
	
	xi = x + width;
	yi = y;

	while (xi > x + 3)
	  {
	    gdk_draw_line (window,
			   style->dark_gc[state_type],
			   x, yi,
			   xi, y + height);

	    --xi;
	    ++yi;

	    gdk_draw_line (window,
			   style->dark_gc[state_type],
			   x, yi,
			   xi, y + height);

	    --xi;
	    ++yi;

	    gdk_draw_line (window,
			   style->light_gc[state_type],
			   x, yi,
			   xi, y + height);

	    xi -= 3;
	    yi += 3;
	    
	  }
      }
      break;
    case GDK_WINDOW_EDGE_SOUTH_EAST:
      {
        gint xi, yi;

        make_square_offset(&width, &height, &y);
        make_square_offset(&height, &width, &x);
     
        xi = x;
        yi = y;

        while (xi < (x + width - 3))
          {
            gdk_draw_line (window,
                           style->light_gc[state_type],
                           xi, y + height,
                           x + width, yi);                           

            ++xi;
            ++yi;
            
            gdk_draw_line (window,
                           style->dark_gc[state_type],
                           xi, y + height,
                           x + width, yi);                           

            ++xi;
            ++yi;
            
            gdk_draw_line (window,
                           style->dark_gc[state_type],
                           xi, y + height,
                           x + width, yi);

            xi += 3;
            yi += 3;
          }
      }
      break;
    default:
      return;
      break;
    }
  
  if (area)
    {
      gdk_gc_set_clip_rectangle (style->light_gc[state_type], NULL);
      gdk_gc_set_clip_rectangle (style->dark_gc[state_type], NULL);
      gdk_gc_set_clip_rectangle (style->bg_gc[state_type], NULL);
    }
}

static const GtkRequisition default_option_indicator_size = { 7, 13 };
static const GtkBorder default_option_indicator_spacing = { 7, 5, 2, 2 };

static void
option_menu_get_props (GtkWidget      *widget,
		       GtkRequisition *indicator_size,
		       GtkBorder      *indicator_spacing)
{
  GtkRequisition *tmp_size = NULL;
  GtkBorder *tmp_spacing = NULL;
  
  if (widget)
    gtk_widget_style_get (widget, 
			  "indicator_size", &tmp_size,
			  "indicator_spacing", &tmp_spacing,
			  NULL);

  if (tmp_size)
    {
      *indicator_size = *tmp_size;
      g_free (tmp_size);
    }
  else
    *indicator_size = default_option_indicator_size;

  if (tmp_spacing)
    {
      *indicator_spacing = *tmp_spacing;
      g_free (tmp_spacing);
    }
  else
    *indicator_spacing = default_option_indicator_spacing;
}

static void
draw_tab (GtkStyle      *style,
		      GdkWindow     *window,
		      GtkStateType   state_type,
		      GtkShadowType  shadow_type,
		      GdkRectangle  *area,
		      GtkWidget     *widget,
		      const gchar   *detail,
		      gint           x,
		      gint           y,
		      gint           width,
		      gint           height)
{
#define ARROW_SPACE 0

  GtkRequisition indicator_size;
  GtkBorder indicator_spacing;
  gint arrow_height;
  gboolean solid = SOLID_ARROW(style);
  GdkGC * border_gc = style->fg_gc[state_type], * fill_gc = style->fg_gc[state_type];
  gint alternate;
  
  g_return_if_fail(sanitize_parameters(style, window, &width, &height));
  
  alternate = ARROW_STYLE(style);

  if ((!solid))
    fill_gc = style->base_gc[state_type];
      
  option_menu_get_props (widget, &indicator_size, &indicator_spacing);

  indicator_size.width += 2;
  arrow_height = indicator_size.width;

  x += (width - indicator_size.width) / 2;
  y += (height - (2 * arrow_height + ARROW_SPACE)) / 2;

  if (state_type == GTK_STATE_INSENSITIVE)
    {
     solid=TRUE;
     border_gc = style->dark_gc[state_type];
     fill_gc = style->dark_gc[state_type];
     do_draw_arrow(window, area, GTK_ARROW_UP, style->light_gc[state_type], style->light_gc[state_type], x+1, y+1, indicator_size.width, arrow_height, alternate); 
     do_draw_arrow(window, area, GTK_ARROW_DOWN, style->light_gc[state_type], style->light_gc[state_type], x+1, y + arrow_height + ARROW_SPACE + 1, indicator_size.width, arrow_height, alternate); 
    }
  
  do_draw_arrow(window, area, GTK_ARROW_UP, fill_gc, border_gc, x, y, indicator_size.width, arrow_height, alternate); 
  do_draw_arrow(window, area, GTK_ARROW_DOWN, fill_gc, border_gc, x, y + arrow_height + ARROW_SPACE, indicator_size.width, arrow_height, alternate); 
}

static void draw_layout (GtkStyle * style, GdkWindow * window,
			 GtkStateType state_type, gboolean use_text,
			 GdkRectangle * area, GtkWidget * widget,
			 const gchar * detail, gint x, gint y,
			 PangoLayout * layout) {
/*  if ((strstr (g_type_name (GTK_WIDGET_TYPE (widget->parent)),
	       "CheckButton") ||
       strstr (g_type_name (GTK_WIDGET_TYPE (widget->parent)),
	       "RadioButton")) &&
      state_type == GTK_STATE_PRELIGHT) {
    if (area) {
      gdk_gc_set_clip_rectangle (style->bg_gc[state_type], area);
    }
    gdk_draw_layout (window, style->bg_gc[state_type], x, y, layout);
    if (area) {
      gdk_gc_set_clip_rectangle (style->bg_gc[state_type], NULL);
    }
  } else {*/
    parent_class->draw_layout (style, window, state_type, use_text,
			       area, widget, detail, x, y, layout);
}

static void 
draw_flat_box (GtkStyle * style,
               GdkWindow * window,
	       GtkStateType state_type,
	       GtkShadowType shadow_type,
	       GdkRectangle * area,
	       GtkWidget * widget,
	       const gchar * detail,
	       gint x, gint y, gint width, gint height)
{
   GdkGC *gc1;
 
   g_return_if_fail(sanitize_parameters(style, window, NULL, NULL));

   gc1 = style->bg_gc[state_type];
   
   if (gc1 != style->bg_gc[state_type]) 
   {
     FLAT_FILL_BACKGROUND(style, window, state_type, area, widget, NULL, x, y, width, height);

     if (DETAIL("tooltip")) 
       gdk_draw_rectangle(window, style->black_gc, FALSE, x, y, width - 1, height - 1);
   } else
     parent_class->draw_flat_box (style, window, state_type, shadow_type,
			          area, widget, detail, x, y, width, height);
}

static void
smooth_style_class_init (SmoothStyleClass *klass)
{
  GtkStyleClass *style_class = GTK_STYLE_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  style_class->draw_hline = draw_hline;
  style_class->draw_vline = draw_vline;
  style_class->draw_shadow = draw_shadow;

  style_class->draw_polygon = draw_polygon;
  style_class->draw_diamond = draw_diamond;

  style_class->draw_box = draw_box;
  style_class->draw_flat_box = draw_flat_box;
  style_class->draw_check = draw_check;
  style_class->draw_option = draw_option;
  style_class->draw_tab = draw_tab;
  style_class->draw_shadow_gap = draw_shadow_gap;
  style_class->draw_box_gap = draw_box_gap;
  style_class->draw_extension = draw_extension;
  style_class->draw_slider = draw_slider;
  style_class->draw_handle = draw_handle;

  style_class->draw_arrow = draw_arrow;
  style_class->draw_resize_grip = draw_resize_grip;
  
  style_class->draw_layout = draw_layout;  
}

GType smooth_type_style = 0;

void
smooth_style_register_type (GTypeModule *module)
{
  static const GTypeInfo object_info =
  {
    sizeof (SmoothStyleClass),
    (GBaseInitFunc) NULL,
    (GBaseFinalizeFunc) NULL,
    (GClassInitFunc) smooth_style_class_init,
    NULL,           /* class_finalize */
    NULL,           /* class_data */
    sizeof (SmoothStyle),
    0,              /* n_preallocs */
    (GInstanceInitFunc) NULL,
  };
  
  smooth_type_style = g_type_module_register_type (module,
							   GTK_TYPE_STYLE,
							   "SmoothStyle",
							   &object_info, 0);
}
#endif

#ifdef GTK1
static void draw_cross (GtkStyle * style,
			GdkWindow * window,
			GtkStateType state_type,
			GtkShadowType shadow_type,
			GdkRectangle * area,
			GtkWidget * widget,
			gchar * detail,
			gint x, gint y, gint width, gint height)
{}

static void draw_ramp (GtkStyle * style,
		       GdkWindow * window,
		       GtkStateType state_type,
		       GtkShadowType shadow_type,
		       GdkRectangle * area,
		       GtkWidget * widget,
		       gchar * detail,
		       GtkArrowType arrow_type,
		       gint x, gint y, gint width, gint height)
{}

static void
draw_tab(GtkStyle * style,
	 GdkWindow * window,
	 GtkStateType state_type,
	 GtkShadowType shadow_type,
	 GdkRectangle * area,
	 GtkWidget * widget,
	 detail_char * detail,
	 gint x,
	 gint y,
	 gint width,
	 gint height)
{
#define ARROW_SPACE 4

  GtkRequisition indicator_size;
  gint arrow_height,arrow_width;
  gboolean solid = SOLID_ARROW(style);
  GdkGC * border_gc = style->fg_gc[state_type], * fill_gc = style->fg_gc[state_type];
  gint alternate;
  
  g_return_if_fail(sanitize_parameters(style, window, &width, &height));
  
  alternate = ARROW_STYLE(style);

  if ((!solid))
    fill_gc = style->base_gc[state_type];
      
  arrow_height = height - 2;
  arrow_width = width - 2;
  x = widget->allocation.width - 20;
  y = 0;
  x += (19 - arrow_width) / 2;
  y += (widget->allocation.height - (2 * arrow_height + ARROW_SPACE)) / 2;

  if (state_type == GTK_STATE_INSENSITIVE)
    {
     solid=TRUE;
     border_gc = style->dark_gc[state_type];
     fill_gc = style->dark_gc[state_type];
     do_draw_arrow(window, area, GTK_ARROW_UP, style->light_gc[state_type], style->light_gc[state_type], x+1, y+1, arrow_width, arrow_height, alternate); 
     do_draw_arrow(window, area, GTK_ARROW_DOWN, style->light_gc[state_type], style->light_gc[state_type], x+1, y + arrow_height + ARROW_SPACE + 1, indicator_size.width, arrow_height, alternate); 
    }
  
  do_draw_arrow(window, area, GTK_ARROW_UP, fill_gc, border_gc, x, y, arrow_width, arrow_height, alternate); 
  do_draw_arrow(window, area, GTK_ARROW_DOWN, fill_gc, border_gc, x, y + arrow_height + ARROW_SPACE, arrow_width, arrow_height, alternate); 
}

static void draw_string (GtkStyle * style,
			 GdkWindow * window,
			 GtkStateType state_type,
			 GdkRectangle * area,
			 GtkWidget * widget,
			 detail_char * detail,
			 gint x, gint y, 
			 const gchar * string)
{
  g_return_if_fail(sanitize_parameters(style, window, NULL, NULL));
  if (area) {
    gdk_gc_set_clip_rectangle (style->light_gc[state_type], area);
    gdk_gc_set_clip_rectangle (style->dark_gc[state_type], area);
    gdk_gc_set_clip_rectangle (style->fg_gc[state_type], area);
  }
  if (state_type == GTK_STATE_INSENSITIVE) {
    gdk_draw_string (window, style->font, style->light_gc[state_type], x + 1, y + 1,
		     string);
    gdk_draw_string (window, style->font, style->dark_gc[state_type], x, y,
	  	    string);
  } else {
    gdk_draw_string (window, style->font, style->fg_gc[state_type], x, y,
		   string);
  }  
  if (area) {
    gdk_gc_set_clip_rectangle (style->light_gc[state_type], NULL);
    gdk_gc_set_clip_rectangle (style->dark_gc[state_type], NULL);
    gdk_gc_set_clip_rectangle (style->fg_gc[state_type], NULL);
  }
}
			

static void 
draw_flat_box (GtkStyle * style,
               GdkWindow * window,
	       GtkStateType state_type,
	       GtkShadowType shadow_type,
	       GdkRectangle * area,
	       GtkWidget * widget,
	       gchar * detail,
	       gint x, gint y, gint width, gint height)
{
   GdkGC *gc1;
 
   g_return_if_fail(sanitize_parameters(style, window, NULL, NULL));

   if (DETAIL("text") && (state_type == GTK_STATE_SELECTED))
     gc1 = style->bg_gc[state_type];
   else if (DETAIL("viewportbin"))
     gc1 = style->bg_gc[state_type];
   else if (DETAIL("entry_bg"))
     gc1 = style->base_gc[state_type];
   else 
     gc1 = style->bg_gc[state_type];
   
   if ((!style->bg_pixmap[state_type]) || (gc1 != style->bg_gc[state_type]) ||
     (gdk_window_get_type(window) == GDK_WINDOW_PIXMAP)) 
   {
     FLAT_FILL_BACKGROUND(style, window, state_type, area, widget, NULL, x, y, width, height);

     if (DETAIL("tooltip")) 
       gdk_draw_rectangle(window, style->black_gc, FALSE, x, y, width - 1, height - 1);
   } else {
     gtk_style_apply_default_background(style, window, widget && !GTK_WIDGET_NO_WINDOW(widget), 
       state_type, area, x, y, width, height);
   }
}

static void
draw_focus (GtkStyle * style,
	    GdkWindow * window,
	    GdkRectangle * area,
	    GtkWidget * widget,
	    detail_char * detail, 
	    gint x, 
	    gint y, 
	    gint width, 
	    gint height)
{
  GdkGC *gc;
  gint8 dashes[] = { 1, 1 };

  g_return_if_fail(sanitize_parameters(style, window, &width, &height));

  gc = gdk_gc_new (window);
  gdk_gc_copy (gc, style->black_gc);
  gdk_gc_set_line_attributes (gc, 1, GDK_LINE_ON_OFF_DASH, GDK_CAP_NOT_LAST,
			      GDK_JOIN_MITER);
  gdk_gc_set_dashes (gc, 0, dashes, 2);
  if (area) {
    gdk_gc_set_clip_rectangle (gc, area);
  }
  gdk_draw_rectangle (window, gc, FALSE, x, y, width-1, height-1);
  if (area) {
    gdk_gc_set_clip_rectangle (gc, NULL);
  }
  gdk_gc_destroy (gc);
}

GtkStyleClass smooth_default_class = {
  2,
  2,
  draw_hline,
  draw_vline,
  draw_shadow,
  draw_polygon,
  draw_arrow,
  draw_diamond,
  draw_oval,
  draw_string,
  draw_box,
  draw_flat_box,
  draw_check,
  draw_option,
  draw_cross,
  draw_ramp,
  draw_tab,
  draw_shadow_gap,
  draw_box_gap,
  draw_extension,
  draw_focus,
  draw_slider,
  draw_handle
};
#endif
