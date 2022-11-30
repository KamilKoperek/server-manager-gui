#include <gtk/gtk.h>
#include <glib/gstdio.h>

GtkBuilder *builder;
GObject *buttonGrid;
GObject *mainBox;
GObject *mainWindow;
GObject *refreshButton;
GObject *optionsButton;
#include "servers.cpp"

void serverTypeSelect(GtkWidget *widget, ServerType *clickedType)
{
  clickedType->selectServerType();
}

void open_options_windows()
{
  GtkBuilder *optionsBuilder = gtk_builder_new();
  gtk_builder_add_from_file(optionsBuilder, "theme/main.ui", NULL);
  GObject *optionsWindow = gtk_builder_get_object(optionsBuilder, "window");
  gtk_widget_show(GTK_WIDGET(optionsWindow));
}

void maximize_application()
{
  if (gtk_window_is_maximized(GTK_WINDOW(mainWindow)))
    gtk_window_unmaximize(GTK_WINDOW(mainWindow));
  else
    gtk_window_maximize(GTK_WINDOW(mainWindow));
}

void minimize_application()
{
  //  if (gtk_window_is_maximized(GTK_WINDOW(mainWindow)))
  //    gtk_window_unmaximize(GTK_WINDOW(mainWindow));
  // else
  //   gtk_window_minimize(GTK_WINDOW(mainWindow));
}

void stop_application(GtkWindow *window)
{
  gtk_window_close(window);
}

void activate(GtkApplication *app, gpointer user_data)
{
  proftpd();
  loadServers();
  GtkCssProvider *cssProvider = gtk_css_provider_new();
  gtk_css_provider_load_from_file(cssProvider, g_file_new_for_path("theme/theme.css"));
  gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "theme/main.ui", NULL);
  subServersGrid = gtk_builder_get_object(builder, "subServersList");
  configurationGrid = gtk_builder_get_object(builder, "configurationGrid");
  GObject *window = gtk_builder_get_object(builder, "window");
  buttonGrid = gtk_builder_get_object(builder, "serversList");
  refreshButton = gtk_builder_get_object(builder, "refreshButton");
  optionsButton = gtk_builder_get_object(builder, "optionsButton");
  g_signal_connect(G_OBJECT(refreshButton), "clicked", *G_CALLBACK(refresh), NULL);
  g_signal_connect(G_OBJECT(optionsButton), "clicked", *G_CALLBACK(open_options_windows), NULL);

  GtkWidget *img = gtk_picture_new_for_filename("icons/types/48/error.png");
  GtkWidget *button = gtk_button_new_with_label("error");

  for (int i = 0; i < sizeof(serverTypes) / sizeof(serverTypes[0]); i++)
  {
    img = gtk_picture_new_for_filename(serverTypes[i].icon.s48);
    gtk_style_context_add_class(gtk_widget_get_style_context(img), "serverTypeIcon");
    gtk_grid_attach(GTK_GRID(buttonGrid), img, 0, i, 1, 1);

    button = gtk_button_new_with_label(serverTypes[i].description);

    g_signal_connect(G_OBJECT(button), "clicked", *G_CALLBACK(serverTypeSelect), (gpointer)&serverTypes[i]);
    gtk_style_context_add_class(gtk_widget_get_style_context(button), "serverTypeButton");
    gtk_grid_attach(GTK_GRID(buttonGrid), button, 1, i, 1, 1);

    gtk_widget_show(img);
    gtk_widget_show(button);
  }

  gtk_window_set_application(GTK_WINDOW(window), app);

  gtk_widget_show(GTK_WIDGET(window));

  g_object_unref(builder);

  gtk_window_set_default_size(GTK_WINDOW(window), 1000, 600);
}

int main(int argc, char *argv[])
{

  // declareServers();

  GtkApplication *app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
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
    // g_signal_connect(G_OBJECT(exit_button), "clicked", *G_CALLBACK(stop_application), NULL);
    GObject *maximize_button = gtk_builder_get_object(builder, "top_bar_maximize");
    // g_signal_connect(G_OBJECT(maximize_button), "clicked", *G_CALLBACK(maximize_application), NULL);

    GtkWidget *img = gtk_image_new_from_file("icons/types/48/error.png");
    GtkWidget *button = gtk_button_new_with_label("error");

    for (int i = 0; i < sizeof(serverTypes) / sizeof(serverTypes[0]); i++)
    {
      img = gtk_image_new_from_file(serverTypes[i].icon.s48);
      gtk_style_context_add_class(gtk_widget_get_style_context(img), "serverTypeImage");
      // gtk_grid_attach(GTK_GRID(buttonGrid), img, 0, i, 1, 1);

      button = gtk_button_new_with_label(serverTypes[i].description);

      g_signal_connect(G_OBJECT(button), "clicked", *G_CALLBACK(serverTypeSelect), (gpointer)&serverTypes[i]);
      gtk_style_context_add_class(gtk_widget_get_style_context(button), "serverTypeButton");
      // gtk_grid_attach(GTK_GRID(buttonGrid), button, 1, i, 1, 1);

      gtk_widget_show(img);
      gtk_widget_show(button);
    }
  */
  // gtk_main();

  // gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);

  int status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
