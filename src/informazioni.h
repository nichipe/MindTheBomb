/**
 * @file informazioni.h
 * @brief Racchiude tutti i prototipi delle funzioni di creazione delle statistiche.
*/

#include <gtk/gtk.h>

void catturaInformazioni();
void nuovaSconfitta();
void nuovaVittoria();
void stampaStatistiche(GtkBuilder *);
void eliminaStatistiche(GtkBuilder *);
