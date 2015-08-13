#ifndef __APP__
#define __APP__
    
#include <gtk/gtk.h>

#include <locale.h>
#include <libintl.h>

#include "../config.h"

#define UI_DEFINITIONS_FILE DATADIR"/ui.glade"
    
#define GET_OBJECT(TYPE, ELEMENT)   TYPE *ELEMENT = (TYPE *)\
    gtk_builder_get_object(app->definitions, #ELEMENT);

typedef struct app_
{
  GtkBuilder *definitions;    
} App;
    
void app_init (App * );
    
#endif
