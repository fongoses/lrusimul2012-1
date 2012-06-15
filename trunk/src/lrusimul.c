#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/lrusimul.h"
#include "../include/processos.h"



/*   Fun��es internas - INICIO     */
// vars globais
int         clockPointer;
int         quant_frames;
tmemoria*   Memoria;
process*    Processos;

/*
    Fun��o: criaMemoria
    Par�metros: n(int)
    Descri��o: Cria vetor que representa a mem�ria f�sica (RAM) com n quadros. Retorna um ponteiro para o vetor.
*/
tmemoria* criaMemoria(int n)
{
    int i;
    tmemoria* aux;

    aux = (tmemoria*)malloc(sizeof(tmemoria) * n);

    // Seta todos os quadros para dispon�vel
    for(i = 0;i < n; i++){
        aux[i].pid     = DISPONIVEL;
		aux[i].pagina  = DISPONIVEL;
        aux[i].bitRef  = 0;
        aux[i].bitSujo = 0;
    }

    return aux;
}


/*      Fun��es internas - FIM     */
/*
    Fun��o: memSize
    Par�metros: size(int)
    Descri��o: Define o tamanho da mem�ria f�sica (RAM) em size quadros.
*/
void memSize(int size)
{
    clockPointer = 0;
    quant_frames = size;
    Memoria = criaMemoria(size);        // memoria
    Processos = criaLista();            // area de swap, onde os processos s�o inicializados
}

/*
    Fun��o: procSize
    Par�metros: id(int), size(int)
    Descri��o: Cria processo identificado por id com size p�ginas. Considerase
                que essa cria��o coloca todas as p�ginas do processo no swap
                e n�o na mem�ria RAM.
*/
void procSize(int id, int size)
{
    if (existe(Processos, id))
        printf("Processo %d jah existe e nao pode ser criado\n",id);
    else
        Processos = insere(Processos, id, size);
}

/*
    Fun��o: Read
    Par�metros: page(int), id(int)
    Descri��o: Realiza a leitura de uma posi��o de mem�ria da p�gina page
                do processo id. Se a p�gina n�o estiver na mem�ria, ela deve
                ser carregada. Se n�o houver quadros livres, o algoritmo LRU
                deve ser acionado para providenciar a substitui��o de uma outra
                p�gina e a carga da p�gina solicitada.
*/
void Read(int pagina, int id)
{
    int i;

    int frame;

    int pid_vitima,pag_vitima;
    process* vitProcess;

    int pageFault = 1;
    process* auxProcess;

    for(i = 0;i<quant_frames;i++){
        if((Memoria[i].pid == id) && (Memoria[i].pagina == pagina))   // n�o haver� page fault
        {
            pageFault = 0;
            break;
        }
    }


    auxProcess = consulta(Processos, id); // se n�o existe retorna nulo

    switch(pageFault)
    {
        case 0:                 // n�o ocorreu pageFault
        {
            auxProcess->paginas[pagina].acessos++;
            Memoria[i].bitRef = 1;
            break;
        }
        case 1:                 // Ocorreu pageFault
        {
            // verifica se solicitacao existe
            if(auxProcess==NULL)
            {
                printf("Solicitacao de leitura invalida! \n");
            }
            else
            {
                trataPageFault(Memoria,&pid_vitima,&pag_vitima,&frame);
                
                auxProcess->paginas[pagina].nroPageFault++;
                auxProcess->paginas[pagina].acessos++;
                auxProcess->paginas[pagina].local = 'M';

                Memoria[frame].pid = id;
                Memoria[frame].pagina = pagina;
                Memoria[frame].bitRef = 1;
                Memoria[frame].bitSujo = 0;
                if(pid_vitima!=-1){
                    vitProcess = consulta(Processos, pid_vitima);
                    vitProcess->paginas[pag_vitima].nroSubst++;
                    printf("Substituiu %d em READ\n", pid_vitima);
                    vitProcess->paginas[pag_vitima].local = 'S';
                }
            }
            break;
        }
    }
}

/*
    Fun��o: Write
    Par�metros: page(int), id(int)
    Descri��o: Realiza a escrita em uma posi��o de mem�ria na p�gina page
                do processo id. Se a p�gina n�o estiver na mem�ria, ela deve
                ser carregada. Se n�o houver quadros livres, o algoritmo LRU
                deve ser acionado para providenciar a substitui��o de uma outra
                p�gina e a carga da p�gina solicitada.
*/
void Write(int pagina, int id)
{
    int i;

    int frame;

    int pid_vitima,pag_vitima;
    process* vitProcess;

    int pageFault = 1;
    process* auxProcess;

    for(i = 0;i<quant_frames;i++){
        if((Memoria[i].pid == id) && (Memoria[i].pagina == pagina))   // n�o haver� page fault
        {
            pageFault = 0;
            break;
        }
    }

    auxProcess = consulta(Processos, id); // se n�o existe retorna nulo

    switch(pageFault)
    {
        case 0:                 // n�o ocorreu pageFault
        {
            auxProcess->paginas[pagina].acessos++;
            Memoria[i].bitRef = 1;
            Memoria[i].bitSujo = 1;
            break;
        }
        case 1:                 // Ocorreu pageFault
        {
            // verifica se solicitacao existe
            if(auxProcess==NULL)
            {
                printf("Solicitacao de leitura invalida! \n");
            }
            else
            {

                trataPageFault(Memoria,&pid_vitima,&pag_vitima,&frame);
                
                auxProcess->paginas[pagina].nroPageFault++;
                auxProcess->paginas[pagina].acessos++;
                auxProcess->paginas[pagina].local = 'M';
                Memoria[frame].pid = id;
                Memoria[frame].pagina = pagina;
                Memoria[frame].bitRef = 1;
                Memoria[frame].bitSujo = 1;

                if(pid_vitima!=-1){
                    vitProcess = consulta(Processos, pid_vitima);
                    printf("Substituiu %d em WRITE\n", pid_vitima);
                    vitProcess->paginas[pag_vitima].nroSubst++;
                    vitProcess->paginas[pag_vitima].local = 'S';
                }
                
            }
            break;
        }
    }
}

/*
    Fun��o: endProc
    Par�metros: id(inteiro)
    Descri��o: Termina a execu��o do processo id. Todos os quadros alocados
                a este processo devem ser liberados.
*/
void endProc(int id)
{
    int i ;
    // libera processo no swap
    process* auxProcess;

    if (!(existe(Processos, id))){
        printf("Processo %d nao existe logo nao pode ser finalizado!\n", id);
        return;
    }
    auxProcess = consulta(Processos, id);
    auxProcess->estado = ENCERRADO;

    // libera todos os quadros alocados a este processo
    for(i = 0;i<quant_frames;i++)
    {
        if (Memoria[i].pid == id)
            Memoria[i].pid = DISPONIVEL;
    }
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
    Fun��o: LRUclock
    Par�metros: Memoria(tmemoria*), vitima(int[]), frame(int*)
    Descri��o:
*/
void LRUclock(tmemoria* Memoria,int* pid_vitima, int* pag_vitima,int* frame)
{
    int cont = 0;
    int ini  = clockPointer;

    do{
        if(ini == clockPointer)
            cont++;
        if (((Memoria[clockPointer].bitRef == 0) && (Memoria[clockPointer].bitSujo == 0))
            || ((cont==3) && (Memoria[clockPointer].bitRef == 0))){
            *pid_vitima = Memoria[clockPointer].pid;
            *pag_vitima = Memoria[clockPointer].pagina;
            *frame = clockPointer;
            break;
        }

        Memoria[clockPointer].bitRef = 0;
        clockPointer = (clockPointer + 1) % quant_frames;

    }while(!(cont>3));


    clockPointer = (clockPointer + 1) % quant_frames;

}

/*
    Fun��o: trataPageFault
    Par�metros: Nenhum
    Descri��o: Trata PageFault
*/
void trataPageFault(tmemoria* Memoria,int* pid_vitima, int* pag_vitima,int* frame)
{
    int i;

    *pid_vitima = -1;
    *pag_vitima = -1;
    *frame = -1;
    
    //procura um quadro livre
    for(i = 0;i<quant_frames;i++)
    {
        if (Memoria[i].pid == DISPONIVEL){
            *frame = i;
            return;                         //encontrou frame livre
        }
    }
    // N�o encontrou, chama LRUclock
    LRUclock(Memoria,pid_vitima,pag_vitima,frame);

}

/*
    Fun��o: mostraRelatorio();
    Par�metros: Nenhum
    Descri��o: Mostra o Relat�rio de Processos com as p�ginas e os acessos �
               mem�ria na tela, usa a fun��o imprimeCrescente().
*/
void mostraRelatorio() {
    imprimeCrescente(Processos);
}

/*
    Fun��o: gravaRelatorio();
    Par�metros: Nenhum
    Descri��o: Grava o arquivo de LOG no local definido por ARQ_LOG. O arquivo
               cont�m o Relat�rio de Processos com as p�ginas e os acessos �
               mem�ria, usa a fun��o imprimeArquivo().
*/
void gravaRelatorio() {
    imprimeArquivo(ARQ_LOG, Processos);
}

/*
    Fun��o:
    Par�metros:
    Descri��o:
*/
