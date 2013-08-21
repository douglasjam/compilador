/* Exemplo de Programa na linguagem L */

int n;
string nome;
byte naoTerminou;
final MAXITER=10;

/* Bloco Principal */

main
begin
  write("Digite seu nome: 
");
  read(nome);
  naoTerminou=true;
  n=0;
  while (naoTerminou) 
  begin
    writeln("Ola' ",nome);
    n=n+1;
    naoTerminou=n<MAXITER;
  end
end#