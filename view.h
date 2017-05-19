#ifndef VIEW_H
#define VIEW_H

#include "controller.h"
#include "global.h"

gpointer last;
GtkWidget *lastWidget;
Field grid[9][9];
char name[256];
int gameTime;
GtkWidget *dialog, *entry, *label, *window;
GtkContainer *container;
bool autosave, hints, windowOpen;

void myCss(void);
void setStyleClicked(int x, int y, bool clicked);
void setCurrentNumber(GtkWidget *widget, int nr);
void fill_grid_with_buttons(GtkWidget *gtkGrid);
void createDialog(GtkWidget *parent);
GtkWidget* createMenu();
GdkPixbuf *create_pixbuf(const gchar * filename);
void setCorresponding(int x, int y, int val);

#endif /* VIEW_H */

