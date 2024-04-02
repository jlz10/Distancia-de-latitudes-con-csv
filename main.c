#include "Header.h"

int main(int argc, char* argv[]){
    Emb_y_km embKms[10];
    int ce = 0;

    generarArchivoMaster(argv[ARCH_POSM],argv[ARCH_POSA],argv[ARCH_POSB],cmpFyH);
    ce=calcularKmRecorridos(argv[ARCH_POSM], embKms, ce);

    char mat[TAMFIL][TAMPAT];

    cargarTopEmbarcaciones(mat,embKms,ce,sizeof(Emb_y_km));

    system("pause");

    return 0;
}
