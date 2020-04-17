/**
 * @file struttura_dati.h
 * @brief Racchiude tutte le variabili, le costanti e le strutture per il funzionamento del programma.
*/

#ifndef STRUTTURA_DATI
#define STRUTTURA_DATI

const int player_lenght = 20, /**< Dimensione massima del nome utente inserito. */
          data_lenght = 12; /**< Lunghezza dell'array contenente la data */
const char PUNTEGGI[] = "punteggi.txt", /**< File contenente i migliori punteggi. */
           STATISTICHE[] = "statistiche.txt"; /**< File contenente le statisctiche di gioco. */

/** Descrittore dei record
 *
 * Rappresenta i record contenuti nel file dei punteggi
*/
struct record{
    char nomi[10][player_lenght], /**< Nomi dei vincitori */
         data[10][data_lenght]; /**< Data in cui e' stato registrato il record */
    int punti[10], /**< Punti del vincitore */
        dim; /**< Numero di record presenti */
};

/** Descrittore della cella
 *
 * Rappresenta la singola cella dell'arena di gioco.
*/
struct cell{
    bool bomb, /**< 'true' se la cella contiene una bomba. */
         flag, /**< 'true' se la cella e' stat segnalata con un flag dall'utente. */
         visited; /**< 'true' se la cella e' stata "visitata" dalla funzione di controllo. */
};

/** Descrittore del giocatore
 *
 * Rappresenta l'utente che gioca la partita.
*/
struct player{
    int pnt, /**< Punteggio accumulato dal giocatore. */ 
        bombs; /**< Bombe (probabilmente) trovate dal giocatore, segnalate con flag. */
    char name[player_lenght]; /**< Nome del giocatore */
    cell c[15][20]; /**< Matrice che rappresenta l'arena di gioco */
};

/** Descrittore delle informazioni di gioco
 *
 * Rappresenta le informazioni sulle statistiche di gioco.
*/
struct info{
    int played, /**< Numero di partite giocate. */
        win, /**< Numero di partite vinte */
        lose; /**< Numero di partite perse */
};

#endif
