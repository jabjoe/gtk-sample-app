#include "app.h"

int main( int argc, char **argv )
{
  //the system locale data base.
  bindtextdomain(PROJECT_NAME, LOCALDIR);
 
  //Set the current default message catalog to DOMAINNAME.
  textdomain(PROJECT_NAME);

  //new application 
  App *app = g_new(App, 1);

  //initialization
  gtk_init (&argc, &argv);
  app_init (app);

  //get main window
  GET_OBJECT (GtkWidget, window);
  
  //set icon
  GError *error = NULL;
  GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(DATADIR"/"PROJECT_NAME".png", &error);   
  gtk_window_set_icon(GTK_WINDOW(window), pixbuf);
  
  //display
  gtk_widget_show_all (window);
  
  //main loop
  gtk_main ();
    
  return 0;
}
