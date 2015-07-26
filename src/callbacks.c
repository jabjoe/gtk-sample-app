#include "app.h"

G_MODULE_EXPORT void on_imagemenuitem_about_activate (GtkMenuItem *menuitem,
                                                      App *app){
  GET_OBJECT (GtkWindow, aboutdialog);
  gtk_dialog_run(GTK_DIALOG(aboutdialog));
  gtk_widget_hide (GTK_WIDGET(aboutdialog)); 

}
