#include <Wire.h> //INCLUSÃO DA BIBLIOTECA
#include "RTClib.h" //INCLUSÃO DA BIBLIOTECA
#include <LiquidCrystal.h> //INCLUSÃO DA BIBLIOTECA
#include <DHT11.h> //INCLUSÃO DA BIBLIOTECA

LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2); 

int contador = 0;
int luminosidadeTotal = 0;
int umidadeTotal = 0;
int temperaturaTotal = 0;

void setup() {
  byte outputPin[] = {};
  byte inputPin[] = {};
  Serial.begin(9600); //COMUNICAÇÃO ARDUINO PROMPT
}

void loop() {
  int luminosidade = calculaLuminosidade(); //VALOR DA LUMINOSIDADE EM %
  int umidade = calculaUmidade(); //VALOR DA UMIDADE
  delay(10000);
  contador++;
  if(contador == 6){
    conferir();
  }
  Serial.println(luminosidade); //PRINTAR NO PROMPT
}

int calculaLuminosidade(){
  int sensorValue = analogRead(A0); //LÊ O SINAL ANALÓGICO
  int luminosity = map(sensorValue,0,1023,0,100); //RELAÇÃO DE TENSÃO
  luminosidadeTotal = luminosidadeTotal + luminosity;
  return luminosity;
}

int calculaUmidade(){
  
}

int calcularMedia(int valores){
  
}

bool conferir(){
  luminosidadeMedia = calcularMedia(luminosidadeTotal)
  luminosidadeMedia = 0;
  contador = 0;
}
