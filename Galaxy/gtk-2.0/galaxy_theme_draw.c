/*  galaxy
 *  Copyright (C) 2003 Frederic Crozat - MandrakeSoft
 *                1999 Olivier Fourdan (fourdan@xfce.org) for XFCE code
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <math.h>
#include <gtk/gtk.h>
#include <string.h>

#include "galaxy_style.h"
#include "galaxy_rc_style.h"

#define DETAIL(s)   ((detail) && (!strcmp(s, detail)))


/* 
  Port to GTK+-2.0 based on Thinice port by Tim Gerla <timg@rrv.net>
      Tomas Ögren <stric@ing.umu.se> and  Richard Hult <rhult@codefactory.se>
  Portions based on BlueCurve by Alexander Larsson
  Portions based on Raleigh theme by Owen Taylor
  Portions based on Notif theme
  Portions based on Notif2 theme
  Portions based on original GTK theme
 */

static GtkStyleClass *parent_class;

#define RADIO_SIZE 13
#define PART_SIZE 13
#define SCALE_SIZE 5

static const guchar check_cross_bits[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x03, 0xb8, 0x03, 0xf0, 0x01,
    0xe0, 0x00, 0xf0, 0x01, 0xb8, 0x03, 0x18, 0x03, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00,
};

static const guchar menu_check_bits[] = {
  0x00,0x00,0x00,0x04,0x00,0x06,0x00,0x07,0x84,0x07,0xcc,0x03,0xfc,0x01,0xfc,
  0x00,0x78,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00};


static unsigned char dot_intensity[] = {
0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,
0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,
0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,
0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,
0x6e,0x6e,0x6e,0x6e,0x78,0x99,0xa6,0x99,0x71,0x6e,0x6e,0x6e,0x6e,
0x6e,0x6e,0x6e,0x6e,0x99,0x9d,0x7c,0x6e,0x55,0x6e,0x6e,0x6e,0x6e,
0x6e,0x6e,0x6e,0x6e,0xa6,0x7c,0x6e,0x66,0x4c,0x6e,0x6e,0x6e,0x6e,
0x6e,0x6e,0x6e,0x6e,0x99,0x6e,0x66,0x52,0x55,0x6e,0x6e,0x6e,0x6e,
0x6e,0x6e,0x6e,0x6e,0x71,0x55,0x4c,0x55,0x68,0x6e,0x6e,0x6e,0x6e,
0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,
0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,
0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,
0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,
};
static unsigned char dot_alpha[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x66,0xd4,0xff,0xd4,0x66,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x66,0xff,0xff,0xff,0xff,0xff,0x66,0x00,0x00,0x00,
0x00,0x00,0x00,0xd4,0xff,0xff,0xff,0xff,0xff,0xd4,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0xd4,0xff,0xff,0xff,0xff,0xff,0xd4,0x00,0x00,0x00,
0x00,0x00,0x00,0x66,0xff,0xff,0xff,0xff,0xff,0x66,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x66,0xd4,0xff,0xd4,0x66,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

static unsigned char circle_alpha[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x23,0x62,0x92,0xb3,0xb2,0x95,0x2b,0x00,0x00,0x00,
0x00,0x00,0x3e,0xab,0xc9,0xeb,0xf9,0xf5,0xfd,0xff,0x57,0x00,0x00,
0x00,0x1f,0xb5,0xd8,0xfc,0xff,0xff,0xff,0xff,0xff,0xff,0x2b,0x00,
0x00,0x67,0xb9,0xf2,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x9c,0x00,
0x00,0x9a,0xe2,0xfc,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe5,0x00,
0x00,0xba,0xeb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,
0x00,0xc0,0xfa,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe5,0x00,
0x00,0x9b,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x9c,0x00,
0x00,0x2b,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x2b,0x00,
0x00,0x00,0x57,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x57,0x00,0x00,
0x00,0x00,0x00,0x2b,0x9c,0xe5,0xff,0xe5,0x9c,0x2b,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};
static unsigned char outline_alpha[] = {
0x00,0x00,0x00,0x4a,0xac,0xe9,0xff,0xe9,0xac,0x4a,0x00,0x00,0x00,
0x00,0x00,0x98,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x98,0x00,0x00,
0x00,0x98,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x98,0x00,
0x4a,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x4a,
0xac,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xac,
0xe9,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe9,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xe9,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe9,
0xac,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xac,
0x4a,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x4a,
0x00,0x98,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x98,0x00,
0x00,0x00,0x98,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x98,0x00,0x00,
0x00,0x00,0x00,0x4a,0xac,0xe9,0xff,0xe9,0xac,0x4a,0x00,0x00,0x00,
};
static unsigned char inconsistent_alpha[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

/* internal functions */
static void draw_hline(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x1, gint x2, gint y);
static void draw_vline(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint y1, gint y2, gint x);
static void draw_shadow(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height);

static void draw_polygon(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, GdkPoint * point, gint npoints, gint fill);
static void draw_diamond(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height);
static void draw_box(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height);
static void draw_check(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height);
static void draw_option(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height);
static void draw_shadow_gap(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height, GtkPositionType gap_side, gint gap_x, gint gap_width);
static void draw_box_gap(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height, GtkPositionType gap_side, gint gap_x, gint gap_width);
static void draw_extension(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height, GtkPositionType gap_side);
static void draw_slider(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height, GtkOrientation orientation);
static void draw_handle(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height, GtkOrientation orientation);


static gboolean 
sanitize_size (GdkWindow      *window,
	       gint           *width,
	       gint           *height)
{
  gboolean set_bg = FALSE;

  if ((*width == -1) && (*height == -1))
    {
      set_bg = GDK_IS_WINDOW (window);
      gdk_drawable_get_size (window, width, height);
    }
  else if (*width == -1)
    gdk_drawable_get_size (window, width, NULL);
  else if (*height == -1)
    gdk_drawable_get_size (window, NULL, height);

  return set_bg;
}


static GdkPixbuf *
generate_bit (unsigned char alpha[], GdkColor *color, double mult)
{
  guint r, g, b;
  GdkPixbuf *pixbuf;
  unsigned char *pixels;
  int w, h, rs;
  int x, y;
  
  r = (color->red >> 8) * mult;
  r = MIN(r, 255);
  g = (color->green >> 8) * mult;
  g = MIN(g, 255);
  b = (color->blue >> 8) * mult;
  b = MIN(b, 255);

  pixbuf = gdk_pixbuf_new (GDK_COLORSPACE_RGB, TRUE, 8, RADIO_SIZE, RADIO_SIZE);

  w = gdk_pixbuf_get_width (pixbuf);
  h = gdk_pixbuf_get_height (pixbuf);
  rs = gdk_pixbuf_get_rowstride (pixbuf);
  pixels = gdk_pixbuf_get_pixels (pixbuf);


  for (y=0; y < h; y++)
    {
      for (x=0; x < w; x++)
	{
	  pixels[y*rs + x*4 + 0] = r;
	  pixels[y*rs + x*4 + 1] = g;
	  pixels[y*rs + x*4 + 2] = b;
	  if (alpha)
	    pixels[y*rs + x*4 + 3] = alpha[y*w + x];
	  else
	    pixels[y*rs + x*4 + 3] = 255;
	}
    }

  return pixbuf;
}

#define CLAMP_UCHAR(v) ((guchar) (CLAMP (((int)v), (int)0, (int)255)))

static GdkPixbuf *
colorize_bit (unsigned char *bit,
	      unsigned char *alpha,
	      GdkColor  *new_color)
{
  GdkPixbuf *pixbuf;
  double intensity;
  int x, y;
  const guchar *src, *asrc;
  guchar *dest;
  int dest_rowstride;
  int width, height;
  guchar *dest_pixels;
  
  pixbuf = gdk_pixbuf_new (GDK_COLORSPACE_RGB, TRUE, 8,
			   RADIO_SIZE, RADIO_SIZE);

  if (pixbuf == NULL)
    return NULL;
  
  dest_rowstride = gdk_pixbuf_get_rowstride (pixbuf);
  width = gdk_pixbuf_get_width (pixbuf);
  height = gdk_pixbuf_get_height (pixbuf);
  dest_pixels = gdk_pixbuf_get_pixels (pixbuf);
  
  for (y = 0; y < RADIO_SIZE; y++)
    {
      src = bit + y * RADIO_SIZE;
      asrc = alpha + y * RADIO_SIZE;
      dest = dest_pixels + y * dest_rowstride;

      for (x = 0; x < RADIO_SIZE; x++)
        {
          double dr, dg, db;
          
          intensity = (src[x] + 0 )/ 255.0;

          if (intensity <= 0.5)
            {
              /* Go from black at intensity = 0.0 to new_color at intensity = 0.5 */
              dr = (new_color->red * intensity * 2.0) / 65535.0;
              dg = (new_color->green * intensity * 2.0) / 65535.0;
              db = (new_color->blue * intensity * 2.0) / 65535.0;
            }
          else
            {
              /* Go from new_color at intensity = 0.5 to white at intensity = 1.0 */
              dr = (new_color->red + (65535 - new_color->red) * (intensity - 0.5) * 2.0) / 65535.0;
              dg = (new_color->green + (65535 - new_color->green) * (intensity - 0.5) * 2.0) / 65535.0;
              db = (new_color->blue + (65535 - new_color->blue) * (intensity - 0.5) * 2.0) / 65535.0;
            }
          
          dest[0] = CLAMP_UCHAR (255 * dr);
          dest[1] = CLAMP_UCHAR (255 * dg);
          dest[2] = CLAMP_UCHAR (255 * db);

	  dest[3] = asrc[x];
	  dest += 4;
        }
    }

  return pixbuf;
}


static GtkRequisition default_option_indicator_size = { 7, 13 };
static GtkBorder default_option_indicator_spacing = { 7, 5, 2, 2 };

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
draw_vgradient (GdkDrawable *drawable, GdkGC *gc, GdkColormap *colormap,
		int x, int y, int width, int height,
		GdkColor *top_color, GdkColor *bottom_color)
{
  int i;
  GdkColor col;
  int dr, dg, db;
  GdkGCValues old_values;

  if (height == 0) {
  	return;
  }

  col = *top_color;
  dr = (bottom_color->red - top_color->red) / height;
  dg = (bottom_color->green - top_color->green) / height;
  db = (bottom_color->blue - top_color->blue) / height;
  
  gdk_gc_get_values (gc, &old_values);
  
  for (i = 0; i < height; i++)
    {
      gdk_rgb_find_color (colormap,
			  &col);
      
      gdk_gc_set_foreground (gc, &col);
      gdk_draw_line (drawable, gc,
		     x, y + i,
		     x + width - 1, y + i);
					   
      col.red += dr;
      col.green += dg;
      col.blue += db;
    }

  gdk_gc_set_foreground (gc, &old_values.foreground);
}


static void
draw_hgradient (GdkDrawable *drawable, GdkGC *gc, GdkColormap *colormap,
		int x, int y, int width, int height,
		GdkColor *left_color, GdkColor *right_color)
{
  int i;
  GdkColor col;
  int dr, dg, db;
  GdkGCValues old_values;

  col = *left_color;
  dr = (right_color->red - left_color->red) / width;
  dg = (right_color->green - left_color->green) / width;
  db = (right_color->blue - left_color->blue) / width;
  
  gdk_gc_get_values (gc, &old_values);
  
  for (i = 0; i < width; i++)
    {
      gdk_rgb_find_color (colormap,
			  &col);
      
      gdk_gc_set_foreground (gc, &col);
      gdk_draw_line (drawable, gc,
		     x + i, y,
		     x + i, y + height - 1);
					   
      col.red += dr;
      col.green += dg;
      col.blue += db;
    }

  gdk_gc_set_foreground (gc, &old_values.foreground);
}

static void galaxy_draw_point (GalaxyStyle * galaxy_style, GdkWindow * window, gint x, gint y) {

    gdk_draw_point(window, galaxy_style->gray_gc[7],x+1,y);
    gdk_draw_point(window, galaxy_style->gray_gc[7],x+2,y);
    gdk_draw_point(window, galaxy_style->gray_gc[7],x,y+1);
    gdk_draw_point(window, galaxy_style->gray_gc[7],x+1,y+1);
    
    gdk_draw_point(window, galaxy_style->gray_gc[4],x+2,y+1);
    gdk_draw_point(window, galaxy_style->gray_gc[4],x+3,y+1);
    gdk_draw_point(window, galaxy_style->gray_gc[4],x+1,y+2);
    
    gdk_draw_point(window, galaxy_style->gray_gc[2],x,y+2);
    gdk_draw_point(window, galaxy_style->gray_gc[2],x+1,y+3);
    gdk_draw_point(window, galaxy_style->gray_gc[2],x+3,y+3);
    
    gdk_draw_point(window, galaxy_style->gray_gc[0],x+2,y+2);
    gdk_draw_point(window, galaxy_style->gray_gc[0],x+2,y+3); 
}

static void galaxy_draw_handlers(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GdkRectangle * area, GtkWidget * widget, gint x, gint y, gint width, gint height, GtkOrientation orientation)
{
    GalaxyStyle *galaxy_style = GALAXY_STYLE (style);

    int i;
    int delta;
    gint xthick, ythick;
    GdkRectangle dest;

    sanitize_size (window, &width, &height);

    xthick = style->xthickness;
    ythick = style->ythickness;

    if (widget && GTK_IS_PANED (widget)) {
      /* we want to ignore the shadow border in paned widgets */
      xthick = 0;
      ythick = 0;
    }

    dest.x = x + xthick;
    dest.y = y + ythick;
    dest.width = width - (xthick * 2);
    dest.height = height - (ythick * 2);

    gdk_gc_set_clip_rectangle(galaxy_style->gray_gc[7], &dest);
    gdk_gc_set_clip_rectangle(galaxy_style->gray_gc[4], &dest);
    gdk_gc_set_clip_rectangle(galaxy_style->gray_gc[2], &dest);
    gdk_gc_set_clip_rectangle(galaxy_style->gray_gc[0], &dest);

    if(orientation == GTK_ORIENTATION_HORIZONTAL) {
        if(width > 30)
        {
            delta = x + (width/2) - 11;
            for(i = 0; i < 3; i++) {
	      galaxy_draw_point (galaxy_style, window, delta + 9*i,
				 y + MAX((height-4)/2,0));
            }
        }
	else {
	  galaxy_draw_point (galaxy_style, window,  x + (width-4)/2,
				 y + MAX((height-4)/2,0));
	}
    }
    else {
        if(height > 30) {
	  delta = y + (height / 2) - 11;
            for(i = 0; i < 3; i++) {
	      galaxy_draw_point (galaxy_style, window, x + MAX((width-4)/2,0), 
				 delta+9*i);
            }
        }
	else {
	  galaxy_draw_point (galaxy_style, window, x + MAX((width-4)/2,0), 
			      y + (height-4) / 2);
	}
    }
    gdk_gc_set_clip_rectangle(galaxy_style->gray_gc[7], NULL);
    gdk_gc_set_clip_rectangle(galaxy_style->gray_gc[4], NULL);
    gdk_gc_set_clip_rectangle(galaxy_style->gray_gc[2], NULL);
    gdk_gc_set_clip_rectangle(galaxy_style->gray_gc[0], NULL);
}

static void draw_hline(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x1, gint x2, gint y)
{
    GalaxyStyle *galaxy_style = GALAXY_STYLE (style);

    g_return_if_fail(style != NULL);
    g_return_if_fail(window != NULL);

    if(area)
    {
        gdk_gc_set_clip_rectangle(galaxy_style->gray_gc[2], area);
        gdk_gc_set_clip_rectangle(style->white_gc, area);
    }

    gdk_draw_line(window, galaxy_style->gray_gc[2], x1, y, x2, y);
    gdk_draw_line(window, style->white_gc, x1, y + 1, x2, y+1);

    if(area)
    {
        gdk_gc_set_clip_rectangle(galaxy_style->gray_gc[2], NULL);
        gdk_gc_set_clip_rectangle(style->white_gc, NULL);
    }
}

static void draw_vline(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint y1, gint y2, gint x)
{
    GalaxyStyle *galaxy_style = GALAXY_STYLE (style);

    g_return_if_fail(style != NULL);
    g_return_if_fail(window != NULL);

    if(area)
    {
        gdk_gc_set_clip_rectangle(galaxy_style->gray_gc[2], area);
        gdk_gc_set_clip_rectangle(style->white_gc, area);
    }

    gdk_draw_line(window, galaxy_style->gray_gc[2], x, y1, x, y2);
    gdk_draw_line(window, style->white_gc, x+1, y1, x+1, y2);

    if(area)
    {
        gdk_gc_set_clip_rectangle(galaxy_style->gray_gc[2], NULL);
        gdk_gc_set_clip_rectangle(style->white_gc, NULL);
    }
}

static void draw_shadow(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height)
{
  GalaxyStyle *galaxy_style = GALAXY_STYLE (style);
  GdkGC *gc1, *gc2;
  int xthick, ythick;
  gboolean is_combo_button;

    g_return_if_fail(style != NULL);
    g_return_if_fail(window != NULL);

    if (shadow_type == GTK_SHADOW_NONE) {
      return;
    }
    xthick = style->xthickness;
    ythick = style->ythickness;

    sanitize_size (window, &width, &height);

    if(area)
    { 
        gdk_gc_set_clip_rectangle(style->bg_gc[GTK_STATE_NORMAL], area);
	gdk_gc_set_clip_rectangle (style->white_gc, area);
	gdk_gc_set_clip_rectangle (galaxy_style->gray_gc[0], area);
	gdk_gc_set_clip_rectangle (galaxy_style->gray_gc[1], area);
	gdk_gc_set_clip_rectangle (galaxy_style->gray_gc[2], area);
	gdk_gc_set_clip_rectangle (galaxy_style->gray_gc[3], area);
	gdk_gc_set_clip_rectangle (galaxy_style->gray_gc[4], area);
	gdk_gc_set_clip_rectangle (galaxy_style->gray_gc[5], area);
	gdk_gc_set_clip_rectangle (galaxy_style->gray_gc[7], area);
    }

    if (is_combo_button = (DETAIL("button") && 
			   GTK_IS_COMBO(gtk_widget_get_parent(widget)))) {
      xthick = ythick = 1;
    }

    if ((DETAIL ("button") ||
	(DETAIL ("togglebutton")) ||
	(DETAIL ("buttondefault")) ||
	 (DETAIL ("optionmenu")))
	&& GALAXY_RC_STYLE(style->rc_style)->enable_gradient
	&& (xthick >= 3)
	&& (ythick >= 3)) /* Button, Combobox */
      {
	int color1;
	switch (shadow_type) {
	case GTK_SHADOW_IN:
	  color1 = 7;
	  break;
	case GTK_SHADOW_OUT:
	  color1 = 5;
	  break;
	default:
	  color1 = 0;
	}

	if (color1 != 0) {
	  gdk_draw_point (window, galaxy_style->gray_gc[color1],x+3,y+3);
	  gdk_draw_line (window, galaxy_style->gray_gc[color1], x+4,y+2,x+width-5,y+2);
	  gdk_draw_line (window,galaxy_style->gray_gc[color1], x+2,y+4,x+2,y+height-5);
	
	  gdk_draw_point (window, galaxy_style->gray_gc[5], x+width-4, y+3);
	  gdk_draw_line (window,galaxy_style->gray_gc[5], x+width-3,y+4,x+width-3,y+height-5);
	  gdk_draw_point (window, galaxy_style->gray_gc[5], x+width-4, y+height-4);
	  gdk_draw_line (window,galaxy_style->gray_gc[5], x+4,y+height-3,x+width-5,y+height-3);
	  gdk_draw_point (window, galaxy_style->gray_gc[5], x+3, y+height-4);	  

	}	
      }


    if ((shadow_type == GTK_SHADOW_ETCHED_IN) || 
	(shadow_type == GTK_SHADOW_ETCHED_OUT)) {
      if (shadow_type == GTK_SHADOW_ETCHED_IN) {
	gc1 = galaxy_style->gray_gc[5];
	gc2 = style->white_gc;
      }
      else { /*GTK_SHADOW_ETCHED_OUT */
	gc2 = galaxy_style->gray_gc[5];
	gc1 = style->white_gc;
      }
      gdk_draw_line (window, gc1, x,y,x+width-2,y);
      gdk_draw_line (window, gc1, x,y+1,x,y+height-2);
      gdk_draw_line (window, gc1, x+width-2,y+1,x+width-2,y+height-2);
      gdk_draw_line (window, gc1, x+1,y+height-2,x+width-3,y+height-2);
      
      gdk_draw_line (window, gc2, x+1,y+1,x+width-3,y+1);
      gdk_draw_line (window, gc2, x+width-1,y,x+width-1,y+height-1);
      gdk_draw_line (window, gc2, x,y+height-1,x+width-1,y+height-1);
      gdk_draw_line (window, gc2, x+1,y+2,x+1,y+height-3);
    }

    if (detail && 
	(strncmp("spinbutton",detail,strlen("spinbutton")) == 0))
      {
	if (DETAIL ("spinbutton_up") || DETAIL("spinbutton_down")) {
	  gdk_draw_rectangle (window, galaxy_style->gray_gc[5],FALSE,
			      x,y,width-1,height-1);
	} else { /* spinbutton */
	  gdk_draw_line(window, galaxy_style->gray_gc[2], x, y, x + width - 1, y);
	  
	  gdk_draw_line(window, style->white_gc, x + width-1, y + 1, x + width - 1, y + height-1);
	  gdk_draw_line(window, style->white_gc, x, y + height-1, x + width-1, y + height - 1);
	  if (gtk_widget_get_direction (widget) == GTK_TEXT_DIR_RTL) {
	    gdk_draw_line (window, galaxy_style->gray_gc[2], x,y,x,y+height-2);
	  }
	}
      }
    else {
    
    switch (shadow_type) {
        case GTK_SHADOW_IN:
	  if (is_combo_button) {
	     gdk_draw_rectangle (window, galaxy_style->gray_gc[5],FALSE,
				x+1,y+1,width-3,height-3);
	      if (gtk_widget_get_direction (widget) == GTK_TEXT_DIR_LTR) {
		gdk_draw_line (window, style->white_gc,x,y+2,x,y+height-2);
		gdk_draw_point (window, galaxy_style->gray_gc[5],x,y+1);
		gdk_draw_line (window, style->white_gc,x+width-1,y+1,x+width-1,y+height-1);
		gdk_draw_line (window, galaxy_style->gray_gc[2],x,y,x+width-1,y);
		gdk_draw_point (window, galaxy_style->gray_gc[0],x,y+height-2);
		gdk_draw_line (window, style->white_gc,x+width-1,y,x+width-1,y+height-1);
		gdk_draw_line (window, style->white_gc,x,y+height-1,x+width-1,y+height-1);
	      }
	      else {
		gdk_draw_line (window, style->white_gc,x+width-1,y+2,x+width-1,y+height-3);
		gdk_draw_point (window, galaxy_style->gray_gc[5],x+width-1,y+1);
		gdk_draw_point (window, galaxy_style->gray_gc[0],x+width-1,y+height-2);
		gdk_draw_line (window, style->white_gc,x,y+height-1,x+width-1,y+height-1);
		gdk_draw_line (window, galaxy_style->gray_gc[2],x,y,x+width-1,y);
		gdk_draw_line (window, galaxy_style->gray_gc[2],x,y+1,x,y+height-1);
	      }
	  } else
	  if (DETAIL ("button") ||
	      DETAIL ("togglebutton") || 
	      DETAIL ("buttondefault") ||
	      DETAIL ("optionmenu")) {
	    if ((xthick>=3) &&
		(ythick>=3) && GALAXY_RC_STYLE(style->rc_style)->enable_gradient) {
	    /* white */
	    gdk_draw_line (window, style->white_gc, x+width-4,y+4,x+width-4,y+height-5);
	    gdk_draw_line (window, style->white_gc, x+4,y+height-4,x+width-5,y+height-4);
	    /* grey 3 */
	    gdk_draw_line (window, galaxy_style->gray_gc[3],x+4,y+1,x+width-6,y+1);
	    gdk_draw_point (window,galaxy_style->gray_gc[3],x+3,y+2);
	    gdk_draw_point (window,galaxy_style->gray_gc[3],x+2,y+3);
	    gdk_draw_line (window, galaxy_style->gray_gc[3],x+1,y+4,x+1,y+height-6);

	    /* grey 2 */

	    gdk_draw_point (window,galaxy_style->gray_gc[2],x+1,y+height-5);
	    gdk_draw_point (window,galaxy_style->gray_gc[2],x+width-5,y+1);
	    gdk_draw_point (window,galaxy_style->gray_gc[2],x+3,y+1);
	    gdk_draw_point (window,galaxy_style->gray_gc[2],x+2,y+2);
	    gdk_draw_point (window,galaxy_style->gray_gc[2],x+1,y+3);

	    }
	    else if ((xthick == 1) && (ythick == 1)) {
	      gdk_draw_rectangle (window, galaxy_style->gray_gc[7],FALSE,
				  x,y,width-1,height-1);	     
	      gdk_draw_line (window, style->white_gc, x+1, y+1, x+width-2,y+1);
	      gdk_draw_line (window, style->white_gc, x+1, y+2, x+1,y+height-2);
	    } else {

	      gdk_draw_line(window, galaxy_style->gray_gc[3], x + 1, y, x + width - 2, y);
	      gdk_draw_line(window, galaxy_style->gray_gc[3], x, y + 1, x, y + height - 2);
	      
	      gdk_draw_line(window, galaxy_style->gray_gc[5], x + 1, y + height - 1, x + width - 2, y + height - 1);
	      gdk_draw_line(window, galaxy_style->gray_gc[5], x + width - 1, y + 1, x + width - 1, y + height - 2);
	      
	      gdk_draw_line(window, galaxy_style->gray_gc[7], x + 1, y + 1, x + width - 2, y + 1);
	      gdk_draw_line(window, galaxy_style->gray_gc[7], x + 1, y + 1, x + 1, y + height - 2);
		
	      gdk_draw_line(window, style->white_gc, x + 2, y + height - 2, x + width - 2, y + height - 2);
	      gdk_draw_line(window, style->white_gc, x + width - 2, y + 2, x + width - 2, y + height - 2);
	      
	      gdk_draw_point(window, style->bg_gc[GTK_STATE_NORMAL], x, y);
	      gdk_draw_point(window, style->bg_gc[GTK_STATE_NORMAL], x + width - 1, y);
	      gdk_draw_point(window, style->bg_gc[GTK_STATE_NORMAL], x, y + height - 1);
	      gdk_draw_point(window, style->bg_gc[GTK_STATE_NORMAL], x + width - 1, y + height - 1);
	    }
	  }
	  else if (DETAIL("trough") && !GTK_IS_RANGE(widget)) { /* progressbar */
	    gdk_draw_line (window, galaxy_style->gray_gc[5],x,y,x+width-1,y);
	    gdk_draw_line (window, galaxy_style->gray_gc[5],x,y+1,x,y+height-1);
	    gdk_draw_line (window, style->white_gc, x+width-1, y+1, x+width-1,y+height-1);
	    gdk_draw_line (window, style->white_gc, x+1,y+height-1,x+width-1, y+height-1);
	  } else {
 gdk_draw_line (window, galaxy_style->gray_gc[2], x,y,x+width-2,y);
	      gdk_draw_line (window, galaxy_style->gray_gc[2], x,y+1,x,y+height-2);

	      gdk_draw_line (window, style->white_gc, x+width-1,y,x+width-1,y+height-1);
	      gdk_draw_line (window, style->white_gc, x,y+height-1,x+width-1,y+height-1);
  
	      gdk_draw_line (window, galaxy_style->gray_gc[5], x+1,y+1,x+width-2,y+1);
	      gdk_draw_line (window, galaxy_style->gray_gc[5], x+1,y+2,x+1,y+height-2);

	      gdk_draw_line (window, galaxy_style->gray_gc[0], x+width-2,y+2,x+width-2,y+height-2);
	      gdk_draw_line (window, galaxy_style->gray_gc[0], x+2,y+height-2,x+width-3,y+height-2);
	    }
	  break;
        case GTK_SHADOW_OUT:
	  if (is_combo_button) {
	     gdk_draw_rectangle (window, galaxy_style->gray_gc[5],FALSE,
				x+1,y+1,width-3,height-3);	     
	     if (gtk_widget_get_direction (widget) == GTK_TEXT_DIR_LTR) {
	     gdk_draw_line (window, style->white_gc,x,y+2,x,y+height-2);
	     gdk_draw_line (window, style->white_gc,x+width-1,y+1,x+width-1,y+height-1);
	     gdk_draw_line (window, galaxy_style->gray_gc[2],x,y,x+width-1,y);
	     gdk_draw_point (window, galaxy_style->gray_gc[0],x,y+height-2);
	     gdk_draw_line (window, style->white_gc,x+width-1,y,x+width-1,y+height-1);
	     gdk_draw_line (window, style->white_gc,x,y+height-1,x+width-1,y+height-1);
	       gdk_draw_point (window, galaxy_style->gray_gc[5],x,y+1);
	     }
	     else {
	       gdk_draw_line (window, style->white_gc,x+width-1,y+2,x+width-1,y+height-3);
	       gdk_draw_point (window, galaxy_style->gray_gc[5],x+width-1,y+1);
	       gdk_draw_point (window, galaxy_style->gray_gc[0],x+width-1,y+height-2);
	       gdk_draw_line (window, style->white_gc,x,y+height-1,x+width-1,y+height-1);
	       gdk_draw_line (window, galaxy_style->gray_gc[2],x,y,x+width-1,y);
	       gdk_draw_line (window, galaxy_style->gray_gc[2],x,y+1,x,y+height-1);
	     }

	  } else
	  if (DETAIL ("button") || 
	      DETAIL ("togglebutton") || 
	      DETAIL ("togglebutton") || 
	      DETAIL ("optionmenu")) {
	    if ((xthick>=3) &&
		(ythick>=3) && GALAXY_RC_STYLE(style->rc_style)->enable_gradient ){
	      if (state_type != GTK_STATE_INSENSITIVE) {
		/* white */	  		
		gdk_draw_line (window, style->white_gc, x+4,y+3,x+width-5,y+3);
		gdk_draw_line (window, style->white_gc, x+3,y+4,x+3,y+height-5);	  
	      /* grey 3 */

		gdk_draw_line (window, galaxy_style->gray_gc[3], x+width-2, y+5, x+width-2, y+height-5);
		gdk_draw_point (window, galaxy_style->gray_gc[3], x+width-3, y+height-4);
		gdk_draw_point (window, galaxy_style->gray_gc[3], x+width-4, y+height-3);
		gdk_draw_line (window, galaxy_style->gray_gc[3], x+5, y+height-2, x+width-5, y+height-2);
		
		/* grey 2 */
		gdk_draw_point(window,galaxy_style->gray_gc[2],x+4,y+height-2);
		gdk_draw_point(window,galaxy_style->gray_gc[2],x+width-4,y+height-2);
		gdk_draw_point(window,galaxy_style->gray_gc[2],x+width-3,y+height-3);
		gdk_draw_point(window,galaxy_style->gray_gc[2],x+width-2,y+height-4);
		gdk_draw_point(window,galaxy_style->gray_gc[2],x+width-2,y+4);
	      }
	      
	    } else if ((xthick == 1) && (ythick == 1)) {
	      gdk_draw_rectangle (window, galaxy_style->gray_gc[5],
				  FALSE,x,y,width-1,height-1);
	      gdk_draw_line (window, style->white_gc, x+1, y+1, x+width-2,y+1);
	      gdk_draw_line (window, style->white_gc, x+1, y+2, x+1,y+height-2);
	    } else  {
	      gdk_draw_line(window, galaxy_style->gray_gc[7], x + 1, y, x + width - 2, y);
	      gdk_draw_line(window, galaxy_style->gray_gc[7], x, y + 1, x, y + height - 2);
	      
	      gdk_draw_line(window, galaxy_style->gray_gc[7], x + 1, y + height - 1, x + width - 2, y + height - 1);
	      gdk_draw_line(window, galaxy_style->gray_gc[7], x + width - 1, y + 1, x + width - 1, y + height - 2);
	      
	      gdk_draw_line(window, style->white_gc, x + 1, y + 1, x + width - 3, y + 1);
	      gdk_draw_line(window, style->white_gc, x + 1, y + 1, x + 1, y + height - 3);
	      
	      gdk_draw_line(window, galaxy_style->gray_gc[5], x + 1, y + height - 2, x + width - 2, y + height - 2);
	      gdk_draw_line(window, galaxy_style->gray_gc[5], x + width - 2, y + 1, x + width - 2, y + height - 2);
	      
	      gdk_draw_point(window, style->bg_gc[GTK_STATE_NORMAL], x, y);
	      gdk_draw_point(window, style->bg_gc[GTK_STATE_NORMAL], x + width - 1, y);
	      gdk_draw_point(window, style->bg_gc[GTK_STATE_NORMAL], x, y + height - 1);
	      gdk_draw_point(window, style->bg_gc[GTK_STATE_NORMAL], x + width - 1, y + height - 1);
	    }
	  }
	  else if (DETAIL ("menu")) {
	    gdk_draw_line(window, galaxy_style->gray_gc[5], x, y, x + width - 1, y);
	    gdk_draw_line(window, galaxy_style->gray_gc[5], x, y, x, y + height - 1);

	    gdk_draw_line(window, galaxy_style->gray_gc[5], x + 1, y + height - 1, x + width - 1, y + height - 1);
	    gdk_draw_line(window, galaxy_style->gray_gc[5], x + width - 1, y + 1, x + width - 1, y + height - 1);

	    gdk_draw_line(window, style->white_gc, x + 1, y + 1, x + width - 3, y + 1);
	    gdk_draw_line(window, style->white_gc, x + 1, y + 1, x + 1, y + height - 3);

	    gdk_draw_line(window, galaxy_style->gray_gc[2], x + 1, y + height - 2, x + width - 2, y + height - 2);
	    gdk_draw_line(window, galaxy_style->gray_gc[2], x + width - 2, y + 1, x + width - 2, y + height - 2);
	  }
	  else {
	    gdk_draw_line(window, galaxy_style->gray_gc[7], x + 1, y, x + width - 2, y);
	    gdk_draw_line(window, galaxy_style->gray_gc[7], x, y + 1, x, y + height - 2);
	    
	    gdk_draw_line(window, galaxy_style->gray_gc[7], x + 1, y + height - 1, x + width - 2, y + height - 1);
	    gdk_draw_line(window, galaxy_style->gray_gc[7], x + width - 1, y + 1, x + width - 1, y + height - 2);
	    
	    gdk_draw_line(window, style->white_gc, x + 1, y + 1, x + width - 3, y + 1);
	    gdk_draw_line(window, style->white_gc, x + 1, y + 1, x + 1, y + height - 3);
	    
	    gdk_draw_line(window, galaxy_style->gray_gc[5], x + 1, y + height - 2, x + width - 2, y + height - 2);
	    gdk_draw_line(window, galaxy_style->gray_gc[5], x + width - 2, y + 1, x + width - 2, y + height - 2);
	    
	    gdk_draw_point(window, style->bg_gc[GTK_STATE_NORMAL], x, y);
	    gdk_draw_point(window, style->bg_gc[GTK_STATE_NORMAL], x + width - 1, y);
	    gdk_draw_point(window, style->bg_gc[GTK_STATE_NORMAL], x, y + height - 1);
	    gdk_draw_point(window, style->bg_gc[GTK_STATE_NORMAL], x + width - 1, y + height - 1);
	  }
            break;
    default:
      break;
    }
    }

    if (shadow_type == GTK_SHADOW_IN && 
	widget && (GTK_IS_SPIN_BUTTON (widget) || (GTK_IS_COMBO (gtk_widget_get_parent (widget)))) &&
	 DETAIL ("entry"))
    {
      GdkGC * gc1 = style->base_gc[GTK_WIDGET_STATE(widget)];

      if (area) {
	gdk_gc_set_clip_rectangle (style->bg_gc[GTK_WIDGET_STATE(widget)], area);
      }
      
      if (gtk_widget_get_direction (widget) == GTK_TEXT_DIR_LTR)
	{
	  gdk_draw_line (window,
			 gc1,
			 x + width - 2, y + 2,
			 x + width - 2, y + height - 3);

	  gdk_draw_point (window,
			  galaxy_style->gray_gc[5],
			  x + width - 1, y + 1);
	  gdk_draw_point (window,
			  galaxy_style->gray_gc[2],
			  x + width - 1, y);


	  gdk_draw_point (window,
			 galaxy_style->gray_gc[0],
			  x + width - 1, y + height-2);
	}
      else
	{
	  gdk_draw_line (window,
			 gc1,
			 x, y + 1,
			 x, y + height - 3);
	  gdk_draw_line (window,
			 galaxy_style->gray_gc[0],
			 x, y + height-2,
			 x+1,y+height-2);
	  gdk_draw_line (window,
			 gc1,
			 x + 1, y + 1,
			 x + 1, y + height - 3);
	  gdk_draw_line (window,
			  galaxy_style->gray_gc[5],
			  x, y + 1, x+1,y+1);
	}
      if (area) {
	gdk_gc_set_clip_rectangle (style->bg_gc[GTK_WIDGET_STATE(widget)], NULL);
      }

    }

    if(area)
    {
        gdk_gc_set_clip_rectangle (style->bg_gc[GTK_STATE_NORMAL], NULL);
	gdk_gc_set_clip_rectangle (style->white_gc, NULL);
	gdk_gc_set_clip_rectangle (galaxy_style->gray_gc[0], NULL);
	gdk_gc_set_clip_rectangle (galaxy_style->gray_gc[1], NULL);
	gdk_gc_set_clip_rectangle (galaxy_style->gray_gc[2], NULL);
	gdk_gc_set_clip_rectangle (galaxy_style->gray_gc[3], NULL);
	gdk_gc_set_clip_rectangle (galaxy_style->gray_gc[4], NULL);
	gdk_gc_set_clip_rectangle (galaxy_style->gray_gc[5], NULL);
	gdk_gc_set_clip_rectangle (galaxy_style->gray_gc[7], NULL);
    }
}

static void draw_polygon(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, GdkPoint * points, gint npoints, gint fill)
{
#ifndef M_PI
#define M_PI    3.14159265358979323846
#endif /* M_PI */
#ifndef M_PI_4
#define M_PI_4  0.78539816339744830962
#endif /* M_PI_4 */

    static const gdouble pi_over_4 = M_PI_4;
    static const gdouble pi_3_over_4 = M_PI_4 * 3;

    GdkGC *gc1;
    GdkGC *gc2;
    GdkGC *gc3;
    GdkGC *gc4;
    gdouble angle;
    gint xadjust;
    gint yadjust;
    gint i;

    g_return_if_fail(style != NULL);
    g_return_if_fail(window != NULL);
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

    if(area)
    {
        gdk_gc_set_clip_rectangle(gc1, area);
        gdk_gc_set_clip_rectangle(gc2, area);
        gdk_gc_set_clip_rectangle(gc3, area);
        gdk_gc_set_clip_rectangle(gc4, area);
    }

    if(fill)
        gdk_draw_polygon(window, style->bg_gc[state_type], TRUE, points, npoints);

    npoints--;

    for(i = 0; i < npoints; i++)
    {
        if((points[i].x == points[i + 1].x) && (points[i].y == points[i + 1].y))
        {
            angle = 0;
        }
        else
        {
            angle = atan2(points[i + 1].y - points[i].y, points[i + 1].x - points[i].x);
        }

        if((angle > -pi_3_over_4) && (angle < pi_over_4))
        {
            if(angle > -pi_over_4)
            {
                xadjust = 0;
                yadjust = 1;
            }
            else
            {
                xadjust = 1;
                yadjust = 0;
            }

            gdk_draw_line(window, gc1, points[i].x - xadjust, points[i].y - yadjust, points[i + 1].x - xadjust, points[i + 1].y - yadjust);
            gdk_draw_line(window, gc3, points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }
        else
        {
            if((angle < -pi_3_over_4) || (angle > pi_3_over_4))
            {
                xadjust = 0;
                yadjust = 1;
            }
            else
            {
                xadjust = 1;
                yadjust = 0;
            }

            gdk_draw_line(window, gc4, points[i].x + xadjust, points[i].y + yadjust, points[i + 1].x + xadjust, points[i + 1].y + yadjust);
            gdk_draw_line(window, gc2, points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }
    }
    if(area)
    {
        gdk_gc_set_clip_rectangle(gc1, NULL);
        gdk_gc_set_clip_rectangle(gc2, NULL);
        gdk_gc_set_clip_rectangle(gc3, NULL);
        gdk_gc_set_clip_rectangle(gc4, NULL);
    }
}

static void draw_diamond(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height)
{
    gint half_width;
    gint half_height;

    g_return_if_fail(style != NULL);
    g_return_if_fail(window != NULL);

    sanitize_size(window, &width, &height);

    half_width = width / 2;
    half_height = height / 2;

    if(area)
    {
        gdk_gc_set_clip_rectangle(style->light_gc[state_type], area);
        gdk_gc_set_clip_rectangle(style->bg_gc[state_type], area);
        gdk_gc_set_clip_rectangle(style->dark_gc[state_type], area);
        gdk_gc_set_clip_rectangle(style->black_gc, area);
    }
    switch (shadow_type)
    {
        case GTK_SHADOW_IN:
            gdk_draw_line(window, style->light_gc[state_type], x + 2, y + half_height, x + half_width, y + height - 2);
            gdk_draw_line(window, style->light_gc[state_type], x + half_width, y + height - 2, x + width - 2, y + half_height);
            gdk_draw_line(window, style->light_gc[state_type], x + 1, y + half_height, x + half_width, y + height - 1);
            gdk_draw_line(window, style->light_gc[state_type], x + half_width, y + height - 1, x + width - 1, y + half_height);
            gdk_draw_line(window, style->light_gc[state_type], x, y + half_height, x + half_width, y + height);
            gdk_draw_line(window, style->light_gc[state_type], x + half_width, y + height, x + width, y + half_height);

            gdk_draw_line(window, style->dark_gc[state_type], x + 2, y + half_height, x + half_width, y + 2);
            gdk_draw_line(window, style->dark_gc[state_type], x + half_width, y + 2, x + width - 2, y + half_height);
            gdk_draw_line(window, style->dark_gc[state_type], x + 1, y + half_height, x + half_width, y + 1);
            gdk_draw_line(window, style->dark_gc[state_type], x + half_width, y + 1, x + width - 1, y + half_height);
            gdk_draw_line(window, style->dark_gc[state_type], x, y + half_height, x + half_width, y);
            gdk_draw_line(window, style->dark_gc[state_type], x + half_width, y, x + width, y + half_height);
            break;
        case GTK_SHADOW_OUT:
            gdk_draw_line(window, style->dark_gc[state_type], x + 2, y + half_height, x + half_width, y + height - 2);
            gdk_draw_line(window, style->dark_gc[state_type], x + half_width, y + height - 2, x + width - 2, y + half_height);
            gdk_draw_line(window, style->dark_gc[state_type], x + 1, y + half_height, x + half_width, y + height - 1);
            gdk_draw_line(window, style->dark_gc[state_type], x + half_width, y + height - 1, x + width - 1, y + half_height);
            gdk_draw_line(window, style->dark_gc[state_type], x, y + half_height, x + half_width, y + height);
            gdk_draw_line(window, style->dark_gc[state_type], x + half_width, y + height, x + width, y + half_height);

            gdk_draw_line(window, style->light_gc[state_type], x + 2, y + half_height, x + half_width, y + 2);
            gdk_draw_line(window, style->light_gc[state_type], x + half_width, y + 2, x + width - 2, y + half_height);
            gdk_draw_line(window, style->light_gc[state_type], x + 1, y + half_height, x + half_width, y + 1);
            gdk_draw_line(window, style->light_gc[state_type], x + half_width, y + 1, x + width - 1, y + half_height);
            gdk_draw_line(window, style->light_gc[state_type], x, y + half_height, x + half_width, y);
            gdk_draw_line(window, style->light_gc[state_type], x + half_width, y, x + width, y + half_height);
            break;
        default:
            break;
    }
    if(area)
    {
        gdk_gc_set_clip_rectangle(style->light_gc[state_type], NULL);
        gdk_gc_set_clip_rectangle(style->bg_gc[state_type], NULL);
        gdk_gc_set_clip_rectangle(style->dark_gc[state_type], NULL);
        gdk_gc_set_clip_rectangle(style->black_gc, NULL);
    }
}

static void draw_box(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height)
{
  
  GalaxyStyle *galaxy_style = GALAXY_STYLE (style);
  int color1, color2, xthick, ythick;

  xthick = style->xthickness;
  ythick = style->ythickness;
  

    g_return_if_fail(style != NULL);
    g_return_if_fail(window != NULL);

    sanitize_size(window, &width, &height);
    
    if (widget && 
	(DETAIL ("button")  ||
	 DETAIL ("togglebutton") ||
	 DETAIL ("spinbutton_up") || 
	 DETAIL ("spinbutton_down") ||
	 DETAIL("optionmenu"))) /* Button, Combobox */ {
      if (area) { 
	gdk_gc_set_clip_rectangle (style->base_gc[state_type], area);
	gdk_gc_set_clip_rectangle (style->white_gc, area);
	gdk_gc_set_clip_rectangle (galaxy_style->gray_gc[5], area);
      }

      if (("button") && GTK_IS_COMBO(gtk_widget_get_parent(widget))) {
	xthick = ythick = 1;
      }

      if ((width > 2*xthick) && (height > 2*ythick) && (height < 38) 
	  && GALAXY_RC_STYLE(style->rc_style)->enable_gradient 
	  ||  DETAIL ("spinbutton_up") || 
	     DETAIL ("spinbutton_down")) {
	  GdkColor top_color, bottom_color;

	  if (state_type == GTK_STATE_PRELIGHT) {
	    bottom_color = galaxy_style->gray[1];
	    top_color = style->white;
	  }
	  else if (state_type == GTK_STATE_ACTIVE) {
	      bottom_color = galaxy_style->gray[0];
	      top_color = galaxy_style->gray[2];
	    }
	  else if (state_type == GTK_STATE_INSENSITIVE) {
	    bottom_color = galaxy_style->gray[2];
	    top_color = galaxy_style->gray[1];
	  }
	  else {
	    bottom_color = galaxy_style->gray[2];
	    top_color = galaxy_style->gray[0];
	    }

	  /* Make the top button overlap the first line of the bottom button */
	  if (DETAIL ("spinbutton_up")) {
	    xthick = ythick = 1;
	    width -= 1;
	    y += 1;
	    if (gtk_widget_get_direction (widget) == GTK_TEXT_DIR_RTL) {
	      x += 1;
	    }
	  } else if (DETAIL ("spinbutton_down")) {
	    xthick = ythick = 1;
	    width -= 1;
	    height -= 1;
	    if (gtk_widget_get_direction (widget) == GTK_TEXT_DIR_RTL) {
	      x += 1;
	    }
	  }

	  
	  draw_vgradient (window, style->base_gc[state_type], style->colormap, 
			  x+xthick,y+ythick, 
			  width-2*xthick, 
			  height-2*ythick, 
			  &top_color, 
			  &bottom_color);
	}
      else {
	gtk_style_apply_default_background(style, window, 1, state_type, 
					   area, x+xthick, 
					   y+ythick, 
					   width-2*xthick, 
					   height-2*ythick);
      }
	  
	if (DETAIL ("optionmenu")) {
	  GtkRequisition indicator_size;
	  GtkBorder indicator_spacing;
	  gint vline_x;
	  
	  option_menu_get_props (widget, &indicator_size, &indicator_spacing);
	  sanitize_size (window, &width, &height);

	  if (gtk_widget_get_direction (widget) == GTK_TEXT_DIR_RTL)
	    vline_x = x + indicator_size.width + indicator_spacing.left 
	      + indicator_spacing.right-1;
	  else
	    vline_x = x + width - (indicator_size.width + indicator_spacing.left
				   + indicator_spacing.right 
				   + xthick+1);
	  
	  gdk_draw_line (window, style->white_gc,
			 vline_x, y+4,
			 vline_x, y+height-4);
	  gdk_draw_line (window, galaxy_style->gray_gc[5],
			 vline_x,y+4, 
			 vline_x,y+height-4);

	}

	if (area) {

	    gdk_gc_set_clip_rectangle (style->base_gc[state_type], NULL);
	    gdk_gc_set_clip_rectangle (style->white_gc, NULL);
	    gdk_gc_set_clip_rectangle (galaxy_style->gray_gc[5], NULL);
	}
	
	draw_shadow(style, window, state_type, shadow_type, area, 
		    widget, detail, x, y, width, height);

      }
    else if (widget && 
	     DETAIL ("menubar") || 
	     DETAIL ("toolbar") || 
	     DETAIL ("dockitem_bin") ) {
      if(area) {
            gdk_gc_set_clip_rectangle(style->bg_gc[state_type], area);
	    gdk_gc_set_clip_rectangle(style->white_gc, area);
	    gdk_gc_set_clip_rectangle(galaxy_style->gray_gc[5], area);
        }
       
        gdk_draw_rectangle(window, style->bg_gc[state_type], TRUE, x+1, y+1, width-1, height-1);

	if (shadow_type == GTK_SHADOW_OUT) {
	  gdk_draw_line (window,style->white_gc,x,y,x+width-1,y);
	  gdk_draw_line (window,style->white_gc,x,y+1,x,y+height-1);
	  gdk_draw_line (window,galaxy_style->gray_gc[5],x+width-1,y+1,x+width-1,y+height-2);
	  gdk_draw_line (window,galaxy_style->gray_gc[5],x+1,y+height-1,x+width-1,y+height-1);	
	}
        if(area) {
            gdk_gc_set_clip_rectangle(style->bg_gc[state_type], NULL);
	    gdk_gc_set_clip_rectangle(style->white_gc, NULL);
	    gdk_gc_set_clip_rectangle(galaxy_style->gray_gc[5], NULL);
        }
    }
    else if (widget && DETAIL ("trough")) {      
      if GTK_IS_HSCALE (widget)
	{
	  y += (height - SCALE_SIZE) / 2;
	  height = SCALE_SIZE;
	}
      
      if GTK_IS_VSCALE (widget)
	{
	  x += (width - SCALE_SIZE) / 2;
	  width = SCALE_SIZE;
	}
      
      if (GTK_IS_RANGE (widget)) {
	if (area) {
	  gdk_gc_set_clip_rectangle(style->base_gc[state_type], area);
	  gdk_gc_set_clip_rectangle(galaxy_style->gray_gc[5], area);
	}

	if (GTK_RANGE (widget)->orientation == GTK_ORIENTATION_HORIZONTAL) {
	  draw_vgradient (window, style->base_gc[state_type], style->colormap, 
			  x+1, y+1, width-2, height-2, 
			  &galaxy_style->gray[2], 
			  &galaxy_style->gray[0]);
	}
	else {
	  draw_hgradient (window, style->base_gc[state_type], style->colormap, 
			  x+1, y+1, width-2, height-2, 
			  &galaxy_style->gray[2], 
			  &galaxy_style->gray[0]);
	}
	gdk_draw_rectangle (window, galaxy_style->gray_gc[5],FALSE,
			    x,y,width-1,height-1);
	if (area) {
	  gdk_gc_set_clip_rectangle(style->base_gc[state_type], NULL);	
	  gdk_gc_set_clip_rectangle(galaxy_style->gray_gc[5], NULL);
	}
      }
      else {
	if (area) {
	  gdk_gc_set_clip_rectangle(galaxy_style->gray_gc[2], area);
	}

	gdk_draw_rectangle (window, galaxy_style->gray_gc[2],TRUE,
			    x+1,y+1,x+width-2,y+height-2);
	if (area) {
	  gdk_gc_set_clip_rectangle(galaxy_style->gray_gc[2], NULL);
	}
       draw_shadow(style, window, state_type, shadow_type, area, widget, 
		  detail, x, y, width, height);
      }

    } 
    else if (widget && DETAIL ("hscrollbar") || DETAIL ("vscrollbar") ) {
      /* draw steppers, buttons used for scrollbar */
	 GdkColor top_color, bottom_color;

	 if (area) {
	   gdk_gc_set_clip_rectangle (style->base_gc[state_type], area);
	   gdk_gc_set_clip_rectangle (galaxy_style->gray_gc[5], area);
	 }

	  if (state_type == GTK_STATE_PRELIGHT) {
	    bottom_color = galaxy_style->gray[1];
	    top_color = style->white;
	  }
	  else if (state_type == GTK_STATE_ACTIVE) {
	    bottom_color = galaxy_style->gray[0];
	    top_color = galaxy_style->gray[2];
	    }
	  else {
	    bottom_color = galaxy_style->gray[2];
	    top_color = galaxy_style->gray[0];
	  }
	 if (DETAIL ("hscrollbar")) {	 
	   draw_vgradient (window, style->base_gc[state_type], style->colormap, 
			   x+1, y+1, width-2, height-2, 
			   &top_color, 
			   &bottom_color);
	 }
	 else {
	   draw_hgradient (window, style->base_gc[state_type], style->colormap, 
			   x+1, y+1, width-2, height-2, 
			   &top_color, 
			   &bottom_color);
	 }

	 gdk_draw_rectangle (window, galaxy_style->gray_gc[5],FALSE,
			     x,y,width-1,height-1);

	 if (area) {
	   gdk_gc_set_clip_rectangle (galaxy_style->gray_gc[5], NULL);
	   gdk_gc_set_clip_rectangle (style->base_gc[state_type], NULL);
	 }
   
       }
    else if (widget && DETAIL ("bar")) { /* progress bar */
      if(area) {
	gdk_gc_set_clip_rectangle (style->base_gc[state_type], area);
	gdk_gc_set_clip_rectangle (style->white_gc, area);
	gdk_gc_set_clip_rectangle (galaxy_style->blue_gc[2], area);
      }
      
      if ((height > 2 ) && (width > 2)) {
	draw_vgradient (window, style->base_gc[state_type], style->colormap,
		       x+1, y+1, width-2, height-2,
		       &style->white,
		       &galaxy_style->blue[2]);
      }
     
      gdk_draw_line (window, style->white_gc, x,y,x+width-1,y);
      gdk_draw_line (window, style->white_gc, x,y+1,x,y+height-1);

      gdk_draw_line (window, galaxy_style->blue_gc[2], x+width-1,y+1, x+width-1,y+height-2);
      gdk_draw_line (window, galaxy_style->blue_gc[2], x+1,y+height-1,x+width-1,y+height-1);

      if(area) {
	gdk_gc_set_clip_rectangle (style->base_gc[state_type], NULL);
	gdk_gc_set_clip_rectangle (style->white_gc, NULL);
	gdk_gc_set_clip_rectangle (galaxy_style->blue_gc[2], NULL);
      }
      draw_shadow(style, window, state_type, shadow_type, area, widget, 
		  detail, x, y, width, height);
    }  

    else if (widget && DETAIL ("menuitem")) {
      if(area) {
	gdk_gc_set_clip_rectangle (style->base_gc[state_type], area);
      }
      
      draw_vgradient (window, style->base_gc[state_type], style->colormap,
		       x+1, y+1, width-1, height-1,
		       &galaxy_style->blue[2],
		       &galaxy_style->blue[0]);

      if(area) {
	gdk_gc_set_clip_rectangle (style->base_gc[state_type], NULL);
      }
      draw_shadow(style, window, state_type, shadow_type, area, widget, 
		  detail, x, y, width, height);
    } 
    else { /* everything else */
       parent_class->draw_box (style, window, state_type, shadow_type, area,
			      widget, detail, x, y, width, height);	      
    }
}

static void draw_check(GtkStyle * style, GdkWindow * window, GtkStateType state, GtkShadowType shadow, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height)
{
  GalaxyStyle *galaxy_style = GALAXY_STYLE (style);
  GdkGCValues old_values;
  static GdkBitmap* button_bmap = NULL;
  static GdkBitmap* menu_bmap = NULL;
  GdkBitmap* bmap = NULL;

  if(area) {
    gdk_gc_set_clip_rectangle(style->base_gc[state], area);
    gdk_gc_set_clip_rectangle(galaxy_style->check_gc, area);
  }

  x -= (1 + PART_SIZE - width) / 2;
  y -= (1 + PART_SIZE - height) / 2;    
  
  
  if (!DETAIL ("check")) {
    gdk_draw_rectangle(window, style->base_gc[state], TRUE, 
		       x, y, PART_SIZE, PART_SIZE);
    
    draw_shadow (style, window, state,GTK_SHADOW_IN,area,widget,detail,
		 x,y,PART_SIZE,PART_SIZE);

    if (button_bmap == NULL) {
      button_bmap = gdk_bitmap_create_from_data(window, check_cross_bits,
						PART_SIZE, PART_SIZE);
    }

    bmap = button_bmap;
  }
  else {
     if (menu_bmap == NULL) {
      menu_bmap = gdk_bitmap_create_from_data(window, menu_check_bits,
					      PART_SIZE, PART_SIZE);
     }
     bmap = menu_bmap;
     y += 1;
  }
  
  if (shadow == GTK_SHADOW_IN) {
      
	gdk_gc_set_stipple(galaxy_style->check_gc, bmap);
	gdk_gc_set_ts_origin(galaxy_style->check_gc, x, y);
	gdk_gc_set_fill(galaxy_style->check_gc, GDK_STIPPLED);

	if ((DETAIL ("cellcheck") || DETAIL ("check")) && 
	    ((state == GTK_STATE_SELECTED) || (state == GTK_STATE_ACTIVE) ||
	     (state == GTK_STATE_PRELIGHT))) {
	  gdk_gc_get_values (galaxy_style->check_gc, &old_values);
	  gdk_gc_set_foreground (galaxy_style->check_gc, &style->white);
	}

	gdk_draw_rectangle(window, galaxy_style->check_gc, TRUE, x, y, 
			   PART_SIZE, PART_SIZE);

	if ((DETAIL ("cellcheck") || DETAIL ("check"))&& 
	    ((state == GTK_STATE_SELECTED) || (state == GTK_STATE_ACTIVE)
	     || (state == GTK_STATE_PRELIGHT))) {
	  gdk_gc_set_foreground (galaxy_style->check_gc, &old_values.foreground);
	  
	}
	gdk_gc_set_fill(galaxy_style->check_gc, GDK_SOLID);
      }

  if(area) {
    gdk_gc_set_clip_rectangle(style->base_gc[state], NULL);
    gdk_gc_set_clip_rectangle(galaxy_style->check_gc, NULL);
  }
}

static void 
draw_option (GtkStyle      *style,
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
  GalaxyStyle *galaxy_style = GALAXY_STYLE (style);
  GdkPixmap *pixmap;

  if (DETAIL ("option")) /* Menu item */
    {
      parent_class->draw_option (style, window, state_type, shadow_type, area,
				 widget, detail, x, y, width, height);
      return;
    }
    
  if (area) {
    gdk_gc_set_clip_rectangle (style->base_gc[state_type], area);
  }

  if (shadow_type == GTK_SHADOW_IN) 
    pixmap = galaxy_style->radio_pixmap_active[state_type];
  else if (shadow_type == GTK_SHADOW_ETCHED_IN) /* inconsistent */
    pixmap = galaxy_style->radio_pixmap_inconsistent[state_type];  
  else 
    pixmap = galaxy_style->radio_pixmap_nonactive[state_type];

  x += (width - RADIO_SIZE)/2;
  y += (height - RADIO_SIZE)/2;

  gdk_gc_set_clip_mask (style->base_gc[state_type],
			galaxy_style->radio_pixmap_mask);
  gdk_gc_set_clip_origin (style->base_gc[state_type], x, y);

  gdk_draw_drawable (window, style->base_gc[state_type],
		     pixmap,
		     0, 0,
		     x, y,
		     RADIO_SIZE, RADIO_SIZE);

  gdk_gc_set_clip_origin (style->base_gc[state_type], 0, 0);
  gdk_gc_set_clip_mask (style->base_gc[state_type], NULL);

  if (area) {
    gdk_gc_set_clip_rectangle (style->base_gc[state_type], NULL);
  }
}


static void draw_shadow_gap(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height, GtkPositionType gap_side, gint gap_x, gint gap_width)
{
    GdkRectangle rect;

    g_return_if_fail(style != NULL);
    g_return_if_fail(window != NULL);

    draw_shadow(style, window, state_type, shadow_type, area, widget, detail, x, y, width, height);

    switch (gap_side)
    {
        case GTK_POS_TOP:
            rect.x = x + gap_x;
            rect.y = y;
            rect.width = gap_width;
            rect.height = 2;
            break;
        case GTK_POS_BOTTOM:
            rect.x = x + gap_x;
            rect.y = y + height - 2;
            rect.width = gap_width;
            rect.height = 2;
            break;
        case GTK_POS_LEFT:
            rect.x = x;
            rect.y = y + gap_x;
            rect.width = 2;
            rect.height = gap_width;
            break;
        case GTK_POS_RIGHT:
            rect.x = x + width - 2;
            rect.y = y + gap_x;
            rect.width = 2;
            rect.height = gap_width;
            break;
    }

    gtk_style_apply_default_background(style, window, 1, state_type, area, rect.x, rect.y, rect.width, rect.height);
}

static void draw_box_gap(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height, GtkPositionType gap_side, gint gap_x, gint gap_width)
{
    GdkGC *gc1 = NULL;
    GdkGC *gc2 = NULL;
    GdkGC *gc3 = NULL;
    GdkGC *gc4 = NULL;

    g_return_if_fail(style != NULL);
    g_return_if_fail(window != NULL);

    gtk_style_apply_default_background(style, window, widget && !GTK_WIDGET_NO_WINDOW(widget), state_type, area, x, y, width, height);

    sanitize_size(window, &width, &height);

    switch (shadow_type)
    {
        case GTK_SHADOW_NONE:
            return;
        case GTK_SHADOW_IN:
            gc1 = style->bg_gc[state_type];
            gc2 = style->dark_gc[state_type];;
            gc3 = style->bg_gc[state_type];
            gc4 = style->light_gc[state_type];
            break;
        case GTK_SHADOW_ETCHED_IN:
            gc1 = style->dark_gc[state_type];
            gc2 = style->light_gc[state_type];
            gc3 = style->dark_gc[state_type];
            gc4 = style->light_gc[state_type];
            break;
        case GTK_SHADOW_OUT:
            gc1 = style->light_gc[state_type];
            gc2 = style->bg_gc[state_type];
            gc3 = style->bg_gc[state_type];
            gc4 = style->dark_gc[state_type];
            break;
        case GTK_SHADOW_ETCHED_OUT:
            gc1 = style->light_gc[state_type];
            gc2 = style->dark_gc[state_type];
            gc3 = style->light_gc[state_type];
            gc4 = style->dark_gc[state_type];
            break;
    }

    if(area)
    {
        gdk_gc_set_clip_rectangle(gc1, area);
        gdk_gc_set_clip_rectangle(gc2, area);
        gdk_gc_set_clip_rectangle(gc3, area);
        gdk_gc_set_clip_rectangle(gc4, area);
    }

    switch (shadow_type)
    {
        case GTK_SHADOW_NONE:
        case GTK_SHADOW_IN:
        case GTK_SHADOW_OUT:
        case GTK_SHADOW_ETCHED_IN:
        case GTK_SHADOW_ETCHED_OUT:
            switch (gap_side)
            {
                case GTK_POS_TOP:
                    gdk_draw_line(window, gc1, x, y, x, y + height - 1);
                    gdk_draw_line(window, gc2, x + 1, y, x + 1, y + height - 2);

                    gdk_draw_line(window, gc3, x + 1, y + height - 2, x + width - 2, y + height - 2);
                    gdk_draw_line(window, gc3, x + width - 2, y, x + width - 2, y + height - 2);
                    gdk_draw_line(window, gc4, x, y + height - 1, x + width - 1, y + height - 1);
                    gdk_draw_line(window, gc4, x + width - 1, y, x + width - 1, y + height - 1);
                    if(gap_x > 0)
                    {
                        gdk_draw_line(window, gc1, x, y, x + gap_x - 1, y);
                        gdk_draw_line(window, gc2, x + 1, y + 1, x + gap_x - 1, y + 1);
                        gdk_draw_line(window, gc2, x + gap_x, y, x + gap_x, y);
                    }
                    if((width - (gap_x + gap_width)) > 0)
                    {
                        gdk_draw_line(window, gc1, x + gap_x + gap_width, y, x + width - 2, y);
                        gdk_draw_line(window, gc2, x + gap_x + gap_width, y + 1, x + width - 2, y + 1);
                        gdk_draw_line(window, gc2, x + gap_x + gap_width - 1, y, x + gap_x + gap_width - 1, y);
                    }
                    break;
                case GTK_POS_BOTTOM:
                    gdk_draw_line(window, gc1, x, y, x + width - 1, y);
                    gdk_draw_line(window, gc1, x, y, x, y + height - 1);
                    gdk_draw_line(window, gc2, x + 1, y + 1, x + width - 2, y + 1);
                    gdk_draw_line(window, gc2, x + 1, y + 1, x + 1, y + height - 1);

                    gdk_draw_line(window, gc3, x + width - 2, y + 1, x + width - 2, y + height - 1);
                    gdk_draw_line(window, gc4, x + width - 1, y, x + width - 1, y + height - 1);
                    if(gap_x > 0)
                    {
                        gdk_draw_line(window, gc4, x, y + height - 1, x + gap_x - 1, y + height - 1);
                        gdk_draw_line(window, gc3, x + 1, y + height - 2, x + gap_x - 1, y + height - 2);
                        gdk_draw_line(window, gc3, x + gap_x, y + height - 1, x + gap_x, y + height - 1);
                    }
                    if((width - (gap_x + gap_width)) > 0)
                    {
                        gdk_draw_line(window, gc4, x + gap_x + gap_width, y + height - 1, x + width - 2, y + height - 1);
                        gdk_draw_line(window, gc3, x + gap_x + gap_width, y + height - 2, x + width - 2, y + height - 2);
                        gdk_draw_line(window, gc3, x + gap_x + gap_width - 1, y + height - 1, x + gap_x + gap_width - 1, y + height - 1);
                    }
                    break;
                case GTK_POS_LEFT:
                    gdk_draw_line(window, gc1, x, y, x + width - 1, y);
                    gdk_draw_line(window, gc2, x, y + 1, x + width - 2, y + 1);

                    gdk_draw_line(window, gc3, x, y + height - 2, x + width - 2, y + height - 2);
                    gdk_draw_line(window, gc3, x + width - 2, y + 1, x + width - 2, y + height - 2);
                    gdk_draw_line(window, gc4, x, y + height - 1, x + width - 1, y + height - 1);
                    gdk_draw_line(window, gc4, x + width - 1, y, x + width - 1, y + height - 1);
                    if(gap_x > 0)
                    {
                        gdk_draw_line(window, gc1, x, y, x, y + gap_x - 1);
                        gdk_draw_line(window, gc2, x + 1, y + 1, x + 1, y + gap_x - 1);
                        gdk_draw_line(window, gc2, x, y + gap_x, x, y + gap_x);
                    }
                    if((width - (gap_x + gap_width)) > 0)
                    {
                        gdk_draw_line(window, gc1, x, y + gap_x + gap_width, x, y + height - 2);
                        gdk_draw_line(window, gc2, x + 1, y + gap_x + gap_width, x + 1, y + height - 2);
                        gdk_draw_line(window, gc2, x, y + gap_x + gap_width - 1, x, y + gap_x + gap_width - 1);
                    }
                    break;
                case GTK_POS_RIGHT:
                    gdk_draw_line(window, gc1, x, y, x + width - 1, y);
                    gdk_draw_line(window, gc1, x, y, x, y + height - 1);
                    gdk_draw_line(window, gc2, x + 1, y + 1, x + width - 1, y + 1);
                    gdk_draw_line(window, gc2, x + 1, y + 1, x + 1, y + height - 2);

                    gdk_draw_line(window, gc3, x + 1, y + height - 2, x + width - 1, y + height - 2);
                    gdk_draw_line(window, gc4, x, y + height - 1, x + width - 1, y + height - 1);
                    if(gap_x > 0)
                    {
                        gdk_draw_line(window, gc4, x + width - 1, y, x + width - 1, y + gap_x - 1);
                        gdk_draw_line(window, gc3, x + width - 2, y + 1, x + width - 2, y + gap_x - 1);
                        gdk_draw_line(window, gc3, x + width - 1, y + gap_x, x + width - 1, y + gap_x);
                    }
                    if((width - (gap_x + gap_width)) > 0)
                    {
                        gdk_draw_line(window, gc4, x + width - 1, y + gap_x + gap_width, x + width - 1, y + height - 2);
                        gdk_draw_line(window, gc3, x + width - 2, y + gap_x + gap_width, x + width - 2, y + height - 2);
                        gdk_draw_line(window, gc3, x + width - 1, y + gap_x + gap_width - 1, x + width - 1, y + gap_x + gap_width - 1);
                    }
                    break;
            }
    }

    if(area)
    {
        gdk_gc_set_clip_rectangle(gc1, NULL);
        gdk_gc_set_clip_rectangle(gc2, NULL);
        gdk_gc_set_clip_rectangle(gc3, NULL);
        gdk_gc_set_clip_rectangle(gc4, NULL);
    }
}

static void draw_extension(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height, GtkPositionType gap_side)
{ 
  GalaxyStyle *galaxy_style = GALAXY_STYLE (style);

    GdkGC *gc1 = NULL;
    GdkGC *gc2 = NULL;
    GdkGC *background_gc = NULL;

    g_return_if_fail(style != NULL);
    g_return_if_fail(window != NULL);
    gtk_style_apply_default_background (style, window,
					widget && !GTK_WIDGET_NO_WINDOW (widget),
					GTK_STATE_NORMAL, area, x, y, width, height);
    sanitize_size(window, &width, &height);

    switch (shadow_type) {

    case GTK_SHADOW_NONE:
      return;

    case GTK_SHADOW_IN:
    case GTK_SHADOW_ETCHED_IN:
      gc1 = galaxy_style->gray_gc[5];
      if (state_type == GTK_STATE_NORMAL) { /* we draw current page */
	gc2 = style->white_gc;
      } else {
	gc2 = galaxy_style->gray_gc[0];
      }
      break;

      gc1 = galaxy_style->gray_gc[5];
      if (state_type == GTK_STATE_NORMAL) { /* we draw current page */
	gc2 = style->white_gc;		
      } else {
	gc2 = galaxy_style->gray_gc[0];
      }
      break;

    case GTK_SHADOW_OUT:
    case GTK_SHADOW_ETCHED_OUT:
      if (state_type == GTK_STATE_NORMAL) { /* we draw current page */
	gc1 = style->white_gc;		
      } else {
	gc1 = galaxy_style->gray_gc[0];
      }
      gc2 = galaxy_style->gray_gc[5];
      break;
      if (state_type == GTK_STATE_NORMAL) { /* we draw current page */
	gc1 = style->white_gc;		
      } else {
	gc1 = galaxy_style->gray_gc[0];
      }
      gc2 = galaxy_style->gray_gc[5];
      break;
    }

    if(area)
    {
        gdk_gc_set_clip_rectangle(gc1, area);
        gdk_gc_set_clip_rectangle(gc2, area);
        gdk_gc_set_clip_rectangle( galaxy_style->gray_gc[2], area);
        gdk_gc_set_clip_rectangle( galaxy_style->gray_gc[1], area);
    }

    switch (shadow_type)
    {
        case GTK_SHADOW_NONE:
        case GTK_SHADOW_IN:
        case GTK_SHADOW_OUT:
        case GTK_SHADOW_ETCHED_IN:
        case GTK_SHADOW_ETCHED_OUT:
            switch (gap_side)
            {
                case GTK_POS_TOP:
		  gtk_style_apply_default_background (style, window,
						      widget && !GTK_WIDGET_NO_WINDOW (widget),
						      state_type, area,
						      x + style->xthickness, 
						      y, 
						      width - (2 * style->xthickness), 
						      height - (style->ythickness));
						      
                    gdk_draw_line(window, gc1, x, y, x, y + height - 3);
		    gdk_draw_point (window, gc1, x+1,y+height-2);
                    gdk_draw_line(window, gc2, x + 2, y + height - 1, x + width - 3, y + height - 1);
                    gdk_draw_line(window, gc2, x + width - 1, y, x + width - 1, y + height - 3);
		    gdk_draw_point (window, gc2, x+width-2,y+height-2);
		    

                    break;
                case GTK_POS_BOTTOM:		  
		  gtk_style_apply_default_background (style, window,
						      widget && !GTK_WIDGET_NO_WINDOW (widget),
						      state_type, area,
						      x + style->xthickness, 
						      y + style->ythickness, 
						      width - (2 * style->xthickness), 
						      height - (style->ythickness));
                    gdk_draw_line(window, gc1, x + 2, y, x + width - 3, y);
                    gdk_draw_point(window, gc1, x + 1, y+1);
                    gdk_draw_line(window, gc1, x, y + 2, x, y + height - 1);
		    gdk_draw_point (window, gc2, x + width-2, y+1);
                    gdk_draw_line (window, gc2, x + width - 1, y + 2, x + width - 1, y + height - 1);
		    
                    break;
                case GTK_POS_LEFT:
		  gtk_style_apply_default_background (style, window,
						      widget && !GTK_WIDGET_NO_WINDOW (widget),
						      state_type, area,
						      x, 
						      y + style->ythickness, 
						      width - (style->xthickness), 
						      height - (2 * style->ythickness));
                    gdk_draw_line(window, gc1, x, y, x + width - 3, y);
		    gdk_draw_point (window, gc1, x+width-2,y+1);
                    gdk_draw_line(window, gc2, x, y + height - 1, x + width - 3, y + height - 1);
                    gdk_draw_line(window, gc2, x + width - 1, y + 2, x + width - 1, y + height - 3);
                    gdk_draw_point(window, gc2, x + width - 2, y + height - 2);
                    break;
                case GTK_POS_RIGHT:
		  gtk_style_apply_default_background (style, window,
						      widget && !GTK_WIDGET_NO_WINDOW (widget),
						      state_type, area,
						      x + style->xthickness, 
						      y + style->ythickness, 
						      width - (style->xthickness), 
						      height - (2 * style->ythickness));
                    gdk_draw_line(window, gc1, x + 2, y, x + width - 1, y);
                    gdk_draw_line(window, gc1, x, y + 2, x, y + height - 3);
                    gdk_draw_point(window, gc1, x+1, y +height-2);
		    gdk_draw_point(window, gc1, x+1, y+1);
                    gdk_draw_line(window, gc2, x + 2, y + height - 1, x + width - 1, y + height - 1);
                    break;
            }
    }

    if(area)
    {
        gdk_gc_set_clip_rectangle(gc1, NULL);
        gdk_gc_set_clip_rectangle(gc2, NULL);
        gdk_gc_set_clip_rectangle( galaxy_style->gray_gc[2], NULL);
        gdk_gc_set_clip_rectangle( galaxy_style->gray_gc[1], NULL);
    }
}

static void draw_slider(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height, GtkOrientation orientation)
{
  GalaxyStyle *galaxy_style = GALAXY_STYLE (style);
  GdkColor *top_color, *bottom_color;

    g_return_if_fail(style != NULL);
    g_return_if_fail(window != NULL);

    sanitize_size(window, &width, &height);

    orientation = GTK_ORIENTATION_HORIZONTAL;
    if(height > width)
        orientation = GTK_ORIENTATION_VERTICAL;
    
    if (area) {
      gdk_gc_set_clip_rectangle (galaxy_style->gray_gc[0],area);
      gdk_gc_set_clip_rectangle (galaxy_style->gray_gc[4],area);
      gdk_gc_set_clip_rectangle (galaxy_style->gray_gc[5],area);
      gdk_gc_set_clip_rectangle (style->white_gc,area);
      gdk_gc_set_clip_rectangle (style->base_gc[state_type],area);
    }

    /* Make sure stepper and slider outlines "overlap" */
      if (widget && GTK_IS_RANGE (widget))
    {
      GtkAdjustment *adj = GTK_RANGE (widget)->adjustment;

      if (adj->value <= adj->lower &&
	  (GTK_RANGE (widget)->has_stepper_a ||
	   GTK_RANGE (widget)->has_stepper_b))
	{
	  if (GTK_IS_VSCROLLBAR (widget))
	    {
	      height += 1;
	      y -= 1;
	    }
	  else if (GTK_IS_HSCROLLBAR (widget))
	    {
	      width += 1;
	      x -= 1;
	    }
	}
      if (adj->value >= adj->upper - adj->page_size &&
	  (GTK_RANGE (widget)->has_stepper_c ||
	   GTK_RANGE (widget)->has_stepper_d))
	{
	  if (GTK_IS_VSCROLLBAR (widget))
	    {
	      height += 1;
	    }
	  else if (GTK_IS_HSCROLLBAR (widget))
	    {
	      width += 1;
	    }
	}
    }

      if (state_type == GTK_STATE_PRELIGHT) {
	bottom_color = &galaxy_style->gray[1];
	top_color = &style->white;
      }
      else {
	bottom_color = &galaxy_style->gray[2];
	top_color = &galaxy_style->gray[0];
      }

    if (orientation == GTK_ORIENTATION_HORIZONTAL) {
      draw_vgradient (window, style->base_gc[state_type], style->colormap, 
		      x+1, y+1, width-2, height-2, 
		      top_color, 
		      bottom_color);
    }
    else {
      draw_hgradient (window, style->base_gc[state_type], style->colormap, 
		      x+2, y+1, width-3, height-2, 
		      top_color, 
		      bottom_color);
    }

    if (DETAIL ("slider")) {
      if (orientation == GTK_ORIENTATION_HORIZONTAL) {
	height -= 2;
	y+=1;
	width += 1;
      }
      else {     
	width -= 1;
	x+=1;
      }
    
      gdk_draw_line (window, style->white_gc, x,y,x+width-2,y);
      
      gdk_draw_line (window, style->white_gc, x,y+1,x,y+height-1);
      
      gdk_draw_line (window, galaxy_style->gray_gc[5], x+1,y+height-1,x+width-2,y+height-1);
      gdk_draw_line (window, galaxy_style->gray_gc[5], x+width-2,y+1,x+width-2,y+height-1);
    } 
    else  if (DETAIL ("hscale")  || DETAIL ("vscale")) {
      
      gdk_draw_line (window, galaxy_style->gray_gc[5],x+1,y,x+width-2,y);
      gdk_draw_line (window, galaxy_style->gray_gc[5],x,y+1,x,y+height-2);

      gdk_draw_line (window, galaxy_style->gray_gc[5],x+width-1,y+1,x+width-1,y+height-2);
      gdk_draw_line (window, galaxy_style->gray_gc[5],x+1,y+height-1,x+width-2,y+height-1);
      gdk_draw_line (window, style->white_gc,x+1,y+1,x+width-2,y+1);
      gdk_draw_line (window, style->white_gc,x+1,y+2,x+1,y+height-2);

      if (orientation == GTK_ORIENTATION_HORIZONTAL) {
	gtk_paint_vline (style, window, state_type, area, widget, detail, 
			 y + style->ythickness+1, 
			 y + height - style->ythickness - 1, x + width / 2);

      }
      else {
	gtk_paint_hline (style, window, state_type, area, widget, detail,
			 x + style->xthickness+1, 
			 x + width - style->xthickness - 1, y + height / 2);
      }
    }

    if (area) {
      gdk_gc_set_clip_rectangle (galaxy_style->gray_gc[0],NULL);
      gdk_gc_set_clip_rectangle (galaxy_style->gray_gc[4],NULL);
      gdk_gc_set_clip_rectangle (galaxy_style->gray_gc[5],NULL);
      gdk_gc_set_clip_rectangle (style->white_gc,NULL);
      gdk_gc_set_clip_rectangle (style->base_gc[state_type],NULL);
    }

}

static void draw_handle(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height, GtkOrientation orientation)
{
  GalaxyStyle *galaxy_style = GALAXY_STYLE (style);

    g_return_if_fail(style != NULL);
    g_return_if_fail(window != NULL);

    sanitize_size(window, &width, &height);

    if (DETAIL ("dockitem") ||
	(widget && strcmp (g_type_name (G_TYPE_FROM_INSTANCE (widget)), 
			   "PanelAppletFrame") == 0)) {
      /* Work around orientation bugs */
      if (orientation == GTK_ORIENTATION_VERTICAL) {
	orientation = GTK_ORIENTATION_HORIZONTAL;
      }
      else {
	orientation = GTK_ORIENTATION_VERTICAL;
      }
    }

    if(area) {
	gdk_gc_set_clip_rectangle (style->base_gc[state_type], area);
	gdk_gc_set_clip_rectangle (style->white_gc, area);
	gdk_gc_set_clip_rectangle (galaxy_style->gray_gc[4], area);
	gdk_gc_set_clip_rectangle (galaxy_style->gray_gc[5], area);
      }
    if (DETAIL ("paned")) {
      gtk_style_apply_default_background(style, window, 1, state_type, 
					 area, x, 
					 y, 
					 width, 
					 height);
    }
    else {
      if ((height > 2 ) && (width > 2)) {
	if (orientation == GTK_ORIENTATION_VERTICAL) {
	  draw_vgradient (window, style->base_gc[state_type], style->colormap,
			  x+1, y+1, width-2, height-2,
			  &galaxy_style->gray[0],
			  &galaxy_style->gray[2]);
	}
	else {
	  draw_hgradient (window, style->base_gc[state_type], style->colormap,
			  x+1, y+1, width-2, height-2,
			  &galaxy_style->gray[0],
			  &galaxy_style->gray[2]);
	}
      }
    

      gdk_draw_line (window, galaxy_style->gray_gc[5], x,y+height-1, 
		     x+width-2,y+height-1);
      gdk_draw_line (window, galaxy_style->gray_gc[5], x+width-1,y+1,
		     x+width-1,y+height-1);
      gdk_draw_line (window, galaxy_style->gray_gc[4], x+width-2,y+1, 
		     x+width-2,y+height-2);
      gdk_draw_line (window, galaxy_style->gray_gc[4], x,y+height-2,
		     x+width-3,y+height-2);
      gdk_draw_line (window, style->white_gc, x,y,x+width-2,y);
      gdk_draw_line (window, style->white_gc, x,y+1,x,y+height-2);
    }

      if(area) {
	gdk_gc_set_clip_rectangle (style->base_gc[state_type], NULL);
	gdk_gc_set_clip_rectangle (style->white_gc, NULL);
	gdk_gc_set_clip_rectangle (galaxy_style->gray_gc[4], NULL);
	gdk_gc_set_clip_rectangle (galaxy_style->gray_gc[5], NULL);
      }
    
    galaxy_draw_handlers(style, window, state_type, area, widget, x, y, width, height, orientation);
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
  GalaxyStyle *galaxy_style = GALAXY_STYLE (style);
  g_return_if_fail (GTK_IS_STYLE (style));
  g_return_if_fail (window != NULL);

  if (area)
    {
      gdk_gc_set_clip_rectangle (galaxy_style->gray_gc[2], area);
      gdk_gc_set_clip_rectangle (galaxy_style->gray_gc[6], area);
      gdk_gc_set_clip_rectangle (galaxy_style->gray_gc[7], area);
      gdk_gc_set_clip_rectangle (style->white_gc, area);
    }

  switch (edge) {
   case GDK_WINDOW_EDGE_NORTH_WEST:
      /* make it square */
      if (width < height)
	{
	  height = width;
	}
      else if (height < width)
	{
	  width = height;
	}
      break;
    case GDK_WINDOW_EDGE_NORTH:
      if (width < height)
	{
	  height = width;
	}
      break;
    case GDK_WINDOW_EDGE_NORTH_EAST:
      /* make it square, aligning to top right */
      if (width < height)
	{
	  height = width;
	}
      else if (height < width)
	{
	  x += (width - height);
	  width = height;
	}
      break;
    case GDK_WINDOW_EDGE_WEST:
      if (height < width)
	{
	   width = height;
	}
      break;
    case GDK_WINDOW_EDGE_EAST:
      /* aligning to right */
      if (height < width)
	{
	  x += (width - height);
	  width = height;
	}
      break;
    case GDK_WINDOW_EDGE_SOUTH_WEST:
      /* make it square, aligning to bottom left */
      if (width < height)
	{
	  y += (height - width);
	  height = width;
	}
      else if (height < width)
	{
	  width = height;
	}
      break;
    case GDK_WINDOW_EDGE_SOUTH:
      /* align to bottom */
      if (width < height)
	{
	  y += (height - width);
	  height = width;
	}
      break;
    case GDK_WINDOW_EDGE_SOUTH_EAST:
      /* make it square, aligning to bottom right */
      if (width < height)
	{
	  y += (height - width);
	  height = width;
	}
      else if (height < width)
	{
	  x += (width - height);
	  width = height;
	}
      break;
    default:
      g_assert_not_reached ();
    }


  /* Clear background */
  gtk_style_apply_default_background (style, window, FALSE,
				      state_type, area,
				      x, y, width, height);   

  switch (edge) {
    case GDK_WINDOW_EDGE_WEST:
    case GDK_WINDOW_EDGE_EAST:
      {
	gint xi;

	xi = x;

	while (xi < x + width)
	  {
	    gdk_draw_line (window,
			   style->white_gc,
			   xi, y,
			   xi, y + height);

	    xi++;
	    gdk_draw_line (window,
			   galaxy_style->gray_gc[5],
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

	yi = y;

	while (yi < y + height)
	  {
	    gdk_draw_line (window,
			   style->white_gc,
			   x, yi,
			   x + width, yi);

	    yi++;
	    gdk_draw_line (window,
			   galaxy_style->gray_gc[5],
			   x, yi,
			   x + width, yi);

	    yi+= 2;
	  }
      }
      break;
    case GDK_WINDOW_EDGE_SOUTH_EAST:
      {
        int xi;
	int max_length = 8;

	if (width > max_length) {
	  x += width-max_length+1;
	  y += width-max_length;
	}
	else {
	  max_length = width-1;
	}

	for (xi = 0; xi < max_length+1; xi++) {
	  gdk_draw_point(window,galaxy_style->gray_gc[6], x+xi,y+max_length-xi);

	}

	for (xi = 4; xi < max_length+1; xi++) {
	  gdk_draw_point(window,galaxy_style->gray_gc[6], x+xi,y+max_length+4-xi);

	}

	for (xi = 1; xi < max_length+1; xi++) {
	  gdk_draw_point(window,galaxy_style->gray_gc[7], x+xi,y+max_length+1-xi);
	}

	for (xi = 5; xi < max_length+1; xi++) {
	  gdk_draw_point(window,galaxy_style->gray_gc[7], x+xi,y+max_length +5-xi);

	}

	for (xi = 2; xi < max_length+1; xi++) {
	  gdk_draw_point(window,style->white_gc, x+xi,y+max_length+2-xi);
	}
	
	gdk_draw_point (window, style->white_gc, x+max_length,y+max_length-2);
	gdk_draw_point (window, style->white_gc, x+max_length-1,y+max_length-1);
	gdk_draw_point (window, style->white_gc, x+max_length-2,y+max_length);

	for (xi = 3; xi < max_length+1; xi++) {
	  gdk_draw_point(window,galaxy_style->gray_gc[2], x+xi,y+max_length+3-xi);
	}
	
	gdk_draw_point(window,galaxy_style->gray_gc[2], x+max_length,y+max_length-1);
	gdk_draw_point(window,galaxy_style->gray_gc[2], x+max_length-1,y+max_length);
      }
      break;
    case GDK_WINDOW_EDGE_SOUTH_WEST:
      {
        int xi;
	int max_length=8;

	if (height > max_length) {
	  y += height-max_length;
	}
	else {
	  max_length = height-1;
	}


	for (xi = 0; xi < max_length+1; xi++) {
	  gdk_draw_point(window,galaxy_style->gray_gc[6], x+xi,y+xi);

	}

	for (xi = 0; xi < max_length-3; xi++) {
	  gdk_draw_point(window,galaxy_style->gray_gc[6], x+xi,y+4+xi);

	}

	for (xi = 0; xi < max_length; xi++) {
	  gdk_draw_point(window,galaxy_style->gray_gc[7], x+xi,y+1+xi);
	}

	for (xi = 0; xi < max_length-4; xi++) {
	  gdk_draw_point(window,galaxy_style->gray_gc[7], x+xi,y+5+xi);

	}

	for (xi = 0; xi < max_length-1; xi++) {
	  gdk_draw_point(window,style->white_gc, x+xi,y+2+xi);
	}
	
	gdk_draw_point (window, style->white_gc, x,y+max_length-2);
	gdk_draw_point (window, style->white_gc, x+1,y+max_length-1);
	gdk_draw_point (window, style->white_gc, x+2,y+max_length);

	for (xi = 0; xi < max_length-2; xi++) {
	  gdk_draw_point(window,galaxy_style->gray_gc[2], x+xi,y+3+xi);
	}
	
	gdk_draw_point(window,galaxy_style->gray_gc[2], x,y+max_length-1);
	gdk_draw_point(window,galaxy_style->gray_gc[2], x+1,y+max_length);
      }
      break; 
    case GDK_WINDOW_EDGE_NORTH_WEST:
      {
        int xi;
	int max_length=8;

	for (xi = 0; xi < max_length+1; xi++) {
	  gdk_draw_point(window,galaxy_style->gray_gc[6], x+xi,y+max_length-xi);

	}

	for (xi = 0; xi < max_length-3; xi++) {
	  gdk_draw_point(window,galaxy_style->gray_gc[6], x+xi,y+max_length-4-xi);

	}

	for (xi = 0; xi < max_length; xi++) {
	  gdk_draw_point(window,galaxy_style->gray_gc[7], x+xi,y+max_length-1-xi);
	}

	for (xi = 0; xi < max_length-4; xi++) {
	  gdk_draw_point(window,galaxy_style->gray_gc[7], x+xi,y+max_length-5-xi);

	}

	for (xi = 0; xi < max_length-1; xi++) {
	  gdk_draw_point(window,style->white_gc, x+xi,y+max_length-2-xi);
	}
	
	gdk_draw_point (window, style->white_gc, x,y+2);
	gdk_draw_point (window, style->white_gc, x+1,y+1);
	gdk_draw_point (window, style->white_gc, x+2,y);

	for (xi = 0; xi < max_length-2; xi++) {
	  gdk_draw_point(window,galaxy_style->gray_gc[2], x+xi,y+max_length-3-xi);
	}

	gdk_draw_point(window,galaxy_style->gray_gc[2], x,y+1);
	gdk_draw_point(window,galaxy_style->gray_gc[2], x+1,y);
      }
      break; 
    case GDK_WINDOW_EDGE_NORTH_EAST:
      {
        int xi;
	int max_length=8;

	for (xi = 0; xi < max_length+1; xi++) {
	  gdk_draw_point(window,galaxy_style->gray_gc[6], x+xi,y+xi);

	}

	for (xi = 0; xi < max_length-3; xi++) {
	  gdk_draw_point(window,galaxy_style->gray_gc[6], x+xi+4,y+xi);

	}

	for (xi = 0; xi < max_length; xi++) {
	  gdk_draw_point(window,galaxy_style->gray_gc[7], x+xi+1,y+xi);
	}

	for (xi = 0; xi < max_length-4; xi++) {
	  gdk_draw_point(window,galaxy_style->gray_gc[7], x+xi+5,y+xi);
	}

	for (xi = 0; xi < max_length-1; xi++) {
	  gdk_draw_point(window,style->white_gc, x+xi+2,y+xi);
	}
	
	gdk_draw_point (window, style->white_gc, x+max_length,y+2);
	gdk_draw_point (window, style->white_gc, x+max_length-1,y+1);
	gdk_draw_point (window, style->white_gc, x+max_length-2,y);

	for (xi = 0; xi < max_length-2; xi++) {
	  gdk_draw_point(window,galaxy_style->gray_gc[2], x+xi+3,y+xi);
	}

	gdk_draw_point(window,galaxy_style->gray_gc[2], x+max_length-1,y);
	gdk_draw_point(window,galaxy_style->gray_gc[2], x+max_length,y+1);
      }
      break; 
    default:
      g_assert_not_reached ();
      break;
    }
  
  if (area)
    {
      gdk_gc_set_clip_rectangle (galaxy_style->gray_gc[2], NULL);
      gdk_gc_set_clip_rectangle (galaxy_style->gray_gc[6], NULL);
      gdk_gc_set_clip_rectangle (galaxy_style->gray_gc[7], NULL);
      gdk_gc_set_clip_rectangle (style->white_gc, NULL);
    }
}

static void draw_arrow (GtkStyle      *style,
			GdkWindow     *window,
			GtkStateType   state,
			GtkShadowType  shadow,
			GdkRectangle  *area,
			GtkWidget     *widget,
			const gchar   *detail,
			GtkArrowType   arrow_type,
			gboolean       fill,
			gint           x,
			gint           y,
			gint           width,
			gint           height) {

  if (DETAIL ("spinbutton") &&
      (arrow_type == GTK_ARROW_DOWN)) {
    y += 1;
  }

  parent_class->draw_arrow (style, window, state, shadow, area, widget, detail, arrow_type, fill, x, y, width, height);

}


static GdkGC *
realize_color (GtkStyle * style,
	       GdkColor * color)
{
  GdkGCValues gc_values;

  gdk_colormap_alloc_color (style->colormap, color,
			    FALSE, TRUE);

  gc_values.foreground = *color;

  return gtk_gc_get (style->depth, style->colormap,
		     &gc_values, GDK_GC_FOREGROUND);
}
static GdkPixmap *
pixbuf_to_pixmap (GtkStyle * style, GdkPixbuf *pixbuf)
{
  GdkGC *tmp_gc;
  GdkPixmap *pixmap;
  
  pixmap = gdk_pixmap_new (NULL,
			   gdk_pixbuf_get_width (pixbuf),
			   gdk_pixbuf_get_height (pixbuf),
			   style->depth);
  gdk_drawable_set_colormap (pixmap, style->colormap);

  tmp_gc = gdk_gc_new (pixmap);
  
  gdk_pixbuf_render_to_drawable (pixbuf, pixmap, tmp_gc, 0, 0, 0, 0,
				 gdk_pixbuf_get_width (pixbuf),
				 gdk_pixbuf_get_height (pixbuf),
				 GDK_RGB_DITHER_NORMAL, 0, 0);
  gdk_gc_unref (tmp_gc);

  return pixmap;
}



static void galaxy_style_realize(GtkStyle * style)
{
  GalaxyStyle *galaxy_style = GALAXY_STYLE (style);
  GalaxyRcStyle *galaxy_rc = GALAXY_RC_STYLE (style->rc_style);
  GdkPixbuf *dot, *circle, *outline, *inconsistent, *composite, *check;
  GdkColor *composite_color;

  int i;

  parent_class->realize (style);

  gdk_color_parse ("#EFEFEF", &galaxy_style->gray[0]);
  gdk_color_parse ("#E6E7E6", &galaxy_style->gray[1]);
  gdk_color_parse ("#CECECE", &galaxy_style->gray[2]);
  gdk_color_parse ("#BDBEBD", &galaxy_style->gray[3]);
  gdk_color_parse ("#ADAAAD", &galaxy_style->gray[4]);
  gdk_color_parse ("#A5A6A5", &galaxy_style->gray[5]);
  gdk_color_parse ("#949694", &galaxy_style->gray[6]);
  gdk_color_parse ("#848684", &galaxy_style->gray[7]);
		                                  
  gdk_color_parse ("#7382BC", &galaxy_style->blue[0]);
  gdk_color_parse ("#4A61AD", &galaxy_style->blue[1]);
  gdk_color_parse ("#21459C", &galaxy_style->blue[2]);

  gdk_color_parse ("#333333", &galaxy_style->check_color);

  galaxy_style->check_gc = realize_color (style, &galaxy_style->check_color);

  for (i=0; i <8 ; i++) {
    galaxy_rc->enable_gradient = galaxy_rc->enable_gradient || gdk_color_equal (&galaxy_style->gray[i],&style->bg[GTK_STATE_NORMAL]);
    galaxy_style->gray_gc[i] = realize_color (style, &galaxy_style->gray[i]);
  }

  if (!galaxy_rc->enable_gradient) {
    style->xthickness = style->ythickness = 1;
  }

  for (i=0; i <3 ; i++) {
    galaxy_style->blue_gc[i] = realize_color (style, &galaxy_style->blue[i]);
  }

  inconsistent = generate_bit (inconsistent_alpha, &galaxy_style->gray[2], 1.0);
  outline = generate_bit (outline_alpha, &galaxy_style->gray[6], 1.0);
  dot = colorize_bit (dot_intensity, dot_alpha, &galaxy_style->check_color);

  gdk_pixbuf_render_pixmap_and_mask (outline,
				     NULL,
				     &galaxy_style->radio_pixmap_mask,
				     1);
  
  for (i = 0; i < 5; i++)
    {
      if (i == GTK_STATE_ACTIVE)
	{
	  composite_color = &style->bg[GTK_STATE_PRELIGHT];
	  circle = generate_bit (circle_alpha, &style->bg[i], 1.0);
	}   
      else
	{
	  composite_color = &style->bg[i];
	  circle = generate_bit (circle_alpha, &style->white, 1.0);
	}

      composite = generate_bit (NULL, composite_color, 1.0);

      gdk_pixbuf_composite (outline, composite,
			    0, 0, RADIO_SIZE, RADIO_SIZE, 0, 0,
			    1.0, 1.0, GDK_INTERP_NEAREST, 255);
      gdk_pixbuf_composite (circle, composite,
			    0, 0, RADIO_SIZE, RADIO_SIZE, 0, 0,
			    1.0, 1.0, GDK_INTERP_NEAREST, 255);

      galaxy_style->radio_pixmap_nonactive[i] = pixbuf_to_pixmap (style, composite);
      
      gdk_pixbuf_composite (dot, composite,
			    0, 0, RADIO_SIZE, RADIO_SIZE, 0, 0,
			    1.0, 1.0, GDK_INTERP_NEAREST, 255);
      
      galaxy_style->radio_pixmap_active[i] = pixbuf_to_pixmap (style, composite);
      
      g_object_unref (composite);

      composite = generate_bit (NULL, composite_color,1.0);

      gdk_pixbuf_composite (outline, composite,
			    0, 0, RADIO_SIZE, RADIO_SIZE, 0, 0,
			    1.0, 1.0, GDK_INTERP_NEAREST, 255);
      gdk_pixbuf_composite (circle, composite,
			    0, 0, RADIO_SIZE, RADIO_SIZE, 0, 0,
			    1.0, 1.0, GDK_INTERP_NEAREST, 255);
      gdk_pixbuf_composite (inconsistent, composite,
			    0, 0, RADIO_SIZE, RADIO_SIZE, 0, 0,
			    1.0, 1.0, GDK_INTERP_NEAREST, 255);
      
      galaxy_style->radio_pixmap_inconsistent[i] = pixbuf_to_pixmap (style, composite);
      
      g_object_unref (composite);
      g_object_unref (circle);

    }
  g_object_unref (dot);  
  g_object_unref (inconsistent);
  g_object_unref (outline);

}

static void galaxy_style_unrealize(GtkStyle * style)
{  
  GalaxyStyle *galaxy_style = GALAXY_STYLE (style);
  int i;

  /* We don't free the colors, because we don't know if
   * gtk_gc_release() actually freed the GC. FIXME - need
   * a way of ref'ing colors explicitely so GtkGC can
   * handle things properly.
   */

  for (i=0; i <8 ; i++) {
    gtk_gc_release (galaxy_style->gray_gc[i]);
  }

  for (i=0; i <3 ; i++) {
    gtk_gc_release (galaxy_style->blue_gc[i]);
  }

  for (i = 0; i < 5; i++) {
    g_object_unref (galaxy_style->radio_pixmap_nonactive[i]);
    g_object_unref (galaxy_style->radio_pixmap_active[i]);
    g_object_unref (galaxy_style->radio_pixmap_inconsistent[i]);
  }

  g_object_unref (galaxy_style->radio_pixmap_mask);

  parent_class->unrealize (style);
}

static void galaxy_style_class_init(GalaxyStyleClass * klass)
{
    GtkStyleClass *style_class = GTK_STYLE_CLASS(klass);

    parent_class = g_type_class_peek_parent(klass);

    style_class->realize = galaxy_style_realize;
    style_class->unrealize = galaxy_style_unrealize;

    style_class->draw_hline = draw_hline;
    style_class->draw_vline = draw_vline;
    style_class->draw_shadow = draw_shadow;
    style_class->draw_polygon = draw_polygon;
    style_class->draw_diamond = draw_diamond;
    style_class->draw_box = draw_box;
    style_class->draw_check = draw_check;
    style_class->draw_option = draw_option;
    style_class->draw_shadow_gap = draw_shadow_gap;
    style_class->draw_box_gap = draw_box_gap;
    style_class->draw_extension = draw_extension;
    style_class->draw_slider = draw_slider;
    style_class->draw_handle = draw_handle;
    style_class->draw_resize_grip = draw_resize_grip;
    style_class->draw_arrow = draw_arrow;
}


static void
galaxy_style_init (GalaxyStyle * style)
{
}

GType galaxy_type_style = 0;

void galaxy_style_register_type(GTypeModule * module)
{
    static const GTypeInfo object_info = {
        sizeof(GalaxyStyleClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) galaxy_style_class_init,
        NULL,                   /* class_finalize */
        NULL,                   /* class_data */
        sizeof(GalaxyStyle),
        0,                      /* n_preallocs */
        (GInstanceInitFunc) galaxy_style_init,
	NULL
    };

    galaxy_type_style = g_type_module_register_type(module, GTK_TYPE_STYLE, 
						    "GalaxyStyle", 
						    &object_info, 0);
}
