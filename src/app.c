#include "app.h"    
    
void
app_init (App * app)
{
  //init builder  
  GError *err = NULL;
    
  app->definitions = gtk_builder_new ();

  gchar definition_file[PATH_MAX] = {0};
  GET_FILE(SHARE_DIR"/"PROJECT_NAME"/"UI_DEFINITION_FILE, definition_file);

  gtk_builder_add_from_file (app->definitions,
                             definition_file, &err);
                             
  if (err != NULL) {
    g_printerr
      ("Error while loading UI definitions file: %s\n",
       err->message);
    g_error_free (err);
    gtk_main_quit ();
  }
    
  gtk_builder_connect_signals (app->definitions, app);
  
  //init gsettings
  GSettings * settings = g_settings_new ("sampleapp");
  gboolean display_at_startup = g_settings_get_boolean(settings, "display-at-startup");
  gchar *message = g_settings_get_string(settings, "message");
  
  if(display_at_startup){
    g_printf(message);
  }
}

#ifdef _WIN32
void path_relative(gchar *path, gchar *res){
  //get the .exe full path and filename
  gchar buffer[PATH_MAX];
  GetModuleFileName(NULL, buffer, PATH_MAX) ;
	
  gchar *dirname = g_path_get_dirname(buffer);
  g_strlcat(res, dirname, PATH_MAX);
  g_free(dirname);

  g_strlcat(res, "\\", PATH_MAX);
  g_strlcat(res, path, PATH_MAX);
}
#endif
