#include <stdio.h>
#include <math.h>
#include "grRFD.h"

/* Imposo el polinomi t+2xy+x^2+y^2 */

/*!
 * \brief Funcio f del problema mixt per l'equaci\'o de la
 * calor, imposant que la soluci\'o sigui un polinomi.
 */
double f_pol (double t, double x, double y) {
    return -3;
}


/*!
 * \brief Funcio g del problema mixt per l'equaci\'o de la
 * calor, imposant que la soluci\'o sigui un polinomi.
 */
double g_pol (double t, double x, double y) {
    return t+2*x*y+x*x+y*y;
}

/*!
 * \brief Funcio h del problema mixt per l'equaci\'o de la
 * calor, imposant que la soluci\'o sigui un polinomi.
 */
double h_pol (double x, double y) {
    return 2*x*y+x*x+y*y;
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

    /* Inicialitzo graella (paràmetres i llesca t=0) */
    grRFD_init(&gr,dx,dy,dt,nx,ny,h_pol);
    /* Escric graella inicial */
    grRFD_escriure(&gr,stdout);
    /*
     * Bucle en temps:
     * A cada pas crida grRFD_pasCalExpl(&gr,f_pol,g_pol)
     * i escriu graella mitjan\c{c}ant crida a grRFD_escriure(&gr,stdout)
     */
    for (k=0; k<nt+1; k++) {
        grRFD_pasCalCN(&gr,omega,tol,maxit,f_pol,g_pol);
        grRFD_escriure(&gr,stdout);
    }
    /* All done! */
    grRFD_allib(&gr);
    return 0;
}
