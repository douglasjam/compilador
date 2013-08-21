/* Exemplo de Programa na linguagem L */

int n;
string nome;
byte naoTerminou;
final MAXITER=10;

/* Bloco Principal */

main {
  write("Digite seu nome: ");
  read(nome);
  naoTerminou=true;
  n=0;
  while (naoTerminou) {
    writeln("Ola' ,nome);
    n=n+1;
    naoTerminou=n<MAXITER;
  }
}