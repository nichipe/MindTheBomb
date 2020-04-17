/**
 * @file handlers.h
 * @brief Racchiude tutti gli header che permettono al software di comunicare con la GUI.
*/

#include "debug.h"
#include <gtk/gtk.h>
#include <iostream>
#include "gestione_gioco.h"
#include "punteggi.h"
#include "manutenzione.h"
#include "informazioni.h"

using namespace std;

extern GtkBuilder *builder; /* Riferimento esterno al builder GTK dichiarato nel modulo <main.cc> */
bool stats = true; /**< Determina se eliminare le statistiche ('true') o i record ('false'). */

/** Handler tasto uscita
 * 
 * Apre la finestra che chiede all'utente se vuole davvero uscire.
*/
extern "C" void delete_event(GtkButton *button, gpointer user_data)
{ 
    D1("Tasto esci.");

    gtk_widget_show(GTK_WIDGET(gtk_builder_get_object(builder,"check_delete_w"))); 

    D2("Mostra finestra conferma uscita.");
}

/** Handler annullamento uscita
 *
 * Nasconde la finestra di conferma uscita se l'utente non conferma di voler uscire.
*/
extern "C" void exit_no(GtkButton *button, gpointer user_data)
{ 
    D1("Tasto uscita: NO.");

    gtk_widget_hide(GTK_WIDGET(gtk_builder_get_object(builder,"check_delete_w"))); 

    D2("Nascondi finestra conferma uscita.");
}

/** Handler conferma uscita
 *
 * Chiude il programma, ovvero esce dal ciclo di gestione degli eventi GTK.
*/
extern "C" void exit_yes(GtkButton *button, gpointer user_data)
{ 
    D1("Tasto uscita: SI.");

    gtk_main_quit(); 
}

/** Handler gioco
 *
 * Gestisce l'evento di click del tasto "Gioca". 
 * Richiama la funzione che setta i parametri iniziali e inizializza l'arena, dopodiche' nasconde la finestra principale e mostra quella di
 * gioco.
*/
extern "C" void button_gioco(GtkButton *button, gpointer user_data)
{   
    D1("Tasto: GIOCA.");

    D2("Funzione: gioco.");
    gioco(builder);  
        
    gtk_widget_show(GTK_WIDGET(gtk_builder_get_object(builder,"arena_w")));
    
    D2("Mostra finestra arena.");
}

/** Handler punteggi
 *
 * Gestisce l'evento di selezione del tasto "Hall of Fame". 
 * Mostra all'utente la finestra dei migliori punteggi dopo averla decorata, nascondendo quella principale.
*/
extern "C" void button_hof(GtkButton *button, gpointer user_data)
{
    D1("Tasto: HALL OF FAME.");

    D2("Funzione: stampaPunteggi.");
    stampaPunteggi(builder);

    GtkWidget *win_w = GTK_WIDGET(gtk_builder_get_object(builder,"win_w")),
              *arena_w = GTK_WIDGET(gtk_builder_get_object(builder,"arena_w")),
              *hof_w = GTK_WIDGET(gtk_builder_get_object(builder,"hof_w"));

    gtk_widget_show(hof_w);
    D2("Mostra finestra punteggi.");
    gtk_widget_hide(win_w);
    D2("Nascondi finestra vittoria.");
    gtk_widget_hide(arena_w);
    D2("Nascondi finestra arena.");
}

/** Handler chiusura punteggi
 *
 * Chiude la finestra di visualizzazione dei punteggi e mostra quella del menu principale.
*/
extern "C" void button_chiudi_hof(GtkButton *button, gpointer user_data)
{
    D1("Tasto punteggi: CHIUDI.");

    gtk_widget_hide(GTK_WIDGET(gtk_builder_get_object(builder,"hof_w")));

    D2("Nascondi finestra punteggi.");
}

/** Handler help
 *
 * Gestisce l'evento di selezione del tasto "?". 
 * Mostra la finestra di aiuto all'utente, nascondendo quella principale.
*/
extern "C" void button_help(GtkButton *button, gpointer user_data)
{
    D1("Tasto: ?.");

    gtk_widget_show(GTK_WIDGET(gtk_builder_get_object(builder,"help_w")));   

    D2("Mostra finestra aiuto.");
}

/** Handler chiusura help
 *
 * Chiude la finestra di aiuto e mostra quella del menu principale.
*/
extern "C" void button_chiudi_help(GtkButton *button, gpointer user_data)
{
    D1("Tasto aiuto: OK.");

    gtk_widget_hide(GTK_WIDGET(gtk_builder_get_object(builder,"help_w")));

    D2("Nascondi finestra aiuto.");
}

/** Handler informazioni
 *
 * Gestisce l'evento di selezione del tasto "i". 
 * Mostra la finestra di informazioni all'utente dopo averla decorata, nascondendo quella principale.
*/
extern "C" void button_info(GtkButton *button, gpointer user_data)
{
    D1("Tasto: i.");

    D2("Funzione: stampaStatistiche.");
    stampaStatistiche(builder);

    gtk_widget_show(GTK_WIDGET(gtk_builder_get_object(builder,"info_w")));   

    D2("Mostra finestra informazioni.");
}

/** Handler chiusura informazioni
 *
 * Chiude la finestra di informazioni e mostra quella del menu principale.
*/
extern "C" void button_chiudi_info(GtkButton *button, gpointer user_data)
{
    D1("Tasto informazioni: CHIUDI.");

    gtk_widget_hide(GTK_WIDGET(gtk_builder_get_object(builder,"info_w")));

    D2("Nascondi finestra informazioni.");
}

/** Handler tasto menu' principale
 * 
 * Apre la finestra che chiede all'utente se vuole davvero tornare al menu' principale.
*/
extern "C" void menu_event(GtkButton *button, gpointer user_data)
{ 
    D1("Tasto arena: MENU PRINCIPALE.");

    gtk_widget_show(GTK_WIDGET(gtk_builder_get_object(builder,"check_menu_w"))); 

    D2("Mostra finestra conferma ritorno al menu principale.");
}

/** Handler conferma menu' principale
 *
 * Mostra il menu' principale e nasconde la finestra dell'arena.
 *
*/
extern "C" void main_menu_yes(GtkButton *button, gpointer user_data)
{
    D1("Tasto ritorno menu: SI.");

    GtkWidget *main_w = GTK_WIDGET(gtk_builder_get_object(builder,"main_w")),
              *arena_w = GTK_WIDGET(gtk_builder_get_object(builder,"arena_w")),
              *check_menu_w = GTK_WIDGET(gtk_builder_get_object(builder,"check_menu_w")),
              *win_w = GTK_WIDGET(gtk_builder_get_object(builder,"win_w")),
              *lose_w = GTK_WIDGET(gtk_builder_get_object(builder,"lose_w"));

    gtk_widget_hide(lose_w);
    D2("Nascondi finestra sconfitta.");
    gtk_widget_hide(check_menu_w);
    D2("Nascondi finestra conferma ritorno al menu principale.");
    gtk_widget_hide(arena_w);
    D2("Nascondi finestra arena.");
    gtk_widget_hide(win_w);
    D2("Nascondi finestra vittoria.");
    gtk_widget_show(main_w);
    D2("Mostra finestra menu principale.");
}

/** Handler annullamento menu' principale
 *
 * Nasconde la finestra di conferma ritorno al menu se l'utente non conferma di voler uscire.
*/
extern "C" void main_menu_no(GtkButton *button, gpointer user_data)
{ 
    D1("Tasto ritorno menu: NO.");

    gtk_widget_hide(GTK_WIDGET(gtk_builder_get_object(builder,"check_menu_w"))); 

    D2("Nascondi finestra conferma ritorno menu principale.");    
}

/** Handler click cella
 *
 * Gestisce l'evento del click su una cella.
 * Se è premuto il tastro destro inserisce/rimuove la bandierina di avviso (flag).
 * Se è premuto il tasto sinistro imposta la cella "non sensitive" e chiama la funzione di controllo.
 *
 * Dopodichè lancia la funzione che controlla se il giocatore ha vinto la partita.
*/
extern "C" void click_button_arena(GtkButton *button,GdkEventButton *event, gpointer user_data)
{ 
    if(event->type == GDK_BUTTON_PRESS && event->button == 3){
        tastoDestro(button,builder);
        D1("Click destro.");
    }
    if(event->type == GDK_BUTTON_PRESS && event->button == 1){
        D1("Click sinistro.");
        if(!gestioneCella(button,builder)){
            gtk_widget_show(GTK_WIDGET(gtk_builder_get_object(builder,"lose_w")));
            D2("Mostra finestra sconfitta.");        
        }
    }
    
    D2("Funzione: controlloVittoria.");    
    if(controlloVittoria(builder)){
        D2("Funzione: controlloPunteggio.");
        if(controlloPunteggio(builder)){
            gtk_widget_show(GTK_WIDGET(gtk_builder_get_object(builder,"inserimento_nome")));
            gtk_widget_show(GTK_WIDGET(gtk_builder_get_object(builder,"conferma_nome")));
            D2("Mostra inserimento e conferma nome.");        
        }
        else{
            gtk_widget_show(GTK_WIDGET(gtk_builder_get_object(builder,"vittoria_prosegui")));
            D2("Mostra tasti proseguimento.");
        }
        gtk_widget_show(GTK_WIDGET(gtk_builder_get_object(builder,"win_w")));
        D2("Mostra finestra vittoria.");
    }
}

/** Handler rigioca
 *
 * Gestisce il click del tasto rigioca dopo una sconfitta, richiamando l'inizializzazione del gioco e nascondendo la finestra di scelta.
*/
extern "C" void button_rigioca(GtkButton *button, gpointer user_data)
{ 
    D1("Tasto vittoria: RIGIOCA.");

    D2("Funzione: gioco.");
    gioco(builder);
    
    gtk_widget_hide(GTK_WIDGET(gtk_builder_get_object(builder,"win_w")));
    D2("Nascondi finestra vittoria.");
    gtk_widget_hide(GTK_WIDGET(gtk_builder_get_object(builder,"lose_w")));
    D2("Nascondi finestra sconfitta.");
}

/** Handler conferma record
 *
 * Si occupa di estrapolare il nome del giocatore dalla GtkEntry e richiama la funzione di inserimento del record nel file dei punteggi.
*/
extern "C" void conferma_record(GtkButton *button, gpointer user_data)
{ 
    D1("Tasto vittoria: CONFERMA.");

    char nome[20];
    sprintf(nome,"%s",gtk_entry_get_text(GTK_ENTRY(GTK_WIDGET(gtk_builder_get_object(builder,"nome")))));

    D2("Funzione: inserimentoPunteggio.");
    inserimentoPunteggio(nome);
    
    gtk_widget_show_all(GTK_WIDGET(gtk_builder_get_object(builder,"vittoria_prosegui")));
    D2("Mostra tasti proseguimento.");
    gtk_widget_set_sensitive(GTK_WIDGET(gtk_builder_get_object(builder,"nome")),false);
    D2("Spazio inserimento nome insensibile.");
    gtk_widget_hide(GTK_WIDGET(gtk_builder_get_object(builder,"conferma_nome"))); 
    D2("Nascondi tasto conferma.");
}

/** Handler tema "Greek"
 *
 * Disattiva il toggle button relativo al tema attivo precedentemente e chiama la funzione di modifica del tema.
*/
extern "C" void theme_greek(GtkButton *button, gpointer user_data)
{ 
    D1("Selezione tema: Greek.");

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"b_fw")),false);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"b_jungle")),false);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"b_fire")),false);

    D2("Funzione: cambiaTema.");
    cambiaTema(builder,1);
}

/** Handler tema "Far West"
 *
 * Disattiva il toggle button relativo al tema attivo precedentemente e chiama la funzione di modifica del tema.
*/
extern "C" void theme_fw(GtkButton *button, gpointer user_data)
{ 
    D1("Selezione tema: Far West.");

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"b_greek")),false);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"b_jungle")),false);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"b_fire")),false);

    D2("Funzione: cambiaTema.");
    cambiaTema(builder,2);
}

/** Handler tema "Jungle"
 *
 * Disattiva il toggle button relativo al tema attivo precedentemente e chiama la funzione di modifica del tema.
*/
extern "C" void theme_jungle(GtkButton *button, gpointer user_data)
{ 
    D1("Selezione tema: Jungle.");

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"b_greek")),false);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"b_fw")),false);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"b_fire")),false);

    D2("Funzione: cambiaTema.");
    cambiaTema(builder,3);
}

/** Handler tema "Fire"
 *
 * Disattiva il toggle button relativo al tema attivo precedentemente e chiama la funzione di modifica del tema.
*/
extern "C" void theme_fire(GtkButton *button, gpointer user_data)
{ 
    D1("Selezione tema: Fire.");

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"b_greek")),false);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"b_jungle")),false);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"b_fw")),false);

    D2("Funzione: cambiaTema.");
    cambiaTema(builder,4);
}

/** Handler azzeramento statistiche
 *
 * Apre la finestra di conferma di eliminazione delle statistiche e setta la variabile booleana di controllo.
*/
extern "C" void b_del_stats(GtkButton *button, gpointer user_data)
{ 
    D1("Tasto informazioni: AZZERA STATISTICHE.");

    stats = true;  
    gtk_label_set_text(GTK_LABEL(GTK_WIDGET(gtk_builder_get_object(builder,"messaggio_remove"))),"Sei sicuro di voler azzerare le statistiche? (L'operazione e' irreversibile.)");
    gtk_widget_show(GTK_WIDGET(gtk_builder_get_object(builder,"check_remove_w"))); 

    D2("Mostra messaggio di conferma azzeramento.");
}

/** Handler azzeramento record
 *
 * Apre la finestra di conferma di eliminazione dei record e resetta la variabile booleana di controllo.
*/
extern "C" void b_del_hof(GtkButton *button, gpointer user_data)
{ 
    D1("Tasto informazioni: AZZERA PUNTEGGI.");

    stats = false;   
    gtk_label_set_text(GTK_LABEL(GTK_WIDGET(gtk_builder_get_object(builder,"messaggio_remove"))),"Sei sicuro di voler azzerare i record? (L'operazione e' irreversibile.)");
    gtk_widget_show(GTK_WIDGET(gtk_builder_get_object(builder,"check_remove_w"))); 

    D2("Mostra messaggio di conferma azzeramento.");
}

/** Handler annullamento eliminazione file
 *
 * Chiude la finestra di conferma di eliminazione.
*/
extern "C" void annulla_remove(GtkButton *button, gpointer user_data)
{   
    D1("Tasto azzeramento: NO.");

    gtk_widget_hide(GTK_WIDGET(gtk_builder_get_object(builder,"check_remove_w"))); 

    D2("Nascondi messaggio di conferma azzeramento.");
}

/** Handler conferma eliminazione file
 *
 * Chiude la finestra di conferma di eliminazione e elimina il file selezionato.
*/
extern "C" void conferma_remove(GtkButton *button, gpointer user_data)
{   
    D1("Tasto azzeramento: SI.");

    if(stats){
        eliminaStatistiche(builder);
        D2("Funzione: eliminaStatistiche.");
    }
    else {
        eliminaPunteggi(builder);
        D2("Funzione: eliminaPunteggi.");
    }

    gtk_widget_hide(GTK_WIDGET(gtk_builder_get_object(builder,"check_remove_w")));

    D2("Nascondi messaggio di conferma azzeramento.");
}









