/*MÉTODO

NOME: void desenhaMenu()

DESCRIÇÃO: Desenha o menu principal e coleta a opcão desejada

RETORNO: Retorna um ponteiro de char
         -> "about": o usuário escolheu a opção about
         -> "sair": o usuário escolheu a opção sair
         -> qualquer outro valor diferente dos citados acima
            é o nome do arquivo que o usuário digitou.
                                                                              */
char * desenhaMenu(){
   char opcao;
   char nomeArquivoTemp[30];
   char *nomeArq;
   
   printf("|-----------------------------------------------------|\n");
   printf("|                                                     |\n");
   printf("|                    COMPILADOR                       |\n");
   printf("|                                                     |\n");
   printf("|-----------------------------------------------------|\n\n");
   printf("1) Compilar projeto\n\n");
   printf("2) About\n\n");
   printf("3) Sair\n\n");
   printf("DIGITE A OPCAO DESEJADA: ");
   opcao = getch();
   
   if (opcao == '1'){
      system("cls");
      printf("Digite o nome do arquivo texto: ");
      scanf("%s", nomeArquivoTemp);
      nomeArq = (char*) calloc(strlen(nomeArquivoTemp), sizeof(char));
      strcpy(nomeArq, nomeArquivoTemp);
      return nomeArq;       
   } else if (opcao == '2'){
      return "about";
   } else 
      return "sair";    
}
