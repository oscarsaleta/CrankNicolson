#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "grRFD.h"

void grRFD_init (grRFD *gr, double dx, double dy, double dt,
      int nx, int ny, double (*h)(double x, double y)) {
    int i,j;
    /* Assignar paràmetres de l'estructura */
    gr->dx = dx;
    gr->dy = dy;
    gr->dt = dt;
    gr->t = 0.0;
    gr->nx = nx;
    gr->ny = ny;
    gr->mux = dt/(dx*dx);
    gr->muy = dt/(dy*dy);
    /* Assignar memòria per la graella */
    gr->u = malloc((nx+1)*(ny+1)*sizeof(double));
    /* Assignar condició inicial a la graella */
    for (i=0; i<nx+1; i++) {
        for (j=0; j<ny+1; j++) {
            gr->u[j*(nx+1)+i] = h(i*dx,j*dy);
        }
    }
}

void grRFD_pasCalExpl (grRFD *gr,
      double (*f)(double t, double x, double y),
      double (*g)(double t, double x, double y)) {
    int i,j;
    /* Paràmetres de l'estructura */
    double dx = gr->dx;
    double dy = gr->dy;
    double mux = gr->mux;
    double muy = gr->muy;
    int nx = gr->nx;
    int ny = gr->ny;
    double t = gr->t;
    double dt = gr->dt;
    /* Graella auxiliar de l'instant anterior */
    double *uaux = malloc((nx+1)*(ny+1)*sizeof(double));

    /* Copia del temps anterior */
    for (i=0; i<nx+1; i++) {
        for (j=0; j<ny+1; j++) {
            uaux[j*(nx+1)+i] = gr->u[j*(nx+1)+i];
        }
    }

    /* Omplim les fronteres */
    for (i=0; i<nx+1; i++) {
        gr->u[i] = g(t+dt,i*dx,0);
        gr->u[ny*(nx+1)+i] = g(t+dt,i*dx,ny*dy);
    }
    for (j=0; j<ny+1; j++) {
        gr->u[j*(nx+1)] = g(t+dt,0,j*dy);
        gr->u[j*(nx+1)+nx] = g(t+dt,nx*dx,j*dy);
    }

    /* Algorisme 1.1 */
    for (i=1; i<nx; i++) {
        for (j=1; j<ny; j++) {
            gr->u[j*(nx+1)+i] = (1-2*mux-2*muy)*uaux[j*(nx+1)+i] +
                mux*(uaux[j*(nx+1)+(i+1)]+uaux[j*(nx+1)+(i-1)]) +
                muy*(uaux[(j+1)*(nx+1)+i]+uaux[(j-1)*(nx+1)+i]) +
                dt*f(t,i*dx,j*dy);
        }
    }

    /* Incrementem el temps */
    gr->t = t+dt;

    free(uaux);
}

void grRFD_escriure (grRFD *gr, FILE *fp) {
    int i,j;

    fprintf(fp,"# t %10.6G\n",gr->t);

    for (i=0; i < gr->nx+1; i++) {
        for (j=0; j < gr->ny+1; j++) {
            fprintf(fp,"%10.6G  %10.6G %10.6G\n",i*gr->dx,j*gr->dy,gr->u[j*(gr->nx+1)+i]);
        }
        fprintf(fp,"\n");
    }
    fprintf(fp,"\n");
}

void grRFD_allib (grRFD *gr) {
    free(gr->u);
}
   
