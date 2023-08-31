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
float umidadeTotal = 0;
float temperaturaTotal = 0;
int luminosidadeMedia = 0;
float umidadeMedia = 0;
float temperaturaMedia = 0;
DateTime now;

void setup() {
    pinMode(13, OUTPUT);
  
  /***
    Iterate through each byte of the EEPROM storage.

    Larger AVR processors have larger EEPROM sizes, E.g:
    - Arduno Duemilanove: 512b EEPROM storage.
    - Arduino Uno:        1kb EEPROM storage.
    - Arduino Mega:       4kb EEPROM storage.

    Rather than hard-coding the length, you should use the pre-provided length function.
    This will make your code portable to all AVR processors.
  ***/

  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }

  // turn the LED on when we're done
  digitalWrite(13, HIGH);
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
  DHT.read11(pinoDHT11);
  calculaLuminosidade(); //VALOR DA LUMINOSIDADE EM %
  calculaUmidade(); //VALOR DA UMIDADE
  calculaTemperatura();
  delay(1000);
  contador++;
  if(contador == 2)//ALTERAR DEPOIS DE TESTES
  {
    lcd.clear();
    now = rtc.now();
    luminosidadeMedia = calcularMedia(luminosidadeTotal);
    umidadeMedia = calcularMedia(umidadeTotal);
    temperaturaMedia = calcularMedia(temperaturaTotal);
    luminosidadeTotal = 0;
    umidadeTotal = 0;
    temperaturaTotal = 0;
    contador = 0;
    lcd.setCursor(0,0);
    lcd.print(String(now.day()) + "/" + String(now.month()) + "/" + String(now.year()) + " " + String(now.hour()) + ":" + String(now.minute()));
    lcd.setCursor(0,1);
    lcd.print("L:" + String(luminosidadeMedia) + "%" + "U:" + String(umidadeMedia, 0) + "%" + "T:" + String(temperaturaMedia,0) + "C");
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

float calcularMedia(int valor){
  return valor/2;
}

void conferir(int luminosidade, float umidade, float temperatura){
  luminosidadeTotal = 0;
  temperaturaTotal = 0;
  umidadeTotal = 0;
  String caracteres = "";
  if(luminosidade>30){
      Serial.println("Conferir l");
    caracteres = caracteres + "L" + String(luminosidade);
  }
  if(umidade<30 || umidade>50){
      Serial.println("Conferir u");
    caracteres = caracteres + "U" + String(umidade, 0);
  }
  if(temperatura<15 || temperatura > 25){
      Serial.println("Conferir t");
    caracteres = caracteres + "T" + String(temperatura, 0);
  }
  if(caracteres.length() > 0){
    
      Serial.println("Conferir alerta");
    alerta(caracteres);
  }
}

void alerta(String caracteres){
  now = rtc.now();
  String mensagem = "";
  mensagem = String(now.day()) + String(now.month()) + String(now.year()) + String(now.hour()) + String(now.minute()) + caracteres;
  Serial.print(mensagem);
  Serial.println();
  guardaEeprom(mensagem);
  ascendeLed();
  alertaSonoro();
}

void guardaEeprom(String mensagem){
    for (int i = 0; i<mensagem.length(); i++){
       EEPROM.write(0,mensagem[i]);
       Serial.println(mensagem[i]);
    }
    for (int i = 0; mensagem.length(); i++){
    
       Serial.print(char(EEPROM.read(i)));
    }
}


void ascendeLed(){

}

void alertaSonoro(){

  
}
