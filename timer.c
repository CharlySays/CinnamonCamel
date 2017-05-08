#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>

/* Determines if to continue the timer or not */
static gboolean continue_timer = FALSE;

/* Determines if the timer has started */
static gboolean start_timer = FALSE;

/* Display seconds expired */
static int sec_expired = -1;

static void
_quit_cb (GtkWidget *button, gpointer data)
{
    (void)button; (void)data; /*Avoid compiler warnings*/
    gtk_main_quit();
    return;
}


static gboolean
_label_update(gpointer data)
{
    GtkLabel *label = (GtkLabel*)data;
    char buf[256];
    memset(&buf, 0x0, 256);
    snprintf(buf, 255, "Time elapsed: %d secs", ++sec_expired);
    gtk_label_set_label(label, buf);
    return continue_timer;

}

static void 
_start_timer (GtkWidget *button, gpointer data)
{
    (void)button;/*Avoid compiler warnings*/
    GtkWidget *label = data;
    if(!start_timer)
    {
        g_timeout_add_seconds(1, _label_update, label);
        start_timer = TRUE;
        continue_timer = TRUE;
    }
}

static void
_pause_resume_timer (GtkWidget *button, gpointer data)
{
    (void)button;/*Avoid compiler warnings*/
    if(start_timer)
    {
        GtkWidget *label = data;
        continue_timer = !continue_timer;
        if(continue_timer)
        {
            g_timeout_add_seconds(1, _label_update, label);
        }
        else
        {
            /*Decrementing because timer will be hit one more time before expiring*/
            sec_expired--;
        }
    }
}

static void
_reset_timer (GtkWidget *button, gpointer data)
{
    (void)button; (void)data;/*Avoid compiler warnings*/
    /*Setting to -1 instead of 0, because timer will be triggered once more before expiring*/
    sec_expired = -1;
    continue_timer = FALSE;
    start_timer = FALSE;
}