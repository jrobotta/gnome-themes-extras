/*  ggalaxy
 *  Copyright (C) 2003 Frederic Crozat - MandrakeSoft
 *  1999 Olivier Fourdan (fourdan@xfce.org) for XFCE code
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

#include <gtk/gtkrc.h>

typedef struct _GalaxyRcStyle GalaxyRcStyle;
typedef struct _GalaxyRcStyleClass GalaxyRcStyleClass;

extern GType galaxy_type_rc_style;

#define GALAXY_TYPE_RC_STYLE              galaxy_type_rc_style
#define GALAXY_RC_STYLE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), GALAXY_TYPE_RC_STYLE, GalaxyRcStyle))
#define GALAXY_RC_STYLE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), GALAXY_TYPE_RC_STYLE, GalaxyRcStyleClass))
#define GALAXY_IS_RC_STYLE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), GALAXY_TYPE_RC_STYLE))
#define GALAXY_IS_RC_STYLE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GALAXY_TYPE_RC_STYLE))
#define GALAXY_RC_STYLE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), GALAXY_TYPE_RC_STYLE, GalaxyRcStyleClass))

struct _GalaxyRcStyle
{
  GtkRcStyle parent_instance;

  gboolean enable_gradient;

};

struct _GalaxyRcStyleClass
{
    GtkRcStyleClass parent_class;
};

void galaxy_rc_style_register_type(GTypeModule * module);
