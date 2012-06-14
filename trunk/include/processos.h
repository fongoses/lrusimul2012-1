#define INICIALIZADO   1
#define ENCERRADO      0

#include "../include/lrusimul.h"

typedef struct page {
    int  pagina;
    int  acessos;
    int  nroPageFault;   // ser� no m�nimo 1, quando a p�gina � lida pela primeira vez
    int  nroSubst;       // Quantas vezes esta p�gina foi escolhida como "v�tima", caso n�o existam mais p�ginas dispon�veis na mem�ria RAM
    char local;          // Indica se a p�gina est� na mem�ria 'M' ou no swap 'S', quando o processo � criado todas as p�ginas est�o no swap
} page;

typedef struct process {
    int         pid;
    int         size;
    int         estado;
    int         quant_pages;
    page*       paginas;
    process*    prox;
} process;
  
// procedimentos e fun��es da lista de processos
process* criaLista(void);
process* insere(process *l, int pid, int size);
process* remove(process* l, int pid);
process* destroi(process* l);

void imprimeCrescente(process* l);
void imprimeArquivo(char* nome_arquivo, process* l);