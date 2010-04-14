/*  Copyright (C) 2007-2010, Evgeny Ratnikov

    This file is part of termit.
    termit is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 2 
    as published by the Free Software Foundation.
    termit is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with termit. If not, see <http://www.gnu.org/licenses/>.*/

#include <string.h>
#include <gtk/gtk.h>

#include <config.h>

#include "termit_style.h"

void termit_style_init(struct TermitStyle* style)
{
    style->font_name = g_strdup("Monospace 10");
    style->font = pango_font_description_from_string(style->font_name);
    {
        GdkColor color = {0};
        if (gdk_color_parse("gray", &color) == TRUE) {
            style->foreground_color = color;
        }
    }
    {
        GdkColor color = {0};
        if (gdk_color_parse("black", &color) == TRUE) {
            style->background_color = color;
        }
    }
    style->colormap = NULL;
    style->transparency = 0;    
}

void termit_style_free(struct TermitStyle* style)
{
    g_free(style->font_name);
    pango_font_description_free(style->font);
    if (style->colormap) {
        g_free(style->colormap->colors);
        g_free(style->colormap);
    }
    struct TermitStyle tmp = {0};
    *style = tmp;
}

void termit_style_copy(struct TermitStyle* dest, const struct TermitStyle* src)
{
    dest->font_name = g_strdup(src->font_name);
    dest->foreground_color = src->foreground_color;
    dest->background_color = src->background_color;
    dest->font = pango_font_description_from_string(src->font_name);
    dest->transparency = src->transparency;
    if (dest->colormap) {
        dest->colormap = g_malloc0(sizeof(GdkColormap));
        dest->colormap->size = src->colormap->size;
        dest->colormap->colors = g_memdup(src->colormap->colors, src->colormap->size * sizeof(GdkColor));
    } else {
        dest->colormap = NULL;
    }
}
