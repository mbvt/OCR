#include <stdlib.h>
#include <gtk/gtk.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "image.h"
#include "load_image.h"
#include "decoupage.h"


GdkPixbuf *p;
GdkPixbuf *g;
GtkWidget *label;
GtkWidget *load;
GtkImage *img2;
GtkImage *img3;
GtkWidget *window;
int cpt = 0;
int a = 0;

gchar *new;

int main(int argc, char *argv[])
{


    GtkBuilder *builder;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "IHM.glade", NULL);


    window = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));
    load = GTK_WIDGET(gtk_builder_get_object(builder, "load"));
    img2 = GTK_IMAGE(gtk_builder_get_object(builder, "image1"));
    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(G_OBJECT(builder));

    gtk_widget_show(window);
    gtk_main();

    return 0;
}




void on_load_clicked()
{

    GtkWidget  *dialog = gtk_file_chooser_dialog_new("Choose an image",
    GTK_WINDOW(window),GTK_FILE_CHOOSER_ACTION_OPEN,("OK"),
    GTK_RESPONSE_OK,("CANCEL"), GTK_RESPONSE_CANCEL, NULL);
    gtk_widget_show(dialog);
    gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog),g_get_home_dir());
    gint res= gtk_dialog_run(GTK_DIALOG(dialog));

    if(res == GTK_RESPONSE_OK)
    {
        new = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        GError *error = NULL;
        p = gdk_pixbuf_new_from_file(new,&error);
        if(p == NULL)
        {
            g_error_free(error);
        }
        gtk_image_set_from_pixbuf(img2,p);
    }
    else
    {
        g_print("You pressed Cancel\n");
    }
    gtk_widget_destroy(dialog);
}


void on_binarize_clicked()
{
  init_sdl();
  SDL_Surface* image = load_image((char*) new);
  struct image* matrix = convert_image((char*) new);
  conversion(matrix, image);
  GError *error = NULL;
  p = gdk_pixbuf_new_from_file("img.bmp", &error);
  gtk_image_set_from_pixbuf(img2,p);
}

void on_cut_clicked()
{
  init_sdl();
  SDL_Surface* image = load_image((char*) new);
  struct image* matrix = convert_image((char*) new);
  search_text(matrix);
  edge_letter(matrix, image);
  GError *error = NULL;
  g = gdk_pixbuf_new_from_file("imgCut.bmp", &error);
  gtk_image_set_from_pixbuf(img2,g);
}

void on_quit_clicked()
{
  gtk_main_quit();
}


void on_window_main_destroy()
{
  gtk_main_quit();
}
