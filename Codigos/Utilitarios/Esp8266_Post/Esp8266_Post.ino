#include <SoftwareSerial.h>

SoftwareSerial ESP8266(10, 11); // RX, TX.
String cadena = ""; //variavel para verificar a resposta da ESP8266.

int RGB[3] = {7, 6, 5};
int RGB2[3] = {4, 3, 2};
bool estadoRGB;

void setup() {
    
  for (int i = 0; i < 3; i++){
    pinMode(RGB[i], OUTPUT);
    pinMode(RGB2[i], OUTPUT);
  }
  
  mudarCor(RGB, "Verde", true);
  mudarCor(RGB2, "Verde", true);
  
  Serial.begin(9600);
  ESP8266.begin(9600);
  ESP8266.setTimeout(2000);
  
  configuracao_ESP8266();
  
  delay(1000);
}

void loop() 
{  
  configuracao_ESP8266();
  conectadoInternet();
  enviarDadosServidor();
  
  delay(6000);
}

bool configuracao_ESP8266()
{ //Configurando os parametros da ESP82668266
  bool teste_esp = false;

  do
  {
    ESP8266.println("AT");  //Testando se a ESP82668266 estб concectada ao arduino.
    if (ESP8266.find("OK"))
    {
      Serial.println("Resposta AT correto");
      mudarCor(RGB, "Verde", true);
      mudarCor(RGB2, "Verde", true);
      teste_esp = true;
    }
    else
    {
      Serial.println("Erro na ESP8266, sem resposta do AT");
      mudarCor(RGB, "Azul", true);
      mudarCor(RGB2, "Azul", true);
    }
  }while (teste_esp == false);

  ESP8266.println("AT+CWMODE=1"); //Selecionando uma porta de rede para a ESP82668266
  if (ESP8266.find("OK"))
    Serial.println("ESP82668266 em modo de estacao de rede");

  return teste_esp;
}

bool conectadoInternet()
{
  bool teste_rede = false;

  do
  {
    ESP8266.println("AT+CWJAP=\"Usa o 3G bb\",\"pureequipe\""); //Login e senha do Wi-fi local
    Serial.println("Conectando a rede...");
    ESP8266.setTimeout(10000);
    if (ESP8266.find("OK"))
    {
      Serial.println("Wifi Conectado");
      mudarCor(RGB, "Verde", true);
      mudarCor(RGB2, "Verde", true);
      teste_rede = true;
    }
    else
    {
      Serial.println("Erro ao conectar com a rede");
      mudarCor(RGB, "Vermelho", true);
      mudarCor(RGB2, "Vermelho", true);
    }

    ESP8266.setTimeout(2000);
    
  }while (teste_rede == false);

  ESP8266.println("AT+CIPMUX=0"); //Desabilitando multiplas conexoes
  if (ESP8266.find("OK"))
    Serial.println("Multiplas conexoes desabilitadas");
    
  return teste_rede;
}

int enviarDadosServidor()
{
  //Ordem: Módulo > dia > mes > ano > hora > minuto > segundo > temperatura > ph > turbidez
  
  ESP8266.println("AT+CIPSTART=\"TCP\",\"www.pythonanywhere.com\",80"); //Alterar o servidor

  if ( ESP8266.find("OK") )
  {
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println("ESP8266 conectado com o servidor...");
    
    mudarCor(RGB, "Verde", true);
    mudarCor(RGB2, "Verde", true);

    String dados = "campo1=12&campo2=34";
    String peticaoHTTP = "POST /entradadadosteste HTTP/1.1\n";
    peticaoHTTP = peticaoHTTP + "Host: pureequipe.pythonanywhere.com\n";
    peticaoHTTP = peticaoHTTP + "Cache-Control: no-cache\n";
    peticaoHTTP = peticaoHTTP + "Content-Type: application/x-www-form-urlencoded\n";
    peticaoHTTP = peticaoHTTP + "Content-Length: ";
    peticaoHTTP = peticaoHTTP + String(dados.length());
    peticaoHTTP = peticaoHTTP + "\n\n";
    peticaoHTTP = peticaoHTTP + dados;
    peticaoHTTP = peticaoHTTP + "\n";
    Serial.println(peticaoHTTP);

    mudarCor(RGB, "Branco", true);
    mudarCor(RGB2, "Branco", true);
    
    ESP8266.print("AT+CIPSEND=");
    ESP8266.println(peticaoHTTP.length());

    if (ESP8266.find(">"))
    {
      Serial.println("Enviando peticao HTTP . . .");
      ESP8266.println(peticaoHTTP);
      
      if ( ESP8266.find("SEND OK"))
      {
        Serial.println("peticao HTTP enviada:");
        mudarCor(RGB, "Branco", true);
        mudarCor(RGB2, "Branco", true);
        Serial.println();
        Serial.println(peticaoHTTP);
        Serial.println("Esperando resposta...");

        boolean fim_resposta = false;
        long tempo_inicio = millis();
        cadena = "";

        while (fim_resposta == false)
        {
          while (ESP8266.available() > 0)
          {
            char c = ESP8266.read();
            Serial.write(c);
            cadena.concat(c);
          }

          if (cadena.length() > 500)
          {
            Serial.println("A resposta excedeu o tamanho maximo");
            ESP8266.println("AT+CIPCLOSE");
            if ( ESP8266.find("OK"))
              Serial.println("Conexao finalizada.");
            fim_resposta = true;
          }
          
          if ((millis() - tempo_inicio) > 10000)
          {
            Serial.println("Tempo de espera esgotado");
            ESP8266.println("AT+CIPCLOSE");
            if ( ESP8266.find("OK"))
              Serial.println("Conexao finalizada");
            fim_resposta = true;
          }

          if (cadena.indexOf("CLOSED") > 0)
          {
            Serial.println();
            Serial.println("Cadena recebida corretamente, conexao finalizada");
            fim_resposta = true;
          }
        }
      }
      else
      {
        Serial.println("Nao conseguiu enviar a peticao HTTP...");
        mudarCor(RGB, "Amarelo", true);
        mudarCor(RGB2, "Amarelo", true);
        return 1;
      }
    }
  }
  else
  {
    Serial.println("Nao conseguiu se conectar com o servidor");
    mudarCor(RGB, "Purpura", true);
    mudarCor(RGB2, "Purpura", true);
    return 1;
  }
  
  mudarCor(RGB, "Verde", true);
  mudarCor(RGB2, "Verde", true);
  return 0;
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
