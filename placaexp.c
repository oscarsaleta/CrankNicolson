#include <stdio.h>
#include <math.h>
#include "grRFD.h"

/*!
 * \brief Funcio f del problema mixt per l'equaci\'o de la
 * calor, imposant que la soluci\'o sigui un polinomi.
 */
double f_pol (double t, double x, double y) {
    if ( (x-0.5)*(x-0.5)+(y-0.5)*(y-0.5) < 0.04 )
        return 100./0.13;
    return 0;
}


/*!
 * \brief Funcio g del problema mixt per l'equaci\'o de la
 * calor, imposant que la soluci\'o sigui un polinomi.
 */
double g_pol (double t, double x, double y) {
    return 0;
}

/*!
 * \brief Funcio h del problema mixt per l'equaci\'o de la
 * calor, imposant que la soluci\'o sigui un polinomi.
 */
double h_pol (double x, double y) {
    return 0;
}

/*!\brief Implementa l'algorisme 1.1 per al punt 2 del gui\'o. */
int main (int argc, char *argv[]) {
    int k;
    double dx, dy, dt, T;
    int nx, ny, nt;
    /* Objecte graella */
    grRFD gr;

    /* Lectura de paràmetres ( en l'ordre de grRFD_init() )*/
    if (argc != 7
            || sscanf(argv[1],"%lf",&dx)!=1
            || sscanf(argv[2],"%lf",&dy)!=1
            || sscanf(argv[3],"%lf",&dt)!=1
            || sscanf(argv[4],"%d",&nx)!=1
            || sscanf(argv[5],"%d",&ny)!=1
            || sscanf(argv[6],"%lf",&T)!=1) {
        fprintf(stderr,"%s dx dy dt nx ny T\n",argv[0]);
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
    for (k=0; k<nt; k++) {
        grRFD_pasCalExpl(&gr,f_pol,g_pol);
        grRFD_escriure(&gr,stdout);
    }
    /* All done! */
    grRFD_allib(&gr);
    return 0;
}
