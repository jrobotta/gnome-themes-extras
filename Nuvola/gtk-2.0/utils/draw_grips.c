#include "draw_grips.h"

/* This function is taken for the most part from Xenophilia */
void 
do_draw_lines(GdkWindow * window,
             GdkRectangle * area,
             GdkGC * light_gc,
   	     GdkGC * dark_gc,
   	     GdkGC * mid_gc,
	     gint x,
	     gint y,
             gint width,
	     gint height,	     
	     GtkOrientation orientation,
	     gboolean invert)
{
  gint	i;
  GdkGC * light=(invert?dark_gc:light_gc),* dark=(invert?light_gc:dark_gc), * mid=mid_gc;


	if (area) {
		gdk_gc_set_clip_rectangle (light, area);
		gdk_gc_set_clip_rectangle (dark, area);
		gdk_gc_set_clip_rectangle (mid, area);
	}
	
	if (orientation == GTK_ORIENTATION_HORIZONTAL) {
		for (i = y + ((height % 3) & 0x01); i < y + height; i += 3) {
			gdk_draw_line  (window, light,	x,			i,		x+width-2,	i  );
			gdk_draw_line  (window, dark,	x+1, 		i+1,	x+width-1,	i+1);
			gdk_draw_point (window, mid,		x,			i+1);
			gdk_draw_point (window, mid,		x+width-1,	i);
		}
	} else {
		for (i = x + ((width % 3) & 0x01); i < x + width; i += 3) {
			gdk_draw_line  (window, light,	i,		y,   	i,   y+height-2);
			gdk_draw_line  (window, dark,	i+1,	y+1, 	i+1, y+height-1);
			gdk_draw_point (window, mid,		i+1,	y);
			gdk_draw_point (window, mid,		i,		y+height-1);
		}
	}
	
	if (area) {
		gdk_gc_set_clip_rectangle (mid, NULL);
		gdk_gc_set_clip_rectangle (dark, NULL);
		gdk_gc_set_clip_rectangle (light, NULL);
	}
}

/* This function is based for the most part on XFCE (xfce_draw_handlers), and EnGradient*/
void
do_draw_fixed_midlines(GdkWindow * window, 
                    GdkRectangle * area, 
		    GdkGC * light_gc,
   	            GdkGC * dark_gc,
		    gint x, 
		    gint y, 
		    gint width, 
		    gint height, 
		    GtkOrientation orientation,
		    gint count,
		    gint spacing,
		    gboolean invert,
		    gboolean diagonal,
		    gboolean bar)
{
  gint i,offset;
  gint centerx=(orientation==GTK_ORIENTATION_HORIZONTAL?(width/2) + x:(width/2) + x);
  gint centery=(orientation==GTK_ORIENTATION_HORIZONTAL?(height/2) + y:(height/2) + y);
  
  gint thick=((orientation==GTK_ORIENTATION_HORIZONTAL?height:width) >> 1)-2;
  gfloat delta_offset = (count < 2)?0:((count - 1)*spacing/2) + (count) - 1 ;
  gint delta=((orientation==GTK_ORIENTATION_HORIZONTAL?centerx-1:centery-1)) - delta_offset;

  GdkGC *light=light_gc,*dark=dark_gc;

  if (invert) {light=dark_gc;dark=light_gc;}
  
  gdk_gc_set_clip_rectangle (light, area);
  gdk_gc_set_clip_rectangle (dark, area);
  

  for (i = 0, offset = delta; (i < count); offset += (spacing + 2), i++)
  {
     gint xthick = thick, ythick = thick;
     if ((((bar) && (!diagonal)) && (orientation != GTK_ORIENTATION_HORIZONTAL)) || (orientation == GTK_ORIENTATION_HORIZONTAL)) {
       if  (!diagonal) xthick = 0;
       gdk_draw_line (window, dark, 
          offset + xthick, centery - ythick, 
	  offset - xthick, centery + ythick);
       gdk_draw_line (window, light, 
          offset + xthick + 1, centery - ythick, 
	  offset - xthick + 1, centery + ythick);
     } else {
       if  (!diagonal) ythick = 0;
       gdk_draw_line (window, dark, 
          centerx - xthick, offset + ythick, 
	  centerx + xthick, offset - ythick);
       gdk_draw_line (window, light, 
          centerx - xthick, offset + ythick + 1, 
	  centerx + xthick, offset - ythick + 1);
     }
  }
  
  gdk_gc_set_clip_rectangle (light, NULL);
  gdk_gc_set_clip_rectangle (dark, NULL);
}

/* This function is taken for the most part from CleanIce */
void
do_draw_fixed_dots(GdkWindow * window, 
                    GdkRectangle * area, 
		    GdkGC * light_gc,
   	            GdkGC * dark_gc,
   	            GdkGC * mid_gc,
		    gint x, 
		    gint y, 
		    gint width, 
		    gint height, 
		    GtkOrientation orientation,
		    gint count,
		    gint spacing,
		    gboolean small)
{
  gint i, size=(small?2:3);
  gint centerx=(orientation==GTK_ORIENTATION_HORIZONTAL?(width/2) + x:(width/2) + x);
  gint centery=(orientation==GTK_ORIENTATION_HORIZONTAL?(height/2) + y:(height/2) + y);
  gfloat delta_offset = (count < 2)?0:((count - 1)*spacing/2) + (count*size/2) - ((count%2)?(size%2):(size%2) + 1);
  gint delta=(orientation==GTK_ORIENTATION_HORIZONTAL?centerx:centery) - delta_offset;
  
   if (area) {
     gdk_gc_set_clip_rectangle (dark_gc, area);
     gdk_gc_set_clip_rectangle (light_gc, area);
     gdk_gc_set_clip_rectangle (mid_gc, area);
   }

  for (i=0; i < count*(spacing + size); i += (spacing + size))
  {
    gint dot_x, dot_y; 
    
    if (orientation == GTK_ORIENTATION_HORIZONTAL) {
      dot_x = i + delta;
      dot_y = centery;
    } else {
      dot_x = centerx;
      dot_y = i + delta;
    }

    if (small) {
      gdk_draw_point(window, light_gc, dot_x, dot_y);
      gdk_draw_point(window, dark_gc, dot_x+1, dot_y+1);

      gdk_draw_point(window, mid_gc, dot_x+1, dot_y);
      gdk_draw_point(window, mid_gc, dot_x, dot_y+1);
    } else {
      GdkPoint points[3];
      points[0].x = dot_x-1; points[0].y = dot_y;
      points[1].x = dot_x-1; points[1].y = dot_y-1;
      points[2].x = dot_x;   points[2].y = dot_y-1;

      gdk_draw_points(window, light_gc, points, 3);

      points[0].x = dot_x+1; points[0].y = dot_y;
      points[1].x = dot_x+1; points[1].y = dot_y+1;
      points[2].x = dot_x;   points[2].y = dot_y+1;

      gdk_draw_points(window, dark_gc, points, 3);

      gdk_draw_point(window, mid_gc, dot_x+1, dot_y-1);
      gdk_draw_point(window, mid_gc, dot_x-1, dot_y+1);
    }   
  }
  
   if (area) {
     gdk_gc_set_clip_rectangle (mid_gc, NULL);
     gdk_gc_set_clip_rectangle (light_gc, NULL);
     gdk_gc_set_clip_rectangle (dark_gc, NULL);
   }
}

/* This function is taken for the most part from Xenophilia */
void 
do_draw_buds(GdkWindow * window,
             GdkRectangle * area,
             GdkGC * light_gc,
   	     GdkGC * dark_gc,
   	     GdkGC * mid_gc,
	     gint x,
	     gint y,
             gint width,
	     gint height,
	     GtkOrientation orientation,
	     gboolean ns)
{
   gint	x2, y2;
   
   if (area) {
     gdk_gc_set_clip_rectangle (dark_gc, area);
     gdk_gc_set_clip_rectangle (light_gc, area);
     gdk_gc_set_clip_rectangle (mid_gc, area);
   }
       
   if (orientation == GTK_ORIENTATION_VERTICAL && ns) {
     x -= (width % 2) & 0x01;
     y -= (height% 2) & 0x01;
     /* netscape - style */
     for (y2 = y+1; y2 < y+height-1; y2 += 3) {
       for (x2 = x; x2 < x+width-1; x2 += 6) {
         gdk_draw_point (window, light_gc,x2,y2);
         gdk_draw_point (window, dark_gc,x2 + 1, y2 + 1);
         gdk_draw_point (window, mid_gc,x2 + 1,y2);
         gdk_draw_point (window, mid_gc,x2,y2 + 1);
       }
     }
     for (y2 = y; y2 < y+height-1; y2 += 3) {
       for (x2 = x+3; x2 < x+width-1; x2 += 6) {
         gdk_draw_point (window, light_gc, x2,y2);
         gdk_draw_point (window, dark_gc, x2 + 1, y2 + 1);
         gdk_draw_point (window, mid_gc,x2 + 1,y2);
         gdk_draw_point (window, mid_gc,x2,y2 + 1);
       }
     }
   } else {
     /* mac - style */
     x += (width % 3) & 0x01;
     y += (height% 3) & 0x01;
      
     for (y2 = y; y2 < y+height-1; y2 += 3) {
       for (x2 = x; x2 < x+width-1; x2 += 3) {
         gdk_draw_point (window, light_gc,x2,y2);
         gdk_draw_point (window, mid_gc,x2+1,y2);
         gdk_draw_point (window, mid_gc,x2,y2+1);
         gdk_draw_point (window, dark_gc,x2+1,y2+1);
       }
     }
   }
       
   if (area) {
     gdk_gc_set_clip_rectangle (mid_gc, NULL);
     gdk_gc_set_clip_rectangle (light_gc, NULL);
     gdk_gc_set_clip_rectangle (dark_gc, NULL);
   }
}

gboolean 
TranslateGripStyleName (gchar * str, gint *retval)
{
#define is_enum(XX)  (g_ascii_strncasecmp(str, XX, strlen(XX))==0)
  if (is_enum("none"))
    *retval = NO_GRIP;

  else if (is_enum("bars_in"))
    *retval = BARS_IN_GRIP;
  else if (is_enum("bars") || is_enum("bars_out"))
    *retval = BARS_OUT_GRIP;

  else if (is_enum("lines_in"))
    *retval = LINES_IN_GRIP;
  else if (is_enum("lines") || is_enum("lines_out"))
    *retval = LINES_OUT_GRIP;

  else if (is_enum("fixedlines_out"))
    *retval = FIXEDLINES_OUT_GRIP;
  else if (is_enum("midlines") || is_enum("fixedlines") || is_enum("fixedlines_in"))
    *retval = FIXEDLINES_IN_GRIP;

  else if (is_enum("slashes"))
    *retval = SLASHES_GRIP;

  else if (is_enum("mac_buds_out"))
    *retval = MAC_BUDS_OUT_GRIP;
  else if (is_enum("mac_buds") || is_enum("mac_buds_in"))
    *retval = MAC_BUDS_IN_GRIP;

  else if (is_enum("buds_out") || is_enum("ns_buds_out"))
    *retval = NS_BUDS_OUT_GRIP;
  else if (is_enum("buds") || is_enum("buds_in") || is_enum("ns_buds") || is_enum("ns_buds_in"))
    *retval = NS_BUDS_IN_GRIP;

  else if (is_enum("smalldots_out"))
    *retval = SMALLDOTS_OUT_GRIP;
  else if (is_enum("smalldots") || is_enum("smalldots_in"))
    *retval = SMALLDOTS_IN_GRIP;

  else if (is_enum("dots_out"))
    *retval = DOTS_OUT_GRIP;
  else if (is_enum("dots") || is_enum("dots_in"))
    *retval = DOTS_IN_GRIP;

  else if (is_enum("xpm"))
    *retval = XPM_GRIP;
  else
    return FALSE; 

  return TRUE;
}
