typedef enum enumComandos{
    MEMSIZE,
    PROCSIZE,
    READ,
    WRITE,
    ENDPROC
}enumComandos;

 typedef struct process{
    int pid;
    
} process;
 
 typedef struct page{
    int pagina;
    int acessos;
    int nroPageFault; // ser� no m�nimo 1, quando a p�gina � lida pela primeira vez
    int nroSubst;     // Quantas vezes esta p�gina foi escolhida como "v�tima", caso n�o existam mais p�ginas dispon�veis na mem�ria RAM
} page;

typedef struct LDECpages{

} LDECpages;