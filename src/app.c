#include "app.h"


static void settings_changed(GSettings *settings,
                               gchar *key,
                               gpointer user_data)
{
}

void
app_init (App * app)
{
  //init builder
  GError *err = NULL;

  app->definitions = gtk_builder_new ();


  const gchar * const * dirs = g_get_system_data_dirs();
  gchar* rest = g_strjoin(G_DIR_SEPARATOR_S,
			  PROJECT_NAME,
			  "ui",
			  UI_DEFINITION_FILE,
			  NULL);
  const gchar* definition_file = get_file(dirs, rest);
  g_free(rest);

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
  app->settings = g_settings_new ("sampleapp");

  g_signal_connect(app->settings,
                   "changed",
                   G_CALLBACK (settings_changed),
                   NULL);

  //set the entry message text
  gchar *message = g_settings_get_string(app->settings, "message");
  GET_OBJECT (GtkWidget, entry_message);
  gtk_entry_set_text(GTK_ENTRY(entry_message), message);

}

const gchar* get_file(const gchar* const *dirs, const gchar* rest){
  gint i;
  const gchar* res = NULL;
  for (i = 0; dirs[i]; i++){
    res = g_strjoin (G_DIR_SEPARATOR_S, dirs[i], rest, NULL);
    if(g_file_test(res, G_FILE_TEST_EXISTS))return res;
    else g_free(res);
  }
  return NULL;
}


#ifdef _WIN32
void path_relative(gchar *path, gchar *res){
  //get the .exe full path and filename
  gchar buffer[PATH_MAX];
  GetModuleFileName(NULL, buffer, PATH_MAX) ;

  //get only the directory path (without filename.exe)
  gchar *dirname = g_path_get_dirname(buffer);

  //copy to the result varable
  g_strlcat(res, dirname, PATH_MAX);

  //free now unneeded variable
  g_free(dirname);

  //append the path to the result
  g_strlcat(res, "\\", PATH_MAX);
  g_strlcat(res, path, PATH_MAX);
}
#endif
