#include "app.h"

int main( int argc, char **argv )
{
  gchar localdir[PATH_MAX] = {0};
  GET_FILE(LOCALE_DIR, localdir);
  
  //the system locale data base.
  bindtextdomain(PROJECT_NAME, localdir);
 
  //Set the current default message catalog to DOMAINNAME.
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
