#include <glib/gstdio.h>
#include <gtk/gtk.h>


GtkBuilder *builder;
GObject *buttonGrid;
GObject *mainBox;
GObject *mainGrid;
GObject *mainWindow;
GObject *refreshButton;
GObject *optionsButton;
GtkCssProvider *cssProvider;




#include "servers.cpp"
#include "options.cpp"

/*
void serverTypeSelect(GtkWidget *widget, ServerType *clickedType) {
  clickedType->selectServerType();
}

void maximize_application() {
  if (gtk_window_is_maximized(GTK_WINDOW(mainWindow)))
    gtk_window_unmaximize(GTK_WINDOW(mainWindow));
  else
    gtk_window_maximize(GTK_WINDOW(mainWindow));
}*/

void minimize_application() {
  //  if (gtk_window_is_maximized(GTK_WINDOW(mainWindow)))
  //    gtk_window_unmaximize(GTK_WINDOW(mainWindow));
  // else
  //   gtk_window_minimize(GTK_WINDOW(mainWindow));
}

void stop_application(GtkWindow *window) { gtk_window_close(window); }

void activate(GtkApplication *app, gpointer user_data) {
  //  proftpd();
  loadServers();
  cssProvider = gtk_css_provider_new();

  set_theme(get_config("theme"));

  gtk_style_context_add_provider_for_display(gdk_display_get_default(),
                                             GTK_STYLE_PROVIDER(cssProvider),
                                             GTK_STYLE_PROVIDER_PRIORITY_USER);
  builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "theme/main.ui", NULL);
  // subServersGrid = gtk_builder_get_object(builder, "subServersList");
  //  configurationGrid = gtk_builder_get_object(builder, "configurationGrid");
  GObject *window = gtk_builder_get_object(builder, "window");
  buttonGrid = gtk_builder_get_object(builder, "serversList");
  mainGrid = gtk_builder_get_object(builder, "mainGrid");
  refreshButton = gtk_builder_get_object(builder, "refreshButton");
  optionsButton = gtk_builder_get_object(builder, "optionsButton");
  //  g_signal_connect(G_OBJECT(refreshButton), "clicked", *G_CALLBACK(refresh),
  //                 NULL);
  g_signal_connect(G_OBJECT(optionsButton), "clicked",
                   *G_CALLBACK(open_options_windows), NULL);

  GtkWidget *img = gtk_picture_new_for_filename("icons/types/48/error.png");
  GtkWidget *button1 = gtk_button_new_with_label("erro1r");
  GtkWidget *button2 = gtk_button_new_with_label("err2or");
  GtkWidget *button3 = gtk_button_new_with_label("err3or");

  GtkWidget *sidebar = gtk_stack_sidebar_new();
  GtkWidget *stack = gtk_stack_new();
  gtk_grid_attach(GTK_GRID(mainGrid), sidebar, 1, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(mainGrid), stack, 2, 1, 1, 3);
  gtk_widget_set_vexpand(GTK_WIDGET(mainGrid), 1);
  gtk_widget_set_hexpand(GTK_WIDGET(mainGrid), 1);
  gtk_widget_set_vexpand(GTK_WIDGET(sidebar), 1);
  gtk_widget_set_vexpand(GTK_WIDGET(stack), 1);
  gtk_widget_set_hexpand(GTK_WIDGET(stack), 1);
  gtk_stack_sidebar_set_stack(GTK_STACK_SIDEBAR(sidebar), GTK_STACK(stack));


for(int i = 0; i < servers.size(); i++)
{
  gtk_stack_add_titled(GTK_STACK(stack), servers[i].configuration_grid, str2gchar(servers[i].service_name), str2gchar(servers[i].name));
}



  //g_print(gtk_widget_get_css_name(gtk_search_entry_new()));


  GtkWidget *search_entry = gtk_search_entry_new();
  gtk_grid_attach(GTK_GRID(mainGrid), search_entry, 1, 2, 1, 1);
  GtkWidget *only_installed_button =
      gtk_check_button_new_with_label("Show only installed");
  gtk_grid_attach(GTK_GRID(mainGrid), only_installed_button, 1, 3, 1, 1);
  gtk_style_context_add_class(gtk_widget_get_style_context(sidebar), "sidebar");

  /*
    for (int i = 0; i < sizeof(serverTypes) / sizeof(serverTypes[0]); i++)
    {
      img = gtk_picture_new_for_filename(serverTypes[i].icon.s48);
      gtk_style_context_add_class(gtk_widget_get_style_context(img),
    "serverTypeIcon"); gtk_grid_attach(GTK_GRID(buttonGrid), img, 0, i, 1, 1);

      button = gtk_button_new_with_label(serverTypes[i].description);

      g_signal_connect(G_OBJECT(button), "clicked",
    *G
_CALLBACK(serverTypeSelect), (gpointer)&serverTypes[i]);
      gtk_style_context_add_class(gtk_widget_get_style_context(button),
    "serverTypeButton"); gtk_grid_attach(GTK_GRID(buttonGrid), button, 1, i, 1,
    1);

      gtk_widget_show(img);
      gtk_widget_show(button);
    }
  */
  gtk_window_set_application(GTK_WINDOW(window), app);

  gtk_widget_show(GTK_WIDGET(window));
  g_object_unref(builder);
}

int main(int argc, char *argv[]) {

  // declareServers();

  GtkApplication *app =
      gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  //// mainWindow = gtk_builder_get_object(builder, "window");
  //  buttonGrid =
  // gtk_builder_get_object(GTK_BUILDER(builder), "serversList");
  // GtkWidget* label1 = gtk_label_new("ta?");
  // gtk_grid_attach(GTK_GRID(buttonGrid), label1, 0, 0, 1, 1);
  // mainBox = gtk_builder_get_object(builder, "mainBox");
  // subServersGrid = gtk_builder_get_object(builder, "subServersList");

  /*
    GObject *exit_button = gtk_builder_get_object(builder, "top_bar_exit");
    // g_signal_connect(G_OBJECT(exit_button), "clicked",
    *G_CALLBACK(stop_application), NULL); GObject *maximize_button =
    gtk_builder_get_object(builder, "top_bar_maximize");
    // g_signal_connect(G_OBJECT(maximize_button), "clicked",
    *G_CALLBACK(maximize_application), NULL);

    GtkWidget *img = gtk_image_new_from_file("icons/types/48/error.png");
    GtkWidget *button = gtk_button_new_with_label("error");

    for (int i = 0; i < sizeof(serverTypes) / sizeof(serverTypes[0]); i++)
    {
      img = gtk_image_new_from_file(serverTypes[i].icon.s48);
      gtk_style_context_add_class(gtk_widget_get_style_context(img),
    "serverTypeImage");
      // gtk_grid_attach(GTK_GRID(buttonGrid), img, 0, i, 1, 1);

      button = gtk_button_new_with_label(serverTypes[i].description);

      g_signal_connect(G_OBJECT(button), "clicked",
    *G_CALLBACK(serverTypeSelect), (gpointer)&serverTypes[i]);
      gtk_style_context_add_class(gtk_widget_get_style_context(button),
    "serverTypeButton");
      // gtk_grid_attach(GTK_GRID(buttonGrid), button, 1, i, 1, 1);

      gtk_widget_show(img);
      gtk_widget_show(button);
    }
  */
  // gtk_main();

  // gtk_style_context_add_provider_for_display(gdk_display_get_default(),
  // GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);

  int status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
