#include <stdio.h>
#include <stdlib.h>
#include "lrusimul.h"


int main(int argc, char *argv[])
{
    FILE* pFile;
    char* nomeArquivo;
    
    nomeArquivo = argv[1];
    
    // � uma entrada v�lida
    if (nomeArquivo==NULL){
        printf("Arquivo inv�lido.");
        return -1;
    }
    // Inicializa��o das estruturas
    
    // Abre arquivo para leitura
    pFile = fopen (nomeArquivo,"r");
    
}
