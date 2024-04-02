#include "Header.h"

//FUNCIONES PRINCIPALES PARA EL TP.

int generarArchivoMaster(const char* rutaMaster,const char* rutaA,const char* rutaB ,Cmp cmp){
    char lineaA[TAM];
    char lineaB[TAM];
    Embarcacion embA;
    Embarcacion embB;
    int res;

    FILE* posA = fopen(rutaA, "rt");
    if(!posA){
        printf("[ERROR] - No se pudo abrir el archivo");
    }
    FILE* posB = fopen(rutaB, "rt");
    if(!posB){
        fclose(posA);
        printf("[ERROR] - No se pudo abrir el archivo");
    }
    FILE* posM = fopen(rutaMaster,"wt");
    if(!posM){
        fclose(posA);
        fclose(posB);
        printf("[ERROR] - No se pudo abrir el archivo");
    }

     if(!posM)
    {
        return 0;
    }


    fgets(lineaA, TAM, posA);
    fgets(lineaB, TAM, posB);

    while(!feof(posA)&&!feof(posB))
    {
        parseo(lineaA,&embA);
        parseo(lineaB,&embB);

        res = cmp(&embA.FyH,&embB.FyH);
        if(res > 0)
        {
            fprintf(posM,"%ld,%s,%lf,%lf\n",embB.FyH,embB.mat,embB.lat,embB.pos);
            fgets(lineaB, TAM, posB);
        }else if(res < 0)
        {
            fprintf(posM,"%ld,%s,%lf,%lf\n",embA.FyH,embA.mat,embA.lat,embA.pos);
            fgets(lineaA, TAM, posA);
        }
        else if(res!=0)
        {
            fprintf(posM,"%ld,%s,%lf,%lf\n",embB.FyH,embB.mat,embB.lat,embB.pos);
            fgets(lineaB, TAM, posB);

            fprintf(posM,"%ld,%s,%lf,%lf\n",embA.FyH,embA.mat,embA.lat,embA.pos);
            fgets(lineaA, TAM, posA);

        }else
        {
            fprintf(posM,"%ld,%s,%lf,%lf\n",embA.FyH,embA.mat,embA.lat,embA.pos);
            fgets(lineaA, TAM, posA);
            fgets(lineaB, TAM, posB);
        }
    }

    while(!feof(posA))
    {
        parseo(lineaA,&embA);
        fprintf(posM,"%ld,%s,%lf,%lf\n",embA.FyH,embA.mat,embA.lat,embA.pos);
        fgets(lineaA, TAM, posA);
    }

    while(!feof(posB))
    {
        parseo(lineaB,&embB);
        fprintf(posM,"%ld,%s,%lf,%lf\n",embB.FyH,embB.mat,embB.lat,embB.pos);
        fgets(lineaB, TAM, posB);
    }

    fclose(posA);
    fclose(posB);
    fclose(posM);

    return TODO_OK;
}

void mostrarVector(Emb_y_km *v,int ce)
{
    int i;
    Emb_y_km *p = v;

    printf("\t\t\t-----LISTADO DE EMBARCACIONES Y SUS RECORRIDOS------\n\n");

    for(i=0;i<ce;i++)
    {

        printf("Embarcacion: %s   latitud final: %lf   longitud final: %lf    Kilometros recorridos: %.3lfKms\n",p->mat,p->lat,p->pos,p->kilometros);
        printf("\n\n");
        p++;
    }

}

int cargarMatriz(char mat[][TAMPAT], char* cad, Emb_y_km* vec, int ce){

    int i, elemMat, j;
    char* str;

    Emb_y_km* ini = vec;

    // cant elem del vector no se pasara del top 5 (No mostrara mas valores que 5)
    if(ce <= 5){
        elemMat = ce;
    }
    else{
        elemMat = 5;
    }

    for(i = 0; i < elemMat; i++){
        str = cad;
        strcpyMe(str, ini->mat);
        for(j = 0; j < TAMPAT; j++){
            mat[i][j] = *str;
            str++;
        }
        ini++;
    }

    return elemMat;
}

void mostrarMatriz(char mat[][TAMPAT], int ce){
    int i, j;

    printf("\t\t\t-----TOP 5 PATENTES CON MAS KILOMETROS RECORRIDOS------\n\n");


    for(i = 0; i < ce; i++){
            printf("\nPuesto numero %d\nEmbacacion:", i+1);
        for(j = 0; j < TAMPAT; j++){
            printf("%c", mat[i][j]);
        }
    }
    printf("\n\n\t*****Contemplando que haya menos de 5 embarcaciones solo imprimira las existentes.*****\n");
    printf("\nAtentamente el duenio del programa :)\n");
}

//*************************************************//

Emb_y_km* buscarEnVec(Emb_y_km* vec, int ce, char* pat){
    int i;
    int cmp = -1;

    Emb_y_km* ini = vec;

    for(i = 0; i < ce; i++){
        cmp = strcmpMe(ini->mat, pat);
        if(cmp == 0){
            return ini;
        }
        ini++;
    }

    return NULL;

}

void* buscarMayor(void*act,void* ult, size_t tamElem,Cmp cmp)
{
    void* i;
    void* mayor=act;

    for(i=act+tamElem;i<=ult;i+=tamElem)
    {
        if(cmp(i,mayor)>0)
        {
            mayor=i;
        }
    }

    return mayor;

}

int intercambiar(void * elem1,void*elem2, size_t tam)
{
    void* aux=malloc(tam);

    if(!aux)
    {
        return ERR_MEM;
    }

    memcpy(aux,elem1,tam);
    memcpy(elem1,elem2,tam);
    memcpy(elem2,aux,tam);

    return TODO_OK;
}

void ordenarSeleccionGenerico(void* vec,int ce,size_t tam,Cmp cmp)
{
    void* ult=vec+(ce-1)*tam;
    void* pri=vec;
    void* i;
    void* mayor;

    for(i=pri;i<ult;i+=tam)
    {
        mayor=buscarMayor(i,ult,tam,cmp);
        if(cmp(i,mayor)!=0)
        {
            intercambiar(i,mayor,tam);
        }

    }
}

//*************************************************//

int calcularKmRecorridos(const char* rutaArchM, Emb_y_km* vec, int ce){
    FILE* archM = fopen(rutaArchM, "rt");
    if(!archM){
        printf("Error abriendo archivo\n");
        return 0;
    }
    char linea[TAM];
    Embarcacion emb;
    Emb_y_km* aux;

    while(fgets(linea, TAM, archM))
    {
        parseo(linea, &emb);


        if(!(aux = buscarEnVec(vec, ce, emb.mat))){
            agregarEmbarcacion(vec,&emb,ce);
            ce++;
        }
        else{
            sumarKms(aux,&emb);
        }

    }
    mostrarVector(vec,ce);

    fclose(archM);
    return ce;
}

void cargarTopEmbarcaciones(char mat[][TAMPAT], Emb_y_km* vec, int ce, size_t tamElem){
    int elemMat;
    char cad[TAMPAT];

    ordenarSeleccionGenerico(vec,ce,tamElem,cmpKms);
    elemMat = cargarMatriz(mat, cad, vec, ce);
    mostrarMatriz(mat, elemMat);

}

void sumarKms(Emb_y_km* embASumar,Embarcacion* emb){
    embASumar->kilometros += calcularDist(embASumar->lat,embASumar->pos,emb->lat,emb->pos);
    embASumar->lat = emb->lat;
    embASumar->pos = emb->pos;
}

void agregarEmbarcacion(Emb_y_km* vec, Embarcacion* emb, int ce){
    Emb_y_km* aux = vec + ce;
    strcpy(aux->mat, emb->mat);
    aux->lat = emb->lat;
    aux->pos = emb->pos;
    aux->kilometros =0;
}

//*************************************************//

double calcularDist(double latitud1, double long1, double latitud2, double long2)
{
    double dist;
    dist = sin(paseARadianes(latitud1)) * sin(paseARadianes(latitud2)) + cos(paseARadianes(latitud1)) * cos(paseARadianes(latitud2)) * cos(paseARadianes(long1 - long2));
    dist = acos(dist);
    dist = 6371*1000 * dist;
    return dist;
}

double paseARadianes(double nro)
{
    double pi= 3.14159;

    return nro/180 * pi;
}

//*************************************************//

int parseo(char* linea, Embarcacion *emb){


    sscanf(linea,"%ld,%[^,],%lf,%lf\n",&emb->FyH,emb->mat,&emb->lat,&emb->pos);
    return 1;

}

char* strcpyMe(char *s1, const char* s2){
    char* ini = s1;
    while(*s2){
        *ini++ = *s2++;
    }
    *ini = '\0';
    return ini;
}

int strcmpMe(const char *s1, const char *s2){
    while(*s1 && *s2 && *s1 == *s2){
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

int cmpKms(const void* elem1,const void* elem2)
{
    const Emb_y_km* e1 = elem1;
    const Emb_y_km* e2 = elem2;

    return e1->kilometros - e2->kilometros;
}

int cmpFyH(const void* elem1, const void* elem2){
    const Embarcacion* e1 = elem1;
    const Embarcacion* e2 = elem2;

    return e1->FyH - e2->FyH;
}
