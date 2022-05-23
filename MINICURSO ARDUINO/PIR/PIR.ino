int pirPin = 2; //digital 2

void setup(){
 Serial.begin(9600); 
 pinMode(pirPin, INPUT_PULLUP);
}


void loop(){
  int pirVal = digitalRead(pirPin);

  if(pirVal == LOW){ // Se for detectado movimento
    Serial.println("Movimento detectado"); 
    delay(500); 
  }

}

