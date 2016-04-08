# Optimització
OPT=-g -Wall
#OPT=-O3 -Wall

# Tot:
all : polexpl placaexp polcn placacn

# Utilitats:
# - Polinomi explícit
polexpl : polexpl.c grRFD.o grRFD.h
	gcc -o polexpl $(OPT) polexpl.c grRFD.o -lm
# - Placa explícita
placaexp : placaexp.c grRFD.o grRFD.h
	gcc -o placaexp $(OPT) placaexp.c grRFD.o -lm
# - Polinomi Crank-Nicolson
polcn : polcn.c grRFD.o grRFD.h
	gcc -o polcn $(OPT) polcn.c grRFD.o -lm
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
	rm -f polexpl placaexp polcn placacn
