/** 

percorre todo arquivo para verificar se existe algum caracter que n�o �
permitido pela linguagem.

Retorno: 
         ->  1: caso n�o tenha encontrado nenhum caracter inv�lido
         -> -1: caso ocorra algum erro ao abrir o arquivo
         ->  0: caso encontre algum caracter inv�lido

**/

int verificaCaracteresValidos(char *nomeArquivo){ 
    FILE *arq = fopen(nomeArquivo, "r");
    char caracter;
    int linha = 1;
    
    if (!arq){
       system("cls");
       printf ("Erro ao abrir o arquivo!!\n\n");
       system("PAUSE");
       return -1;
    }

    caracter = fgetc(arq);    
    
    while (!feof(arq)){
        
        if (caracter == '\n'){
           linha++;
        } 
        else if (isalpha(caracter) != 0 || isdigit(caracter) != 0 ||
                 caracter == '_' || caracter == ' ' || caracter == '.' || caracter == ',' ||
                 caracter == ';' || caracter == ':' || caracter == '(' || caracter == ')' ||
                 caracter == '{' || caracter == '}' || caracter == '[' || caracter == ']' ||
                 caracter == '+' || caracter == '-' || caracter == '"' || caracter == '\'' ||
                 caracter == '/' || caracter == '\\' || caracter == '|' || caracter == '&' ||
                 caracter == '!' || caracter == '?' || caracter == '>' || caracter == '<' ||
                 caracter == '=' || caracter == '*' || caracter == '#'){
    
             
        } else {
           system("cls");
           printf("erro\n");
           
           if (linha < 10)
              printf("0%d: caracter invalido.\n\n", linha);  
           else    
              printf("%d: caracter invalido.\n\n", linha);
              
           fclose(arq);                
           return 0;    
        }
        
        caracter = fgetc(arq);
             
    }
    
    fclose(arq);
    
    return 1;
}
