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

gpointer last = NULL;
GtkWidget *lastWidget;
char name[255];

Field Grid[9][9];

void gameManagement(Field grid[][9], FILE *myFile);
void myCss(void);
int getI(int nr) { return nr/10; }
int getJ(int nr) { return (nr-1)%10;}
bool locked(int nr, Field grid[][9]) { return !grid[getI(nr)][getJ(nr)].fixed; }
void on_key_press (GtkWidget *widget, GdkEventKey *event, gpointer user_data);
void callback( GtkWidget *widget, gpointer nr);
void setCurrentNumber(GtkWidget *widget, int nr);
void fill_grid_with_buttons(GtkWidget *grid, Field g[][9]);
static void activate (GtkApplication* app,gpointer user_data);
void setKeyNumber(guint keyval);
void setStyleClicked(int x, int y, bool clicked);

int main (int    argc, char **argv)
{
  GtkApplication *app;
  int status;
  
  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);  
  
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}

void gameManagement(Field grid[][9], FILE *myFile)
{
    
    printf("Spielname: ");
    scanf("%s",name);

    myFile = fopen(strcat(name,".txt"), "r+");
    if(myFile == NULL) //if file does not exist, create it
    {
       myFile = fopen(name, "wb");
       // genrator here bum bang done
       generateGrid(grid,20,name);
       setLocked(grid);
       gridToFile(grid,name);
       myFile = fopen(name, "r+");
    }
    readGridWithFile(grid,myFile);
}

void myCss(void)
{
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;

    provider = gtk_css_provider_new ();
    display = gdk_display_get_default ();
    screen = gdk_display_get_default_screen (display);
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    const gchar *myCssFile = "mystyle.css";
    GError *error = 0;

    gtk_css_provider_load_from_file(provider, g_file_new_for_path(myCssFile), &error);
    g_object_unref (provider);
}


void on_key_press (GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
    int lastnum = GPOINTER_TO_INT(last);
    int y = getJ(lastnum);
    int x = getI(lastnum);
            
    if(event->keyval == 65361 /*left_arrow*/){
        if(GPOINTER_TO_INT(last) > 10){
            int offset = 1;
            while(x - offset >= 0 && Grid[x - offset][y].fixed) offset++;
            if(x - offset < 0) return;
                
            setStyleClicked(x,y,false);
            setStyleClicked(x - offset, y, true);
            
            lastWidget = Grid[x-offset][y].button;
            last -= offset*10;   
        }
    }
    else if(event->keyval == 65364 /*down_arrow*/){
        if(GPOINTER_TO_INT(last)%10 != 9){
            int offset = 1;
            while(y + offset <= 8 && Grid[x][y+offset].fixed) offset++;
            if(y + offset  > 8) return;
            
            setStyleClicked(x,y,false);
            setStyleClicked(x,y + offset, true);
            
            lastWidget = Grid[x][y+offset].button;
            last +=1*offset;
        }
    }
    else if(event->keyval == 65363 /*right_arrow*/){
        if(GPOINTER_TO_INT(last) < 80){
            int offset = 1;
            while(x + offset <= 8 && Grid[x+ offset][y].fixed) offset++;
            if(x + offset  > 8) return;
            
            setStyleClicked(x,y,false);
            setStyleClicked(x + offset, y, true);
            
            lastWidget = Grid[x+offset][y].button;
            last +=10*offset;
        }
    }
    else if(event->keyval == 65362 /*up_arrow*/){
        if(GPOINTER_TO_INT(last)%10 !=1){
            int offset = 1;
            while(y - offset >= 0 && Grid[x][y - offset].fixed) offset++;
            if(y - offset < 0) return;
            
            setStyleClicked(x,y,false);
            setStyleClicked(x,y - offset, true);
            
            lastWidget = Grid[x][y - offset].button;
            last -=1*offset;
        }
    }
    else{
        setKeyNumber(event->keyval);
    }
}

void callback( GtkWidget *widget, gpointer nr)
{   
    g_print("%i\n", GPOINTER_TO_INT(nr));
    int num = GPOINTER_TO_INT(nr);
    if(num%10){
        if(locked(num, Grid)){
            if(last != NULL){
                int lastnum = GPOINTER_TO_INT(last);
                setStyleClicked(getI(lastnum), getJ(lastnum), false);
            }
            setStyleClicked(getI(num), getJ(num), true);
            
            lastWidget = widget;
            last = nr;
        }
    }
}

void setCurrentNumber(GtkWidget *widget, int nr)
{
    if(last != NULL){
        int lastnum = GPOINTER_TO_INT(last);
        char newLabel[10] = "";
        itoa(GPOINTER_TO_INT(nr)/10, newLabel, 10 );
        Grid[getI(lastnum)][getJ(lastnum)].value=GPOINTER_TO_INT(nr)/10;
        strcpy(Grid[getI(lastnum)][getJ(lastnum)].show, newLabel);
        gtk_button_set_label(GTK_BUTTON(lastWidget), newLabel);
    }
}

void fill_grid_with_buttons(GtkWidget *grid, Field g[][9]) 
{
  GtkWidget *button, *label;
  int i, j, id=1;
  
  label = gtk_label_new("Time elapsed: 0 secs");

  for (i = 0; i < 9; i += 1) {
    for (j = 0; j < 10; j += 1, id++) {
        
        if(j != 9 ){
            button = gtk_button_new_with_label (strcmp(g[i][j].show, "0") ? g[i][j].show : "  ");
            g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(_start_timer), label);
            g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(callback), GINT_TO_POINTER(id));
            g_signal_connect (G_OBJECT (button), "key_press_event", G_CALLBACK (on_key_press), NULL);
        }
        else {
            char temp[1];
            itoa(i+1, temp, 10);
            button = gtk_button_new_with_label(temp);
        }
        
        gtk_widget_set_size_request(button, 50,50);
        
        if((i == 2 && j == 2) || (i == 5 && j == 5)){
            g[i][j].normalState = malloc(sizeof(char)*50);
            strcpy(g[i][j].normalState,"intersectionspace\0");
            g[i][j].value == 0 ? gtk_widget_set_name(button, "myButton_white_intersectionspace"):gtk_widget_set_name(button, "myButton_white_intersectionspace_lock");
        }
        else if((i == 2 && j == 5) || (i == 5 && j == 2)){
            g[i][j].normalState = malloc(sizeof(char)*50);
            strcpy(g[i][j].normalState,"intersectionspace\0");
            g[i][j].value == 0 ? gtk_widget_set_name(button, "myButton_white_intersectionspace"):gtk_widget_set_name(button, "myButton_white_intersectionspace_lock");
        }
        else if(j == 9){
            gtk_widget_set_name(button, "myButton_numbers");
        }
        else if((i == 2 && j != 2) || (i == 5 && j != 5)){
            g[i][j].normalState = malloc(sizeof(char)*50);
            strcpy(g[i][j].normalState,"rightspace\0");
            g[i][j].value == 0 ? gtk_widget_set_name(button, "myButton_white_rightspace"): gtk_widget_set_name(button, "myButton_white_rightspace_lock");
        }
        else if((j == 2 && i != 2) || (j == 5 && i != 5)){
            g[i][j].normalState = malloc(sizeof(char)*50);
            strcpy(g[i][j].normalState,"bottomspace\0");
            g[i][j].value == 0 ? gtk_widget_set_name(button, "myButton_white_bottomspace"): gtk_widget_set_name(button, "myButton_white_bottomspace_lock");
        }
        else{
            g[i][j].normalState = malloc(sizeof(char)*50);
            strcpy(g[i][j].normalState,"nospace\0");
            g[i][j].value == 0 ? gtk_widget_set_name(button, "myButton_white_nospace"):gtk_widget_set_name(button, "myButton_white_nospace_lock");
        }
        
        if(j != 9) {
            Grid[i][j].normalState = malloc (sizeof(char)*50);
            Grid[i][j] = g[i][j];
            Grid[i][j].button = button;
            gtk_grid_attach (GTK_GRID (grid), button, i, j, 1, 1);
        }
    }
  }
  g_timeout_add_seconds(1, _label_update, label);
  gtk_grid_attach(GTK_GRID (grid), label, 0, -1, 3,1);
  
  int nr=1;
  while(Grid[getI(nr)][getJ(nr)].fixed) nr++;
  
  lastWidget = Grid[getI(nr)][getJ(nr)].button;
  last = GINT_TO_POINTER(nr);
  
  setStyleClicked(getI(nr), getJ(nr), true );  
}

static void activate (GtkApplication* app,gpointer user_data)
{
  GtkWidget *window;
  GtkWidget *mygrid;
  
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Sudoku");
  gtk_window_set_default_size (GTK_WINDOW (window), 300, 350);
  
  mygrid = gtk_grid_new();
  
  FILE *gameFile = NULL;

  Field grid[9][9];
  gameManagement(grid,gameFile);
  
  myCss();
  fill_grid_with_buttons(mygrid, grid);
  
  gtk_container_add(GTK_CONTAINER(window), mygrid);
  
  gtk_widget_show_all (window);
}

void setKeyNumber(guint keyval){
    int curNum;
    
    if(keyval == 65457 || keyval == 49){ /*1*/
        curNum=10;
        setCurrentNumber(NULL, curNum);
    }
    else if(keyval == 65458 || keyval == 50){ /*2*/
        curNum=20;
        setCurrentNumber(NULL, curNum);
    }
    else if(keyval == 65459 || keyval == 51){ /*3*/
        curNum=30;
        setCurrentNumber(NULL, curNum);
    }
    else if(keyval == 65460 || keyval == 52){ /*4*/
        curNum=40;
        setCurrentNumber(NULL, curNum);
    }
    else if(keyval == 65461 || keyval == 53){ /*5*/
        curNum=50;
        setCurrentNumber(NULL, curNum);
    }
    else if(keyval == 65462 || keyval == 54){ /*6*/
        curNum=60;
        setCurrentNumber(NULL, curNum);
    }
    else if(keyval == 65463 || keyval == 55){ /*7*/
        curNum=70;
        setCurrentNumber(NULL, curNum);
    }
    else if(keyval == 65464 || keyval == 56){ /*8*/
        curNum=80;
        setCurrentNumber(NULL, curNum);
    }
    else if(keyval == 65465 || keyval == 57){ /*9*/
        curNum=90;
        setCurrentNumber(NULL, curNum);
    }
    else if(keyval == 65288 || keyval == 48 || keyval == 65456){ /*0*/
        int x = getI(GPOINTER_TO_INT(last));
        int y = getJ(GPOINTER_TO_INT(last));
        char show[10] ="";
        itoa(0, show, 10);
        Grid[x][y].value = 0;
        strcpy(Grid[x][y].show, show);
        gtk_button_set_label(GTK_BUTTON(Grid[x][y].button), "");
    }
    gridToFile(Grid, name);
}

void setStyleClicked(int x, int y, bool clicked){
    char style[50] = "myButton_white_";
    strcat(style, Grid[x][y].normalState);
    if(clicked) strcat(style, "_clicked");
    
    gtk_widget_set_name(Grid[x][y].button, style);
}