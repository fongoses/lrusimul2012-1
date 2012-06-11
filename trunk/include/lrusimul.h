typedef enum enumComandos{
    MEMSIZE,
    PROCSIZE,
    READ,
    WRITE,
    ENDPROC
}enumComandos;


typedef struct page{
    int pagina;
    int acessos;
    int nroPageFault; // ser� no m�nimo 1, quando a p�gina � lida pela primeira vez
    int nroSubst;     // Quantas vezes esta p�gina foi escolhida como "v�tima", caso n�o existam mais p�ginas dispon�veis na mem�ria RAM
} page;

typedef struct LDECpages{
    page        pg;
    LDECpages*  ant;
    LDECpages*  prox;
} LDECpages;

 typedef struct process{
    int pid;
    LDECpages paginas;
} process;
 
 


// procedimentos e fun��es de leitura do arquivo
void memSize(int size);
void procSize(int id, int size);
void Read(int id, int size);
void Write(int id, int size);
void endProc(int id);

// procedimentos e fun��es utilizados
void corta(char string[]);
