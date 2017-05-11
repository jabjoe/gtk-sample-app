#include "app.h"

int main( int argc, char **argv )
{
  //internationalization
  setlocale(LC_MESSAGES, "");
  bindtextdomain(PROJECT_NAME, LOCALE_DIR);
  textdomain(PROJECT_NAME);

  //new application
  App *app = g_new(App, 1);

  //initialization
  gtk_init (&argc, &argv);
  app_init (app);

  //get main window
  GET_OBJECT (GtkWidget, window);

  //display
  gtk_widget_show_all (window);

  //main loop
  gtk_main ();

  return 0;
}
