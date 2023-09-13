# :house_with_garden:  AMBITECH - SEU AMBIENTE, NOSSA TECNOLOGIA

## 📝 Descrição

Esse projeto tem como objetivo detectar variações de temperatura, umidade e luminosidade do ambiente de acordo com os padrões estabelecidos através de sensores e da plataforma de prototipação Arduino.

## 📚 Funcionalidades

Nosso sistema monitora em tempo real a temperatura, umidade e luminosidade do ambiente que é visualizado através de um display LCD 16x2.

Ele segue regras estabelecidas, na qual, quando uma variável dessas sai do padrão ele emite um aviso sonoro através de um Buzzer e um aviso visual com um LED vermelho e guarda na memória EEPRON do microcontrolador a data,horário e qual variável saiu desse padrão. Quando as variáveis estão nos níveis adequados um LED verde se mantém aceso, mostrando-nos que está tudo operando conforme a regra estabelecida.

## Regra das variáveis

**Níveis adequados:**

Temperatura: **15ºC < T < 25 ºC**

Luminosidade: **0 < L < 30%**

Umidade: **30% < U < 50%**

## 🔧 Ferramentas utilizadas

- 1 MCU (Atmega 328P) - Arduino Uno R3 
- 1 LDR + Resistor 10KOhm
- 1 DHT-11 (Sensor de temperatura e umidade)
- 1 LCD 16x2
- 1 Bateria de 9V
- 1 Suporte para bateria
- 1 RTC (Real Time Clock)
- 1 protoboard
- Jumpers
- LEDs
- Resistores
- Buzzer

## ⚡ Circuito

![imagem do circuito](./Circuito.png)

Obs: No projeto real é utilizado o sensor DHT11 ao invés do sensor DHT22 e ao invés de usar um módulo de sensor de luz, foi utilizado um sensor LDR com um resistor de 10kOhm para fazer a divisão de tensão.

### Pinagem do circuito

| Pinos |              Descrição               | Cor do jumper |
| :---: | :----------------------------------: | :-----------: |
|  13   |        Sinal para o Led verde        |    Laranja    |
|  12   |           RS (Entrada LCD)           |  Verde claro  |
|  11   |           RW (Entrada LCD)           |    Amarelo    |
|  10   |           E (Entrada LCD)            |     Azul      |
|   9   | Sinal de alerta para o Led vermelho  |     Ciano     |
|   8   |    Sinal de alerta para o Buzzer     |     Cinza     |
|   5   |           D4 (Entrada LCD)           | Verde escuro  |
|   4   |           D5 (Entrada LCD)           |     Cinza     |
|   3   |           D6 (Entrada LCD)           |     Roxo      |
|   2   |           D7 (Entrada LCD)           |     Rosa      |
|  A0   |  INPUT - Recebe sinal do sensor LDR  |     Azul      |
|  A1   | INPUT - Recebe sinal do sensor DHT11 |    Amarelo    |
|  SCL  |          SCL do módulo RTC           |    Marrom     |
|  SDA  |          SDA do módulo RTC           |     Rosa      |
|  5V   |      Alimentação da Protoboard       |   Vermelho    |
|  GND  |         Terra da Protoboard          |     Preto     |



## 🚀 Rodando o projeto

Para rodar o repositório é necessário clonar o mesmo, dar o seguinte comando para clonar o projeto:

``git clone https://github.com/guigarciag/AMBITECH``

Após isso, encontre o arquivo **main.ino** dentro da pasta **main** e abra-o com o IDE do seu Arduino. Lembre-se que para funcionar o código, são necessárias a instalação das seguintes bibliotecas:

- DHT
- pitches
- RTCLIB
- Wire
- Liquid Crystal
- EEPROM

As bibliotecas podem ser encontradas no formato **.zip** dentro do diretório **lib** ao baixar o repositório para sua máquina.Caso não estejam, instale-as diretamente por meio da IDE do Arduino ou teste-as, pois podem já estarem instaladas juntamente com a IDE. 
Para fazer sua instalação, verifique o procedimento para a IDE escolhida.

## :heavy_check_mark: Resultados obtidos

Conseguimos alcançar os objetivos do projeto, os sensores, os efeitos sonoros e visuais funcionaram adequadamente, além de salvar a o ultimo alerta na memória EEPRON do microcontrolador.

## :video_camera: Vídeo do projeto

https://www.youtube.com/watch?v=Jso6bTLblRY

## 🤝 Colaboradores

### Beatriz de Sa Silva

# [![img](https://camo.githubusercontent.com/927d6b3961fa048ff7303daf291cb5869dfa25018997cf8c1373c2f6a85b1458/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f2d476d61696c2d2532333333333f7374796c653d666f722d7468652d6261646765266c6f676f3d676d61696c266c6f676f436f6c6f723d7768697465)](mailto:beatriz2812.bia@gmail.com) [![img](https://camo.githubusercontent.com/acaa286597b43c96dc02b69b90de15a65c52063e31835b763a061cc815f64bac/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f2d496e7374616772616d2d2532334534343035463f7374796c653d666f722d7468652d6261646765266c6f676f3d696e7374616772616d266c6f676f436f6c6f723d7768697465)](https://www.instagram.com) [![img](https://camo.githubusercontent.com/c00f87aeebbec37f3ee0857cc4c20b21fefde8a96caf4744383ebfe44a47fe3f/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f2d4c696e6b6564496e2d2532333030373742353f7374796c653d666f722d7468652d6261646765266c6f676f3d6c696e6b6564696e266c6f676f436f6c6f723d7768697465)](https://www.linkedin.com/in/beatriz-s%C3%A1-03987a279)[![img](https://camo.githubusercontent.com/1a7b49c5d4070f7164266f86480dcca3b86ee75be04930051b191d7be660c547/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f6769746875622d3138313731373f267374796c653d666f722d7468652d6261646765266c6f676f3d676974687562266c6f676f436f6c6f723d7768697465)](https://github.com/BlackFox2812)

### Guilherme Gonçalves Garcia

# [![img](https://camo.githubusercontent.com/927d6b3961fa048ff7303daf291cb5869dfa25018997cf8c1373c2f6a85b1458/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f2d476d61696c2d2532333333333f7374796c653d666f722d7468652d6261646765266c6f676f3d676d61696c266c6f676f436f6c6f723d7768697465)](mailto:guigg.garcia@gmail.com) [![img](https://camo.githubusercontent.com/acaa286597b43c96dc02b69b90de15a65c52063e31835b763a061cc815f64bac/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f2d496e7374616772616d2d2532334534343035463f7374796c653d666f722d7468652d6261646765266c6f676f3d696e7374616772616d266c6f676f436f6c6f723d7768697465)](https://www.instagram.com/_guigarciag) [![img](https://camo.githubusercontent.com/c00f87aeebbec37f3ee0857cc4c20b21fefde8a96caf4744383ebfe44a47fe3f/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f2d4c696e6b6564496e2d2532333030373742353f7374796c653d666f722d7468652d6261646765266c6f676f3d6c696e6b6564696e266c6f676f436f6c6f723d7768697465)](https://www.linkedin.com/in/guigarciag)[![img](https://camo.githubusercontent.com/1a7b49c5d4070f7164266f86480dcca3b86ee75be04930051b191d7be660c547/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f6769746875622d3138313731373f267374796c653d666f722d7468652d6261646765266c6f676f3d676974687562266c6f676f436f6c6f723d7768697465)](https://github.com/guigarciag)

### Lohan Batista Moreira

# [![img](https://camo.githubusercontent.com/927d6b3961fa048ff7303daf291cb5869dfa25018997cf8c1373c2f6a85b1458/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f2d476d61696c2d2532333333333f7374796c653d666f722d7468652d6261646765266c6f676f3d676d61696c266c6f676f436f6c6f723d7768697465)](mailto:lohanbatista2003@gmail.com) [![img](https://camo.githubusercontent.com/acaa286597b43c96dc02b69b90de15a65c52063e31835b763a061cc815f64bac/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f2d496e7374616772616d2d2532334534343035463f7374796c653d666f722d7468652d6261646765266c6f676f3d696e7374616772616d266c6f676f436f6c6f723d7768697465)](https://www.instagram.com/lohan_b_moreira/) [![img](https://camo.githubusercontent.com/c00f87aeebbec37f3ee0857cc4c20b21fefde8a96caf4744383ebfe44a47fe3f/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f2d4c696e6b6564496e2d2532333030373742353f7374796c653d666f722d7468652d6261646765266c6f676f3d6c696e6b6564696e266c6f676f436f6c6f723d7768697465)](https://www.linkedin.com/in/lohanbatista/)[![img](https://camo.githubusercontent.com/1a7b49c5d4070f7164266f86480dcca3b86ee75be04930051b191d7be660c547/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f6769746875622d3138313731373f267374796c653d666f722d7468652d6261646765266c6f676f3d676974687562266c6f676f436f6c6f723d7768697465)](https://github.com/Lohan1303)

### Paulo Henrique dos Santos Tristão

# [![img](https://camo.githubusercontent.com/927d6b3961fa048ff7303daf291cb5869dfa25018997cf8c1373c2f6a85b1458/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f2d476d61696c2d2532333333333f7374796c653d666f722d7468652d6261646765266c6f676f3d676d61696c266c6f676f436f6c6f723d7768697465)](mailto:email@.com) [![img](https://camo.githubusercontent.com/acaa286597b43c96dc02b69b90de15a65c52063e31835b763a061cc815f64bac/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f2d496e7374616772616d2d2532334534343035463f7374796c653d666f722d7468652d6261646765266c6f676f3d696e7374616772616d266c6f676f436f6c6f723d7768697465)](https://www.instagram.com/paulo_ht2) [![img](https://camo.githubusercontent.com/c00f87aeebbec37f3ee0857cc4c20b21fefde8a96caf4744383ebfe44a47fe3f/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f2d4c696e6b6564496e2d2532333030373742353f7374796c653d666f722d7468652d6261646765266c6f676f3d6c696e6b6564696e266c6f676f436f6c6f723d7768697465)](https://www.linkedin.com/in/paulo-henrique-tristao)[![img](https://camo.githubusercontent.com/1a7b49c5d4070f7164266f86480dcca3b86ee75be04930051b191d7be660c547/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f6769746875622d3138313731373f267374796c653d666f722d7468652d6261646765266c6f676f3d676974687562266c6f676f436f6c6f723d7768697465)](https://github.com/PauloTristao)

### Rodrigo Puertas Matioli

# [![img](https://camo.githubusercontent.com/927d6b3961fa048ff7303daf291cb5869dfa25018997cf8c1373c2f6a85b1458/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f2d476d61696c2d2532333333333f7374796c653d666f722d7468652d6261646765266c6f676f3d676d61696c266c6f676f436f6c6f723d7768697465)](mailto:mattiolli.puertas@gmail.com) [![img](https://camo.githubusercontent.com/acaa286597b43c96dc02b69b90de15a65c52063e31835b763a061cc815f64bac/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f2d496e7374616772616d2d2532334534343035463f7374796c653d666f722d7468652d6261646765266c6f676f3d696e7374616772616d266c6f676f436f6c6f723d7768697465)](https://www.instagram.com/rodrigo_mattiolli/) [![img](https://camo.githubusercontent.com/c00f87aeebbec37f3ee0857cc4c20b21fefde8a96caf4744383ebfe44a47fe3f/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f2d4c696e6b6564496e2d2532333030373742353f7374796c653d666f722d7468652d6261646765266c6f676f3d6c696e6b6564696e266c6f676f436f6c6f723d7768697465)](https://www.linkedin.com/in/rodrigopuertas/)[![img](https://camo.githubusercontent.com/1a7b49c5d4070f7164266f86480dcca3b86ee75be04930051b191d7be660c547/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f6769746875622d3138313731373f267374796c653d666f722d7468652d6261646765266c6f676f3d676974687562266c6f676f436f6c6f723d7768697465)](https://github.com/RodrigoPuertas)

