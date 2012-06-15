#include <stdio.h>
#include <stdlib.h>  //necessaria para o malloc
#include <string.h> //necessaria para o strcmp
#include "../include/processos.h"

/*
    Fun��o: criaLista
    Par�metros: Nenhum
    Descri��o: Inicializa a lista de processos
*/
process* criaLista(void)
{
    pid_contador = 0;
    return NULL;
}

/*
    Fun��o: insere
    Par�metros: l(process*), pid(int), size(int)
    Descri��o: Insere um novo processo com o pid e o size especificado na lista
               de processos l. J� cria as respectivas p�ginas de mem�ria para o
               processo. As p�ginas s�o "carregadas" inicialmente no swap.
*/
process* insere(process* l, int pid, int size)
{
    process* novo; //novo elemento
    process* ant = NULL; //ponteiro auxiliar para a posi��o anterior
    process* ptaux = l; //ponteiro auxiliar para percorrer a lista
    page* paginas; // Ponteiro para as p�ginas do processo que ser�o alucadas como uma matriz
    int i;

    /* Gera um array que � um conjunto de p�ginas para o processo */
    paginas = (page*) malloc((sizeof(page) * size));
    for(i = 0; i < size; i++) {
        paginas[i].pagina = i;
        paginas[i].acessos = 0;
        paginas[i].nroPageFault = 0;
        paginas[i].nroSubst = 0;
        paginas[i].local = 'S';
    }

    /* Gera um novo elemento processo na lista */
    novo = (process*) malloc(sizeof(process));
    novo->pid  = pid;
    novo->size = size;
    novo->estado = INICIALIZADO;
    novo->paginas = paginas;

    /* procurando a posi��o de inser��o */
    while ((ptaux!=NULL) && (ptaux->pid < pid))
    {
        ant = ptaux;
        ptaux = ptaux->prox;
    }

    /* encaeia o elemento */
    if (ant == NULL) /*o anterior n�o existe, logo o elemento ser� inserido na primeira posi��o*/
    {
        novo->prox = l;
        l = novo;
    }
    else /* elemento inserido no meio da lista */
    {
        novo->prox = ant->prox;
        ant->prox = novo;
    }

    pid_contador++; // incrementa o total de processos na lista

    return l;
}

/*
    Fun��o: remove
    Par�metros: l(process*), pid(int)
    Descri��o: Remove da lista de processos l o processo com o pid especificado.
*/
process* removeProc(process* l, int pid)
{
    process *ant = NULL; //ponteiro auxiliar para a posi��o anterior
    process *ptaux = l;  //ponteiro auxiliar para percorrer a lista

    /*procura o elemento na lista*/
    while (ptaux !=NULL && (ptaux->pid != pid))
    {
        ant = ptaux;
        ptaux = ptaux->prox;
    }

    /*verifica se achou*/
    if (ptaux == NULL)
        return l; /*retorna a lista original*/

    if (ant == NULL) /*vai remover o primeiro elemento*/
        l = ptaux->prox;
    else /*vai remover do meio ou do final*/
        ant->prox = ptaux->prox;

    // libera a mem�ria alocada
    free(ptaux->paginas);
    free(ptaux);

    pid_contador--; // decrementa o total de processos na lista

    return l;
}

/*
    Fun��o: consulta
    Par�metros: l(process*), pid(int)
    Retorno: O processo pid ou NULL se n�o encontrar
    Descri��o: Consulta o processo identificado pelo pid na lista de processos l.
*/
process* consulta(process* l, int pid)
{
    process* ptaux = l;  //ponteiro auxiliar para percorrer a lista

    /*procura o elemento na lista*/
    while (ptaux != NULL)
    {
        if(ptaux->pid == pid)
            break;
        ptaux = ptaux->prox;
    }

    return ptaux;
}

/*
    Fun��o: existe
    Par�metros: l(process*), pid(int)
    Retorno: 1, se o processo est� na lista l; 0, caso contr�rio
    Descri��o: Verifica se o processo identificado pelo pid existe na lista de
               processos l.
*/
int existe(process* l, int pid)
{
    process *ptaux = NULL; //ponteiro o processo

    ptaux = consulta(l, pid);

    /*verifica se achou*/
    if(ptaux != NULL){
        if(ptaux->estado == INICIALIZADO)
            return 1;
    }
    return 0;
}

/*
    Fun��o: existePagina
    Par�metros: l(process*), pid(int), page(int)
    Retorno: 1, se existe a p�gina solicitada no processo pid;
             0, caso contr�rio
    Descri��o: Verifica se o processo identificado pelo pid, que est� na lista
               l, possui a p�gina solicitada.
*/
int existePagina(process* l, int pid, int page)
{
    process *ptaux = NULL; //ponteiro o processo

    ptaux = consulta(l, pid);

    // Verifica se acho o processo
    if(ptaux != NULL) {
        /* Verifica se a p�gina existe, como s�o sequenciais, basta verificar se
           � menor que o tamanho do processo em p�ginas (size) */
        if(page < ptaux->size) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

/*
    Fun��o: destroi
    Par�metros: l(process*)
    Descri��o: Remove todos os processos da lista.
*/
process* destroi(process* l)
{
    process *ptaux; //ponteiro auxiliar para percorrer a lista
    while (l != NULL) {
        ptaux = l;
        l = l->prox;
        free(ptaux->paginas);
        free(ptaux);
    }
    free(l);

    pid_contador = 0; // zera o total de processos na lista

    return NULL;
}

/*
    Fun��o: imprimeCrescente
    Par�metros: l(process*)
    Descri��o: Mostra na tela a listagem de processos com algumas informa��es
               al�m da especifica��o.
*/
void imprimeCrescente(process* l)
{
    process* ptaux;
    int i;
    int contador;

    printf("TOTAL DE PROCESSOS = %d\n\n", pid_contador);
    if (l != NULL) {
        for(ptaux=l, contador = 0; ptaux!=NULL; ptaux=ptaux->prox, contador++) {
            printf("PROCESSO %d - Size(paginas) = %d - Estado = %d\n",
                ptaux->pid, ptaux->size, ptaux->estado);
            printf("Pagina Acessos(R/W) NroPageFault NroSubst Local\n");
            for(i = 0; i < ptaux->size; i++) {
                printf("%-6d %12d %12d %8d %5c\n",
                    ptaux->paginas[i].pagina,
                    ptaux->paginas[i].acessos,
                    ptaux->paginas[i].nroPageFault,
                    ptaux->paginas[i].nroSubst,
                    ptaux->paginas[i].local);
            }
            printf("\n");
        }
        printf("\nRECONTAGEM DE PROCESSOS = %d\n", contador);
    } else {
        printf("\nERRO: A lista de processos esta vazia.\n");
    }
}

/*
    Fun��o: imprimeArquivo
    Par�metros: nome_arquivo (char[]), l(process*)
    Descri��o: Grava no arquivo nome_arquivo a listagem de processos conforme a
               especifica��o.
*/
void imprimeArquivo(char nome_arquivo[], process* l)
{
    FILE* arq;
    process* ptaux;
    int i;
    int result;

    printf("Nome arq: %s\n", nome_arquivo);
    //arq = fopen("log.txt", "wt"); // abre para escrita de arquivo texto
    arq = fopen(nome_arquivo, "w"); // abre para escrita de arquivo texto
    if (arq != NULL) {
        if (l != NULL) {
            for(ptaux=l; ptaux!=NULL; ptaux=ptaux->prox) {
                result = fprintf(arq, "PROCESSO %d\n",
                                ptaux->pid);
                if(result == EOF) {
                    printf("\nERRO: N�o foi possivel gravar no arquivo de LOG (1).\n");
                    break;
                }
                result = fprintf(arq, "Pagina Acessos(R/W) NroPageFault NroSubst\n");
                for(i = 0; i < ptaux->size; i++) {
                    
                    if(result == EOF) {
                        printf("\nERRO: N�o foi possivel gravar no arquivo de LOG (2).\n");
                        break;
                    }

                    result = fprintf(arq, "%-6d %12d %12d %8d\n",
                        ptaux->paginas[i].pagina,
                        ptaux->paginas[i].acessos,
                        ptaux->paginas[i].nroPageFault,
                        ptaux->paginas[i].nroSubst);
                    if(result == EOF) {
                        printf("\nERRO: N�o foi possivel gravar no arquivo de LOG (3).\n");
                        break;
                    }
                }
                result = fprintf(arq, "\n");
                if(result == EOF) {
                    printf("\nERRO: N�o foi possivel gravar no arquivo de LOG (4).\n");
                    break;
                }
            }
        } else {
            printf("\nERRO: A lista de processos esta vazia.\n");
        }
        fclose(arq);
    } else {
        printf("\nERRO: N�o foi possivel criar o arquivo de LOG.\n");
    }
}
