/**
 * @file gestione_gioco.cc
 * @brief Racchiude tutte le funzioni per la gestione e lo svolgimento del gioco.
*/

#include "debug.h"
#include <gtk/gtk.h>
#include <cstring>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "struttura_dati.h"
#include "manutenzione.h"
#include "punteggi.h"
#include "informazioni.h"

using namespace std;

player p; /**< Istanza della struttura "player", utilizzata per la partita. */
int celle_visitate=0, /**< Numero di celle visitate dopo ogni click (utile per il calcolo del punteggio */
    bombe=0; /**< Numero casuale di bombe inserito dall'algoritmo nell'arena nella partita in corso. */
bool primo_colpo = true; /**< Determina se il click attuale e' il primo della partita */ 

/** Funzione di inizializzazione dell'arena
 *
 * Inizializza la struttura che descrive le celle dell'arena ("cell"). Resetta i campi 'flag' e 'visited', dopodiche' inserisce randomicamente 
 * le bombe, contando quante ne vengono inserite. Questo valore viene poi restituito.
 *
 * @return bombe Numero di bombe inserite dalla funzione nell'arena.
*/
int inizializza()
{
    srand(time(NULL));
    int bombe = 0;

    for(int i=0;i<15;i++){
        for(int j=0;j<20;j++){
            p.c[i][j].flag = false;
            D3("Flag ("<<i<<","<<j<<") = FALSE.");
            p.c[i][j].visited = false;
            D3("Visited ("<<i<<","<<j<<") = FALSE.");
            if(((rand()%1234)*(rand()%4321))%11 == 0){
                bombe++;
                p.c[i][j].bomb = true;  
                DS(cout<<"1 ");     
            }                     
            else{
                p.c[i][j].bomb = false;                
                DS(cout<<"0 ");
            }   
        }
        DS(cout<<endl);
    }

    return bombe;
}

/** Funzione di reset dei parametri di gioco
 *
 * Resetta alcuni parametri di gioco ai valori predefiniti, richiamata all'inizio di ogni partita.
 * Elimina tutte le immagini o i label dai bottoni e li imposta tutti "sensitive".
 *
 * @param builder Il builder GTK.
*/
void reset(GtkBuilder *builder)
{
    GtkButton *button;

    for(int i=0;i<15;i++){
        for(int j=0;j<20;j++){
            D3("Button ("<<i*100<<","<<j<<")");
            button = GTK_BUTTON(gtk_builder_get_object(builder,g_strdup_printf("%d", i*100+j)));
            gtk_widget_set_sensitive(GTK_WIDGET(button),true);
            gtk_button_set_image(button,NULL);
            gtk_button_set_label(button," ");
            D3("Button: sensitive, image=NULL, label=NULL.");
        }
    }

    gtk_widget_hide(GTK_WIDGET(gtk_builder_get_object(builder,"vittoria_prosegui")));
    gtk_widget_set_sensitive(GTK_WIDGET(gtk_builder_get_object(builder,"nome")),true);
    gtk_entry_set_text(GTK_ENTRY(GTK_WIDGET(gtk_builder_get_object(builder,"nome"))),"");
    gtk_widget_hide(GTK_WIDGET(gtk_builder_get_object(builder,"conferma_nome"))); 
}

/** Funzione di creazione del gioco
 * 
 * Setta punteggio e bombe trovate a 0 nella struttura del giocatore "player" e modifica i label che stampano questi valori nella schermata di 
 * gioco. Dopodiche' richiama la funzione di reset.
 *
 * @param builder Il builder GTK.
*/
void gioco(GtkBuilder *builder)
{
    p.pnt = 0; 
    gtk_label_set_text(GTK_LABEL(GTK_WIDGET(gtk_builder_get_object(builder,"gioco_punti"))),g_strdup_printf("%d", p.pnt));

    D2("Funzione: inizializza.");
    bombe = inizializza();
    p.bombs = 0;
    gtk_label_set_text(GTK_LABEL(GTK_WIDGET(gtk_builder_get_object(builder,"bombe"))),g_strdup_printf("%d", bombe));
    gtk_label_set_text(GTK_LABEL(GTK_WIDGET(gtk_builder_get_object(builder,"bombe_trovate"))),g_strdup_printf("%d", p.bombs));
        
    D2("Scrivi punteggio e numero bombe.");

    D2("Funzione: reset.");
    reset(builder);
}


/** Funzione di controllo della singola cella
 *
 * Richiamata se la cella non contiene una bomba.
 * Se la cella non e' ancora stata visitata setta il campo corrispondente a 'true'.
 * Controlla tutte le celle intorno ad essa, calcola quante bombe ci sono:
 * - se il numero e' 0: ritorna 'true';
 * - se il numero e' maggiore di 0: scrive il numero nella cella e ritorna 'false'.
 *
 * @param i Coordinata X della cella su cui eseguire il controllo.
 * @param j Coordinata Y della cella su cui eseguire il controllo.
 * @param builder Il builder GTK.
 * @return 'true' se la cella non ha bombe vicine, altrimenti 'false'.
*/
bool controlloCella(int i,int j,GtkBuilder *builder)
{
    D2("Cella ("<<i<<","<<j<<").");

    if(p.c[i][j].visited || p.c[i][j].flag){        
        D2("Cella gia' visitata o flaggata: controllo annullato.");        
        return false;
    }

    celle_visitate++;

    p.c[i][j].visited = true; 
    GtkButton *button = GTK_BUTTON(gtk_builder_get_object(builder,g_strdup_printf("%d", i*100+j))); 
    gtk_widget_set_sensitive(GTK_WIDGET(button),false);  
    D2("Button ("<<i*100<<","<<j<<"): sensitive=FALSE, visited=TRUE.");


    int num=0;
    if(i>0 && j>0 && p.c[i-1][j-1].bomb) num++;
    if(i>0 && p.c[i-1][j].bomb) num++;
    if(i>0 && j<19 && p.c[i-1][j+1].bomb) num++;
    if(j>0 && p.c[i][j-1].bomb) num++;
    if(j<19 && p.c[i][j+1].bomb) num++;
    if(i<14 && j>0 && p.c[i+1][j-1].bomb) num++;
    if(i<14 && p.c[i+1][j].bomb) num++;
    if(i<14 && j<19 && p.c[i+1][j+1].bomb) num++;

    if(num != 0){
        gtk_button_set_label(button,g_strdup_printf("%d", num)); 
        return false;
    }
    return true;
}

/** Funzione di espansione arena
 *
 * Richiamata su una cella che non ha bombe nelle celle limitrofe.
 * Controlla ognuna di quelle celle e si richiama su di loro se a loro volta non hanno bombe nelle celle vicine.
 * Questo permette di eliminare ricorsivamente blocchi di celle senza bombe e bloccarsi solo quando ci sono bombe nelle vicinanze.
 *
 * @param i Coordinata X della cella su cui eseguire il controllo.
 * @param j Coordinata Y della cella su cui eseguire il controllo.
 * @param builder Il builder GTK.
*/
void espandiArena(int i,int j,GtkBuilder *builder)
{
    if(i>0 && j>0 && controlloCella(i-1,j-1,builder)) espandiArena(i-1,j-1,builder);
    if(i>0 && controlloCella(i-1,j,builder)) espandiArena(i-1,j,builder);
    if(i>0 && j<19 && controlloCella(i-1,j+1,builder)) espandiArena(i-1,j+1,builder);
    if(j>0 && controlloCella(i,j-1,builder)) espandiArena(i,j-1,builder);
    if(j<19 && controlloCella(i,j+1,builder)) espandiArena(i,j+1,builder);
    if(i<14 && j>0 && controlloCella(i+1,j-1,builder)) espandiArena(i+1,j-1,builder);
    if(i<14 && controlloCella(i+1,j,builder)) espandiArena(i+1,j,builder);
    if(i<14 && j<19 && controlloCella(i+1,j+1,builder)) espandiArena(i+1,j+1,builder);
}

/** Funzione di controllo flag
 *
 * Richiamata al click con il tasto destro su una cella dell'arena.
 * Setta/resetta il flag per quella cella e inserisce/toglie l'icona di flag.
 * Inoltre modifica il valore di 'bombe_trovate' e aggiorna il label che lo stampa nella schermata di gioco.
 *
 * @param button Il button su cui e' stato fatto click destro.
 * @param builder Il builder GTK.
*/
void tastoDestro(GtkButton *button,GtkBuilder *builder)
{
    int i,j;
    trovaPosizione(i,j,button);
    D2("Click destro sul button ("<<i<<","<<j<<").");

    if(p.c[i][j].flag){
        D2("Button flaggato: rimozione flag.");
        p.c[i][j].flag = false;
        gtk_button_set_image(button,NULL);
        p.bombs--;
    } 
    else if(p.bombs < bombe){
        D2("Button non flaggati: inserimento flag.");
        p.c[i][j].flag = true;
        GtkWidget *image = gtk_image_new_from_file("../media/flag.png");
        gtk_button_set_always_show_image(button,true);
        gtk_button_set_image(button,image);
        p.bombs++;
    }

    gtk_label_set_text(GTK_LABEL(GTK_WIDGET(gtk_builder_get_object(builder,"bombe_trovate"))),g_strdup_printf("%d", p.bombs));
}

/** Funzione di stampa delle bombe
 *
 * Richimata alla sconfitta, mostra al giocatore l'ubicazione di tutte le bombe, stampando l'icona nelle rispettive celle.
 *
 * @param builder Il builder GTK.
*/
void mostraBombe(GtkBuilder *builder)
{
    GtkButton *button;

    for(int i=0;i<15;i++){
        for(int j=0;j<20;j++){
            if(p.c[i][j].bomb){
                GtkWidget *image = gtk_image_new_from_file("../media/bomb.png");
                button = GTK_BUTTON(gtk_builder_get_object(builder,g_strdup_printf("%d", i*100+j)));
                gtk_button_set_always_show_image(button,true);
                gtk_button_set_image(button,image);
            }
        }
    } 
}

/** Funzione di controllo della cella
 *
 * Richiamata al click di una cella dell'arena.
 * Trova la posizione dela cella e controlla cosa rappresenta, se e' una bomba richiama la finestra di sconfitta.
 * Se non lo e' richiama il controllo e se questo ritorna 'true', attiva l'espansione dell'arena. Dopodiche' chiama la funzione di aggiornamento 
 * del punteggio.
 *
 * @param button Il button su cui e' stato fatto click.
 * @param builder Il builder GTK.
 * @return 'true' se la cella non e' una bomba (o se vi e' il flag), altrimenti 'false'.
*/
bool gestioneCella(GtkButton *button,GtkBuilder *builder)
{
    int i,j;
    trovaPosizione(i,j,button);

    D2("Gestione cella ("<<i<<","<<j<<").");

    if(p.c[i][j].flag){
        D2("Cella flaggata: annullo gestione.");
        return true;
    }

    gtk_widget_set_sensitive(GTK_WIDGET(button),false);
    D2("Button ("<<i<<","<<j<<"): sensitive=FALSE.");

    if(p.c[i][j].bomb){
        D2("Bomba: sconfitta.");
        if(!primo_colpo) nuovaSconfitta(); // Se si colpisce la bomba al primo click, questa non viene conteggiata come partita persa.
        D2("Funzione: mostraBombe.");
        mostraBombe(builder);  
        return false;
    }
    else if(controlloCella(i,j,builder)) espandiArena(i,j,builder);

    if(primo_colpo) primo_colpo = false;

    calcolaPunteggio(builder,celle_visitate,p);
    celle_visitate = 0;
    return true;
}

/** Funzione di controllo della vittoria
 *
 * Controlla se il giocatore e' riuscito a marcare tutte le bombe con un flag o a bloccare tutte le altre celle. In tal caso ritorna 'true',
 * altrimenti 'false'.
 *
 * @param builder Il builder GTK.
 * @return 'true' se il giocatore ha vinto, altrimenti 'false'.
*/
bool controlloVittoria(GtkBuilder *builder)
{   
    for(int i=0;i<15;i++){
        for(int j=0;j<20;j++){
            D3("Controllo cella ("<<i<<","<<j<<") per vittoria.");
            GtkButton *button = GTK_BUTTON(gtk_builder_get_object(builder,g_strdup_printf("%d", i*100+j))); 
            if(!p.c[i][j].bomb && gtk_widget_get_sensitive(GTK_WIDGET(button))){
                for(int a=0;a<15;a++) for(int b=0;b<20;b++) if(p.c[a][b].bomb && !p.c[a][b].flag) return false;
            }
        }
    }
    return true;
}

/** Funzione di controllo del punteggio
 *
 * Aggiorna definitivamente il punteggio in base alla corretta (+10) o errata (-10) marcatura di una cella con il flag. Poi controlla se il 
 * punteggio ottenuto e' sufficiente per entrare in classifica.
 *
 * @param builder Il builder GTK.
 * @return 'true' se il punteggio e' entrato in classifica, altrimenti 'false'.
*/
bool controlloPunteggio(GtkBuilder *builder)
{   
    for(int i=0;i<15;i++){
        for(int j=0;j<20;j++){
            D3("Controllo cella ("<<i<<","<<j<<") per flag.");
            if(p.c[i][j].bomb && p.c[i][j].flag) p.pnt += 10;
            if(p.c[i][j].flag && !p.c[i][j].bomb) p.pnt -= 10;
        }
    }
    
    nuovaVittoria();

    D2("Funzione: cercaRecord.");
    if(cercaRecord(p.pnt)){
        gtk_label_set_text(GTK_LABEL(GTK_WIDGET(gtk_builder_get_object(builder,"gioco_punti"))),g_strdup_printf("%d", p.pnt));
        gtk_label_set_text(GTK_LABEL(GTK_WIDGET(gtk_builder_get_object(builder,"l_punteggio"))),g_strdup_printf("%d", p.pnt));        
        return true;
    }
    else return false;
}




