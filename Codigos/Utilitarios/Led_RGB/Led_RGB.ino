int RGB[3] = {7, 6, 5};
bool estadoRGB;

void setup() 
{
  Serial.begin(9600);
  
  for (int i = 0; i < 3; i++)
    pinMode(RGB[i], OUTPUT);  
}

void loop() 
{
  mudarCor(RGB, "Branco", true);
  delay(500);
  mudarCor(RGB, "Amarelo", true);
  delay(500);
  mudarCor(RGB, "Verde", true);
  delay(500);
  mudarCor(RGB, "Vermelho", true);
  delay(500);
  mudarCor(RGB, "Azul", true);
  delay(500);
  mudarCor(RGB, "Purpura", true);
  delay(500);
  mudarCor(RGB, "Verde", false);
  delay(500);
}

void mudarCor(int RGB[], String cor, bool estadoRGB)
{
  if (estadoRGB)
  {
    if (cor.equalsIgnoreCase("Branco"))
    {
      analogWrite(RGB[0], 255);
      analogWrite(RGB[1], 255);
      analogWrite(RGB[2], 255);
      estadoRGB = false;
    }
    
    if (cor.equalsIgnoreCase("Amarelo"))
    {
      analogWrite(RGB[0], 255);
      analogWrite(RGB[1], 0);
      analogWrite(RGB[2], 255);
      estadoRGB = false;
    }

    if (cor.equalsIgnoreCase("Verde"))
    {
      analogWrite(RGB[0], 0);
      analogWrite(RGB[1], 255);
      analogWrite(RGB[2], 0);
      estadoRGB = false;
    }

    if (cor.equalsIgnoreCase("Vermelho"))
    {
      analogWrite(RGB[0], 255);
      analogWrite(RGB[1], 0);
      analogWrite(RGB[2], 0);
      estadoRGB = false;
    }

    if (cor.equalsIgnoreCase("Azul"))
    {
      analogWrite(RGB[0], 0);
      analogWrite(RGB[1], 0);
      analogWrite(RGB[2], 255);
      estadoRGB = false;
    }

    if (cor.equalsIgnoreCase("Purpura"))
    {
      analogWrite(RGB[0], 255);
      analogWrite(RGB[1], 255);
      analogWrite(RGB[2], 0);
      estadoRGB = false;
    }

  }
  else
  {
    analogWrite(RGB[0], 0);
    analogWrite(RGB[1], 0);
    analogWrite(RGB[2], 0);
    estadoRGB = true;
  }
}
