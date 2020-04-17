/**
 * @file informazioni.cc
 * @brief Racchiude tutte le funzioni di creazione delle statistiche.
*/

#include "debug.h"
#include <fstream>
#include <gtk/gtk.h>
#include <cstring>
#include <cstdio>
#include <iostream>
#include "struttura_dati.h"

using namespace std;

info i; /**< Struttura per il salvataggio delle statistiche del giocatore */
bool sstampa = true; /**< Valore booleano che decide se è necessario o meno chiamare la funzione di stampa delle statistiche. */

/** Funzione di salvataggio delle statistiche 
 *
 * Scrive le statistiche sul file.
*/
void salvaStatistiche(){
    D2("Apertura (o creazione) file: statistiche.txt in scrittura.");
    ofstream f(STATISTICHE);

    f<<i.played<<endl<<i.win<<endl<<i.lose<<endl;
}

/** Funzione di caricamento statistiche
 *
 * Apre il file delle statistiche e ne salva i valori nella struttura preposta. Se il file non esiste setta i valori a default(0).
*/
void catturaInformazioni(){
    D2("Apertura file: statistiche.txt in lettura.");
    ifstream f(STATISTICHE);

    if(!f){
        D2("File non esistente.");
        i.played = i.win = i.lose = 0;    
    }
    else{
        D2("File esistente.");
        f>>i.played;
        f>>i.win;
        f>>i.lose;
    }
}

/** Incremento vittorie
 *
 * Aumenta il numero delle vittorie.
*/
void nuovaVittoria(){   
    i.played++;
    i.win++; 
    sstampa = true;
    salvaStatistiche();
}

/** Incremento sconfitte 
 *
 * Aumenta il numero delle sconfitte.
*/
void nuovaSconfitta(){ 
    i.played++;
    i.lose++; 
    sstampa = true;
    salvaStatistiche();
}

/** Funzione di stampa delle statistiche
 *
 * Se non e' ancora stata decorata la finestra delle statistiche o se ci sono stati aggiornamenti, vengono stampate le nuove statistiche.
 *
 * @param builder Il builder GTK.
*/
void stampaStatistiche(GtkBuilder *builder){
    if(sstampa){
        int percent_V=0, percent_L=0;
        if(i.played != 0){
            percent_V = (i.win*100)/i.played;
            percent_L = (i.lose*100)/i.played;
        }
        gtk_label_set_text(GTK_LABEL(GTK_WIDGET(gtk_builder_get_object(builder,"partite_giocate"))),g_strdup_printf("%d",i.played));
        gtk_label_set_text(GTK_LABEL(GTK_WIDGET(gtk_builder_get_object(builder,"vinte"))),g_strdup_printf("%d",i.win));
        gtk_label_set_text(GTK_LABEL(GTK_WIDGET(gtk_builder_get_object(builder,"percent_vinte"))),g_strdup_printf("(%d%)",percent_V));
        gtk_label_set_text(GTK_LABEL(GTK_WIDGET(gtk_builder_get_object(builder,"perse"))),g_strdup_printf("%d",i.lose));
        gtk_label_set_text(GTK_LABEL(GTK_WIDGET(gtk_builder_get_object(builder,"percent_perse"))),g_strdup_printf("(%d%)",percent_L));

        D2("Stampa delle statistiche.");
    }
    sstampa = false;
}

/** Funzione di azzeramento statistiche
 *
 * Elimina il file delle statistiche e ristampa la pagina delle statistiche.
 *
 * @param builder Il builder GTK. 
*/
void eliminaStatistiche(GtkBuilder *builder){
    D2("Rimozione file (se presente): statistiche.txt");

    remove(STATISTICHE);
    i.played = i.win = i.lose = 0; 
    sstampa = true;
    stampaStatistiche(builder);
}










