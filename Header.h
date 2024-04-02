#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ARCH_POSA 1
#define ARCH_POSB 2
#define ARCH_POSM 3

#define TAM 256

#define TAMPAT 9
#define TAMFIL 5

#define ERR_MEM 0
#define TODO_OK 1

typedef struct
{
    char mat[20];
    double lat;
    double pos;
    double kilometros;

}Emb_y_km;

typedef struct{
    long int FyH;
    char mat[20];
    double lat;
    double pos;
}
Embarcacion;

typedef int (*Cmp)(const void*,const void*);

//Aca parseamos el archivo, cualquier cosa preguntame. Pasamos de texto a binario para trabajar en memoria.

int generarArchivoMaster(const char* rutaMaster,const char* rutaA,const char* rutaB ,Cmp cmp);
void mostrarVector(Emb_y_km *v,int ce);
int cargarMatriz(char mat[][TAMPAT],char* cad, Emb_y_km* vec, int ce);
void mostrarMatriz(char mat[][TAMPAT], int ce);

//Funciones de strings

int parseo(char* linea, Embarcacion *emb);
int strcmpMe(const char *s1, const char *s2);
char* strcpyMe(char *s1, const char* s2);

//Cargar y Calcular kms recorridos.

void cargarTopEmbarcaciones(char mat[][TAMPAT],Emb_y_km *vec,int ce,size_t tamElem);
int calcularKmRecorridos(const char* rutaArchM, Emb_y_km* vec, int ce);
void agregarEmbarcacion(Emb_y_km* vec, Embarcacion* emb, int ce);

//Funcion de vector generico.

Emb_y_km* buscarEnVec(Emb_y_km* vec, int ce, char* pat);
void ordenarSeleccionGenerico(void* vec,int ce,size_t tam,Cmp cmp);
int intercambiar(void * elem1,void*elem2, size_t tam);
void* buscarMayor(void*act,void* ult, size_t tamElem,Cmp cmp);

//Funciones para acumular Kms

void sumarKms(Emb_y_km* embASumar,Embarcacion* emb);
double calcularDist(double latitud1, double long1, double latitud2, double long2);
double paseARadianes(double nro);

//Comparacion generica

int cmpKms(const void* elem1,const void* elem2);
int cmpFyH(const void* elem1, const void* elem2);

#endif // HEADER_H_INCLUDED
