#define NULL ((void *)0)
#include "tabelaDeSimbolos.h"

int linhas=1;

typedef struct {
   char *lexema;
   int endInsercao;
} TokenId; // tokens identificadores e palavras reservadas

typedef struct {
   char *lexema;
   char *tipo;
} TokenConst; // tokens constantes

typedef struct {
   TokenId *tokensId;
   int qtdTokensId;
   TokenConst *tokensConst;
   int qtdTokensConst;
} TabelaLexica;

char * montaPalavra(char* palavra, char caracter){
     int tam = strlen(palavra);
     char *temp;

     temp = (char*) calloc(tam+2, sizeof(char*));
     strcpy(temp, palavra);
     free(palavra);
     temp[tam] = caracter;
     return temp;
}

void inicializaTabelaLexica(TabelaLexica *tabela){
     tabela->tokensId = NULL;
     tabela->tokensConst = NULL;
     tabela->qtdTokensId = 0;
     tabela->qtdTokensConst = 0;
}

void addLexico(TabelaLexica *tblLexica, TabelaDeSimbolos *tblSimbolos, char *lexema, int posicao){
     TokenConst *tokenConstTemp;
     TokenId *tokenIdTemp;
     int i;


     /**

     **/
     if (tblLexica->qtdTokensId > 1 && posicao > -1){
         if (strcmp(tblLexica->tokensId[tblLexica->qtdTokensId-2].lexema, "final") == 0){ // é constante
            
            char *type = tblLexica->tokensId[tblLexica->qtdTokensId-1].lexema;
            
            if (strcmp(type, "int") == 0 ||
                strcmp(type, "byte") == 0 ||
                strcmp(type, "string") == 0 ){ // contém o tipo da constante e é um tipo válido
                
                tokenConstTemp = (TokenConst*) calloc(tblLexica->qtdTokensConst+1, sizeof(TokenConst));
    
                // copia tudo
                for (i = 0; i < tblLexica->qtdTokensConst; i++){
                    tokenConstTemp[i] = tblLexica->tokensConst[i];
                }
    
                tokenConstTemp[tblLexica->qtdTokensConst].lexema = lexema;
    
                tokenConstTemp[tblLexica->qtdTokensConst].tipo = type;
    
                free(tblLexica->tokensConst);
    
                tblLexica->tokensConst = tokenConstTemp;
    
                tblLexica->qtdTokensConst++;
             } else {
                printf("Tipo da constante \"%s\" incorreto\n\n", lexema);       
             }       

         } else { // não é constante

           tokenIdTemp = (TokenId*) calloc(tblLexica->qtdTokensId+1, sizeof(TokenId));

           // copia tudo
           for (i = 0; i < tblLexica->qtdTokensId; i++){
               tokenIdTemp[i] = tblLexica->tokensId[i];
           }

           tokenIdTemp[tblLexica->qtdTokensId].lexema = lexema;

           tokenIdTemp[tblLexica->qtdTokensId].endInsercao = posicao;

           free(tblLexica->tokensId);

           tblLexica->tokensId = tokenIdTemp;

           tblLexica->qtdTokensId++;
         }

     } else if (posicao == -1 || posicao == -2){ // é palavra reservada ou identificador
         int pos = indexOfTabela(tblSimbolos, lexema);

         tokenIdTemp = (TokenId*) calloc(tblLexica->qtdTokensId+1, sizeof(TokenId));

         // copia tudo
         for (i = 0; i < tblLexica->qtdTokensId; i++){
             tokenIdTemp[i] = tblLexica->tokensId[i];
         }

         tokenIdTemp[tblLexica->qtdTokensId].lexema = lexema;

         tokenIdTemp[tblLexica->qtdTokensId].endInsercao = pos;

         free(tblLexica->tokensId);

         tblLexica->tokensId = tokenIdTemp;

         tblLexica->qtdTokensId++;

     } else { // é uma palavra reservada ou identificador já presente na tabela de símbolos

         tokenIdTemp = (TokenId*) calloc(tblLexica->qtdTokensId+1, sizeof(TokenId));

         // copia tudo
         for (i = 0; i < tblLexica->qtdTokensId; i++){
             tokenIdTemp[i] = tblLexica->tokensId[i];
         }

         tokenIdTemp[tblLexica->qtdTokensId].lexema = lexema;

         tokenIdTemp[tblLexica->qtdTokensId].endInsercao = posicao;

         free(tblLexica->tokensId);

         tblLexica->tokensId = tokenIdTemp;

         tblLexica->qtdTokensId++;
     }
}

void tabelaLexicaToString(TabelaLexica *tabela){
     int i;

     printf("|-----------------------------------------------------|\n");
     printf("|                                                     |\n");
     printf("|          IMPRIMINDO ITENS DA TABELA LEXICA          |\n");
     printf("|                                                     |\n");
     printf("|-----------------------------------------------------|\n\n");
     
     printf("|-----------------------------------------------------|\n");
     printf("|         IDENTIFICADORES E PALAVRAS RESERVADAS       |\n");
     printf("|-----------------------------------------------------|\n\n");
     
     if (tabela->qtdTokensId == 0)
        printf("| Nenhum identificador nem palavra reservada adicionado!!\n\n\n");
     else {
         for (i = 0; i < tabela->qtdTokensId; i++){
             printf("| Nome: %s\n", tabela->tokensId[i].lexema);
             printf("| Endereco de insercao na tabelaDeSimbolos: %d\n\n", tabela->tokensId[i].endInsercao);
         }
     }

     printf("|-----------------------------------------------------|\n");
     printf("|                     CONSTANTES                      |\n");
     printf("|-----------------------------------------------------|\n\n");
     
     if (tabela->qtdTokensConst == 0)
        printf("| Nenhuma constante adicionada!!\n\n\n");
     else {
         for (i = 0; i < tabela->qtdTokensConst; i++){
             printf("| Nome: %s\n", tabela->tokensConst[i].lexema);
             printf("| Tipo: %s\n\n", tabela->tokensConst[i].tipo);
         }
     }
}

void analisadorLexico(TabelaDeSimbolos *tabela, char *nomeArquivo){
   FILE *arq;
   TabelaLexica tblLexica;
   char caracter;
   char *palavra = "";
   int posicao = 0;

   arq = fopen(nomeArquivo, "r");

   inicializaTabelaLexica(&tblLexica);
   caracter = fgetc(arq);
   while(!feof(arq)){

       if (caracter == ' '){
          if (strcmp(palavra, "") != 0){
             posicao = addIdentificador(tabela, palavra, linhas);
             addLexico(&tblLexica, tabela, palavra, posicao);
             palavra = "";
          }
       }

       else if (caracter == '='){
           
           if (strcmp(palavra, "") != 0){ // quando tem palavra colada no igual
              posicao = addIdentificador(tabela, palavra, linhas);
              addLexico(&tblLexica, tabela, palavra, posicao);
              palavra = "";
           } 
           
           palavra = montaPalavra(palavra, caracter); // monto a palavra com =
           caracter = fgetc(arq); // leio próximo caracter para verificar se é ==
           
           if (caracter == '='){
              palavra = montaPalavra(palavra, caracter); // monto o ==
              posicao = addIdentificador(tabela, palavra, linhas);
              addLexico(&tblLexica, tabela, palavra, posicao);
              palavra = "";
           } else {
              posicao = addIdentificador(tabela, palavra, linhas); // adiciono =
              addLexico(&tblLexica, tabela, palavra, posicao);
              palavra = "";
              
              if (caracter != ' ') // não pode montar palavra com espaço
                 palavra = montaPalavra(palavra, caracter); 
           }
       
       }

       else if (caracter == '/'){ // verifica se é comentário
           
           if (strcmp(palavra, "") != 0){ // verifica se existe identificador a ser adicionado (caso de divisao)
              posicao = addIdentificador(tabela, palavra, linhas);
              addLexico(&tblLexica, tabela, palavra, posicao);
              palavra = "";
           } 
           
           palavra = montaPalavra(palavra, caracter); // monto palavra com '/'
           caracter = fgetc(arq); // leio próximo caracter para verificar se é comentário
           
           if (caracter == '*'){ // é comentário (iguinoro caracteres até fechar comentario)
              palavra = ""; // limpo palavra , pois é comentário
              caracter = fgetc(arq);
              while(!feof(arq)){
                 if (caracter == '*'){
                    caracter = fgetc(arq);
                    if (caracter == '/'){
                       printf("identificou comentario!!\n\n");                  
                       break;
                    }
                 } else if(caracter != '*'){
                        caracter = fgetc(arq);
                 }
              }
              
              if (caracter != '/'){
                 printf("erro\n");
                 if (linhas < 10)
                    printf("0%d: comentario nao fechado corretamente.\n\n", linhas);
                 else
                     printf("%d: comentario nao fechado corretamente.\n\n\n", linhas);
    
                 system("pause");
                 exit(0);     
              }
        }else { // não é comentário
              posicao = addIdentificador(tabela, palavra, linhas);
              addLexico(&tblLexica, tabela, palavra, posicao);
              palavra = "";

              if (caracter != ' '){
                 palavra = montaPalavra(palavra, caracter); // monto a próxima palavra depois do /
              }
           }
           
      }

      else if (caracter == '\n'){ // quebra de linha
           if (strcmp(palavra, "") != 0){
             posicao = addIdentificador(tabela, palavra, linhas);
             addLexico(&tblLexica, tabela, palavra, posicao);
             palavra = "";
           }
           linhas++;
      }

      else if (caracter == ';' || caracter == '\\' || caracter == '(' ||
               caracter == ')' || caracter == '-' || caracter == '|' ||
               caracter == '&' || caracter == '*' || caracter == '+' ||
               caracter == ','){
           
           if (strcmp(palavra, "") != 0){
             posicao = addIdentificador(tabela, palavra, linhas);
             addLexico(&tblLexica, tabela, palavra, posicao);
             palavra = "";
           } 
           
           palavra = montaPalavra(palavra, caracter); // monto palavra com ;
           posicao = addIdentificador(tabela, palavra, linhas);
           addLexico(&tblLexica, tabela, palavra, posicao);
           palavra = "";
      }

      else if (caracter == '<' || caracter == '>'){
        
          if (strcmp(palavra, "") != 0){
             posicao = addIdentificador(tabela, palavra, linhas);
             addLexico(&tblLexica, tabela, palavra, posicao);
             palavra = "";
          }
           
          palavra = montaPalavra(palavra, caracter);  // monta a palavra com > ou < 
          caracter = fgetc(arq);
          
          if (caracter == '='){ // verifica se é <= ou >= 
             palavra = montaPalavra(palavra, caracter); // monto a palavra 
          } 

          posicao = addIdentificador(tabela, palavra, linhas);
          addLexico(&tblLexica, tabela, palavra, posicao);
          palavra = "";

          if (caracter != ' ' && caracter != '='){ // não é >= ou <=
             palavra = montaPalavra(palavra, caracter); // monto a palavra 
          } 
          
      }
      
      else if (caracter == '!'){
           
           if (strcmp(palavra, "") != 0){
           
             posicao = addIdentificador(tabela, palavra, linhas);
             addLexico(&tblLexica, tabela, palavra, posicao);
             palavra = "";
           
           } 
           
           palavra = montaPalavra(palavra, caracter); // monta palavra com !
           caracter = fgetc(arq);
           
           if (caracter == '='){ // verifica se é !=
              palavra = montaPalavra(palavra, caracter); // monta a palavra !=
           } 

           posicao = addIdentificador(tabela, palavra, linhas);
           addLexico(&tblLexica, tabela, palavra, posicao);
           palavra = ""; 

           if (caracter != ' ' && caracter != '=') { 
               palavra = montaPalavra(palavra, caracter); // monta a palavra
           }
      }
      
      else if (caracter == '"'){
           
           if (strcmp(palavra, "") != 0){
           
             posicao = addIdentificador(tabela, palavra, linhas);
             addLexico(&tblLexica, tabela, palavra, posicao);
             palavra = "";
           } 
           
           palavra = montaPalavra(palavra, caracter); // monta palavra com "         
           caracter = fgetc(arq);
           
           while(!feof(arq)){
                            
               if(caracter == '"'){
                   palavra = montaPalavra(palavra, caracter);
                   posicao = addIdentificador(tabela, palavra, linhas);
                   addLexico(&tblLexica, tabela, palavra, posicao);
                   palavra = "";
                   break;
               } else if(caracter == '#') {
                   printf("erro\n");
                     if (linhas < 10)
                        printf("0%d: aspas nao fechadas.\n\n", linhas);
                     else
                         printf("%d: aspas nao fechadas.\n\n\n", linhas);
        
                     system("pause");
                     exit(0);
               } else if(caracter == '\n'){
                   printf("erro\n");
                     if (linhas < 10)
                        printf("0%d: quebra de linha dentro de string.\n\n", linhas);
                     else
                         printf("%d: quebra de linha dentro de string.\n\n\n", linhas);
        
                     system("pause");
                     exit(0);
               }
               palavra = montaPalavra(palavra,caracter);
               
               
               caracter = fgetc(arq); 
               if(feof(arq)) {
                   printf("erro\n");
                     if (linhas < 10)
                        printf("0%d: aspas nao fechadas.\n\n", linhas);
                     else
                         printf("%d: aspas nao fechadas.\n\n\n", linhas);
        
                     system("pause");
                     exit(0);
               }
               
           }
      } else if (caracter == '#'){
           if (strcmp(palavra, "") != 0){
           
             posicao = addIdentificador(tabela, palavra, linhas);
             addLexico(&tblLexica, tabela, palavra, posicao);
             palavra = "";
           } 
           
           palavra = montaPalavra(palavra, caracter); // monta palavra com "         
      } 
      
      else {
           palavra = montaPalavra(palavra, caracter);
      }

      caracter = fgetc(arq);
   }
   
   if (strcmp(palavra, "") != 0){
           
       posicao = addIdentificador(tabela, palavra, linhas);
       addLexico(&tblLexica, tabela, palavra, posicao);
       palavra = "";
   } 

   tabelaLexicaToString(&tblLexica);
   fclose(arq);
}
