#include "app.h"    
    
void
app_init (App * app)
{
  GError *err = NULL;
    
  app->definitions = gtk_builder_new ();

  gtk_builder_add_from_file (app->definitions,
                             UI_DEFINITIONS_FILE, &err);
    
  if (err != NULL) {
    g_printerr
      ("Error while loading app definitions file: %s\n",
       err->message);
    g_error_free (err);
    gtk_main_quit ();
  }
    
  gtk_builder_connect_signals (app->definitions, app);
}
