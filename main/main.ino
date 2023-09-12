#include <Wire.h> //INCLUSÃO DA BIBLIOTECA PARA COMUNICAÇÃO COM A PORTA SDA E SCL
#include "RTClib.h" //INCLUSÃO DA BIBLIOTECA DO REAL TIME CLOCK
#include <LiquidCrystal.h> //INCLUSÃO DA BIBLIOTECA DO LCD
#include "dht.h" //INCLUSÃO DA BIBLIOTECA DHT PARA UTILIZAÇÃO DO SENSOR DE UMIDADE E TEMPERATURA
#include <EEPROM.h> //INCLUSÃO DA BIBLIOTECA EEPROM
#include "pitches.h" //INCLUSÃO DA BIBLIOTECA PARA REPRODUZIR SONS

#define BUZZER_PIN 8 // DEFINIÇÃO DO PINO UTILIZADO PELO BUZZER

int melody[] = //MELODIA INICIAL DA MÚSICA DE INTRODUÇÃO
{ 
  NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, REST,
  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, REST,
  NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, REST,
  NOTE_A4, NOTE_G4, NOTE_A4, REST,
  
  NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, REST,
  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, REST,
  NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, REST,
  NOTE_A4, NOTE_G4, NOTE_A4, REST,
  
  NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, REST,
  NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, REST,
  NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, REST,
  NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, REST,
  
  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, REST,
  NOTE_D5, NOTE_E5, NOTE_A4, REST,
  NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, REST,
  NOTE_C5, NOTE_A4, NOTE_B4, REST,
  
  // NOTE_A4, NOTE_A4,
  // //Repeat of first part
  // NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, REST,
  // NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, REST,
  // NOTE_A4, NOTE_G4, NOTE_A4, REST,
  
  // NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, REST,
  // NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, REST,
  // NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, REST,
  // NOTE_A4, NOTE_G4, NOTE_A4, REST,
  
  // NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, REST,
  // NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, REST,
  // NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, REST,
  // NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, REST,
  
  // NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, REST,
  // NOTE_D5, NOTE_E5, NOTE_A4, REST,
  // NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, REST,
  // NOTE_C5, NOTE_A4, NOTE_B4, REST,
  // //End of Repeat
  
  // NOTE_E5, REST, REST, NOTE_F5, REST, REST,
  // NOTE_E5, NOTE_E5, REST, NOTE_G5, REST, NOTE_E5, NOTE_D5, REST, REST,
  // NOTE_D5, REST, REST, NOTE_C5, REST, REST,
  // NOTE_B4, NOTE_C5, REST, NOTE_B4, REST, NOTE_A4,
  
  // NOTE_E5, REST, REST, NOTE_F5, REST, REST,
  // NOTE_E5, NOTE_E5, REST, NOTE_G5, REST, NOTE_E5, NOTE_D5, REST, REST,
  // NOTE_D5, REST, REST, NOTE_C5, REST, REST,
  // NOTE_B4, NOTE_C5, REST, NOTE_B4, REST, NOTE_A4
};

int durations[] = //DURAÇÃO DAS NOTAS DA MELODIA
{ 
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 8,
  
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 8,
  
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 8, 4, 8,
  
  8, 8, 4, 8, 8,
  4, 8, 4, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 4,
  
  // 4, 8,
  // //Repeat of First Part
  // 8, 8, 4, 8, 8,
  // 8, 8, 4, 8, 8,
  // 8, 8, 4, 8,
  
  // 8, 8, 4, 8, 8,
  // 8, 8, 4, 8, 8,
  // 8, 8, 4, 8, 8,
  // 8, 8, 4, 8,
  
  // 8, 8, 4, 8, 8,
  // 8, 8, 4, 8, 8,
  // 8, 8, 4, 8, 8,
  // 8, 8, 8, 4, 8,
  
  // 8, 8, 4, 8, 8,
  // 4, 8, 4, 8,
  // 8, 8, 4, 8, 8,
  // 8, 8, 4, 4,
  // //End of Repeat
  
  // 4, 8, 4, 4, 8, 4,
  // 8, 8, 8, 8, 8, 8, 8, 8, 4,
  // 4, 8, 4, 4, 8, 4,
  // 8, 8, 8, 8, 8, 2,
  
  // 4, 8, 4, 4, 8, 4,
  // 8, 8, 8, 8, 8, 8, 8, 8, 4,
  // 4, 8, 4, 4, 8, 4,
  // 8, 8, 8, 8, 8, 2
};


const int pinoDHT11 = A1; //DEFINIÇÃO DO PINO UTILIZADO PELO DHT11
dht DHT; //CRIAÇÃO DE VARIÁVEL PARA O DHT
RTC_DS3231 rtc; //OBJETO DO TIPO RTC_DS3231

LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2); //DEFINIÇÃO DAS PORTAS UTILIZADA PELO LCD

int redPin = 9; //PORTA UTILIZADA PELO PINO DO LED VERMELHO
int greenPin = 13; //PORTA UTILIZADA PELO PINO DO LED VERDE

int contador = 0; //CONTADOR UTILIZADO PARA VERIFICAR A MEDIÇÃO
int luminosidadeTotal = 0; //SOMA DOS VALORES DA LUMINOSIDADE NO PERÍODO MEDIDO
float umidadeTotal = 0; //SOMA DOS VALORES DA UMIDADE NO PERÍODO MEDIDO
float temperaturaTotal = 0; //SOMA DOS VALORES DA TEMPERATURA NO PERÍODO MEDIDO
int luminosidadeMedia = 0; //MÉDIA DOS VALORES DA LUMINOSIDADE NO PERÍODO MEDIDO
float umidadeMedia = 0; //MÉDIA DOS VALORES DA UMIDADE NO PERÍODO MEDIDO
float temperaturaMedia = 0; //MÉDIA DOS VALORES DA TEMPERATURA NO PERÍODO MEDIDO
DateTime now; //DECLARAÇÃO DA VARIÁVEL PARA O EXATO INSTANTE DE TEMPO

unsigned long noteDuration = 0; //VARIÁVEL UTILIZADA PARA TOCAR A MÚSICA, MEDINDO A DURAÇÃO DA NOTA
int currentNote = 0; //VARIÁVEL UTILIZADA PARA TOCAR A MÚSICA, VERIFICA A NOTA ATUAL TOCADA
bool isPlayingMusic = true; //VARIÁVEL UTILIZADA PARA TOCAR A MÚSIA, VERIFICA SE A MÚSICA ESTÁ TOCANDO

bool functionExecuted = false; //VARIÁVEL PARA VERIFICAR SE JÁ FOI EXECUTADA UMA FUNÇÃO ESTABELECIDA, PARA EXECUTÁ-LA UMA UNICA VEZ
int previousMillis = millis(); //DEFINE O VALOR ANTERIOR

void setup() 
{
    pinMode(9,OUTPUT); //DEFINE O PINO 9 COMO UM OUTPUT (PINO DO LED VERMELHO)
    pinMode(13, OUTPUT); //DEFINE O PINO 13 COMO UM OUTPUT (PINO DO LED VERDE)
    pinMode(BUZZER_PIN, OUTPUT); //DEFINE O PINO DO BUZZER (PINO 8) COMO UM OUTPUT
    ledVerdeEBuzzerOff(); //CHAMA A FUNÇÃO DE DEIXAR O LED VERDE ACESSO E O BUZZER DESLIGADO

  for (int i = 0 ; i < EEPROM.length() ; i++) //LIMPA TODOS OS DADOS CONTIDOS NA EEPROM ANTERIORMENTE
  { 
    EEPROM.write(i, 0);
  }

  Serial.begin(9600); //ESTABELECE COMUNICAÇÃO ARDUINO PROMPT
  if(!rtc.begin()) 
  { // SE O RTC NÃO FOR INICIALIZADO, ESCREVE UMA INFORMAÇÃO AO USUÁRIO
    Serial.println("DS3231 não encontrado"); //IMPRIME O TEXTO NO MONITOR SERIAL
    while(1); //SEMPRE ENTRE NO LOOP
  }
  if(rtc.lostPower()) //SE RTC FOI LIGADO PELA PRIMEIRA VEZ / FICOU SEM ENERGIA / ESGOTOU A BATERIA, FAZ
  { 
    Serial.println("DS3231 OK!"); //IMPRIME O TEXTO NO MONITOR SERIAL
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //CAPTURA A DATA E HORA EM QUE O SKETCH É COMPILADO
  }

  delay(100); //INTERVALO DE 100 MILISSEGUNDOS  
}


void loop() 
{
  unsigned long currentMillis = millis();

  if(!functionExecuted) //MOSTRAR NO LCD E FAZER ANIMAÇÃO DAS LETRAS SE DESLOCAREM PARA A ESQUERDA
  {
    lcd.begin(16,2); //DELIMITA O LCD
    lcd.clear(); //LIMPA OS DADOS ANTERIORES
    lcd.setCursor(3,0); //SET O PRIMEIRO CARACTER DA PRIMEIRA LINHA
    lcd.print("AMBITECH"); //ESCREVER NO LCD
    delay(3000); //PAUSA
  }

  if (!functionExecuted && (currentMillis - previousMillis > 10)) //MÉTODO ASSÍNCRONO POR MEIO DO MIILIS()
  {
    sonzinManeiro(); //EXECUTA O MÉTODO SONZINMANEIRO() PARA CHAMAR O SOM INICIAL
    previousMillis = currentMillis;
  }
  if(!functionExecuted)
  {
    lcd.clear(); //LIMPA A TELA
    lcd.setCursor(0,1); //SET O PRIMEIRO CARACTER DA SEGUNDA LINHA
    lcd.print(" SEU AMBIENTE,NOSSA TECNOLOGIA!!!"); //ESCREVER NO LCD

    for(int posi_LCD = 0; posi_LCD < 18; posi_LCD ++)
    {
      lcd.setCursor(16,1); //SET A POSIÇÃO NA SEGUDA LINHA
      lcd.scrollDisplayLeft();  //FUNÇÃO PARA FAZER AS LETRAS DESLOCAREM
      delay(500); //PAUSA
      if(posi_LCD == 17)
      {
        break;
      }
    }
      functionExecuted = true;
  }
  
  DHT.read11(pinoDHT11); //LÊ O VALOR DO SENSOR DHT
  calculaLuminosidade(); // CALCULA VALOR DA LUMINOSIDADE EM %
  calculaUmidade(); //CALCULA O VALOR DA UMIDADE EM %
  calculaTemperatura(); //CALCULA O VALOR DA TEMPERATURA EM °C
  delay(1000); //TEMPO ESPERADO A CADA MEDIÇÃO
  contador++; //INCREMENTA O VALOR DO CONTADOR
  
  if(contador == 2)//ALTERAR DEPOIS DE TESTES
  {
    lcd.clear(); //LIMPA OS VALORES DA TELA
    now = rtc.now(); //PEGA O VALOR DE DATA ATUAL
    luminosidadeMedia = calcularMedia(luminosidadeTotal); //CALCULA A LUMINOSIDADE MEDIA DO PERÍODO MEDIDO
    umidadeMedia = calcularMedia(umidadeTotal); //CALCULA A UMIDADE MEDIA DO PERÍODO MEDIDO
    temperaturaMedia = calcularMedia(temperaturaTotal); //CALCULA A TEMPERATURA MEDIA DO PERÍODO MEDIDO
    lcd.setCursor(0,0); //COLOCA O CURSOR DO LCD NA POSIÇÃO ORIGINAL
    lcd.print(String(now.day()) + "/" + String(now.month()) + "/" + String(now.year()) + " " + String(now.hour()) + ":" + String(now.minute()));
    //ESCREVE OS VALORES NO LCD
    lcd.setCursor(0,1); //COLOCA O CURSOR NA PRIMEIRA POSIÇÃO DA SEGUNDA LINHA
    lcd.print("L:" + String(luminosidadeMedia) + "%" + "U:" + String(umidadeMedia, 0) + "%" + "T:" + String(temperaturaMedia,0) + "C");
    //ESCREVE OS VALORES NO LCD
    conferir(luminosidadeMedia, umidadeMedia, temperaturaMedia); //CHAMA O MÉTODO PARA CONFERIR OS VALORES MEDIDOS
    Serial.println();
    Serial.println("L:" + String(luminosidadeMedia)); //ESCREVE NO SERIAL MONITOR O VALOR DA LUMINOSIDADE
    Serial.println(" U:" + String(umidadeMedia)); //ESCREVE NO SERIAL MONITOR O VALOR DA UMIDADE
    Serial.println(" T:" + String(temperaturaMedia)); //ESCREVE NO SERIAL MONITOR O VALOR DA TEMPERATURA
    luminosidadeTotal = 0;
    umidadeTotal = 0;
    temperaturaTotal = 0;
    contador = 0;
  }
}


void calculaLuminosidade() //MÉTODO PARA CALCULAR A LUMINOSIDADE POR MEIO DO SENSOR DE LUMINOSIDADE
{ 
  int sensorValue = analogRead(A0); //LÊ O SINAL ANALÓGICO CONECTADA NO SENSOR DE LUMINOSIDADE
  int luminosity = map(sensorValue,0,1023,0,100); //RELAÇÃO DE TENSÃO DE ENTRADA DA PORTA COM A PORCENTAGEM DE LUZ CORRESPONDENTE AO SINAL
  luminosidadeTotal = luminosidadeTotal + luminosity; //SOMA DE TODAS AS MEDIÇÕES DENTRO DE UM INTERVALO
}


void calculaUmidade() //MÉTODO PARA CALCULAR A UMIDADE POR MEIO DO SENSOR DE UMIDADE
{
  float humidity = DHT.humidity; //PROPRIEDADE PARA VERIFICAR A UMIDADE MEDIDA
  umidadeTotal  = umidadeTotal + humidity; //SOMA DE TODAS AS MEDIÇÕES DENTRO DE UM INTERVALO
}


void calculaTemperatura() //MÉTODO PARA CALCULAR A TEMPERATURA POR MEIO DO SENSOR DE TEMPERATURA
{
  float temperature = DHT.temperature; //PROPRIEDADE PARA VERIFICAR A TEMPERATURA MEDIDA
  temperaturaTotal = temperaturaTotal + temperature; //SOMA DE TODAS AS MEDIÇÕES DENTRO DE UM INTERVALO
}


float calcularMedia(int valor) //MÉTODO PARA CALCULAR A MÉDIA DE ACORDO COM AS MEDIÇÕES NO INTERVALO
{
  return valor/contador;
}


void conferir(int luminosidade, float umidade, float temperatura) //MÉTODO COM AS REGRAS PARA VERIFICAR SE OS VALORES ESTÃO DENTRO DO NORMAL OU NÃO
{
  String caracteres = ""; //COLOCARÁ NA STRING OS VALORES INCORRETOS ASSIM COMO QUAL PARÂMETRO MEDIDO ESTÁ ERRADO
  if(luminosidade>30)
  {
    caracteres = caracteres + "L" + String(luminosidade);
  }
  if(umidade<30 || umidade>70)
  {
    caracteres = caracteres + "U" + String(umidade, 0);
  }
  if(temperatura<15 || temperatura > 25)
  {
    caracteres = caracteres + "T" + String(temperatura, 0);
  }
  if(caracteres.length() > 0) //CASO OS VALORES NÃO ESTEJAM CORRETOS, ENTRARÁ NESSA CONDIÇÃO
  {
    ledVermelhoEBuzzerOn(); //CHAMADA DO MÉTODO LEDVERMELHOEBUZZERON()
    alerta(caracteres); //CHAMA O MÉTODO ALERTA()
  }
  else //CASO OS VALORES NÃO ESTEJAM CORRETOS, ENTRARÁ NESSA CONDIÇÃO
  {
    ledVerdeEBuzzerOff(); //CHAMADA DO MÉTODO LEDVERDEEBUZZEROFF()
  }
}


void alerta(String caracteres) //MÉTODO PARA CRIAR A MENSAGEM DE TIMESTAMP PARA ARMAZENAR NA EEPROM
{
  now = rtc.now(); //PEGA O VALOR DA DATA, HORA E MINUTO ATUAL
  String mensagem = "";
  mensagem = String(now.day())+ "/" + String(now.month())+ "/" + String(now.year())+ " - " + String(now.hour())+ ":" + String(now.minute()) + " - " + caracteres;
  Serial.println(" ");
  guardaEeprom(mensagem); //CHAMA O MÉTODO DE GUARDAEEPROM() MANDANDO A MENSAGEM GERADA COMO PARAMETRO
}


void guardaEeprom(String mensagem) //MÉTODO PARA ARMAZENAR OS DADOS FORA DO CORRETO NA MEMÓRIA DA EEPROM
{
    for (int i = 0 ; i < EEPROM.length() ; i++) //LIMPA TODOS OS DADOS CONTIDOS NA EEPROM ANTERIORMENTE
    { 
    EEPROM.write(i, 0);
    }
    for (int i = 0; i < mensagem.length(); i++) 
    {
       EEPROM.write(0,mensagem[i]); //MÉTODO PARA ESCREVER NA MEMÓRIA DA EEPROM
       //Serial.print(mensagem[i]);
    }
    for (int i = 0; i < mensagem.length(); i++)
    {
      Serial.print(char(EEPROM.read(i))); //LER OS DADOS DA EEPROM E MOSTRAR NO SERIAL MONITOR
    }
}


void ledVermelhoEBuzzerOn() //MÉTODO PARA ACENDER O LED VERMELHO E LIGAR O BUZZER, UTILIZADO QUANDO OS PARAMETROS ESTÃO INCORRETOS
{ 
  digitalWrite(greenPin, LOW); //DESLIGA O LED VERDE
  digitalWrite(redPin, HIGH); //LIGA O LED VERMELHO
  tone(BUZZER_PIN,1500); //LIGA O BUZZER
  delay(1000); //DEIXA O BUZZER LIGADO PPOR 1 SEGUNDO
  noTone(BUZZER_PIN); //DESLIGA O BUZZER
}


void ledVerdeEBuzzerOff() //MÉTODO PARA ACENDER O LED VERDE, UTILIZADO QUANDO OS PARAMETROS ESTÃO CORRETOS
{ 
  noTone(BUZZER_PIN); //DESLIGA O BUZZER
  delay(500); //ESPERA POR 0,5s
  digitalWrite(greenPin, HIGH); //LIGA O LED VERDE
  digitalWrite(redPin, LOW); //DESLIGA O LED VERMELHO
} 


void sonzinManeiro() //MÉTODO PARA EXECUTAR O SOM DE ENTRADA AO LIGAR O LCD
{
  int size = sizeof(durations) / sizeof(int);
  for (int note = 0; note < size; note++) 
  {
    //to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int duration = 1000 / durations[note];
    tone(BUZZER_PIN, melody[note], duration);

    //to distinguish the notes, set a minimum time between them.
    //the note's duration + 30% seems to work well:
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);

    //stop the tone playing:
    noTone(BUZZER_PIN);
  }
}
