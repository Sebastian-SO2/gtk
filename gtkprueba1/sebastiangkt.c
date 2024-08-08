/**
 * Adapted by Sebastian Guerrero Cangas
 * from original at https://calcifer.org/documentos/librognome/gtk-basic-example.html
 * gcc `pkg-config --cflags gtk+-3.0` sebastiangkt.c -o sebasEXE `pkg-config --libs gtk+-3.0`
 */

#include <gtk/gtk.h>


void nombre( GtkWidget *widget,
            gpointer   data )
{
    g_print ("SEBASTIAN GUERRERO CANGAS\n");
}

gint delete_event( GtkWidget *widget,
                   GdkEvent  *event,
                   gpointer   data )
{
 
	
    g_print ("Sucedio el evento de eliminacion\n");

    

    return TRUE;
}

/* Another callback */
void destroy( GtkWidget *widget,
              gpointer   data )
{
    gtk_main_quit ();
}

    
int main( int   argc, char *argv[] )
{
    /* GtkWidget is the storage type for widgets */
    GtkWidget *window;
    GtkWidget *button;

    /* This is called in all GTK applications. Arguments are parsed
     * from the command line and are returned to the application. */
    gtk_init (&argc, &argv);

    /* create a new window. crea la ventana*/
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    
	
	/*si recibe la señal del evento de eliminacion
	llama a la funcion delete_event ignorando el callback*/
    g_signal_connect (G_OBJECT (window), "delete_event",
                      G_CALLBACK (delete_event), NULL);

	 //usado para destruir el evento 
    g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (destroy), NULL);

    /* Sets the border width of the window. */
    gtk_container_set_border_width (GTK_CONTAINER (window), 20);

    /* Creates a new button with the label "Sebastian Guerrero Cangas". */
    //se crea un nuevo boton con una la etiqueta del nombre
    button = gtk_button_new_with_label ("SEBASTIAN GUERRERO CANGAS");

    /* When the button receives the "clicked" signal, it will call the
     * function nombre() passing it NULL as its argument. The nombre()
     * function is defined above. */
	//para llamar la funcion nombre si se da un click
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (nombre), NULL);

    
    //hara que se destruya la ventana en el momento que se de un click
    g_signal_connect_swapped (G_OBJECT (button), "clicked",
                              G_CALLBACK (gtk_widget_destroy), G_OBJECT (window));

    /* This packs the button into the window (a gtk container). */
    gtk_container_add (GTK_CONTAINER (window), button);

    /* The final step is to display this newly created widget. */
    gtk_widget_show (button);

    /* and the window */
    gtk_widget_show (window);

    gtk_main ();
    
    return 0;
}

