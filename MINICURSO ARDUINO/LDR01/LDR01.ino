int portaled = 10;
int portaLDR = A5;

void setup() {
  // put your setup code here, to run once:
 pinMode(portaled, OUTPUT);
 Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
int estado = analogRead(portaLDR);
Serial.println(estado);
if (estado > 300)
{
  digitalWrite(portaled, HIGH);
}
else
{
  digitalWrite(portaled, LOW);
}
}

