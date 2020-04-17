/**
 * @file manutenzione.h
 * @brief Racchiude tutti i prototipi delle funzioni di servizio.
*/

#include <gtk/gtk.h>
#include "struttura_dati.h"

void trovaPosizione(int&,int&,GtkButton *);
void calcolaPunteggio(GtkBuilder *r,int,player&);
void cambiaTema(GtkBuilder *,int);
