# Optimització
#OPT=-g -Wall
OPT=-O3 -Wall

# Tot:
all : apartat2 polexpl placaexp placacn

# Utilitats:
# - Polinomi explícit
apartat2 : apartat2.c grRFD.o grRFD.h
	gcc -o apartat2 $(OPT) apartat2.c grRFD.o -lm
polexpl : polexpl.c grRFD.o grRFD.h
	gcc -o polexpl $(OPT) polexpl.c grRFD.o -lm
# - Placa explícita
placaexp : placaexp.c grRFD.o grRFD.h
	gcc -o placaexp $(OPT) placaexp.c grRFD.o -lm
# - Placa Crank-Nicolson
placacn : placacn.c grRFD.o grRFD.h
	gcc -o placacn $(OPT) placacn.c grRFD.o -lm

# Biblioteca
grRFD.o : grRFD.c 
	gcc -c $(OPT) grRFD.c

# Neteja
clean :
	rm -f *.o
realclean : clean
	rm -f polexpl placaexp placacn
