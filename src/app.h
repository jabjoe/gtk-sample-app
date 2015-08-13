#ifndef __APP__
#define __APP__
    
#include <gtk/gtk.h>

#include <locale.h>
#include <libintl.h>

#include "../config.h"

#define UI_DEFINITION_FILE "ui.glade"

/*
Under Window the app can be installed in any directory with a graphical 
installer (NSIS), the path is relative to the exe
Under Linux this is a simple string copy of the absolute path
*/

#ifdef _WIN32
#include <Windows.h>

#define GET_FILE(FILE, RES) path_relative(FILE, RES)
#else	
#include <linux/limits.h>
#define GET_FILE(FILE, RES) strcpy(RES, FILE)
#endif


#define GET_OBJECT(TYPE, ELEMENT)   TYPE *ELEMENT = (TYPE *)\
    gtk_builder_get_object(app->definitions, #ELEMENT);

typedef struct app_
{
  GtkBuilder *definitions;    
} App;
    
void app_init (App * );

void path_relative(gchar *path, gchar *res);
#endif
