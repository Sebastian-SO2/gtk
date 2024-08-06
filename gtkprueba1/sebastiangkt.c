/**
 * Adapted by Sebastian Guerrero Cangas
 * from original at https://calcifer.org/documentos/librognome/gtk-basic-example.html
 * gcc `pkg-config --cflags gtk+-3.0` sebastiangkt.c -o sebasEXE `pkg-config --libs gtk+-3.0`
 */

#include <gtk/gtk.h>

/* This is a callback function. The data arguments are ignored
 * in this example. More on callbacks below.
 */
void nombre( GtkWidget *widget,
            gpointer   data )
{
    g_print ("SEBASTIAN GUERRERO CANGAS\n");
}

gint delete_event( GtkWidget *widget,
                   GdkEvent  *event,
                   gpointer   data )
{
    /* If you return FALSE in the "delete_event" signal handler,
     * GTK will emit the "destroy" signal. Returning TRUE means
     * you don't want the window to be destroyed.
     * This is useful for popping up 'are you sure you want to quit?'
     * type dialogs.
     */
	
    g_print ("Sucedio el evento de eliminacion\n");

    /* Change TRUE to FALSE and the main window will be destroyed with
     * a "delete_event".
     */

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

    /* When the window is given the "delete_event" signal (this is given
     * by the window manager, usually by the "close" option, or on the
     * titlebar), we ask it to call the delete_event () function
     * as defined above. The data passed to the callback
     * function is NULL and is ignored in the callback function. */
	
	/*si recibe la señal del evento de eliminacion
	llama a la funcion delete_event ignorando el callback*/
    g_signal_connect (G_OBJECT (window), "delete_event",
                      G_CALLBACK (delete_event), NULL);

    /* Here we connect the "destroy" event to a signal handler.
     * This event occurs when we call gtk_widget_destroy() on the window,
     * or if we return FALSE in the "delete_event" callback. */
	 //usado para destruir el evento 
    g_signal_connect (G_OBJECT (window), "destroy",
                      G_CALLBACK (destroy), NULL);

    /* Sets the border width of the window. */
    gtk_container_set_border_width (GTK_CONTAINER (window), 20);

    /* Creates a new button with the label "Sebastian Guerrero Cangas". */
    //se crea un nuevo boton con una la etiqueta del nombre
    button = gtk_button_new_with_label ("SEBASTIAN GUERRERO CANGAS");

    /* When the button receives the "clicked" signal, it will call the
     * function nombre() passing it NULL as its argument. The nombre()
     * function is defined above. */
	//para llamar la funcion nombre si se da un click
    g_signal_connect (G_OBJECT (button), "clicked",
                      G_CALLBACK (nombre), NULL);

    /* This will cause the window to be destroyed by calling
     * gtk_widget_destroy(window) when "clicked". Again, the destroy
     * signal could come from here, or the window manager. */
    //hara que se destruya la ventana en el momento que se de un click
    g_signal_connect_swapped (G_OBJECT (button), "clicked",
                              G_CALLBACK (gtk_widget_destroy),
                              G_OBJECT (window));

    /* This packs the button into the window (a gtk container). */
    gtk_container_add (GTK_CONTAINER (window), button);

    /* The final step is to display this newly created widget. */
    gtk_widget_show (button);

    /* and the window */
    gtk_widget_show (window);

    /* All GTK applications must have a gtk_main(). Control ends here
     * and waits for an event to occur (like a key press or
     * mouse event). */
    gtk_main ();
    
    return 0;
}

