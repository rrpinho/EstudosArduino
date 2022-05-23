#define CW  0                     //Sentido ClockWise
#define CCW 1                   //Sentido Counter ClockWise

#define MOTOR_A 2
#define MOTOR_B 4

const byte PWMA = 3;                  // PWM control (speed) for motor A
const byte PWMB = 11;                 // PWM control (speed) for motor B
const byte DIRA = 12;                 // Direction control for motor A
const byte DIRB = 13;                 // Direction control for motor B


void setup() {
        setupArdumoto();
}

void loop() {
  // Mueve solo el Motor A, a diferentes velocidades
      driveArdumoto(MOTOR_A, CCW, 255); // Motor A, avance a toda maquina
      delay(4000);  // Motor A girará 1 segundo
      
      driveArdumoto(MOTOR_A, CW, 127);  // Motor A, avance a media potencia
      delay(4000);   
      
      stopArdumoto(MOTOR_A);  // Parar Motor A
      delay(1000);

     // Mueve solo el Motor B a varias velocidades
     driveArdumoto(MOTOR_B, CCW, 255); // Motor B, retoceso a toda maquina
     delay(4000);  
     driveArdumoto(MOTOR_B, CW, 127);  // Motor B, avance media
     delay(4000);  

     stopArdumoto(MOTOR_B);  // Para Motor B
     delay(1000);

     // Ahora girar ambos motores
     driveArdumoto(MOTOR_A, CW, 255);  // Motor A avance toda
     driveArdumoto(MOTOR_B, CW, 255);  // Motor B avance toda
     delay(4000);  

     stopArdumoto(MOTOR_A);  // Parar Motor A
     stopArdumoto(MOTOR_B);  // Para Motor B
     delay(1000);
     

     // Ahora retroceso a media maquina
     driveArdumoto(MOTOR_A, CCW, 127);  // Motor A at max speed.
     driveArdumoto(MOTOR_B, CCW, 127);  // Motor B at max speed.
     delay(4000);
}

void driveArdumoto(byte motor, byte dir, byte spd)
   {   
    if (motor == MOTOR_A)
         {   digitalWrite(DIRA, dir);
             analogWrite(PWMA, spd);
         }
      else if (motor == MOTOR_B)
         {  digitalWrite(DIRB, dir);
            analogWrite(PWMB, spd);
         }
   }

void stopArdumoto(byte motor)
  {  
    driveArdumoto(motor, 0, 0); 
  }

void setupArdumoto()
   {    pinMode(PWMA, OUTPUT);
        pinMode(PWMB, OUTPUT);
        pinMode(DIRA, OUTPUT);
        pinMode(DIRB, OUTPUT);

        digitalWrite(PWMA, LOW);
        digitalWrite(PWMB, LOW);
        digitalWrite(DIRA, LOW);
        digitalWrite(DIRB, LOW);
   }
