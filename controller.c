/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "controller.h"

#include "view.h"
#include "global.h"
#include "generator.h"
#include "gameManagement.h"
#include "timer.c"

int getI(int nr) { return nr/10; }

int getJ(int nr) { return (nr-1)%10;}

bool locked(int nr) { return !grid[getI(nr)][getJ(nr)].fixed; }


void callback( GtkWidget *widget, gpointer nr)
{   
    int num = GPOINTER_TO_INT(nr);
    if(num%10){
        if(last != NULL){
            int lastnum = GPOINTER_TO_INT(last);
            setStyleClicked(getI(lastnum), getJ(lastnum), false);
        }
        setStyleClicked(getI(num), getJ(num), true);

        lastWidget = widget;
        last = nr;
    }
}

void
on_key_press (GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
    int lastnum = GPOINTER_TO_INT(last);
    int y = getJ(lastnum);
    int x = getI(lastnum);
            
    if(event->keyval == 65361 /*left_arrow*/){
        if(GPOINTER_TO_INT(last) > 10){
            int offset = 1;
            //while(x - offset >= 0 && grid[x - offset][y].fixed) offset++;
            if(x - offset < 0) return;
                
            setStyleClicked(x,y,false);
            setStyleClicked(x - offset, y, true);
            
            lastWidget = grid[x-offset][y].button;
            last -= offset*10;   
        }
    }
    else if(event->keyval == 65364 /*down_arrow*/){
        if(GPOINTER_TO_INT(last)%10 != 9){
            int offset = 1;
            //while(y + offset <= 8 && grid[x][y+offset].fixed) offset++;
            if(y + offset  > 8) return;
            
            setStyleClicked(x,y,false);
            setStyleClicked(x,y + offset, true);
            
            lastWidget = grid[x][y+offset].button;
            last +=1*offset;
        }
    }
    else if(event->keyval == 65363 /*right_arrow*/){
        if(GPOINTER_TO_INT(last) < 80){
            int offset = 1;
            //while(x + offset <= 8 && grid[x+ offset][y].fixed) offset++;
            if(x + offset  > 8) return;
            
            setStyleClicked(x,y,false);
            setStyleClicked(x + offset, y, true);
            
            lastWidget = grid[x+offset][y].button;
            last +=10*offset;
        }
    }
    else if(event->keyval == 65362 /*up_arrow*/){
        if(GPOINTER_TO_INT(last)%10 !=1){
            int offset = 1;
            //while(y - offset >= 0 && grid[x][y - offset].fixed) offset++;
            if(y - offset < 0) return;
            
            setStyleClicked(x,y,false);
            setStyleClicked(x,y - offset, true);
            
            lastWidget = grid[x][y - offset].button;
            last -=1*offset;
        }
    }
    else{
        setKeyNumber(event->keyval);
    }
}

void setKeyNumber(guint keyval){
    int curNum;
    
    int lastnum = GPOINTER_TO_INT(last);
    if( locked( lastnum)){
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
        else if(keyval == 65288 || keyval == 48 || keyval == 65456 || keyval == 65535){ 
            int x = getI(GPOINTER_TO_INT(last));
            int y = getJ(GPOINTER_TO_INT(last));
            char show[10] ="";
            itoa(0, show, 10);
            grid[x][y].value = 0;
            strcpy(grid[x][y].show, show);
            gtk_button_set_label(GTK_BUTTON(grid[x][y].button), "");
        }        
    }
    
    if(keyval == 65307){ /* ESC */
        quit(NULL, NULL);
    }
    
    if(checkFilled()){
        if(checkValid()){
            g_print("\nCongratz\n");
        }
        else{
            g_print("\nBaad\n");
        }
    }
}

bool checkFilled(){
    for(int row = 0; row < 9 ; row++){
        for(int col = 0; col < 9; col++){
            if(!grid[row][col].value){
                return false;
            }
        }
    }
    return true;
}

bool checkValid(){
    for(int row = 0; row < row ; row++){
        for(int col = 0; col < 9; col++){
            if(!isValid(row,col, grid[row][col].value)){
                printf("row %d col %d seems wrong", row, col);
                return false;
            }
        }
    }
    return true;
}

void
on_press (GtkWidget *widget, GdkEventKey *event, gpointer user_data){
    if(event->keyval == 65293){
        GtkWidget *mygrid, *vbox; 
        if(numberFields == 0){
            mygrid = gtk_grid_new();

            strcpy(name, gtk_entry_get_text(GTK_ENTRY(widget)));
        
            readGridWithFile(strcat(name,".save"),30);
            myCss();
            fill_grid_with_buttons(mygrid);
        
            vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
            gtk_container_add(GTK_CONTAINER(user_data),vbox);
        
            gtk_container_add(GTK_CONTAINER(vbox), createMenu());
            gtk_container_add(GTK_CONTAINER(vbox), mygrid);

            gtk_widget_show_all (GTK_WIDGET(user_data));
            windowOpen = true;
            gtk_widget_hide(dialog);
        }
        else{
            strcpy(name, gtk_entry_get_text(GTK_ENTRY(widget)));
            strcat(name,".save"),30;
            newGrid();
            gtk_widget_hide(dialog);
        }
        
    }
    
    else g_print("");
}

void quit( GtkWidget *widget, gpointer user_data){
    if(!windowOpen){
        if(autosave)gridToFile(name);
        exit(0);   
    }
}

void createNewGame( GtkWidget *widget, gpointer numOfFields){
    numberFields = GPOINTER_TO_INT(numOfFields);
    gtk_entry_set_text(GTK_ENTRY(entry), "");
    gtk_widget_show_all(dialog);
}

void loadGame( GtkWidget *widget, gpointer user_data){
    GtkWidget *dialogLoad;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;
    
    dialogLoad = gtk_file_chooser_dialog_new ("Open File",
                                      GTK_WINDOW(window),
                                      action,
                                      ("_Cancel"),
                                      GTK_RESPONSE_CANCEL,
                                      ("_Open"),
                                      GTK_RESPONSE_ACCEPT,
                                      NULL);
    
    res = gtk_dialog_run (GTK_DIALOG (dialogLoad));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        GtkFileChooser *chooser;
        char *filename;
        chooser = GTK_FILE_CHOOSER (dialogLoad);        
        filename = gtk_file_chooser_get_filename (chooser);
        strcpy(name, filename);

        readGridWithFile(name, 0);
        
        for ( int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                setCurrentNumber(grid[i][j].button, (i*10)+1+j);
                g_print("%i ", grid[i][j].value);
                if(grid[i][j].value == 0) strcpy(grid[i][j].show, " ");
                char temp[50] = "myButton_white_";
                strcat(temp, grid[i][j].normalState);
                if (!grid[i][j].fixed ) strcat(temp, "_lock");
                gtk_widget_set_name(grid[i][j].button, temp);
                gtk_button_set_label(GTK_BUTTON(grid[i][j].button), grid[i][j].show);
            }
            g_print("\n");
        }
        
        g_free (filename);
    }

    gtk_widget_destroy (dialogLoad);
}

void saveGame( GtkWidget *widget, gpointer user_data){
    gridToFile(name);
}

void toggleSave( GtkWidget *widget, gpointer user_data){
    if (gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(widget))) {
        autosave = true;
    } 
    else {
        autosave = false;
    }
}

void toggleHints( GtkWidget *widget, gpointer user_data){
    int x = getI(GPOINTER_TO_INT(last));
    int y = getJ(GPOINTER_TO_INT(last));
    if (gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(widget))) {
        hints = true;
        setCorresponding(x, y, grid[x][y].value);
    } 
    else {
        hints = false;
        setCorresponding(x, y, 0);
    }
}

void newGrid(){
    generateGrid(numberFields);
    
    for ( int i = 0; i < 9; i++) {
	for (int j = 0; j < 9; j++) {
            setCurrentNumber(grid[i][j].button, (i*10)+1+j);
            g_print("%i ", grid[i][j].value);
            char temp[50] = "myButton_white_";
            strcat(temp, grid[i][j].normalState);
            if (!grid[i][j].fixed ) strcat(temp, "_lock");
            gtk_widget_set_name(grid[i][j].button, temp);
            gtk_button_set_label(GTK_BUTTON(grid[i][j].button), grid[i][j].show);
        }
        g_print("\n");
    }
    sec_expired = 0; 
    gameTime = 0;
}

void resetGame(GtkWidget *widget, gpointer user_data){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(!grid[i][j].fixed){
                grid[i][j].value = 0;
                strcpy(grid[i][j].show,"");
                gtk_button_set_label(GTK_BUTTON(grid[i][j].button), grid[i][j].show);
            }
        }
    }
    sec_expired = 0; 
    gameTime = 0;
    gridToFile(name);
}

