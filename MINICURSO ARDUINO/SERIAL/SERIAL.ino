
int ledPin = 8; // Pino ao qual o LED será conectado
int piscando = 0; // variável para armazenar taxa de “piscagem”
void setup() {
Serial.begin(9600);
pinMode(ledPin, OUTPUT); // Pino 13 será de saída de sinais
}
void loop()
{
  if (Serial.available()) { // Verificar se há caracteres disponíveis
   char caractere = Serial.read(); // Armazena caractere lido
   if ( caractere == 'a' ) {  // Verificar se o caractere é a letra a
     piscando = 100;
    }
   else if ( caractere == 'b' ) {  // Verificar se o caractere é a letra b
      piscando = 500;
   }
   else if ( caractere == 'c' ) {  // Verificar se o caractere é a letra c
    piscando = 1000;
    }
    else if ( caractere == 'x' ) {  // Verificar se o caractere é a letra x
    piscando = 30;
    }
  }
  pisca(); // Chamando a função pisca(), que será declarada abaixo.
}
/* Declarando a função pisca() que fará o LED piscar na taxa deternminada pelo valor armazenado na variável piscando
*/
void pisca()
{
digitalWrite(ledPin, HIGH);
delay(piscando);
digitalWrite(ledPin, LOW);
delay(piscando);
}
