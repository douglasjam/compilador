#define NULL ((void *)0) 

typedef struct {
        char *token;
        char *lexema;        
} Token;

/************************************************************************/
typedef struct {
        Token *palavrasReservadas;
        int qtdPalavrasReservadas;
        Token *identificadores;
        int qtdIdentificadores;
} TabelaDeSimbolos;

/************************************************************************/
void inicializaTabela(TabelaDeSimbolos * tabela) {
     tabela->qtdPalavrasReservadas = 0;
     tabela->palavrasReservadas = NULL;
     tabela->qtdIdentificadores = 0;
     tabela->identificadores = NULL;
}
/************************************************************************/
/*

Retorna 1 se cont�m o token e o mesmo � palavra reservada, 2 se cont�m e �
identificador e 0 se n�o cont�m.

*/

int tabelaContem(TabelaDeSimbolos * tabela, char * token){
     int i;
     
     /* verifica se � palavra reservada */
     for(i = 0; i < tabela->qtdPalavrasReservadas; i++){
           if(strcmp(tabela->palavrasReservadas[i].lexema, token) == 0){ // s�o iguais
               return 1; // cont�m o token e � palavra reservada
           }
     }
     
     /* verifica se � identificador */
     for(i = 0; i < tabela->qtdIdentificadores; i++){
           if(strcmp(tabela->identificadores[i].lexema, token) == 0) // s�o iguais
               return 2; // cont�m o token e � identificador     
     }
     
     return 0; // n�o cont�m o token
}
/************************************************************************/

void limpaTabela(TabelaDeSimbolos * tabela) {
     int i;
     
     /* limpa as palavras reservadas */
     if(tabela->qtdPalavrasReservadas > 0) {
         free(tabela->palavrasReservadas);
         tabela->qtdPalavrasReservadas = 0; // zera o contador
     }
     
     /* limpa os identificadores */
     if(tabela->qtdIdentificadores > 0) {
         free(tabela->identificadores);
         tabela->qtdIdentificadores = 0; // zera o contador
     }

}
/************************************************************************/
int addIdentificador(TabelaDeSimbolos * tabela, char * identificadorArgumento, int linhas) {
    int existe = tabelaContem(tabela, identificadorArgumento); // verifica se o identificadorArgumento j� existe na tabela
    int i;    
    
    if(existe == 1){
        printf("identificou palavra reservada \"%s\" !!\n\n", identificadorArgumento);
        return -1; // o identificadorArgumento j� existe e � uma palavra reservada
    } else if (existe == 2){ 
        printf("identifidor \"%s\" ja existe!!\n\n", identificadorArgumento);
        return -2; // o identificadorArgumento existe e � um identificador
    }    
      
    // aloca a memoria para a nova lista + 1
    Token * listaIdentificadoresTemp = (Token*) calloc(tabela->qtdIdentificadores + 1, sizeof(Token));

    // copia o conteudo de uma lista para outra
    for(i = 0; i < tabela->qtdIdentificadores; i++) {
          listaIdentificadoresTemp[i] = tabela->identificadores[i];
    }
    
    // adiciona a nova palavra a novaLista
    listaIdentificadoresTemp[tabela->qtdIdentificadores].lexema = identificadorArgumento;
    int tipo = verificaTipo(identificadorArgumento);
    
    if (tipo == 1){ // � identificador
        listaIdentificadoresTemp[tabela->qtdIdentificadores].token = "id";
        printf("identifidor \"%s\" adicionado com sucesso!!\n\n", identificadorArgumento);
    }
    
    else if (tipo == 2){ // � n�mero
        listaIdentificadoresTemp[tabela->qtdIdentificadores].token = "num";         
        printf("numero \"%s\" adicionado com sucesso!!\n\n", identificadorArgumento);
    }
    
    else if (tipo == 3){ // � string 
        int tamString = strlen(identificadorArgumento);
        char string[tamString-2];
        int i;
        
        string[0] = identificadorArgumento[1]; // copio sem aspas
        for (i = 1; i < tamString-3; i++){
            string[i] = identificadorArgumento[i+1];  
        }
        string[tamString-3] = identificadorArgumento[tamString-2];
        
        listaIdentificadoresTemp[tabela->qtdIdentificadores].lexema = string;
        listaIdentificadoresTemp[tabela->qtdIdentificadores].token = "string";
                 
        printf("string %s adicionada com sucesso!!\n\n", string);
    }
    
    else{  // � erro
        printf("erro\n");
        if (linhas < 10)
           printf("0%d: lexema nao identificado [%s].\n\n", linhas, identificadorArgumento);
        else
            printf("%d: lexema nao identificado [%s].\n\n\n", linhas, identificadorArgumento);
        
        system("pause");
        exit(0);
    }
    
    // destroi a lista antiga
    free(tabela->identificadores);

    // seta a novaLista no lugar da antiga
    tabela->identificadores = listaIdentificadoresTemp;
    // incrementa o valor da lista
    tabela->qtdIdentificadores += 1;
    
    return tabela->qtdIdentificadores-1; // identificadorArgumento adicionado com sucesso (retorna posi��o em que foi adicionado)
}
/************************************************************************/
int remIdentificador(TabelaDeSimbolos * tabela, Token * identificadorArgumento) {
    int i,j = 0;
    int contem = tabelaContem(tabela, identificadorArgumento->lexema);
    
    // se n�o contem a palavra n�o tem como retirar, retorna 0 == erro
    if(contem == 0){ // n�o cont�m
        return 0;
    }
    
    if(contem == 2){ // s� remove se for identificador   
            
       // aloca a memoria para a nova lista -1
       Token * identificadoresTemp = (Token*) calloc(tabela->qtdIdentificadores - 1, sizeof(Token*));
       
       // copia o conteudo de uma lista para outra
       for(i = 0; i < tabela->qtdIdentificadores; i++) {
          if(strcmp(tabela->identificadores[i].lexema, identificadorArgumento->lexema) != 0){ // se n�o s�o iguais
              identificadoresTemp[j] = tabela->identificadores[i];
              j++;
          }
       }

       // limpa a lista antiga
       if(tabela->qtdIdentificadores > 0) {
          free(tabela->identificadores);
       }
    
       // seta a novaLista no lugar da antiga
       tabela->identificadores = identificadoresTemp;

       // decrementa o valor da lista
       tabela->qtdIdentificadores -= 1;
    
       return 0;
    }
    
    if (contem == 1) // cont�m o identificador mais o mesmo � palavra reservada e n�o pode ser retirado
       return -1;

	return 0;

}
/************************************************************************/
int indexOfTabela(TabelaDeSimbolos * tabela, char * identificadorArgumento){
     int i;
     
     for(i = 0; i < tabela->qtdIdentificadores; i++){ // pesquisa nos identificadores
           if(strcmp(tabela->identificadores[i].lexema , identificadorArgumento) == 0){
               return i; // retorna a posi��o
           }
     }
     
     for(i = 0; i < tabela->qtdPalavrasReservadas; i++){ // pesquisa nas palavras reservadas
           if(strcmp(tabela->palavrasReservadas[i].lexema , identificadorArgumento) == 0){
               return i; // retorna a posi��o
           }      
     }
     return -1;    
}
/************************************************************************/
void tabelaToString(TabelaDeSimbolos * tabela){
     int i;
     
     printf ("Imprimindo identificadores...\n");
     
     if (tabela->qtdIdentificadores == 0){ // verifica se possui algum identificador
        printf("Nenhum identificador adicionado!!\n\n");
     } else {
          /* imprime os identificadores */
          for(i = 0; i < tabela->qtdIdentificadores; i++){
                printf("Nome: %s\nTipo: %s\n\n",tabela->identificadores[i].lexema, tabela->identificadores[i].token);
          }
     }
     
     printf ("Imprimindo palavras reservadas...\n");
     
     if (tabela->qtdPalavrasReservadas == 0){ // verifica se possui alguma palavra reservada
        printf("Nenhuma palavra reservada adicionada!!\n\n");
     } else {
          /* imprime as palavras reservadas */
          for(i = 0; i < tabela->qtdPalavrasReservadas; i++){
                printf("Nome: %s\nTipo: %s\n\n",tabela->palavrasReservadas[i].lexema, tabela->palavrasReservadas[i].token);
          }
     }
}
/************************************************************************/
void addPalavrasReservadas(TabelaDeSimbolos *tabela){
     int i=0;
     
     char * alfabeto[35] = {"final", "int", "byte", "string", "while", 
                        "\"", "if", "else", "&", "|", "!", "==",
                        "=", "(", ")", "<", ">", "!=", ">=", ",",
                        "<=" , "+", "-", "*", "/", ";", "read",
                        "write", "begin", "end", "main", "true",
                        "false", "boolean", "#"};

     tabela->palavrasReservadas = (Token*) calloc(35, sizeof(Token));
     
     while (i < 35){
         tabela->palavrasReservadas[i].lexema = alfabeto[i];
         tabela->palavrasReservadas[i].token = "pr";
         tabela->qtdPalavrasReservadas += 1;
         i++;
     }
}
/************************************************************************/
/**

RETORNO: 
         -> 1: se � um lexema v�lido 
         -> 0: se � um lexema inv�lido
         -> 2: se � numero
         -> 3: se � string

**/

int verificaTipo(char * argumento){
    int codigoASCII;
    int i=1;
    
    if (isalpha(argumento[0]) != 0) { // come�ou com letra (provavelmente � identificador v�lido)
        while (argumento[i] != '\0') { // percorre toda string para verificar se � composta por letra, d�gito ou sublinhado
            codigoASCII = argumento[i];
            if (isalpha(argumento[i]) != 0 ||
                isdigit(argumento[i]) != 0 || codigoASCII == 95) // � uma letra, d�gito ou sublinhado
                i++;
            else 
                return 0; // n�o � um lexema v�lido, porque possui um caracter n�o permitido
        }
        return 1; // � um lexema v�lido
        
    } else if (isdigit(argumento[0]) != 0) { // verifica se o tipo � num
        while (argumento[i] != '\0'){
            if (isdigit(argumento[i]) != 0)
               i++;
            else{
                return 0;
            }
        }
        return 2; 
    } else if (argumento[0] == '"'){ // verifica se � string
        if (argumento [strlen(argumento)-1] == '"')
           return 3;
    } 
    
    return 0; // erro
}
