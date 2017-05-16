/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "view.h"
#include "timer.c"
#include "gameManagement.h"

void myCss(void){
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
    if(grid[x][y].fixed) strcat(style, "_lock");
    if(clicked) strcat(style, "_clicked");
    
    gtk_widget_set_name(grid[x][y].button, style);
}

void setCurrentNumber(GtkWidget *widget, int nr){
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
  
  char temp[50] = "Time elapsed: ";
  char gameTimeChar[20];
  strcat(temp, itoa(gameTime/2, gameTimeChar, 10));
  strcat(temp, " secs");
  
  label = gtk_label_new(temp);
  
  for (i = 0; i < 9; i += 1) {
    for (j = 0; j < 9; j += 1, id++) {
        
        button = gtk_button_new_with_label (strcmp(grid[i][j].show, "0") ? grid[i][j].show : "  ");
        g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(callback), GINT_TO_POINTER(id));
        g_signal_connect (G_OBJECT (button), "key_press_event", G_CALLBACK (on_key_press), NULL);
                
        gtk_widget_set_size_request(button, 50,50);
        
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
  
  
  _start_timer(button, label);
}

void createDialog(GtkWidget *parent){
    
    GtkWidget *entry, *label;
    
    dialog = gtk_dialog_new();
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(parent));
    entry = gtk_entry_new();
    gtk_dialog_add_action_widget(GTK_DIALOG(dialog), entry, 0);
    gtk_window_set_title (GTK_WINDOW (dialog), "Spielname");
    
    g_signal_connect (G_OBJECT (entry), "key_press_event", G_CALLBACK (on_press), parent);

    gtk_widget_show_all(dialog);
}

GtkWidget* createMenu(){
    GtkWidget *menubar;
    GtkWidget *fileMenu;
    GtkWidget *fileMi;
    GtkWidget *quitMi;

    menubar = gtk_menu_bar_new();
    
    fileMenu = gtk_menu_new();
    fileMi = gtk_menu_item_new_with_label("File");
    quitMi = gtk_menu_item_new_with_label("Quit");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(fileMi), fileMenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), quitMi);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), fileMi);
    
    g_signal_connect(G_OBJECT(quitMi), "activate", G_CALLBACK(quit), NULL);
    
    GtkWidget *gameMenu, *newGameMenu;
    GtkWidget *gameMi;
    GtkWidget *newGameMi, *loadGameMi;
    GtkWidget *easyMi, *mediumMi, *hardMi;

    gameMenu = gtk_menu_new();
    gameMi = gtk_menu_item_new_with_label("Game");
  
    newGameMenu = gtk_menu_new();
    newGameMi = gtk_menu_item_new_with_label("New Game");
    easyMi = gtk_menu_item_new_with_label("Easy...");
    mediumMi = gtk_menu_item_new_with_label("Medium...");
    hardMi = gtk_menu_item_new_with_label("Hard...");
  
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(newGameMi), newGameMenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(newGameMenu), easyMi);
    g_signal_connect(G_OBJECT(easyMi), "activate", G_CALLBACK(createNewGame), GINT_TO_POINTER(50));
    gtk_menu_shell_append(GTK_MENU_SHELL(newGameMenu), mediumMi);
    g_signal_connect(G_OBJECT(mediumMi), "activate", G_CALLBACK(createNewGame), GINT_TO_POINTER(30));
    gtk_menu_shell_append(GTK_MENU_SHELL(newGameMenu), hardMi);
    g_signal_connect(G_OBJECT(hardMi), "activate", G_CALLBACK(createNewGame), GINT_TO_POINTER(20));
    GtkWidget *sep = gtk_separator_menu_item_new();  
    loadGameMi = gtk_menu_item_new_with_label("Load Game");
    g_signal_connect(G_OBJECT(loadGameMi), "activate", G_CALLBACK(loadGame), NULL);

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(gameMi), gameMenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(gameMenu), newGameMi);
    gtk_menu_shell_append(GTK_MENU_SHELL(gameMenu), sep);
    gtk_menu_shell_append(GTK_MENU_SHELL(gameMenu), loadGameMi);
    
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), gameMi);
    
    return menubar;
}

GdkPixbuf *create_pixbuf(const gchar * filename)
{
   GdkPixbuf *pixbuf;
   GError *error = NULL;
   pixbuf = gdk_pixbuf_new_from_file(filename, &error);
   if(!pixbuf) {
      fprintf(stderr, "%s\n", error->message);
      g_error_free(error);
   }

   return pixbuf;
}