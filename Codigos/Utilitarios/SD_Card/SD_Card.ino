/*  Uno ou Nano      ;  Mega
 ** CS - pin 4 ou 10 ;  53
 ** MOSI - pin 11    ;  51
 ** MISO - pin 12    ;  50   (Não precisa de divisor de tensão)
 ** SCK - pin 13     ;  52
 
 Arquivo Excel = .csv e usa o ; para distanciar
                 .xls
                 
 https://www.robocore.net/modules.php?name=Forums&file=viewtopic&t=4161
*/
 
#include <SPI.h>
#include <SD.h>
 
//criar um objeto File para manipular um arquivo
File myFile;
 
void setup() {
  Serial.begin(9600);
  while (!Serial);
 
  Serial.println("Inicializa o SD card...");
 
  if (!SD.begin(53)) {
    Serial.println("Nao inicializado. Veja no texto adiante sobre isso.");
    return;
  }
  Serial.println("Beleza! Seguindo...");
 
  /* A biblioteca SD tem um metodo para abrir arquivos e esse arquivo aberto
  sera armazenado no objeto myFile, descrito ao inicio desse codigo. Somente 
  um arquivo pode ser aberto por vez, portanto nao se esqueca de fecha-lo
  antes de abrir um novo ou voce tera problemas.
  */
 
  myFile = SD.open("teste.txt", FILE_WRITE);
 
  //Se o arquivo foi aberto com sucesso, escreve nele
  if (myFile) {
    Serial.println("Escrevendo para teste.txt");
    myFile.println("Pure arrebenta!!!");
 
    // Terminou de escrever, fecha-se o arquivo:
    myFile.close();
 
    Serial.println("Escrevinhado.");
 
  }
  else {
    // Se nao deu certo, comeca a dar merda desse ponto
    Serial.println("Nao foi possivel abrir o arquivo");
  }
 
  // Agora vamos abri-lo para leitura
  myFile = SD.open("teste.txt");
  if (myFile) {
    Serial.println("Conteudo de teste.txt:");
 
    // Le todo o arquivo...
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    //Finalizado, fecha-se o arquivo
    myFile.close();
  }
  else {
    // Se deu erro acima, aqui tambem dara.
    Serial.println("Nao pude abrir o arquivo.");
  }
}

void limpar_SD()
{
  //Depois que pegar todos os dados do cartão. Pagar apagar os dados tem que excluir o arquivo e cria outro.
  SD.remove("teste.txt");
  myFile = SD.open("teste.txt", FILE_WRITE);
  myFile.close();
}

void enviar_dados()
{
  myFile = SD.open("teste.txt");
  if (myFile) {
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    myFile.close();
  }
  else
    Serial.println("Nao pude abrir o arquivo.");
}

void loop() {
  // Aqui poderia ser colocada uma rotina para leitura de sensores e entao os dados
  // poderiam ser gravados, precedendo-os pelo timestamp. Ai esta seu data logger! 
}
