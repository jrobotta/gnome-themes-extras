#ifndef DRAW_GRADIENTS_H
#define DRAW_GRADIENTS_H

typedef enum {
  GDK_GRADIENT_HORIZONTAL,
  GDK_GRADIENT_VERTICAL,
  GDK_GRADIENT_NORTHERN_DIAGONAL,
  GDK_GRADIENT_SOUTHERN_DIAGONAL
} GdkGradientType;

#define GRADIENT(horizontal) (horizontal ? GDK_GRADIENT_HORIZONTAL : GDK_GRADIENT_VERTICAL)
#define DIAGONALGRADIENT(northern) (northern ? GDK_GRADIENT_NORTHERN_DIAGONAL : GDK_GRADIENT_SOUTHERN_DIAGONAL)

void 
alloc_gradient_color(GdkColor * color,
                     GdkColormap * colormap,
                     GdkColor light, 
                     GdkColor dark,
                     gint position,
                     gint steps,
                     gboolean quadratic);

void
shade (GdkColor * a, GdkColor * b, gdouble k);

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
		   gboolean noclip);

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
			  gboolean noclip);

#endif /* DRAW_GRADIENTS_H */
