OBJ = main.o handlers.h gestione_gioco.o manutenzione.o punteggi.o informazioni.o
OBJ_DEBUG = main.cc gestione_gioco.cc manutenzione.cc punteggi.cc informazioni.cc 
CXXFLAGS=$(DEBUG_FLAGS) -Wall `pkg-config --cflags gtk+-3.0`
LDFLAGS=-export-dynamic `pkg-config --cflags --libs gtk+-3.0` 

MTB: $(OBJ)
	g++ -o Mind_the_Bomb $(OBJ) $(LDFLAGS)

-include dependencies

.PHONY: depend clean debug

depend:
	g++ -MM *.cc > dependencies
clean:
	rm -f *.o
debug:
	g++ $(OBJ_DEBUG) -o debug -g -DDEBUG_MODE=$(M) $(LDFLAGS)
