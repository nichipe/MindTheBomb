MIND THE BOMB! 


Progetto per l'esame del corso di Programmazione II. 

Nicolò Bortolamasi, matricola 108153.



Il progetto e' una versione del popolare videogioco "prato fiorito".

Per maggiori informazioni circa il funzionamento e la struttura del gioco si rimanda alla documentazione nella cartella "doc/html", 
in particolare alla pagina "index.html".


Nella cartella "media" si trovano tutte le immagini e le icone (.jpg e .png) utilizzate all'interno del gioco e il progetto Glade 
con cui sono state progettate tutte le finestre, denominato "GUI.glade".


Nella cartella "src" si trovano tutti i file sorgente, gli header file, il makefile("Makefile"), il file di configurazione di Doxygen("Doxyfile") 
utilizzato per creare la documentazione e il file delle dipendenze("dependencies").

Per compilare il progetto e' necessario utilizzare 
il comando 'make'.

E' possibile creare le dipendenze con il target 'depend' e cancellare i file oggetto con il target 'clean'.

Tramite il target 'debug' si può compilare un eseguibile idoneo al debugging, in cui e' stato implementato un sistema di tracing 
su 3(+1) livelli:

1) Azioni eseguite direttamente dall'utente sull'interfaccia di gioco (maschera=1),

2) Azioni eseguite internamente dal programma (maschera=2),

3) Azioni ripetute più volte all'interno dei cicli (maschera=4).

S) Questo livello, se attivato, mostra la posizione esatta delle bombe nell'arena (maschera=8).

Per compilare il file "debug" e' 
necessario passare la maschera da linea di comando con la seguente sintassi: 'make debug M=<maschera>' (dove <maschera> è la somma 
delle maschere dei livelli che si vuole attivare).



Nella cartella dei sorgenti e' inoltre presente un eseguibile statico del progetto 
("Mind_the_bomb") e un eseguibile per il debugging ("debug") compilato attivando i primi 3 livelli di tracing.
