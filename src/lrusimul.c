#include <stdio.h>
#include <stdlib.h>

/*
    Fun��o: memSize
    Par�metros: size(inteiro)
    Descri��o: Define o tamanho da mem�ria f�sica (RAM) em size quadros.
*/
void memSize(int size)
{

}

/*
    Fun��o: procSize
    Par�metros: id(inteiro), size(inteiro)
    Descri��o: Cria processo identificado por id com size p�ginas. Considerase
                que essa cria��o coloca todas as p�ginas do processo no swap
                e n�o na mem�ria RAM.
*/
void procSize(int id, int size)
{

}

/*
    Fun��o: Read
    Par�metros: page(inteiro), id(inteiro)
    Descri��o: Realiza a leitura de uma posi��o de mem�ria da p�gina page
                do processo id. Se a p�gina n�o estiver na mem�ria, ela deve
                ser carregada. Se n�o houver quadros livres, o algoritmo LRU
                deve ser acionado para providenciar a substitui��o de uma outra
                p�gina e a carga da p�gina solicitada.
*/
void Read(int id, int size)
{

}

/*
    Fun��o: Write
    Par�metros: page(inteiro), id(inteiro)
    Descri��o: Realiza a escrita em uma posi��o de mem�ria na p�gina page
                do processo id. Se a p�gina n�o estiver na mem�ria, ela deve
                ser carregada. Se n�o houver quadros livres, o algoritmo LRU
                deve ser acionado para providenciar a substitui��o de uma outra
                p�gina e a carga da p�gina solicitada.
*/
void Write(int id, int size)
{

}

/*
    Fun��o: endProc
    Par�metros: id(inteiro)
    Descri��o: Termina a execu��o do processo id. Todos os quadros alocados
                a este processo devem ser liberados.
*/
void endProc(int id)
{

}

/*
    Fun��o: corta
    Par�metros: string(char[])
    Descri��o: Fun��o que corta o que sobra do string
*/
void corta(char string[])
{
    if(string[strlen(string)-1]=='\n')
       string[strlen(string)-1] ='\0';
}
/*
    Fun��o: 
    Par�metros: 
    Descri��o: 
*/

/*
    Fun��o: 
    Par�metros: 
    Descri��o: 
*/

/*
    Fun��o: 
    Par�metros: 
    Descri��o: 
*/