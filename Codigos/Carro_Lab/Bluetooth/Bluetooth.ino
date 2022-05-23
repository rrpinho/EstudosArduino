#include <SoftwareSerial.h>

SoftwareSerial Bluetooth(6, 7); // RX, TX

#define Horario  0                     //Sentido Horario
#define AntiHorario 1                   //Sentido Anti-Horario

const byte pwmE = 3;                  // Controle PWM (velocidade) para o motor ESQUERDO
const byte pwmD = 11;                 // Controle PWM (velocidade) para o motor DIREITO
const byte dirE = 12;                 // Controle de direção para o motor ESQUERDO
const byte dirD = 13;                 // Controle de direção para o motor DIREITO

void setup() 
{
  Serial.begin(9600);
  Bluetooth.begin(115200);  // The Bluetooth Mate defaults to 115200bps
  Bluetooth.print("$");  // Print three times individually
  Bluetooth.print("$");
  Bluetooth.print("$");  // Enter command mode
  delay(100);  // Short delay, wait for the Mate to send back CMD
  Bluetooth.println("U,9600,N");  // Temporarily Change the baudrate to 9600, no parity
  // 115200 can be too fast at times for NewSoftSerial to relay the data reliably
  Bluetooth.begin(9600);  // Start bluetooth serial at 9600
  setupArdumoto();
}

void loop() 
{
  if( Bluetooth.available() ){
   char leitura = Bluetooth.read();
   Serial.println(leitura);
  
   if( leitura == 'w' )
    {
      
      moverFrente();
      pararMotores();
    }
  
    if( leitura == 's' )
    {
      moverTras();
      pararMotores();
    }
  
   if( leitura == 'd' )
   {
      virarDireita();
      pararMotores();
    }
    
   if( leitura == 'a' )
   {
     virarEsquerda();
     pararMotores();
    }
  }
}

void setupArdumoto() 
{
  pinMode(pwmE, OUTPUT);
  pinMode(pwmD, OUTPUT);
  pinMode(dirE, OUTPUT);
  pinMode(dirD, OUTPUT);

  digitalWrite(pwmE, LOW);
  digitalWrite(pwmD, LOW);
  digitalWrite(dirE, LOW);
  digitalWrite(dirD, LOW);
}

void mover(const byte sentidoE, const byte sentidoD, int velMax)
{
  digitalWrite(dirE, sentidoE);
  digitalWrite(dirD, sentidoD);
  for (int vel = 0; vel <= velMax; vel++)
  {
    analogWrite(pwmE, vel);
    analogWrite(pwmD, vel);
    delay(20);
  }
  if(velMax != 0)
    delay(4000);
}

void girar(const byte sentidoE, const byte sentidoD, int velMaxE, int velMaxD)
{
  digitalWrite(dirE, sentidoE);
  digitalWrite(dirD, sentidoD);
  if(velMaxE > velMaxD)
  {
    for (int vel = 0; vel <= velMaxE; vel++)
    {
      analogWrite(pwmE, vel);
      analogWrite(pwmD, vel*4/5);
      delay(20);
    }
    delay(2000);
  }
  else
  {
    for (int vel = 0; vel <= velMaxD; vel++)
    {
      analogWrite(pwmE, vel*4/5);
      analogWrite(pwmD, vel);
      delay(20);
    }
    delay(1900);
  }
}

void pararMotores()
{  
  mover(Horario, Horario, 0);
  delay(1000);
}

void moverFrente()
{
  mover(AntiHorario, Horario, 30);
}

void moverTras()
{
  mover(Horario, AntiHorario, 30);
}

void virarDireita()
{
  girar(AntiHorario, AntiHorario, 40, 10);
}

void virarEsquerda()
{
  girar(Horario, Horario, 10, 40);
}
