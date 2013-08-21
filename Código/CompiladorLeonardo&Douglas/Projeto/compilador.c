#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "bibliotecas/analisadorLexico.h"
#include "bibliotecas/verificaCaracteresValidos.h"
#include "bibliotecas/about.h"
#include "bibliotecas/menu.h"
#define maxVariaveis 100

/*VARIÁVEIS GLOBAIS

                                                                              */
TabelaLexica *tabelaLexica;

/*----------------------------------------------------------------------------*/

/*MÉTODO MAIN
                                                                              */
int main(int argc, char *argv[]){
    TabelaDeSimbolos tabela;
    char * nomeArquivo="";
    int validado;
    char nomeArquivoTemp[30];
    
    while(1){
       system("cls");
       nomeArquivo = desenhaMenu();
       
       if (strcmp(nomeArquivo, "sair") == 0){

          exit(0);

       } else if (strcmp(nomeArquivo, "about") == 0){   

          about();
          

       } else if (strcmp(nomeArquivo, "") != 0){     
         
          while (1){
              system("cls");
              validado = verificaCaracteresValidos(nomeArquivo);
                
              if (validado == 0){
                 system("pause");
                 exit(0);             
              }
              else if (validado == 1){
                 inicializaTabela(&tabela);
                 addPalavrasReservadas(&tabela);
                 analisadorLexico(&tabela, nomeArquivo);
                 system("pause");
                 break;
              } else if (validado == -1){  
                 system("cls");               
                 printf("Digite o nome do arquivo novamente: ");
                 scanf("%s", nomeArquivoTemp);
                 nomeArquivo = (char*) calloc(strlen(nomeArquivoTemp), sizeof(char));
                 strcpy(nomeArquivo, nomeArquivoTemp);
              }
          }
       }
    }
    
    system("PAUSE");
    return 0;
}

/*----------------------------------------------------------------------------*/

