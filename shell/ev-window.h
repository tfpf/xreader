/* this file is part of xreader, a generic document viewer
 *
 *  Copyright (C) 2004 Martin Kretzschmar
 *
 *  Author:
 *    Martin Kretzschmar <martink@gnome.org>
 *
 * Xreader is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Xreader is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef EV_WINDOW_H
#define EV_WINDOW_H

#include <glib.h>
#include <gtk/gtk.h>

#include "ev-link.h"
#include "ev-document-model.h"

G_BEGIN_DECLS

/* Gsettings schema names */
#define GS_SCHEMA_NAME             "org.x.reader"
#define GS_SCHEMA_NAME_TOOLBAR     "org.x.reader.toolbar"
#define GS_SCHEMA_NAME_DEFAULT     "org.x.reader.default"

/* Schema keys: General */
#define GS_OVERRIDE_RESTRICTIONS   "override-restrictions"
#define GS_PAGE_CACHE_SIZE         "page-cache-size"
#define GS_AUTO_RELOAD             "auto-reload"
#define GS_LAST_DOCUMENT_DIRECTORY "document-directory"
#define GS_LAST_PICTURES_DIRECTORY "pictures-directory"

/* Schema keys: Toolbar */
#define GS_SHOW_EXPAND_WINDOW      "show-expand-window"
#define GS_SHOW_ZOOM_ACTION        "show-zoom-action"
#define GS_SHOW_HISTORY_BUTTONS    "show-history-buttons"

typedef enum {
    EV_WINDOW_MODE_NORMAL,
    EV_WINDOW_MODE_FULLSCREEN,
    EV_WINDOW_MODE_PRESENTATION
} EvWindowRunMode;

typedef struct {
    gint start;
    gint end;
} EvPrintRange;

typedef enum {
    EV_PRINT_PAGE_SET_ALL,
    EV_PRINT_PAGE_SET_EVEN,
    EV_PRINT_PAGE_SET_ODD
} EvPrintPageSet;

typedef struct _EvWindow EvWindow;
typedef struct _EvWindowClass EvWindowClass;
typedef struct _EvWindowPrivate EvWindowPrivate;

#define EV_TYPE_WINDOW              (ev_window_get_type())
#define EV_WINDOW(object)           (G_TYPE_CHECK_INSTANCE_CAST((object), EV_TYPE_WINDOW, EvWindow))
#define EV_WINDOW_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST((klass), EV_TYPE_WINDOW, EvWindowClass))
#define EV_IS_WINDOW(object)        (G_TYPE_CHECK_INSTANCE_TYPE((object), EV_TYPE_WINDOW))
#define EV_IS_WINDOW_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE((klass), EV_TYPE_WINDOW))
#define EV_WINDOW_GET_CLASS(object) (G_TYPE_INSTANCE_GET_CLASS((object), EV_TYPE_WINDOW, EvWindowClass))


struct _EvWindow {
    GtkApplicationWindow    base_instance;
    EvWindowPrivate        *priv;
};

struct _EvWindowClass {
    GtkApplicationWindowClass     base_class;
};

GType               ev_window_get_type                  (void) G_GNUC_CONST;
GtkWidget *         ev_window_new                       (void);
const char *        ev_window_get_uri                   (EvWindow       *ev_window);
void                ev_window_open_uri                  (EvWindow       *ev_window,
                                                         const char     *uri,
                                                         EvLinkDest     *dest,
                                                         EvWindowRunMode mode,
                                                         const gchar    *search_string);
void                ev_window_open_document             (EvWindow       *ev_window,
                                                         EvDocument     *document,
                                                         EvLinkDest     *dest,
                                                         EvWindowRunMode mode,
                                                         const gchar    *search_string);
gboolean            ev_window_is_empty                  (const EvWindow *ev_window);
void                ev_window_print_range               (EvWindow       *ev_window,
                                                         int             first_page,
                                                         int             last_page);
const gchar *       ev_window_get_dbus_object_path      (EvWindow       *ev_window);
void                ev_window_show_help                 (EvWindow       *ev_window,
                                                         const gchar    *uri);
GtkActionGroup *    ev_window_get_main_action_group     (EvWindow       *window);
EvDocumentModel *   ev_window_get_document_model        (EvWindow       *ev_window);


G_END_DECLS

#endif /* !EV_WINDOW_H */
