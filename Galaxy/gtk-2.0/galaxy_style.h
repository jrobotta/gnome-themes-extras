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

#include <gtk/gtkstyle.h>

typedef struct _GalaxyStyle GalaxyStyle;
typedef struct _GalaxyStyleClass GalaxyStyleClass;

extern GType galaxy_type_style;

#define GALAXY_TYPE_STYLE              galaxy_type_style
#define GALAXY_STYLE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), GALAXY_TYPE_STYLE, GalaxyStyle))
#define GALAXY_STYLE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), GALAXY_TYPE_STYLE, GalaxyStyleClass))
#define GALAXY_IS_STYLE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), GALAXY_TYPE_STYLE))
#define GALAXY_IS_STYLE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GALAXY_TYPE_STYLE))
#define GALAXY_STYLE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), GALAXY_TYPE_STYLE, GalaxyStyleClass))

struct _GalaxyStyle
{
  GtkStyle parent_instance;
  GdkColor gray[8]; /* from light to dark */
  GdkColor blue[3]; /* from light to dark */
  GdkColor check_color;
  
  GdkGC *gray_gc[8]; /* from light to dark */
  GdkGC *blue_gc[3]; /* from light to dark */

  GdkGC *check_gc;

  GdkPixmap *radio_pixmap_nonactive[5];
  GdkPixmap *radio_pixmap_active[5];
  GdkPixmap *radio_pixmap_inconsistent[5];
  GdkBitmap *radio_pixmap_mask; /* All masks are the same */

};

struct _GalaxyStyleClass
{
    GtkStyleClass parent_class;
};

void galaxy_style_register_type(GTypeModule * module);
