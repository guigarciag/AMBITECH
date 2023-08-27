#include <Wire.h> //INCLUSÃO DA BIBLIOTECA
#include "RTClib.h" //INCLUSÃO DA BIBLIOTECA
#include <LiquidCrystal.h> //INCLUSÃO DA BIBLIOTECA
#include <DHT.h> //INCLUSÃO DA BIBLIOTECA
#include <EEPROM.h>

#define DHTPIN A1
#define DHTTYPE DHT11


RTC_DS3231 rtc; //OBJETO DO TIPO RTC_DS3231
DHT dht(DHTPIN, DHTTYPE);


LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2); 

int contador = 0;
int luminosidadeTotal = 0;
int umidadeTotal = 0;
int temperaturaTotal = 0;
int luminosidadeMedia = 0;
int umidadeMedia = 0;
int temperaturaMedia = 0;
int enderecoBase = 0;

void setup() {
  byte outputPin[] = {};
  byte inputPin[] = {};
  Serial.begin(9600); //COMUNICAÇÃO ARDUINO PROMPT
    if(! rtc.begin()) { // SE O RTC NÃO FOR INICIALIZADO, FAZ
    Serial.println("DS3231 não encontrado"); //IMPRIME O TEXTO NO MONITOR SERIAL
    while(1); //SEMPRE ENTRE NO LOOP
  }
  if(rtc.lostPower()){ //SE RTC FOI LIGADO PELA PRIMEIRA VEZ / FICOU SEM ENERGIA / ESGOTOU A BATERIA, FAZ
    Serial.println("DS3231 OK!"); //IMPRIME O TEXTO NO MONITOR SERIAL
    //REMOVA O COMENTÁRIO DE UMA DAS LINHAS ABAIXO PARA INSERIR AS INFORMAÇÕES ATUALIZADAS EM SEU RTC
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //CAPTURA A DATA E HORA EM QUE O SKETCH É COMPILADO
    //rtc.adjust(DateTime(2018, 9, 29, 15, 00, 45)); //(ANO), (MÊS), (DIA), (HORA), (MINUTOS), (SEGUNDOS)
  }
  delay(100); //INTERVALO DE 100 MILISSEGUNDOS
}

void loop() {
  calculaLuminosidade(); //VALOR DA LUMINOSIDADE EM %
  calculaUmidade(); //VALOR DA UMIDADE
  calculaTemperatura();
  delay(10000);
  contador++;
  if(contador == 6){
    luminosidadeMedia = calcularMedia(luminosidadeTotal);
    umidadeMedia = calcularMedia(umidadeTotal);
    temperaturaMedia = calcularMedia(temperaturaTotal);
    if(!conferir(luminosidadeMedia, umidadeMedia, temperaturaMedia)){
      alerta();
    }
  }
  Serial.println(luminosidadeTotal); //PRINTAR NO PROMPT
}

void calculaLuminosidade(){
  int sensorValue = analogRead(A0); //LÊ O SINAL ANALÓGICO
  int luminosity = map(sensorValue,0,1023,0,100); //RELAÇÃO DE TENSÃO
  luminosidadeTotal = luminosidadeTotal + luminosity;
}

void calculaUmidade(){
  float humidity = dht.readHumidity();
  umidadeTotal  = umidadeTotal + humidity;
}

void calculaTemperatura(){
  float temperature = dht.readTemperature();
  temperaturaTotal = temperaturaTotal + temperature;
}

int calcularMedia(int valor){
  return valor/6;
}

bool conferir(int luminosidade, int umidade, int temperatura){
  contador = 0;
  luminosidadeTotal = 0;
  temperaturaTotal = 0;
  umidadeTotal = 0;
  if((0< luminosidade< 30) & (30< umidade< 50) & (15< temperatura< 25)){
    return true;
  }
  else{
    return false;
  }
}

void alerta(){
  DateTime now = rtc.now();
  String mensagem = now.day() + now.month() + now.year();
  guardaEeprom(enderecoBase, mensagem);
  ascendeLed();
}

void guardaEeprom(int enderecoBase, String mensagem){
  if (mensagem.length()>EEPROM.length() || (enderecoBase+mensagem.length()) >EEPROM.length() ){
    Serial.println ("A sua String não cabe na EEPROM");
  }
  else{
    for (int i = 0; i<mensagem.length(); i++){
       EEPROM.write(enderecoBase,mensagem[i]);
       enderecoBase++;
    }
    EEPROM.write(enderecoBase,'_');
  }
}

void ascendeLed(){

}