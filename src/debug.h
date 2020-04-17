/**
 * @file debug.h
 * @brief Contiene le direttive al preprocessore utilizzate per realizzare il tracing per il debugging.
*/

#ifdef DEBUG_MODE
#define DBG(A,B) { if((A)&DEBUG_MODE){ cout<<B<<endl; } } //Tracing di livello generico */
#define DS(A) { if(8&DEBUG_MODE){ A; } } //Livello di tracing speciale: mostra la soluzione del gioco */
#else
#define DBG(A,B) /**<Tracing disattivato (livello generico) */
#define DS(A) /**<Tracing disattivato (livello speciale) */
#endif
#define D1(a) DBG(1,a) /**<Livello di tracing 1: azioni compiute dall'utente */
#define D2(a) DBG(2,a) /**<Livello di tracing 2: azioni compiute dal programma */
#define D3(a) DBG(4,a) /**<Livello di tracing 3: azioni compiute ripetutamente (es: cicli) */
