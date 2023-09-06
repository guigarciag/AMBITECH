#include <Wire.h> //INCLUSÃO DA BIBLIOTECA
#include "RTClib.h" //INCLUSÃO DA BIBLIOTECA
#include <LiquidCrystal.h> //INCLUSÃO DA BIBLIOTECA
#include "dht.h" //INCLUSÃO DA BIBLIOTECA
#include <EEPROM.h>

const int pinoDHT11 = A1;

RTC_DS3231 rtc; //OBJETO DO TIPO RTC_DS3231
dht DHT;

LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2); 

int redPin = 9; 
int greenPin = 13; 
int buzzer = 8; 

int contador = 0;
int luminosidadeTotal = 0;
float umidadeTotal = 0;
float temperaturaTotal = 0;
int luminosidadeMedia = 0;
float umidadeMedia = 0;
float temperaturaMedia = 0;
DateTime now;

void setup() {

    ledVerdeEBuzzerOff(); 
    pinMode(13, OUTPUT);
    pinMode(9,OUTPUT);

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
  lcd.setCursor(3,0);
  lcd.print("AMBITECH");
  delay(3000);
  
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print(" SEU AMBIENTE,NOSSA TECNOLOGIA!!!");

  for(int posi_LCD = 0; posi_LCD < 18; posi_LCD ++)
  {

    
    lcd.setCursor(16,1);
    lcd.scrollDisplayLeft();  //Essa é a função que faz as letras se deslocarem

    delay(500);         // Quanto menor o tempo, mais rápido será o deslocamento
        if(posi_LCD == 17)
    {
      break;
    }
  }
  
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
    Serial.println();
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
    caracteres = caracteres + "L" + String(luminosidade);
  }
  if(umidade<30 || umidade>70){
    caracteres = caracteres + "U" + String(umidade, 0);
  }
  if(temperatura<15 || temperatura > 25){
    caracteres = caracteres + "T" + String(temperatura, 0);
  }
  if(caracteres.length() > 0){
    ledVermelhoEBuzzerOn(); 
    alerta(caracteres);
  }
  else{
    ledVerdeEBuzzerOff();  
    
    }
  
}

void alerta(String caracteres){

  now = rtc.now();
  String mensagem = "";
  mensagem = String(now.day())+ "/" + String(now.month())+ "/" + String(now.year())+ " - " + String(now.hour())+ ":" + String(now.minute()) + " - " + caracteres;
  //Serial.print(mensagem);
  //
  Serial.println();
  guardaEeprom(mensagem);
  //Serial.println("alerta");
  ; 
  //Serial.println("alerta1");
}

void guardaEeprom(String mensagem){
    for (int i = 0; i < mensagem.length(); i++){
       EEPROM.write(0,mensagem[i]);
       Serial.print(mensagem[i]);
    }
    for (int i = 0; i < mensagem.length(); i++){
    
      Serial.print(char(EEPROM.read(i)));
    }
}

void ledVermelhoEBuzzerOn () { 
  digitalWrite(greenPin, LOW); 
  digitalWrite(redPin, HIGH); 
  tone(buzzer,1500); 
  delay(1000); // ver questão do dellay 
  noTone(buzzer); 
} 

  

void ledVerdeEBuzzerOff () 
{ 
  noTone(buzzer); 
  delay(500); // ver questão do dellay 
  digitalWrite(greenPin, HIGH); 
  digitalWrite(redPin, LOW); 
} 
