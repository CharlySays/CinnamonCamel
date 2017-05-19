/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: nils
 *
 * Created on April 5, 2017, 8:21 PM
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "view.h"
#include "global.h"


static void activate (GtkApplication* app,gpointer user_data);

gpointer last;
GtkWidget *lastWidget, *window;
Field grid[9][9];
char name[256];
int numberFields;

int main (int    argc, char **argv)
{
  GtkApplication *app;
  int status;
  last = NULL;
  numberFields = 0;
  
  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);  
  
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}

static void activate (GtkApplication* app,gpointer user_data)
{
    window = gtk_application_window_new (app);

    gtk_window_set_icon(GTK_WINDOW(window), create_pixbuf("icon"));

    int e;
    struct stat sb;
    char *name = ".gamefiles";

    e = stat(name, &sb);
    if (e != 0) mkdir(name, S_IRWXU);

    createDialog(window);
}

