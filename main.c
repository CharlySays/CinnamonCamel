/***** BEGINNING INCLUDES *****/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "view.h"

/***** ENDING INCLUDES *****/

/***** BEGINNING GLOBAL VARIABLES *****/

/** further information in global.h  **/

gpointer last;
GtkWidget *lastWidget, *window;
Field grid[9][9];
char name[256];
int numberFields;
bool windowOpen;

/*****  ENDING GLOBAL VARIABLES *****/

/*****  BEGINNING SLOTS *****/

/**     This slot starts the GTK3+ Application.
        The implementation is under the main.   **/

static void activate (GtkApplication* app,gpointer user_data);

/*****  ENDING SLOTS *****/

/*****  BEGINNING MAIN FUNCTION *****/

int main (int    argc, char **argv)
{
  /*    Defining some variables     */
    
  GtkApplication *app;      // This variable represents the whole 
                            // GTK3+ Application
  int status;  
                            // Initializing some important variables
  last = NULL;              // Further information in --> global.h
  numberFields = 0;
  windowOpen = false;
  
  /*    Create a new GTK3+ Application      */
  
  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);  
  
  /*    This signal is called when a application was started.
        If the application was activated it fires the activate callback.    */
  
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  
  /*    Run the application !
        Now the activate-signal is triggered    */
  
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}

/***** ENDING MAIN FUNCTION *****/

/***** BEGINNING ACTIVATE SLOT *****/

static void activate (GtkApplication* app,gpointer user_data)
{
    /*  Create a new window which will be showed.  
        This is a important step.
        Away from the console - to the Graphical User Interface (GUI)   */
    
    window = gtk_application_window_new (app);

    /*  Create a icon which will be shown in the task bar   */
    
    gtk_window_set_icon(GTK_WINDOW(window), create_pixbuf("icon"));

    /*  Defining some variables  */
    
    struct stat sb;                         // Represents file/directory 
                                            // information
    int status;                             // Status
    char *name = ".gamefiles";              // Secret directory name
                                            // Secret: . (dot) before the name 
                                            // hides the directory
    
    /*  Look up whether there is a directory with this name */
    
    status = stat(name, &sb);        
    
    /*  If no directory with this name was found    */
    
    if (status != 0){
        mkdir(name, S_IRWXU);               // Create a new directory 
                                            // .gamefiles for the game files
    }
    
    /*  Create a new Dialog to read-in game file name   */
    
    createDialog(window);
}

/***** ENDING ACTIVATE SLOT *****/