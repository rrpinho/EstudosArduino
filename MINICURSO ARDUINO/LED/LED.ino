void setup() {  
  //definindo os pinos digitais como pinos de saída.
  pinMode(5,OUTPUT);    
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
}
 
//o método loop é executado repetidamente enquanto o 
//arduino estiver ligado.
void loop() { 

  digitalWrite(5,HIGH);  //acende o led vermelho
  delay(4000);          //espera 4 segundos
  digitalWrite(5,LOW); //apaga o led vermelho
  digitalWrite(6,HIGH); //acende o led verde
  delay(2000);          //espera 2 segundos
  digitalWrite(6,LOW); //apaga o led verde
  digitalWrite(7,HIGH); //acende o led amarelo
  delay(1000);          //espera 1 segundo
  digitalWrite(7,LOW); //apaga o led amarelo
  
   
}

