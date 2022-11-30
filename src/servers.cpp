#include <gtk/gtk.h>
#include <string>
#include <fstream>
#include <thread>
#include <filesystem>
#include <iostream>

GObject *subServersGrid;
GObject *configurationGrid;
gchar *currentServer;

struct icons
{

  gchar *h48;
  gchar *w256;
  gchar *s48;
};

class Server
{

public:
  std::string systemName;
  gchar *name;
  icons icon;
  gchar *description;
  std::string type;
  bool (*configurationFunction)();

  void selectServer()
  {
    currentServer = name;
    printf("Selected %s server\n", this->name);
    GtkWidget *img = gtk_image_new_from_file(this->icon.w256);

    gtk_grid_remove_column(GTK_GRID(configurationGrid), 0);
    gtk_grid_remove_column(GTK_GRID(configurationGrid), 0);

    // gtk_grid_attach(GTK_GRID(configurationGrid), img, 0, 0, 1, 1);
    gtk_widget_show(img);

    system(("./bash_scripts/check_if_package_installed.sh " + this->systemName + ">check_if_package_installed.response").c_str());
    std::ifstream ifs("check_if_package_installed.response");
    std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    system(("rm check_if_package_installed.response"));

    //  printf("%s\n", std::ifstream("check_if_package_installed.response").rdbuf());
    // else
    GtkWidget *installation_status;
    GtkWidget *nameLabel;
    GtkWidget *descriptionLabel;

    GtkWidget *statusLabel;

    nameLabel = gtk_label_new(this->name);
    descriptionLabel = gtk_label_new(this->description);
    gtk_label_set_wrap(GTK_LABEL(descriptionLabel), true);

    GtkWidget *installationButton;

    if (content == "1")
    {
      installation_status = gtk_label_new("installed");
      gtk_style_context_add_class(gtk_widget_get_style_context(installation_status), "green");
      installationButton = gtk_button_new_with_label("uninstall");
      g_signal_connect(G_OBJECT(installationButton), "clicked", *G_CALLBACK(uninstall), (gpointer)this);

      statusLabel = gtk_label_new("status");
      gtk_grid_attach(GTK_GRID(configurationGrid), statusLabel, 0, 2, 1, 1);
    }
    else
    {
      installation_status = gtk_label_new("not installed");
      gtk_style_context_add_class(gtk_widget_get_style_context(installation_status), "red");
      installationButton = gtk_button_new_with_label("Install");
      g_signal_connect(G_OBJECT(installationButton), "clicked", *G_CALLBACK(install), (gpointer)this);
    }
    gtk_grid_attach(GTK_GRID(configurationGrid), descriptionLabel, 0, 0, 2, 1);
    gtk_grid_attach(GTK_GRID(configurationGrid), installation_status, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(configurationGrid), installationButton, 1, 1, 1, 1);

    gtk_widget_set_hexpand(installationButton, true);
    gtk_widget_set_hexpand(descriptionLabel, true);
    gtk_widget_set_hexpand(installation_status, true);

    gtk_widget_show(descriptionLabel);
    gtk_widget_show(installation_status);

    // this->*configurationFunction();
  }

private:
  static void install(GtkWidget *widget, gpointer *server)
  {
    std::string package = (char *)*server;
    system(("gnome-terminal -- ./bash_scripts/install_package.sh " + package).c_str());
  }
  static void uninstall(GtkWidget *widget, gpointer *server)
  {
    std::string package = (char *)*server;
    system(("gnome-terminal -- ./bash_scripts/remove_package.sh " + package).c_str());
  }
};

Server *seletedServer;

void refresh()
{
  if (seletedServer != NULL)
    seletedServer->selectServer();
}

void serverSelect(GtkWidget *widget, Server *clickedServer)
{
  seletedServer = clickedServer;
  clickedServer->selectServer();
}

//#include "../servers/ftp.cpp"

Server servers[3];

class ServerType
{
public:
  std::string typeName;
  icons icon;
  gchar *description;

  void selectServerType()
  {
    printf("Selected %s server type\n", this->typeName.c_str());

    gtk_grid_remove_column(GTK_GRID(subServersGrid), 0);
    gtk_grid_remove_column(GTK_GRID(subServersGrid), 0);

    GtkWidget *img = gtk_picture_new_for_filename("icons/types/48/error.png");
    GtkWidget *button = gtk_button_new_with_label("error");
    int n = 0;
    for (int i = 0; i < sizeof(servers) / sizeof(servers[0]); i++)
    {
      printf("%s\n", servers[i].type.c_str());
      if (servers[i].type == this->typeName)
      {
        img = gtk_picture_new_for_filename(servers[i].icon.h48);
        button = gtk_button_new_with_label(servers[i].name);
        //  gtk_widget_set_size_request(img, -1, 48);
        //  gtk_widget_set_halign(img, GTK_ALIGN_FILL);
        g_signal_connect(G_OBJECT(button), "clicked", *G_CALLBACK(serverSelect), (gpointer)&servers[i]);
        gtk_style_context_add_class(gtk_widget_get_style_context(button), "serverButton");
        gtk_style_context_add_class(gtk_widget_get_style_context(img), "serverIcon");

        gtk_grid_attach(GTK_GRID(subServersGrid), img, 0, n, 1, 1);
        gtk_grid_attach(GTK_GRID(subServersGrid), button, 1, n, 1, 1);

        gtk_style_context_add_class(gtk_widget_get_style_context(img), "server_img");


        gtk_widget_show(img);
        gtk_widget_show(button);
        n++;
      }
    }
  }

  void printName()
  {
    //  printf("%s\n", name);
    // g_print(this->name);
  }
};

ServerType serverTypes[2];

#include "../servers/proftpd.cpp"

void loadServers()
{
  std::cout << "DFgdfgdfgdfg";
  std::string line;
  std::string command;
  std::ifstream serverFile;

  std::string path = "servers";
  for (const auto &entry : std::filesystem::directory_iterator(path))
  {

    serverFile.open(entry.path());
    if (serverFile.is_open())
    {
      while (getline(serverFile, line))
      {

        for (int i = 0; i < line.length(); i++)
        {

          std::cout << line[i];
        }
      }
      serverFile.close();
    }
  }
  // std::cout << entry.path() << std::endl;
  //-----TYPES-----//
  serverTypes[0].typeName = "FTP";
  serverTypes[0].description = "FTP (File Transport Protocol)";
  serverTypes[0].icon.s48 = "icons/types/48/ftp.png";

  serverTypes[1].typeName = "HTTP";
  serverTypes[1].description = "HTTP (Hyper Text Transport Protocol)";
  serverTypes[1].icon.s48 = "icons/types/48/http.png";

  //----SERVERS----//GObject *buttonGrid;
  servers[0].name = "ProFtpd";
  servers[0].description = "proftpdddd";
  servers[0].icon.h48 = "icons/servers/h48/proftpd.png";
  servers[0].icon.w256 = "icons/servers/w256/proftpd.png";
  servers[0].type = "FTP";
  servers[0].systemName = "proftpd-basic";
  // proftpd();
  servers[0].configurationFunction = proftpd;

  servers[1].name = "Apache2";
  servers[1].description = "Apache2 HTTP server";
  servers[1].icon.h48 = "icons/servers/h48/apache2.png";
  servers[1].icon.w256 = "icons/servers/w256/apache2.png";
  servers[1].type = "HTTP";
  servers[1].systemName = "apache2";

  servers[2].name = "Nginx";
  servers[2].description = "Nginx, stylized as NGIИX, is a web server that can also be used as a reverse proxy, load balancer, mail proxy and HTTP cache. The software was created by Igor Sysoev and publicly released in 2004. Nginx is free and open-source software, released under the terms of the 2-clause BSD license. A large fraction of web servers use Nginx, often as a load balancer.";
  servers[2].icon.h48 = "icons/servers/h48/nginx.png";
  servers[2].icon.w256 = "icons/servers/w256/nginx.png";
  servers[2].type = "HTTP";
  servers[2].systemName = "nginx";
}

// void selectServerType(int serverType)
//{
//  switch(serverType)
//  {
//      case
//  }
// }
