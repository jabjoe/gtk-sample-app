    #include "app.h"
    
    int
    main (int argc, char *argv[])
    {
        App *app;
    
        app = (App *) g_new (App, 1);
    
        gtk_init (&argc, &argv);
    
        app_init (app);
    
        GET_UI_ELEMENT (GtkWidget, window1);
    
        gtk_widget_show_all (window1);
    
        gtk_main ();
    
        return 0;
    }
