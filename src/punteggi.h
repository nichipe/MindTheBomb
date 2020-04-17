/**
 * @file punteggi.h
 * @brief Racchiude tutti i prototipi delle funzioni per scrivere/leggere i migliori punteggi su/da file e per decorare l'apposita finestra.
*/

#include <gtk/gtk.h>

bool cercaRecord(int);
void inserimentoPunteggio(char *);
void stampaPunteggi(GtkBuilder *);
void eliminaPunteggi(GtkBuilder *);

