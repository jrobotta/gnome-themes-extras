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

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include "galaxy_rc_style.h"
#include "galaxy_style.h"

static void galaxy_rc_style_init(GalaxyRcStyle * style);
static void galaxy_rc_style_class_init(GalaxyRcStyleClass * klass);
static void galaxy_rc_style_finalize(GObject * object);
static guint galaxy_rc_style_parse(GtkRcStyle * rc_style, GtkSettings * settings, GScanner * scanner);
static void galaxy_rc_style_merge(GtkRcStyle * dest, GtkRcStyle * src);

static GtkStyle *galaxy_rc_style_create_style(GtkRcStyle * rc_style);

static GtkRcStyleClass *parent_class;

GType galaxy_type_rc_style = 0;

enum
{
    TOKEN_GRADIENT = G_TOKEN_LAST + 1,
    TOKEN_TRUE,
    TOKEN_FALSE,
};

static struct
{
  const gchar *name;
  guint        token;
}
theme_symbols[] =
{
  { "enable_gradient", TOKEN_GRADIENT },
  { "TRUE",            TOKEN_TRUE},
  { "FALSE",           TOKEN_FALSE},
};

static guint n_theme_symbols = sizeof(theme_symbols) / sizeof(theme_symbols[0]);


void galaxy_rc_style_register_type(GTypeModule * module)
{
    static const GTypeInfo object_info = {
        sizeof(GalaxyRcStyleClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) galaxy_rc_style_class_init,
        NULL,                   /* class_finalize */
        NULL,                   /* class_data */
        sizeof(GalaxyRcStyle),
        0,                      /* n_preallocs */
        (GInstanceInitFunc) galaxy_rc_style_init,
	NULL
    };

    galaxy_type_rc_style = g_type_module_register_type(module, 
						       GTK_TYPE_RC_STYLE, 
						       "GalaxyRcStyle", 
						       &object_info, 0);
}

static void galaxy_rc_style_init(GalaxyRcStyle * style)
{
}

static void galaxy_rc_style_class_init(GalaxyRcStyleClass * klass)
{
    GtkRcStyleClass *rc_style_class = GTK_RC_STYLE_CLASS(klass);
    GObjectClass *object_class = G_OBJECT_CLASS(klass);

    parent_class = g_type_class_peek_parent(klass);

    rc_style_class->parse = galaxy_rc_style_parse;
    rc_style_class->merge = galaxy_rc_style_merge;
    rc_style_class->create_style = galaxy_rc_style_create_style;
}

static guint theme_parse_boolean(GScanner * scanner, GTokenType wanted_token, guint * retval)
{
    guint token;

    token = g_scanner_get_next_token(scanner);
    if(token != wanted_token)
        return wanted_token;

    token = g_scanner_get_next_token(scanner);
    if(token != G_TOKEN_EQUAL_SIGN)
        return G_TOKEN_EQUAL_SIGN;

    token = g_scanner_get_next_token(scanner);
    if(token == TOKEN_TRUE)
        *retval = TRUE;
    else if(token == TOKEN_FALSE)
        *retval = FALSE;
    else
        return TOKEN_TRUE;

    return G_TOKEN_NONE;
}


static guint galaxy_rc_style_parse(GtkRcStyle * rc_style, GtkSettings * settings, GScanner * scanner)
{
    static GQuark scope_id = 0;
    GalaxyRcStyle *theme_data = GALAXY_RC_STYLE(rc_style);
    guint old_scope;
    guint token;
    guint i;

    /* Set up a new scope in this scanner. */

    if(!scope_id)
        scope_id = g_quark_from_string("theme_engine");

    old_scope = g_scanner_set_scope(scanner, scope_id);

    if(!g_scanner_lookup_symbol(scanner, theme_symbols[0].name)) {
        for(i = 0; i < n_theme_symbols; i++)
        {
            g_scanner_scope_add_symbol(scanner, scope_id, theme_symbols[i].name, 
				       GINT_TO_POINTER(theme_symbols[i].token));
        }
    }
    theme_data->enable_gradient = TRUE;

    token = g_scanner_peek_next_token(scanner);
    while(token != G_TOKEN_RIGHT_CURLY)
    {
      switch (token)
        {
            case TOKEN_GRADIENT:
                token = theme_parse_boolean(scanner, TOKEN_GRADIENT, &i);
                if(token != G_TOKEN_NONE)
                {
                    break;
                }
                theme_data->enable_gradient = i;
                break;
            default:
                g_scanner_get_next_token(scanner);
                token = G_TOKEN_RIGHT_CURLY;
                break;
        }


        if(token != G_TOKEN_NONE)
        {
            g_free(theme_data);
            return token;
        }
        token = g_scanner_peek_next_token(scanner);
    }

    g_scanner_get_next_token(scanner);

    g_scanner_set_scope(scanner, old_scope);

    return G_TOKEN_NONE;
}

static void galaxy_rc_style_merge(GtkRcStyle * dest, GtkRcStyle * src)
{
    parent_class->merge(dest, src);
}

/* Create an empty style suitable to this RC style
 */
static GtkStyle *galaxy_rc_style_create_style(GtkRcStyle * rc_style)
{
    return GTK_STYLE(g_object_new(GALAXY_TYPE_STYLE, NULL));
}
