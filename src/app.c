#include "app.h"    
    
void
app_init (App * app)
{
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
