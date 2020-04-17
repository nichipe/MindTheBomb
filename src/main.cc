/** @mainpage Mind the Bomb!
 *
 * Il progetto "Mind the Bomb!" rappresenta una versione del popolare videogioco "prato fiorito".
 * 
 * E' presente un'arena (in questo caso di dimensioni 20x15) disseminata di "bombe" in numero e posizioni casuali.
 *
 * L'obiettivo del giocatore e' sbloccare tutte le celle, senza urtare nessuna bomba. 
 * 
 * Per farlo potra' avvalersi di due aiuti fondamentali:
 *
 * 1. flags --> l'utente, tramite click del tasto destro, puo' "segnalare" una casella; questo segnala una possibile bomba e impedisce di
 * cliccarla, evitando errori di distrazione, fino a che il flag non viene rimosso (tramite un altro click del tasto destro);
 * 2. indizi numerici --> quando l'utente fa click su una casella vuota al suo interno compare il numero di bombe presenti nelle caselle 
 * confinanti.
 *
 * Se il giocatore riesce a segnalare tutte le bombe o a trovare tutte le caselle senza, la partita e' vinta. Se invece urta una bomba, ha 
 * perso.
 *
 * Nella schermata principale del gioco e' possibile anche visualizzare una schermata di aiuto che riassume le regole e il procedimento di gioco
 * e una schermata dove sono raccolti i migliori dieci punteggi totalizzati. Il punteggio e' calcolato ad ogni click, sulla base di quante
 * caselle vuote vengono trovate, corredato di bonus/malus finale in base a quante caselle sono state marchiate giustamente/erratamente.
 *
 * E' inoltre presente una sezione di informazioni dove e' possibile leggere statistiche su partite giocate, vinte e perse; sia queste statistiche
 * che quelle relative ai migliori record possono essere azzerate in questa sezione del menu.
 * Si da inoltre la possibilita' al giocatore di scegliere tra 4 diversi temi: "Greek"(default), "Far West", "Jungle" e "Fire".
 *
 * L'interfaccia grafica e' stata progettata utilizzando la libreria GTK e il software Glade.
 * 
 * @author Nicolò Bortolamasi, matricola 108153
*/

/**
 * @file main.cc
 * @brief File principale, contiene la funzione main del programma.
*/

#include "debug.h"
#include <iostream>
#include <gtk/gtk.h>
#include "struttura_dati.h"
#include "handlers.h"
#include "manutenzione.h"
#include "informazioni.h"

using namespace std;

GtkBuilder *builder; /**< Builder GTK utilizzato per connettere il codice C++ con l'interfaccia grafica */

/** Funzione main del programma
 * 
 * Gestisce l'interazione del programma con l'interfaccia grafica e la gestione degli eventi.
*/
int main(int argc, char *argv[])
{
	/* Creazione di un nuovo oggetto GtkBuilder */
	gtk_init(&argc, &argv);
	builder = gtk_builder_new();
	
	/* Caricamento di un interfaccia creata con Glade */
	gtk_builder_add_from_file(builder, "../media/GUI.glade", NULL);
	
	/* Aggancio degli handler dell'interfaccia al codice C++ */
	gtk_builder_connect_signals(builder, NULL);

    /* Imposto il tema di default("Greek") e richiamo la funzione di caricamento delle statistiche*/
    cambiaTema(builder,1);
    D2("Tema di default impostato.");
    catturaInformazioni();
    D2("Statistiche aggiornate.");

	/* Inizio ciclo di gestione eventi */
	gtk_main(); 

	return 0;
}
