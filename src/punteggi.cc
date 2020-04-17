/**
 * @file punteggi.cc
 * @brief Racchiude tutte le funzioni di gestione dei punteggi.
*/

#include "debug.h"
#include <fstream>
#include <gtk/gtk.h>
#include <cstring>
#include <cstdio>
#include <iostream>
#include "struttura_dati.h"

using namespace std;

record r; /**< Struttura per il salvataggio dei migliori punteggi */
int punteggio; /**< Variabile intera che contiene il punteggio finale */
bool stampa = true; /**< Valore booleano che decide se è necessario o meno chiamare la funzione di stampa dei record nella pagina dei punteggi */

/** Funzione di stampa dei punteggi 
 *
 * Se la finestra dei punteggi non e' ancora stata decorata o se il file dei punteggi ha subito modifiche, quest'ultimo viene letto e i punteggi
 * stampati, tramite gli opportuni label, sulla rispettiva finestra.
 *
 * @param builder Il builder GTK.
*/
void stampaPunteggi(GtkBuilder *builder)
{
    if(stampa){
        D2("Apertura del file (se presente): punteggi.txt, in lettura.");

        ifstream f(PUNTEGGI);
        int dim,j=1,pnt;
        char nome[player_lenght],data[data_lenght];

        f>>dim;
    
        if(!f || dim == 0){
            D2("File non presente o vuoto.");
            gtk_label_set_text(GTK_LABEL(GTK_WIDGET(gtk_builder_get_object(builder,"l_pos"))),"Non ci sono ancora vincitori. Sarai tu il primo?");
        }
        else{
            gtk_label_set_text(GTK_LABEL(GTK_WIDGET(gtk_builder_get_object(builder,"l_pos"))),"");
            gtk_label_set_text(GTK_LABEL(GTK_WIDGET(gtk_builder_get_object(builder,"l_nome"))),"NOME");
            gtk_label_set_text(GTK_LABEL(GTK_WIDGET(gtk_builder_get_object(builder,"l_punti"))),"PUNTI");
            gtk_label_set_text(GTK_LABEL(GTK_WIDGET(gtk_builder_get_object(builder,"l_data"))),"DATA");
            for(int i=0;i<dim;i++){
                f>>pnt; f>>nome; f>>data;
                gtk_label_set_text(GTK_LABEL(GTK_WIDGET(gtk_builder_get_object(builder,g_strdup_printf("l_%d", j)))),g_strdup_printf("%d", j));
                gtk_label_set_text(GTK_LABEL(GTK_WIDGET(gtk_builder_get_object(builder,g_strdup_printf("ln_%d", j)))),nome);
                gtk_label_set_text(GTK_LABEL(GTK_WIDGET(gtk_builder_get_object(builder,g_strdup_printf("lp_%d", j)))),g_strdup_printf("%d", pnt));
                gtk_label_set_text(GTK_LABEL(GTK_WIDGET(gtk_builder_get_object(builder,g_strdup_printf("ld_%d", j)))),data);
                j++;
            }
        }
        stampa = false;    
    }
}

/** Funzione di lettura record da file
 *
 * Apre il lettura il file dei punteggi e trova il numero di record presenti. Poi riempie i tre array contenenti punteggi e nomi dei vincitori e 
 * data, inserendo nel posto giusto quello attuale ("senzanome" se non e' presente) e, eventualmente, scartando l'ultimo dei precedenti (se 
 * questi erano 10).
 * Ritorna il nuovo numero di vincitori.
 * 
 * @param r Struttura di controllo dei record
 * @param nome Nome del vincitore attuale
 * @return Il nuovo numero dei vincitori
*/
void leggiRecord(record &r,char nome[])
{
    int dim = 0,dim_i,p;
    char n[player_lenght],data[data_lenght];
    bool leggi = true, rec = true;

    time_t ttime = time(NULL);
    struct tm *t = localtime(&ttime);
    int day = t->tm_mday;
    int month = (t->tm_mon)+1;
    int min = t->tm_min;
    int hour = t->tm_hour;

    D2("Calcolo data.");

    if(strcmp(nome,"")==0){
        D2("Nome non presente: stringa di default 'senzanome'.");
        strcpy(nome,"J Doe");
    }

    D2("Apertura del file (se presente): punteggi.txt, in lettura.");
    ifstream f(PUNTEGGI);
    if(!f){
        D2("File non presente.");
        dim_i = 1;
        r.punti[0] = punteggio;
        strcpy(r.nomi[0],nome); 
        if(min<10) strcpy(r.data[0],g_strdup_printf("%d/%d-%d:0%d", day,month,hour,min));
        else strcpy(r.data[0],g_strdup_printf("%d/%d-%d:%d", day,month,hour,min));
    }
    else{
        D2("File presente.");
        f>>dim_i;
        if(dim_i < 10) dim_i++;
        
        for(int i=0;i<dim_i;i++){
            if(leggi){
                f>>p;
                f>>n;
                f>>data;
            }
            if((!leggi || p < punteggio) && rec){
                r.punti[i] = punteggio;
                strcpy(r.nomi[i],nome);
                if(min<10) strcpy(r.data[i],g_strdup_printf("%d/%d-%d:0%d", day,month,hour,min));
                else strcpy(r.data[i],g_strdup_printf("%d/%d-%d:%d", day,month,hour,min));
                rec = false;
                i++;
                if(i < dim_i){
                    r.punti[i] = p;
                    strcpy(r.nomi[i],n);
                    strcpy(r.data[i],data);
                }
            }
            else{
                r.punti[i] = p;
                strcpy(r.nomi[i],n);
                strcpy(r.data[i],data);
                dim++;
                if(dim == dim_i-1) leggi = false;        
            }
        }
    }
    r.dim = dim_i;
}

/** Funzione di scrittura record su file
 *
 * Scrive i record, contenuti negli array in ingresso, sul file dei punteggi utilizzando la corretta formattazione.
 *
 * @param r Struttura di controllo dei record
*/
void scriviRecord(record r)
{
    D2("Apertura (o creazione) del file: punteggi.txt, in scrittura.");
    ofstream f(PUNTEGGI);
    
    f<<r.dim<<endl;
    for(int i=0;i<r.dim;i++) f<<r.punti[i]<<" "<<r.nomi[i]<<" "<<r.data[i]<<endl;
}

/** Funzione di inserimento del punteggio
 *
 * Trova la posizione corretta nel file e vi inserisce il nuovo record e il nome del giocatore. Se il file conteneva dieci record, elimina 
 * l'ultimo.
 * Setta poi il flag ::stampa per ridecorare la finestra dei punteggi.
 * 
 * @param nome Il nome del giocatore.
*/
void inserimentoPunteggio(char nome[player_lenght])
{
    D2("Funzione: leggiRecord.");
    leggiRecord(r,nome);
    D2("Funzione: scriviRecord.");
    scriviRecord(r);
    
    stampa = true;
};

/** Funzione di controllo record
 *
 * Controlla se il punteggio totalizzato e' entrato in classifica e ritorna 'true', altrimenti 'false'.
 * Il punteggio si considera in classifica se:
 * - il file dei punteggi non e' ancora stato creato;
 * - il file dei punteggi contiene meno di dieci record;
 * - il file contiene 10 record, ma il punteggio minore e' minore anche del punteggio del giocatore.
 *
 * @param p Il punteggio finale totalizzato dal giocatore.
 * @return 'true' se il punteggio e' entrato in classifica, altrimenti 'false'.
*/
bool cercaRecord(int p)
{
    punteggio = p;
    D2("Apertura del file (se presente): punteggi.txt, in lettura.");
    ifstream f(PUNTEGGI);
    int dim,i;

    f>>dim;
    if(!f || dim < 10) return true;
    else{
        for(int j=0;j<28;j++){
            f>>i;
            if((j==0 || j%3 == 0) && (i < p)) return true; 
        }
    }
    
    return false;
}

/** Funzione di pulizia della Hall of Fame
 *
 * Quando vengono azzerati i punteggi rimuove tutti quelli stampati nella finestra dei punteggi. 
*/
void pulisciHof(GtkBuilder *builder){
    gtk_label_set_text(GTK_LABEL(GTK_WIDGET(gtk_builder_get_object(builder,"l_pos"))),"");
    gtk_label_set_text(GTK_LABEL(GTK_WIDGET(gtk_builder_get_object(builder,"l_nome"))),"");
    gtk_label_set_text(GTK_LABEL(GTK_WIDGET(gtk_builder_get_object(builder,"l_punti"))),"");
    gtk_label_set_text(GTK_LABEL(GTK_WIDGET(gtk_builder_get_object(builder,"l_data"))),"");
    
    for(int i=1;i<=10;i++){
        gtk_label_set_text(GTK_LABEL(GTK_WIDGET(gtk_builder_get_object(builder,g_strdup_printf("l_%d",i)))),"");
        gtk_label_set_text(GTK_LABEL(GTK_WIDGET(gtk_builder_get_object(builder,g_strdup_printf("ln_%d",i)))),"");
        gtk_label_set_text(GTK_LABEL(GTK_WIDGET(gtk_builder_get_object(builder,g_strdup_printf("lp_%d",i)))),"");
        gtk_label_set_text(GTK_LABEL(GTK_WIDGET(gtk_builder_get_object(builder,g_strdup_printf("ld_%d",i)))),"");
    }

    stampa = true;   
}

/** Funzione di azzeramento record
 *
 * Elimina il file dei punteggi e setta la variabile di controllo della stampa. 
 *
 * @param builder Il builter GTK.
*/
void eliminaPunteggi(GtkBuilder *builder){
    D2("Rimozione file (se presente): punteggi.txt");
    remove(PUNTEGGI);
    D2("Funzione: pulisciHof.");
    pulisciHof(builder);
}
