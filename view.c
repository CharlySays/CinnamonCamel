/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "view.h"
#include "timer.c"
#include "global.h"
#include "gameManagement.h"

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

void setStyleClicked(int x, int y, bool clicked){
    char style[50] = "myButton_white_";
    strcat(style, grid[x][y].normalState);
    if(clicked) strcat(style, "_clicked");
    
    gtk_widget_set_name(grid[x][y].button, style);
}

void setCurrentNumber(GtkWidget *widget, int nr)
{
    if(last != NULL){
        int lastnum = GPOINTER_TO_INT(last);
        char newLabel[10] = "";
        itoa(GPOINTER_TO_INT(nr)/10, newLabel, 10 );
        grid[getI(lastnum)][getJ(lastnum)].value=GPOINTER_TO_INT(nr)/10;
        strcpy(grid[getI(lastnum)][getJ(lastnum)].show, newLabel);
        gtk_button_set_label(GTK_BUTTON(lastWidget), newLabel);
    }
    gridToFile(name);
}

void fill_grid_with_buttons(GtkWidget *gtkGrid) 
{
  GtkWidget *button, *label;
  int i, j, id=1;
  
  label = gtk_label_new("Time elapsed: 0 secs");

  for (i = 0; i < 9; i += 1) {
    for (j = 0; j < 9; j += 1, id++) {
        
        button = gtk_button_new_with_label (strcmp(grid[i][j].show, "0") ? grid[i][j].show : "  ");
        g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(_start_timer), label);
        g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(callback), GINT_TO_POINTER(id));
        g_signal_connect (G_OBJECT (button), "key_press_event", G_CALLBACK (on_key_press), NULL);
                
        gtk_widget_set_size_request(button, 10,10);
        
        if((i == 2 && j == 2) || (i == 5 && j == 5)){
            strcpy(grid[i][j].normalState,"intersectionspace\0");
            !grid[i][j].fixed ? gtk_widget_set_name(button, "myButton_white_intersectionspace"):gtk_widget_set_name(button, "myButton_white_intersectionspace_lock");
        }
        else if((i == 2 && j == 5) || (i == 5 && j == 2)){
            strcpy(grid[i][j].normalState,"intersectionspace\0");
            !grid[i][j].fixed ? gtk_widget_set_name(button, "myButton_white_intersectionspace"):gtk_widget_set_name(button, "myButton_white_intersectionspace_lock");
        }
        else if((i == 2 && j != 2) || (i == 5 && j != 5)){
            strcpy(grid[i][j].normalState,"rightspace\0");
            !grid[i][j].fixed ? gtk_widget_set_name(button, "myButton_white_rightspace"): gtk_widget_set_name(button, "myButton_white_rightspace_lock");
        }
        else if((j == 2 && i != 2) || (j == 5 && i != 5)){
            strcpy(grid[i][j].normalState,"bottomspace\0");
            !grid[i][j].fixed ? gtk_widget_set_name(button, "myButton_white_bottomspace"): gtk_widget_set_name(button, "myButton_white_bottomspace_lock");
        }
        else{
            strcpy(grid[i][j].normalState,"nospace\0");
            !grid[i][j].fixed ? gtk_widget_set_name(button, "myButton_white_nospace"):gtk_widget_set_name(button, "myButton_white_nospace_lock");
        }
        grid[i][j].button = button;
        gtk_grid_attach (GTK_GRID (gtkGrid), button, i, j, 1, 1);
        
        if(j == 8) id++;
    }
  }
  g_timeout_add_seconds(1, _label_update, label);
  gtk_grid_attach(GTK_GRID (gtkGrid), label, 0, -1, 3,1);
  
  int nr=1;
  while(grid[getI(nr)][getJ(nr)].fixed) nr++;
  
  lastWidget = grid[getI(nr)][getJ(nr)].button;
  last = GINT_TO_POINTER(nr);
  
  setStyleClicked(getI(nr), getJ(nr), true);  
}