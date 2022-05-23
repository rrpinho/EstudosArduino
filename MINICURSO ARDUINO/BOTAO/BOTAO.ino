
void setup() {  
  //definindo os pinos digitais como pinos de saída.
  pinMode(5,OUTPUT);    
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);  
  pinMode(8,INPUT_PULLUP);
}
 
//o método loop é executado repetidamente enquanto o 
//arduino estiver ligado.
void loop() { 
  int botao = digitalRead(8);
  if(botao == HIGH){
  digitalWrite(5,HIGH);  //acende o led vermelho
  delay(500);          //espera 4 segundos
  digitalWrite(5,LOW); //apaga o led vermelho
  digitalWrite(6,HIGH); //acende o led verde
  delay(500);          //espera 2 segundos
  digitalWrite(6,LOW); //apaga o led verde
  digitalWrite(7,HIGH); //acende o led amarelo
  delay(500);          //espera 1 segundo
  digitalWrite(7,LOW); //apaga o led amarelo
  }
  else{
  digitalWrite(5,HIGH);  //acende o led vermelho
  delay(50);          //espera 4 segundos
  digitalWrite(5,LOW); //apaga o led vermelho
  digitalWrite(6,HIGH); //acende o led verde
  delay(50);          //espera 2 segundos
  digitalWrite(6,LOW); //apaga o led verde
  digitalWrite(7,HIGH); //acende o led amarelo
  delay(50);          //espera 1 segundo
  digitalWrite(7,LOW); //apaga o led amarelo
    } 
   
}

