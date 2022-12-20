GtkBuilder *optionsBuilder;

int last_inserted_row = 0;

static void on_click_call(GtkWidget *button, gpointer *data);
class settings_item {

public:
  gchar *label;
  int id = -1;
  //  settings_content content;
  GtkWidget *setting_grid;
  GtkWidget *setting_label;

  void show() {
    // gtk_check_button_new
    setting_label = gtk_label_new(label);
    setting_grid = gtk_grid_new();

    gtk_grid_attach(GTK_GRID(gtk_builder_get_object(optionsBuilder,
                                                    "settings_optionsList")),
                    setting_label, 1, last_inserted_row, 1, 1);
    gtk_grid_attach(GTK_GRID(gtk_builder_get_object(optionsBuilder,
                                                    "settings_optionsList")),
                    setting_grid, 2, last_inserted_row, 1, 1);

    gtk_widget_show(setting_label);
    gtk_widget_show(setting_grid);
    last_inserted_row++;
    /*  settings_button = gtk_button_new_with_label(label);
  g_signal_connect (G_OBJECT (settings_button), "clicked", G_CALLBACK
  (on_click_call), this);
  gtk_style_context_add_class(gtk_widget_get_style_context(settings_button),
  "settings_optionButton");
  gtk_grid_attach(GTK_GRID(gtk_builder_get_object(optionsBuilder,
  "settings_optionsList")), settings_button, 1, last_inserted_button_id, 1, 1);
  gtk_widget_show(settings_button);
  last_inserted_button_id++;*/
  }
};

void on_click_call(GtkWidget *button, gpointer *data) {
  settings_item *it = reinterpret_cast<settings_item *>(data);
  //  it->load_setting();
}
void set_theme(std::string t) {
  gtk_css_provider_load_from_file(cssProvider,
                                  g_file_new_for_path("theme/theme_dark.css"));
  if (t == "light") {
    gtk_css_provider_load_from_file(
        cssProvider, g_file_new_for_path("theme/theme_light.css"));
    set_config("theme", "light");
  } else if (t == "debug") {
    gtk_css_provider_load_from_file(
        cssProvider, g_file_new_for_path("theme/theme_debug.css"));
    set_config("theme", "debug");
  } else if (t == "dark") {
    gtk_css_provider_load_from_file(
        cssProvider, g_file_new_for_path("theme/theme_dark.css"));
    set_config("theme", "dark");
  }
}
void theme_change(GtkWidget *button, gpointer *data) {
  gchar *selected_theme = reinterpret_cast<gchar *>(data);
  set_theme((std::string)selected_theme);
}

void open_options_windows() {
  optionsBuilder = gtk_builder_new();
  gtk_builder_add_from_file(optionsBuilder, "theme/options.ui", NULL);
  GObject *optionsWindow = gtk_builder_get_object(optionsBuilder, "window");
  gtk_widget_show(GTK_WIDGET(optionsWindow));

  settings_item theme;

  // theme.label = &get_config("theme")[0];
  theme.label = "Theme:";
  theme.show();

  gchar *themes[2][3] = {{"Dark", "Light", "Debug"},
                         {"dark", "light", "debug"}};
  GtkWidget *theme_button;
  GtkWidget *theme_button_prev;
  for (int i = 0; i < 3; i++) {
    theme_button_prev = theme_button;
    theme_button = gtk_check_button_new_with_label(themes[0][i]);
    gtk_style_context_add_class(gtk_widget_get_style_context(theme_button), "check_button");
    gtk_grid_attach(GTK_GRID(theme.setting_grid), theme_button, 1, i + 1, 1, 1);
    std::string current_theme = get_config("theme");
    g_print(&current_theme[0]);
    if (g_ascii_strncasecmp(&current_theme[0], themes[0][i], 512) == 0)
      gtk_check_button_set_active(GTK_CHECK_BUTTON(theme_button), 1);
    gtk_check_button_set_group(GTK_CHECK_BUTTON(theme_button),
                               GTK_CHECK_BUTTON(theme_button_prev));
    g_signal_connect(theme_button, "toggled", G_CALLBACK(theme_change),
                     (gpointer)themes[1][i]);
  }



  // theme.label = &get_config("theme")[0];

}
