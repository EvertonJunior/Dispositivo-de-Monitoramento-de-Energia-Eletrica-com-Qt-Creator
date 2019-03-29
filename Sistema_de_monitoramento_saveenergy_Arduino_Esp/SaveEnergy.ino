// =============================================================================================================
// --- Bibliotecas utilizadas ---
#include <Wire.h>                 //Biblioteca para o módulo I2C
#include <LiquidCrystal_I2C.h>    //Biblioteca para o display LCD com módulo I2C
#include "EmonLib.h"              //Biblioteca para o Sensor de corrente SCT-013

// =============================================================================================================
// --- Hardware do LCD ---

LiquidCrystal_I2C lcd(0x27,
                      2,
                      1,
                      0,
                      4,
                      5,
                      6,
                      7,
                      3,
                      POSITIVE);
// =============================================================================================================

EnergyMonitor Sensor_SCT;   //cria um objeto para o Sensor de corrente

// =============================================================================================================
//--- Constanto utilizadas no projeto ---

#define      rede        220  //tensão da rede elétrica utilizada
String Potencia = "";
String Eletrodomestico;
int Potencia_aux;
int POTENCIA;


// =============================================================================================================

// --- Mapeamento de Hardware ---

#define     pino_SCT      A1
#define     pino_LEDR     6
#define     pino_LEDG     5

// =============================================================================================================


// --- Configurações Iniciais ---
void setup()
{
  pinMode(pino_SCT, INPUT);
  pinMode(pino_LEDR, OUTPUT);
  pinMode(pino_LEDG, OUTPUT);

  Serial.begin(115200);
  lcd.begin(16, 2);
  lcd.clear();
  
  Sensor_SCT.current(pino_SCT, 9);

  
  digitalWrite(pino_LEDR, LOW);
  digitalWrite(pino_LEDG, LOW);


} // end setup

// =============================================================================================================

// --- Loop Infinito ---
void loop()
{
  double Irms;
  Irms = Sensor_SCT.calcIrms(1480);

  //  Serial.print("Corrente = ");
  //  Serial.print(Irms);
  //  Serial.println(" A");
  //
  //  Serial.print("Potencia = ");
  //  Serial.print(Irms*rede);
  //  Serial.println(" W");
  //  Serial.println("********************");


  lcd.setBacklight(HIGH);
  lcd.setCursor(0, 0);
  lcd.print("Corrente(A):");
  lcd.setCursor(12, 0);
  lcd.print(Irms);

  lcd.setCursor(0, 1);
  lcd.print("Pot(W):");
  lcd.setCursor(11, 1);
  lcd.print(Irms * rede, 1);

// =============================================================================================================
//  --- Comunicação com a aplicação QT ---

  if (Serial.available() > 0)
  {
    String Dados = Serial.readStringUntil('\n');
    if (Dados.startsWith("{") && Dados.endsWith("}"))
    {
      if (Dados.indexOf("POTENCIA:") != -1)
      {
        Potencia = "";
        for (int i = 10; i < Dados.length() - 1; i++)
        {
          Potencia = Potencia + Dados[i];
        }
      }
    }
  }
  
// =============================================================================================================
//  --- Adequação e manipulação de variáveis ---


  POTENCIA = atoi(Potencia.c_str());        //Tranforma a Potencia de String para inteiro e armazena em POTENCIA


  if (POTENCIA == 1230) Eletrodomestico = "Ferro Eletrico";
  if (POTENCIA == 9)Eletrodomestico = "Luminaria";
  if (POTENCIA == 18)Eletrodomestico = "Ferro de Solda";
  if (POTENCIA == 1200)Eletrodomestico = "Forno Microondas";
  if (POTENCIA == 100)Eletrodomestico = "Ventilador";
  if (POTENCIA == 250)Eletrodomestico = "Geladeira Simples" ;
  if (POTENCIA == 600)Eletrodomestico = "Aspirador de Po";
  if (POTENCIA == 200)Eletrodomestico = "Espremedor de Frutas";
  if (POTENCIA == 1600)Eletrodomestico = "Secador de Cabelo";
  if (POTENCIA == 1570)Eletrodomestico = "Prancha de Cabelo";
  if (POTENCIA == 1000)Eletrodomestico = "Maquina de Lavar Roupa";
  if (POTENCIA == 500)Eletrodomestico = "Geladeira Duplex";
  if (POTENCIA == 1500)Eletrodomestico = "Maquina de Lavar Louça";
  if (POTENCIA == 1400)Eletrodomestico = "Condicionador de Ar" ;
  if (POTENCIA == 1300)Eletrodomestico = "Cortador de Grama";
  if (POTENCIA == 3000)Eletrodomestico = "Fogão Elétrico 2 Bocas" ;
  if (POTENCIA == 6000)Eletrodomestico = "Fogão Elétrico 4 Bocas" ;
  if (POTENCIA == 127)Eletrodomestico = "Maquina de Costura";
  else {};


  Potencia_aux = Irms * rede;   //Variável destinada à comparação de Potencia


  while (Eletrodomestico == "Ferro Eletrico")
  {
    Irms = Sensor_SCT.calcIrms(1480);
    Potencia_aux = Irms * rede;

    lcd.setCursor(0, 1);
    lcd.print("Pot(W):");
    lcd.setCursor(11, 1);
    lcd.print(Irms * rede, 1);
    
    if (Potencia_aux > 1230)
    {
      digitalWrite(pino_LEDR, HIGH);
      digitalWrite(pino_LEDG, LOW);
    }
    if (Potencia_aux < 1230 || Potencia_aux == 1230)
    {
      digitalWrite(pino_LEDR, LOW);
      digitalWrite(pino_LEDG, HIGH);
    }
  }
      digitalWrite(pino_LEDR, LOW);
      digitalWrite(pino_LEDG, LOW);
  while (Eletrodomestico == "Luminaria")
  {
    Irms = Sensor_SCT.calcIrms(1480);

    Potencia_aux = Irms * rede;

    lcd.setCursor(0, 1);
    lcd.print("Pot(W):");
    lcd.setCursor(11, 1);
    lcd.print(Irms * rede, 1);
    
    if(Potencia_aux > 9)
    {
      digitalWrite(pino_LEDR, HIGH);
      digitalWrite(pino_LEDG, LOW);
    }
    if(Potencia_aux < 9 || Potencia_aux == 9)
    {
      digitalWrite(pino_LEDR, LOW);
      digitalWrite(pino_LEDG, HIGH);
    }
  }

      digitalWrite(pino_LEDR, LOW);
      digitalWrite(pino_LEDG, LOW);
      
  while (Eletrodomestico == "Ferro de Solda")
  {
    Irms = Sensor_SCT.calcIrms(1480);
    Potencia_aux = Irms * rede;

    lcd.setCursor(0, 1);
    lcd.print("Pot(W):");
    lcd.setCursor(11, 1);
    lcd.print(Irms * rede, 1);
    
    if (Potencia_aux > 18)
    {
      digitalWrite(pino_LEDR, HIGH);
      digitalWrite(pino_LEDG, LOW);
    }
    if (Potencia_aux < 18 || Potencia_aux == 18) 
    {
      digitalWrite(pino_LEDR, LOW);
      digitalWrite(pino_LEDG, HIGH);
    }
  }
      digitalWrite(pino_LEDR, LOW);
      digitalWrite(pino_LEDG, LOW);
      
  while (Eletrodomestico == "Forno Microondas")
  {
    Irms = Sensor_SCT.calcIrms(1480);
    Potencia_aux = Irms * rede;

    lcd.setCursor(0, 1);
    lcd.print("Pot(W):");
    lcd.setCursor(11, 1);
    lcd.print(Irms * rede, 1);
    
    if (Potencia_aux > 1200) 
    {
      digitalWrite(pino_LEDR, HIGH);
      digitalWrite(pino_LEDG, LOW);      
    }
    if (Potencia_aux < 1200 || Potencia_aux == 1200)
    {
      digitalWrite(pino_LEDR, LOW);
      digitalWrite(pino_LEDG, HIGH); 
    }
  }
      digitalWrite(pino_LEDR, LOW);
      digitalWrite(pino_LEDG, LOW);
        
  while (Eletrodomestico == "Ventilador")
  {
    Irms = Sensor_SCT.calcIrms(1480);
    Potencia_aux = Irms * rede;

    lcd.setCursor(0, 1);
    lcd.print("Pot(W):");
    lcd.setCursor(11, 1);
    lcd.print(Irms * rede, 1);
       
    if (Potencia_aux > 100) 
    {
      digitalWrite(pino_LEDR, HIGH);
      digitalWrite(pino_LEDG, LOW);
    }
    if (Potencia_aux < 100 || Potencia_aux == 100) 
    {
      digitalWrite(pino_LEDR, HIGH);
      digitalWrite(pino_LEDG, LOW);
    }
  }
      digitalWrite(pino_LEDR, LOW);
      digitalWrite(pino_LEDG, LOW);
/*


  
  if (Eletrodomestico == "Geladeira Simples")
  {
    if (Potencia_aux > 250) tone (pino_Buzzer, 440, 1000);
    if (Potencia_aux < 250 || Potencia_aux == 250) noTone(pino_Buzzer);
  }
  if (Eletrodomestico == "Aspirador de Po")
  {
    if (Potencia_aux > 600) tone (pino_Buzzer, 440, 1000);
    if (Potencia_aux < 600 || Potencia_aux == 600) noTone(pino_Buzzer);
  }
  if (Eletrodomestico == "Espremedor de Frutas")
  {
    if (Potencia_aux > 200) tone (pino_Buzzer, 440, 1000);
    if (Potencia_aux < 200 || Potencia_aux == 200) noTone(pino_Buzzer);
  }
  if (Eletrodomestico == "Secador de Cabelo")
  {
    if (Potencia_aux > 1600) tone (pino_Buzzer, 440, 1000);
    if (Potencia_aux < 1600 || Potencia_aux == 1600) noTone(pino_Buzzer);
  }
  if (Eletrodomestico == "Secador de Cabelo")
  {
    if (Potencia_aux > 1570) tone (pino_Buzzer, 440, 1000);
    if (Potencia_aux < 1570 || Potencia_aux == 1570) noTone(pino_Buzzer);
  }
  if (Eletrodomestico == "Maquina de Lavar Roupa")
  {
    if (Potencia_aux > 1000) tone (pino_Buzzer, 440, 1000);
    if (Potencia_aux < 1000 || Potencia_aux == 1000) noTone(pino_Buzzer);
  }
  if (Eletrodomestico == "Geladeira Duplex")
  {
    if (Potencia_aux > 500) tone (pino_Buzzer, 440, 1000);
    if (Potencia_aux < 500 || Potencia_aux == 500) noTone(pino_Buzzer);
  }
  if (Eletrodomestico == "Maquina de Lavar Louça")
  {
    if (Potencia_aux > 1500) tone (pino_Buzzer, 440, 1000);
    if (Potencia_aux < 1500 || Potencia_aux == 1500) noTone(pino_Buzzer);
  }
  if (Eletrodomestico == "Condicionador de Ar")
  {
    if (Potencia_aux > 1400) tone (pino_Buzzer, 440, 1000);
    if (Potencia_aux < 1400 || Potencia_aux == 1400) noTone(pino_Buzzer);
  }
  if (Eletrodomestico == "Cortador de Grama")
  {
    if (Potencia_aux > 1300) tone (pino_Buzzer, 440, 1000);
    if (Potencia_aux < 1300 || Potencia_aux == 1300) noTone(pino_Buzzer);
  }
  if (Eletrodomestico == "Fogão Elétrico 2 Bocas")
  {
    if (Potencia_aux > 3000) tone (pino_Buzzer, 440, 1000);
    if (Potencia_aux < 3000 || Potencia_aux == 3000) noTone(pino_Buzzer);
  }
  if (Eletrodomestico == "Fogão Elétrico 4 Bocas")
  {
    if (Potencia_aux > 6000) tone (pino_Buzzer, 440, 1000);
    if (Potencia_aux < 6000 || Potencia_aux == 6000) noTone(pino_Buzzer);
  }
  if (Eletrodomestico == "Maquina de Costura")
  {
    if (Potencia_aux > 100) tone (pino_Buzzer, 440, 1000);
    if (Potencia_aux < 100 || Potencia_aux == 100) noTone(pino_Buzzer);
  }
*/

} // end loop
// =============================================================================================================
