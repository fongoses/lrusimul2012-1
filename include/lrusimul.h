typedef enum enumComandos{
    MEMSIZE,
    PROCSIZE,
    READ,
    WRITE,
    ENDPROC
}enumComandos;

typedef struct ListMEMO{
    int  pagina;
    int  bitRef;
    int  bitMod;
    ListMEMO* prox;
}ListMEMO;

typedef struct page{
    //int  pagina;
    int  quadro;
    int  acessos;
    int  nroPageFault;   // ser� no m�nimo 1, quando a p�gina � lida pela primeira vez
    int  nroSubst;       // Quantas vezes esta p�gina foi escolhida como "v�tima", caso n�o existam mais p�ginas dispon�veis na mem�ria RAM
    char SwapMem;
} page;

typedef struct TABpages{
    page        pg;
    LDECpages*  ant;
    LDECpages*  prox;
} TABpages;

 typedef struct process{
    int pid;
    TABpages* paginas;
} process;
 
 

// procedimentos e fun��es de leitura do arquivo
void memSize(int size);
void procSize(int id, int size);
void Read(int id, int size);
void Write(int id, int size);
void endProc(int id);

// procedimentos e fun��es auxiliares utilizados
void corta(char string[]);
