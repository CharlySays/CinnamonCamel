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

#include "timer.c"
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <string.h>
#include "gameManagement.h"
#include "generator.h"

#include "view.h"
#include "global.h"


void gameManagement(Field grid[][9]);
static void activate (GtkApplication* app,gpointer user_data);

gpointer last;
GtkWidget *lastWidget;
Field grid[9][9];
char name[256];

int main (int    argc, char **argv)
{
  GtkApplication *app;
  int status;
  last = NULL;
  
  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);  
  
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}

void gameManagement(Field grid[][9])
{
    printf("Spielname: ");
    scanf("%s",name);
    strcat(name,".txt");
    
    readGridWithFile(name,20);
}

static void activate (GtkApplication* app,gpointer user_data)
{
  GtkWidget *window;
  GtkWidget *mygrid;
  
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Sudoku");
  gtk_window_set_default_size (GTK_WINDOW (window), 300, 350);
  
  mygrid = gtk_grid_new();

  gameManagement(grid);
  myCss();
  fill_grid_with_buttons(mygrid);
  
  gtk_container_add(GTK_CONTAINER(window), mygrid);
  
  gtk_widget_show_all (window);
}

