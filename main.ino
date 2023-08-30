#include <Wire.h> //INCLUSÃO DA BIBLIOTECA
#include "RTClib.h" //INCLUSÃO DA BIBLIOTECA
#include <LiquidCrystal.h> //INCLUSÃO DA BIBLIOTECA
#include "dht.h" //INCLUSÃO DA BIBLIOTECA
#include <EEPROM.h>

const int pinoDHT11 = A1;


RTC_DS3231 rtc; //OBJETO DO TIPO RTC_DS3231
dht DHT;


LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2); 

int contador = 0;
int luminosidadeTotal = 0;
int umidadeTotal = 0;
int temperaturaTotal = 0;
int luminosidadeMedia = 0;
int umidadeMedia = 0;
int temperaturaMedia = 0;
int enderecoBase = EEPROM.read(0);
DateTime now;

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
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("CALMA AMIGAO, TA");
  lcd.setCursor(0,1);
  lcd.print("LENDO PO");
}

void loop() {
  
  calculaLuminosidade(); //VALOR DA LUMINOSIDADE EM %
  calculaUmidade(); //VALOR DA UMIDADE
  calculaTemperatura();
  delay(10000);
  contador++;
  if(contador == 2
  ){
    DHT.read11(pinoDHT11); //LÊ AS INFORMAÇÕES DO SENSOR
    lcd.clear();
    now = rtc.now();
    luminosidadeMedia = calcularMedia(luminosidadeTotal);
    umidadeMedia = calcularMedia(umidadeTotal);
    temperaturaMedia = calcularMedia(temperaturaTotal);
    luminosidadeTotal = 0;
    umidadeTotal = 0;
    temperaturaTotal = 0;
    lcd.setCursor(0,0);
    lcd.print(String(now.day()) + "/" + String(now.month()) + "/" + String(now.year()));
    lcd.setCursor(0,1);
    lcd.print("L:" + String(luminosidadeMedia) + "%" + " U:" + String(umidadeMedia) + "% " + "T:" + String(temperaturaMedia)) + "°C";
    conferir(luminosidadeMedia, umidadeMedia, temperaturaMedia);
    Serial.println("L:" + String(luminosidadeMedia));
    Serial.println(" U:" + String(umidadeMedia));
    Serial.println(" T:" + String(temperaturaMedia));
    }
  }
  

void calculaLuminosidade(){
  int sensorValue = analogRead(A0); //LÊ O SINAL ANALÓGICO
  int luminosity = map(sensorValue,0,1023,0,100); //RELAÇÃO DE TENSÃO
  luminosidadeTotal = luminosidadeTotal + luminosity;
}

void calculaUmidade(){
  float humidity = DHT.humidity;
  umidadeTotal  = umidadeTotal + humidity;
}

void calculaTemperatura(){
  float temperature = DHT.temperature;
  temperaturaTotal = temperaturaTotal + temperature;
}

int calcularMedia(int valor){
  return valor/6;
}

void conferir(int luminosidade, int umidade, int temperatura){
  contador = 0;
  luminosidadeTotal = 0;
  temperaturaTotal = 0;
  umidadeTotal = 0;
  String caracteres;
  if(0< luminosidade< 30){
    caracteres = "L" + luminosidade;
  }
  if(30< umidade< 50){
    caracteres += "U" + umidade;
  }
  if(15< temperatura< 25){
    caracteres += "T" + temperatura;
  }
  if(caracteres.length() > 0){
    alerta(caracteres);
  }
}

void alerta(String caracteres){
  now = rtc.now();
  String mensagem = String(now.day()) + String(now.month()) + String(now.year()) + caracteres;
  guardaEeprom(mensagem);
  ascendeLed();
  alertaSonoro();
}

void guardaEeprom(String mensagem){
  if (mensagem.length()>EEPROM.length() || (enderecoBase+mensagem.length()) >EEPROM.length() ){
    Serial.println ("A sua String não cabe na EEPROM");
  }
  else{
    for (int i = 0 + 1; i<mensagem.length(); i++){
       EEPROM.write(enderecoBase,mensagem[i]);
       enderecoBase++;
    }
    EEPROM.write(enderecoBase,'_');
    EEPROM.write(0,enderecoBase);
  }
}

void ascendeLed(){

}

void alertaSonoro(){

  
}
