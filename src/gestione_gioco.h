/**
 * @file gestione_gioco.h
 * @brief Racchiude tutti i prototipi delle funzioni per la gestione e lo svolgimento del gioco.
*/

#include <gtk/gtk.h>

void gioco(GtkBuilder *);
bool controlloPunteggio(GtkBuilder *builder);
bool controlloVittoria(GtkBuilder *);
bool gestioneCella(GtkButton *,GtkBuilder *);
void tastoDestro(GtkButton *,GtkBuilder *);
