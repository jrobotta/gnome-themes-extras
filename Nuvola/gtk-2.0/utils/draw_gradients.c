#include "misc_functions.h"

/* Most of the following functions were taken originaly from the 
 * IceGradient & EnGradient engines, however, after taking a 
 * look at the sources more closely I realized that 600+ lines
 * were a waste of repetetive code in multiple routines, so I merged
 * the bulk of the code into one major routine: gdk_draw_gradient,
 * which was then broken out into alloc_gradient_color to take care of
 * several repetitions of that. I then took style specific code from
 * EnGradient and converted into style_draw_gradient, which simply
 * called to gdk_draw_gradient for the real work.
 *
 *It still needs more work, and better support for multiple gradients.
 */

/* This function is taken and slightly from Wonderland, though 
 * I have seen it in other engines as well, and it apears
 * to have originated in GTK+ itself.
 */
static void
rgb_to_hls (gdouble *r,
            gdouble *g,
            gdouble *b)
{
  gdouble red=*r, green=*g, blue=*b;
  gdouble h, l, s;
  gdouble min, max, delta;
    
  if (red > green)
    {
      max = MAX(red, blue);
      min = MIN(green, blue);      
    }
  else
    {
      max = MAX(green, blue);
      min = MIN(red, blue);      
    }
  
  l = (max + min) / 2;
  s = 0;
  h = 0;
  
  if (max != min)
    {
      if (l <= 0.5)
        s = (max - min) / (max + min);
      else
        s = (max - min) / (2 - max - min);
      
      delta = max -min;
      if (red == max)
        h = (green - blue) / delta;
      else if (green == max)
        h = 2 + (blue - red) / delta;
      else if (blue == max)
        h = 4 + (red - green) / delta;
      
      h *= 60;
      if (h < 0.0)
        h += 360;
    }
  
  *r = h;
  *g = l;
  *b = s;
}

/* This function is taken and slightly from Wonderland, though 
 * I have seen it in other engines as well, and it apears
 * to have originated in GTK+ itself.
 */
static void
hls_to_rgb (gdouble *h,
            gdouble *l,
            gdouble *s)
{
  gdouble hue = *h + 120;
  gdouble lightness = *l;
  gdouble saturation = *s;
  gdouble m1, m2;
  gdouble r, g, b;
  
  if (lightness <= 0.5)
    m2 = lightness * (1 + saturation);
  else
    m2 = lightness + saturation - lightness * saturation;
  m1 = 2 * lightness - m2;
  
  if (saturation == 0)
    {
      *h = lightness;
      *l = lightness;
      *s = lightness;
    }
  else
    {
      while (hue > 360)
        hue -= 360;
      while (hue < 0)
        hue += 360;
      
      if (hue < 60)
        r = m1 + (m2 - m1) * hue / 60;
      else if (hue < 180)
        r = m2;
      else if (hue < 240)
        r = m1 + (m2 - m1) * (240 - hue) / 60;
      else
        r = m1;
      
      hue = *h;
      while (hue > 360)
        hue -= 360;
      while (hue < 0)
        hue += 360;
      
      if (hue < 60)
        g = m1 + (m2 - m1) * hue / 60;
      else if (hue < 180)
        g = m2;
      else if (hue < 240)
        g = m1 + (m2 - m1) * (240 - hue) / 60;
      else
        g = m1;
      
      hue = *h - 120;
      while (hue > 360)
        hue -= 360;
      while (hue < 0)
        hue += 360;
      
      if (hue < 60)
        b = m1 + (m2 - m1) * hue / 60;
      else if (hue < 180)
        b = m2;
      else if (hue < 240)
        b = m1 + (m2 - m1) * (240 - hue) / 60;
      else
        b = m1;
      
      *h = r;
      *l = g;
      *s = b;
    }
}

/* This function is taken and slightly from Wonderland, though 
 * I have seen it in other engines as well, and it apears
 * to have originated in GTK+ itself.
 */
void
shade (GdkColor * a, GdkColor * b, gdouble k)
{
  gdouble red = (gdouble) a->red / 65535.0;
  gdouble green = (gdouble) a->green / 65535.0;
  gdouble blue = (gdouble) a->blue / 65535.0;
  
  rgb_to_hls (&red, &green, &blue);
  
  green = MIN(green*k, 1.0);
  green = MAX(green, 0.0);
  
  blue = MIN(blue*k, 1.0);
  blue = MAX(blue, 0.0);
  
  hls_to_rgb (&red, &green, &blue);
  
  b->red = red * 65535.0;
  b->green = green * 65535.0;
  b->blue = blue * 65535.0;
}

void 
alloc_gradient_color(GdkColor * color,
                     GdkColormap * colormap,
                     GdkColor light, 
                     GdkColor dark,
                     gint position,
                     gint steps,
                     gboolean quadratic)
{
  gfloat a, b, c, delta;
  if (quadratic) {
    
    /* delta = ax� + bx� + cx */ 
   
    a = 4.0 / (steps * steps * steps);
    b = -6.0 / (steps * steps);
    c = 3.0 / steps;
   
    delta = (a * pow(position, 3)) + (b * pow(position, 2)) + (c * position);
  } else {
    /* delta = i/steps */     
    delta = ((float)position/(float)steps);
  }
  color->red = light.red + (float)((dark.red - light.red))*delta;
  color->green = light.green + (float)((dark.green - light.green))*delta;
  color->blue = light.blue + (float)((dark.blue - light.blue))*delta;
  gdk_colormap_alloc_color(colormap, color, FALSE, TRUE);
}

/*
 * Explanation of the quadratic gradient formula:
 * y|
 *  |\        /        If you use linear gradients in buttons the text is difficult to read because
 *  | \      /         the color range of the background is too wide. The idea is to make the range
 *  |  \    /          shorter in the center where the text will be. An easy way to do it would be
 *  !   -__-           to set the relative distances between steps corresponding to a something like
 * -+----------|-x                            y = (x - w/2)² for x in [0,w]
 *  |          w       where w is the number of steps in the gradient.
 *                     At step w you'll have the acumulated sum of all steps and thus
 *                                   int(y, 0, w) = w³/12
 * At each step you would get
 *                               int(y) = x³/3 - wx²/2 + w²x/4
 * If you want a coefficient in [0,1]
 *                      int(y) / int(y, 0, w) = 4x³/w³ - 6x²/w² + 3x/w =
 *                                            = ax³ + bx² + cx
*/

void
gdk_draw_gradient (GdkWindow * window,
                   GdkGC * gc,
                   GdkColormap * colormap,
                   GdkRectangle * area,
                   gint x,
                   gint y,
                   gint width,
                   gint height,
                   GdkColor light, 
                   GdkColor dark, 
                   GdkGradientType gradient_type,
                   gboolean quadratic,
		   gboolean noclip)
{
  GdkRectangle clip;
  GdkColor color;
  gint i, steps=0;
  gboolean horizontal = (gradient_type == GDK_GRADIENT_HORIZONTAL);
  gboolean northern   = (gradient_type == GDK_GRADIENT_NORTHERN_DIAGONAL);
  gboolean diagonal   = ((gradient_type == GDK_GRADIENT_NORTHERN_DIAGONAL) || (gradient_type == GDK_GRADIENT_SOUTHERN_DIAGONAL));

  clip.x = x;
  clip.y = y;
  clip.width = width;
  clip.height = height;

  g_return_if_fail(window != NULL);
  g_return_if_fail(colormap != NULL);
  g_return_if_fail(gc != NULL);
    
  if (diagonal)
    steps = width + height - 1;
  else if (horizontal)
    steps = width; 
  else
    steps = height;

  if (!noclip) {
    if (area) {
      GdkRectangle clip2;       
      if (gdk_rectangle_intersect(area,&clip, &clip2))
        gdk_gc_set_clip_rectangle(gc, &clip2);
      else
        gdk_gc_set_clip_rectangle(gc, area);
    } else
      gdk_gc_set_clip_rectangle(gc, &clip);
  }
   
  for(i=0; i < steps; i++) {
    alloc_gradient_color(&color, colormap, light, dark, i, steps, quadratic);
    gdk_gc_set_foreground(gc, &color);
    if (diagonal) {
      if (northern)
        gdk_draw_line (window, gc, x + i, y, x, y + i);
      else
        gdk_draw_line (window, gc, x + width - 1 - i, y, x + width - 1, y + i);         
    } else {
      if (horizontal)
        gdk_draw_line(window, gc, x+i, y, x+i, y+height);
      else
        gdk_draw_line(window, gc, x, y+i, x+width, y+i);
    }
    gdk_colormap_free_colors(colormap, &color, 1);
  }

  if (!noclip)
    gdk_gc_set_clip_rectangle(gc, NULL); 
}

void
gdk_draw_shaded_gradient (GdkWindow * window,
                          GdkGC * gc,
                          GdkColormap * colormap,
                          GdkRectangle * area,
                          gint x,
                          gint y,
                          gint width,
                          gint height,
                          GdkColor color, 
                          gfloat shade_value, 
                          gfloat shine_value, 
                          GdkGradientType gradient_type,
                          gboolean quadratic,
			  gboolean noclip)
{
  GdkColor light, dark;
  
  shade (&color, &dark, shade_value);
  shade (&color, &light, shine_value);

  gdk_draw_gradient(window, gc, colormap, area, x, y, width, height, light, dark, gradient_type, quadratic, noclip);
}
