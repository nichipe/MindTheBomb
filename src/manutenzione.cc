/**
 * @file manutenzione.cc
 * @brief Racchiude tutte le funzioni di servizio.
*/

#include "debug.h"
#include <gtk/gtk.h>
#include <ctime>
#include <iostream>
#include "struttura_dati.h"

using namespace std;

/** Funzione di posizione cella
 *
 * Dato un GtkButton dell'arena, estrapola le sue cordinate i,j(x,y) nella matrice dal suo ID.
 *
 * @param i Coordinata X della cella in cui e' inserito il button.
 * @param j Coordinata Y della cella in cui e' inserito il button.
 * @param button Puntatore ad un oggetto di tipo "GtkButton".
*/
void trovaPosizione(int &i,int &j,GtkButton *button)
{
    i = (gtk_widget_get_name(GTK_WIDGET(button))[0] - '0')*10 + gtk_widget_get_name(GTK_WIDGET(button))[1] - '0';
    j = (gtk_widget_get_name(GTK_WIDGET(button))[2] - '0')*10 + gtk_widget_get_name(GTK_WIDGET(button))[3] - '0';

    D2("Button alla posizione ("<<i<<","<<j<<").");
}

/** Funzione di calcolo del punteggio
 *
 * Richiamata dopo ogni click di una cella dell'arena, aggiorna il punteggio del giocatore. 
 * Per farlo utilizza come parametro il numero di celle che il giocatore ha sbloccato con il click:
 * - da 1 a 4: 1 punto per cella;
 * - da 5 a 9: 3 punti per cella;
 * - da 10 in su: 5 punti per cella;
 *
 * La funzione calcola il punteggio, lo aggiorna nella struttura di tipo "player" e nel label che lo mostra nella schermata di gioco.
 *
 * @param builder Il builder GTK.
 * @param celle Numero di celle sbloccate dal click del giocatore.
 * @param p Struttura che descrive il giocatore (in particolare utilizzata per il paramentro 'pnt' (punti)).
*/
void calcolaPunteggio(GtkBuilder *builder,int celle,player &p)
{
    int punti;
    if(celle>1 && celle <5) punti = celle;
    else if(celle>=5 && celle<10) punti = celle*3;
    else if(celle>=10) punti = celle*5; 

    p.pnt += punti;

    gtk_label_set_text(GTK_LABEL(GTK_WIDGET(gtk_builder_get_object(builder,"gioco_punti"))),g_strdup_printf("%d", p.pnt));
}

/** Funzione di modifica del colore di sfondo
 * 
 * Si occupa di modificare il colore di sfondo di un widget, tramite un oggetto di tipo "GtkColor" di cui si modificano gli attributi RGB.
 *
 * @param window Puntatore all'oggetto di tipo "GtkWidget", ovvero il widget da modificare.
 * @param color Oggetto di tipo GdkColor, rappresenta una combinazione RGB in esadecimale.
 * @param builder Il builder GTK.
*/
void changeWidgetBg(GtkWidget *widget,GdkColor color,GtkBuilder *builder)
{
    gtk_widget_modify_bg(widget, GTK_STATE_NORMAL, &color);
}

/** Funzione di modifica del label
 * 
 * Si occupa di modificare il colore di un label, tramite un oggetto di tipo "GtkColor" di cui si modificano gli attributi RGB.
 *
 * @param window Puntatore all'oggetto di tipo "GtkWidget", ovvero il label da modificare.
 * @param color Oggetto di tipo GdkColor, rappresenta una combinazione RGB in esadecimale.
 * @param builder Il builder GTK.
*/
void changeLabel(GdkColor color,GtkBuilder *builder)
{
    gtk_widget_modify_fg(GTK_WIDGET(gtk_builder_get_object(builder,"l_menu")), GTK_STATE_NORMAL, &color);    
    gtk_widget_modify_fg(GTK_WIDGET(gtk_builder_get_object(builder,"l_esci")), GTK_STATE_NORMAL, &color);
    gtk_widget_modify_fg(GTK_WIDGET(gtk_builder_get_object(builder,"l_check_uscita")), GTK_STATE_NORMAL, &color);
    gtk_widget_modify_fg(GTK_WIDGET(gtk_builder_get_object(builder,"l_no_uscita")), GTK_STATE_NORMAL, &color);
    gtk_widget_modify_fg(GTK_WIDGET(gtk_builder_get_object(builder,"l_si_uscita")), GTK_STATE_NORMAL, &color);
    gtk_widget_modify_fg(GTK_WIDGET(gtk_builder_get_object(builder,"messaggio_remove")), GTK_STATE_NORMAL, &color);
    gtk_widget_modify_fg(GTK_WIDGET(gtk_builder_get_object(builder,"l_annulla_remove")), GTK_STATE_NORMAL, &color);
    gtk_widget_modify_fg(GTK_WIDGET(gtk_builder_get_object(builder,"l_conferma_remove")), GTK_STATE_NORMAL, &color);
    gtk_widget_modify_fg(GTK_WIDGET(gtk_builder_get_object(builder,"l_help")), GTK_STATE_NORMAL, &color);
    gtk_widget_modify_fg(GTK_WIDGET(gtk_builder_get_object(builder,"l_hof")), GTK_STATE_NORMAL, &color);
    gtk_widget_modify_fg(GTK_WIDGET(gtk_builder_get_object(builder,"l_remove_stats")), GTK_STATE_NORMAL, &color);
    gtk_widget_modify_fg(GTK_WIDGET(gtk_builder_get_object(builder,"l_remove_hof")), GTK_STATE_NORMAL, &color);
    gtk_widget_modify_fg(GTK_WIDGET(gtk_builder_get_object(builder,"l_info")), GTK_STATE_NORMAL, &color);
    
    D2("Modifica colore label secondo tema eseguita.");
}

/** Funzione di decorazione delle finestre
 *
 * Richiama per ogni finestra la funzione di cambio dello sfondo, settando il colore giusto in base al tema.
 * 
 * @param builder Il builder GTK.
 * @param c Il colore del tema in uso.
 * @param t Il tema in uso.
*/
void decoraFinestre(GtkBuilder *builder,char c[8],int t)
{
    GdkColor color;

    GtkWidget *main_w = GTK_WIDGET(gtk_builder_get_object(builder,"main_w")),
              *hof_w = GTK_WIDGET(gtk_builder_get_object(builder,"hof_w")),
              *check_delete_w = GTK_WIDGET(gtk_builder_get_object(builder,"check_delete_w")),
              *help_w = GTK_WIDGET(gtk_builder_get_object(builder,"help_w")),
              *arena_w = GTK_WIDGET(gtk_builder_get_object(builder,"arena_w")),
              *check_menu_w = GTK_WIDGET(gtk_builder_get_object(builder,"check_menu_w")),
              *check_remove_w = GTK_WIDGET(gtk_builder_get_object(builder,"check_remove_w")),
              *lose_w = GTK_WIDGET(gtk_builder_get_object(builder,"lose_w")),
              *win_w = GTK_WIDGET(gtk_builder_get_object(builder,"win_w")),
              *info_w = GTK_WIDGET(gtk_builder_get_object(builder,"info_w"));

    gdk_color_parse(c,&color);
    changeWidgetBg(main_w,color,builder);
    changeWidgetBg(arena_w,color,builder);
    changeWidgetBg(check_menu_w,color,builder);
    changeWidgetBg(lose_w,color,builder);
    changeWidgetBg(win_w,color,builder);
    changeLabel(color,builder);

    D2("Modifica colore finestre secondo tema eseguita.");

    gdk_color_parse("#FFFFFF",&color);
    changeWidgetBg(hof_w,color,builder);
    changeWidgetBg(help_w,color,builder);
    changeWidgetBg(check_delete_w,color,builder);
    changeWidgetBg(check_remove_w,color,builder);
    changeWidgetBg(info_w,color,builder);

    D2("Modifica colore finestre bianco eseguita.");
}

/** Funzione di modifica del tema
 *
 * Riceve in ingresso il codice corrispondente al nuovo tema e in base a quello modifica il colore di sfondo delle finestre e le immagini.
 *
 * @param builder Il builder GTK.
 * @param t Il codice del tema da attivare.
*/
void cambiaTema(GtkBuilder *builder,int t){
    switch(t){
        case 1:
            D2("Funzione: decoraFinestre.");
            decoraFinestre(builder,"#0D479D",t);
            gtk_image_set_from_file(GTK_IMAGE(gtk_builder_get_object(builder,"img_main")),"../media/img_main_greek.jpg");
            gtk_image_set_from_file(GTK_IMAGE(gtk_builder_get_object(builder,"img_gioco")),"../media/img_gioco_greek.jpg");
            gtk_image_set_from_file(GTK_IMAGE(gtk_builder_get_object(builder,"img_hof")),"../media/img_hof_greek.jpg");
            gtk_image_set_from_file(GTK_IMAGE(gtk_builder_get_object(builder,"image_help")),"../media/img_help_greek.png");
            gtk_image_set_from_file(GTK_IMAGE(gtk_builder_get_object(builder,"image_chiudi")),"../media/img_exit_greek.png");
            gtk_image_set_from_file(GTK_IMAGE(gtk_builder_get_object(builder,"img_info")),"../media/img_info_greek.png");
            D2("Modifica immagini di gioco secondo tema Greek.");
            break;
        case 2:
            D2("Funzione: decoraFinestre.");
            decoraFinestre(builder,"#FFCC00",t);
            gtk_image_set_from_file(GTK_IMAGE(gtk_builder_get_object(builder,"img_main")),"../media/img_main_fw.jpg");
            gtk_image_set_from_file(GTK_IMAGE(gtk_builder_get_object(builder,"img_gioco")),"../media/img_gioco_fw.jpg");
            gtk_image_set_from_file(GTK_IMAGE(gtk_builder_get_object(builder,"img_hof")),"../media/img_hof_fw.jpg");
            gtk_image_set_from_file(GTK_IMAGE(gtk_builder_get_object(builder,"image_help")),"../media/img_help_fw.png");
            gtk_image_set_from_file(GTK_IMAGE(gtk_builder_get_object(builder,"image_chiudi")),"../media/img_exit_fw.png");
            gtk_image_set_from_file(GTK_IMAGE(gtk_builder_get_object(builder,"img_info")),"../media/img_info_fw.png");
            D2("Modifica immagini di gioco secondo tema Far West.");
            break;
        case 3:
            D2("Funzione: decoraFinestre.");
            decoraFinestre(builder,"#00A86B",t);
            gtk_image_set_from_file(GTK_IMAGE(gtk_builder_get_object(builder,"img_main")),"../media/img_main_jungle.jpg");
            gtk_image_set_from_file(GTK_IMAGE(gtk_builder_get_object(builder,"img_gioco")),"../media/img_gioco_jungle.jpg");
            gtk_image_set_from_file(GTK_IMAGE(gtk_builder_get_object(builder,"img_hof")),"../media/img_hof_jungle.jpg");
            gtk_image_set_from_file(GTK_IMAGE(gtk_builder_get_object(builder,"image_help")),"../media/img_help_jungle.png");
            gtk_image_set_from_file(GTK_IMAGE(gtk_builder_get_object(builder,"image_chiudi")),"../media/img_exit_jungle.png");
            gtk_image_set_from_file(GTK_IMAGE(gtk_builder_get_object(builder,"img_info")),"../media/img_info_jungle.png");
            D2("Modifica immagini di gioco secondo tema Jungle.");
            break;
        case 4:
            D2("Funzione: decoraFinestre.");
            decoraFinestre(builder,"#FF2800",t);
            gtk_image_set_from_file(GTK_IMAGE(gtk_builder_get_object(builder,"img_main")),"../media/img_main_fire.jpg");
            gtk_image_set_from_file(GTK_IMAGE(gtk_builder_get_object(builder,"img_gioco")),"../media/img_gioco_fire.jpg");
            gtk_image_set_from_file(GTK_IMAGE(gtk_builder_get_object(builder,"img_hof")),"../media/img_hof_fire.jpg");
            gtk_image_set_from_file(GTK_IMAGE(gtk_builder_get_object(builder,"image_help")),"../media/img_help_fire.png");
            gtk_image_set_from_file(GTK_IMAGE(gtk_builder_get_object(builder,"image_chiudi")),"../media/img_exit_fire.png");
            gtk_image_set_from_file(GTK_IMAGE(gtk_builder_get_object(builder,"img_info")),"../media/img_info_fire.png");
            D2("Modifica immagini di gioco secondo tema Fire.");
            break;
    }
}










