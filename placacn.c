#include <stdio.h>
#include <math.h>
#include "grRFD.h"

#define CONST_C 0.11
#define CONST_RHO 7.8
#define CONST_K 0.13
/*!
 * \brief Funcio f del problema mixt per l'equaci\'o de la
 * calor.
 */
double f (double t, double x, double y) {
    if ( (x-0.5)*(x-0.5)+(y-0.5)*(y-0.5) < 0.04 )
        return 100./CONST_K;
    return 0;
}


/*!
 * \brief Funcio g del problema mixt per l'equaci\'o de la
 * calor
 */
double g (double t, double x, double y) {
    return 0;
}

/*!
 * \brief Funcio h del problema mixt per l'equaci\'o de la
 * calor
 */
double h (double x, double y) {
    return 0;
}

/*!\brief Implementa l'algorisme 1.1 per al punt 2 del gui\'o. */
int main (int argc, char *argv[]) {
    int k;
    double dx, dy, dt, T;
    int nx, ny, nt;
    /* Objecte graella */
    grRFD gr;
    /* Paràmetres SOR */
    double omega,tol;
    int maxit;

    /* Lectura de paràmetres ( en l'ordre de grRFD_init() )*/
    if (argc != 10
            || sscanf(argv[1],"%lf",&dx)!=1
            || sscanf(argv[2],"%lf",&dy)!=1
            || sscanf(argv[3],"%lf",&dt)!=1
            || sscanf(argv[4],"%d",&nx)!=1
            || sscanf(argv[5],"%d",&ny)!=1
            || sscanf(argv[6],"%lf",&T)!=1
            || sscanf(argv[7],"%lf",&omega)!=1
            || sscanf(argv[8],"%lf",&tol)!=1
            || sscanf(argv[9],"%d",&maxit)!=1) {
        fprintf(stderr,"%s dx dy dt nx ny T omega tol maxit\n",argv[0]);
        return -1;
    }

    /* Nombre de passes temporals a fer */
    nt = floor(T/dt);
    fprintf(stderr,"%d\n",nt);

    /* Inicialitzo graella (paràmetres i llesca t=0) */
    grRFD_init(&gr,dx,dy,dt,nx,ny,h);
    /* Escric graella inicial */
    grRFD_escriure(&gr,stdout);

    for (k=0; k<nt+1; k++) {
        if ( grRFD_pasCalCN(&gr,omega,tol,maxit,f,g) == 1) {
            fprintf(stderr,"%s:: error a la resolució amb SOR\n",argv[0]);
            return 1;
        }
        grRFD_escriure(&gr,stdout);
    }
    /* All done! */
    grRFD_allib(&gr);
    return 0;
}
