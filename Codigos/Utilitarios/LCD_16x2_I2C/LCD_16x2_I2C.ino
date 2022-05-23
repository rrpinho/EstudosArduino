/* 
Link para o site onde tirei o código:
https://www.arduinoecia.com.br/2014/12/modulo-i2c-display-16x2-arduino.html
OBS.: Baixe a bibliotecas lá.
OBS.2: Você vai baixar um arquivo chamado "NewliquidCrystal_1.3.4", quando você extrair
vai aparecer 2 pastas. Uma delas se chama "NewliquidCrystal", você renomeia essa
pasta para "LiquidCrystal_I2C" e cola ela na pasta libraries do arduino na pasta de documentos.
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);
 
void setup()
{
 lcd.begin (16,2);
}
 
void loop()
{
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("Arduino e Cia !!");
  lcd.setCursor(0,1);
  lcd.print("LCD e modulo I2C");
  delay(1000);
  lcd.setBacklight(LOW);
  delay(1000);
}
