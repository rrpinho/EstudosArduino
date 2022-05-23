/* Enviando dados do PC para o ArduínoVamos piscar um LED de forma proporcional ao valor recebido a partir do PC */
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
   if ( caractere == 'a' ) {  // Verificar se o caractere ASCII é um dígito entre 0 e 9
     piscando = 100;
    }
   else if ( caractere == 'b' ) {  // Verificar se o caractere ASCII é um dígito entre 0 e 9
      piscando = 500;
   }
   else if ( caractere == 'c' ) {  // Verificar se o caractere ASCII é um dígito entre 0 e 9
    piscando = 1000;
    }
  }
  pisca(); // Chamando a função blink(), que será declarada abaixo.
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
