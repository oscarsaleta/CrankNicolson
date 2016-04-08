#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
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
    assert(gr->u != NULL);
    /* Assignar condició inicial a la graella */
    for (i=0; i<nx+1; i++) {
        for (j=0; j<ny+1; j++) {
            gr->u[j*(nx+1)+i] = h(i*dx,j*dy);
        }
    }
}

#define Uaux(i,j) uaux[(j)*(nx+1)+(i)]
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
    for (i=0; i<nx+1; i++)
        for (j=0; j<ny+1; j++)
            Uaux(i,j) = gr->u[j*(nx+1)+i];

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
    /* Fw-time ct-space scheme */
    for (i=1; i<nx; i++) {
        for (j=1; j<ny; j++) {
            gr->u[j*(nx+1)+i] = (1-2*mux-2*muy)*Uaux(i,j) +
                mux*(Uaux(i+1,j)+Uaux(i-1,j)) +
                muy*(Uaux(i,j+1)+Uaux(i,j-1)) +
                dt*f(t,i*dx,j*dy);
        }
    }

    /* Incrementem el temps */
    gr->t = t+dt;
    /* Alliberem memòria */
    free(uaux);
}
#undef Uaux

void grRFD_escriure (grRFD *gr, FILE *fp) {
    int i,j;

    fprintf(fp,"# t %10.6G\n",gr->t);

    for (j=0; j<gr->ny+1; j++) {
        for (i=0; i<gr->nx+1; i++) {
            fprintf(fp,"%10.6G %10.6G %10.6G\n",i*gr->dx,j*gr->dy,gr->u[j*(gr->nx+1)+i]);
        }
        fprintf(fp,"\n");
    }
    fprintf(fp,"\n");
}

void grRFD_allib (grRFD *gr) {
    free(gr->u);
}

#define U(i,j) u[(j)*(nx+1)+(i)]
int grRFD_pasCalCN (grRFD *gr, double w, double tol, int maxit,
        double (*f)(double t, double x, double y),
        double (*g)(double t, double x, double y)) {
    int i,j,k;
    double sum,aux;
    /* Paràmetres de l'estructura */
    double dx = gr->dx;
    double dy = gr->dy;
    double mux = gr->mux;
    double muy = gr->muy;
    int nx = gr->nx;
    int ny = gr->ny;
    double t = gr->t;
    double dt = gr->dt;
    /* Solució de l'instant anterior */
    double *u = malloc((nx+1)*(ny+1)*sizeof(double));

    /* Copia del temps anterior */
    for (i=0; i<nx+1; i++) {
        for (j=0; j<ny+1; j++) {
            U(i,j) = gr->U(i,j);
        }
    }
    /* Omplim les fronteres */
    for (i=0; i<nx+1; i++) {
        gr->U(i,0) = g(t+dt,i*dx,0);
        gr->U(i,ny) = g(t+dt,i*dx,ny*dy);
    }
    for (j=0; j<ny+1; j++) {
        gr->U(0,j) = g(t+dt,0,j*dy);
        gr->U(nx,j) = g(t+dt,nx*dx,j*dy);
    }

    /* Mètode SOR per CN */
    for (k=0; k<maxit; k++) {

        sum=0;
        /* Iteració SOR */
        for (j=1; j<ny; j++) {
            for (i=1; i<nx; i++) {
                aux=gr->U(i,j);
                gr->U(i,j) = (1-w)*gr->U(i,j)+
                    w/(1+mux+muy)*( (1-mux-muy)*U(i,j)+
                        mux/2*( gr->U(i+1,j) + gr->U(i-1,j) + U(i+1,j) + U(i-1,j) )+
                        muy/2*( gr->U(i,j+1) + gr->U(i,j-1) + U(i,j+1) + U(i,j-1) )+
                        dt/2*( f(t+dt,i*dx,j*dy) + f(t,i*dx,j*dy) ) );
                sum+=(gr->U(i,j)-aux)*(gr->U(i,j)-aux);
            }
        }

        /* Criteri de convergència */
        if (sum < tol*tol) {
            fprintf(stderr,"t=%8.5g, err=%8.5g, it=%d\n",t,sqrt(sum),k);
            /* Incrementar temps */
            gr->t = t+dt;
            /* Alliberar memòria */
            free(u);
            return 0;
        }

    }
    
    /* Si no convergeix en maxit passos */
    fprintf(stderr,"SOR:: max iterations reached.\n");
    gr->t = t+dt;
    /* Alliberar memòria */
    free(u);
    return 1;
}
#undef U
