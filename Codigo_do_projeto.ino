
/***********************************************************
        Projeto de medição da temperatura remotamente
************************************************************/

//Biblioteca utilizada para conectar o módulo ESP8266 para a rede Wi-Fi
#include <ESP8266WiFi.h>
//Biblioteca utilizada para a publicação de dados no broker
#include <PubSubClient.h>

// Define variáveis globais para utlização no programa 
#define INTERVALO_ENVIO 1000
#define DEBUG 1
#define LM35 A0
#define greenLED D2
#define yellowLED D1
#define redLED D3
#define buzzer D5

//Informações para conectar na rede WIFI
#define ssid        "XXXXXXXXXXXXXXXXXXXX"   // usuário wifi
#define password    "XXXXXXXXXXXXXXXXXXXX"  // senha wifi
 
//Informações para conectar ao broker MQTT 
const char* mqttUser = "XXXXXXXXXXXXXXXXXXXX"; // usuário CloudMQTT
const char* mqttPassword = "XXXXXXXXXXXXXXXXXXXX"; // senha CloudMQTT
const char* mqttServer = "XXXXXXXXXXXXXXXXXXXX";  // endereço servidor MQTT
const int   mqttPort = XXXXXXXXXXXXXXXXXXXX; // porta servidor
const char* mqttTopicSub ="XXXXXXXXXXXXXXXXXXXX"; // tópico que sera assinado 
const char* device_id = "XXXXXXXXXXXXXXXXXXXX";  // ID unico e seu. Caso sejam usados IDs repetidos a ultima conexão irá sobrepor a anterior. 
 
int   ultimoEnvioMQTT = 0;       // intervalo de tempo para o envio ao MQTT
char  MsgTemperaturaMQTT[10];    // var auxiliar para formatar a temperatura envidada ao MQTT
float temperatura;               // armazena a tempetura recebida do sensor

// Criação de objetos globais para comunicar com o broker
WiFiClient  espClient;
PubSubClient client(espClient);

//Prototipo das funções
void setup();
void loop();
void dadosLM35();
void reconect();

 
/**************************************************************
 Função inicialização dos leds, conexão wifi e conexão com servidor MQTT
**************************************************************/
void setup() {
  // inicialização dos leds, todos estão apagados
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  Serial.begin(9600);
  
  // efetua conexão com a rede WIFI
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    #ifdef DEBUG
    Serial.println("Conectando ao WiFi..");
    #endif
  }
  #ifdef DEBUG
  Serial.println("Conectado na rede WiFi");
  #endif

  // Conexão com o servidor MQTT 
  client.setServer(mqttServer, mqttPort);
  // Efetua o Loop até que o esteja conectado ao servidor MQTT 
  while (!client.connected()) {
    #ifdef DEBUG
    Serial.println("Conectando ao Broker MQTT...");
    #endif
    // Efetua tentativa de conexão  
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
      #ifdef DEBUG
      Serial.println("Conectado");  
      #endif
    }
    else {
      #ifdef DEBUG 
      Serial.print("falha estado  ");
      Serial.print(client.state());
      #endif
      delay(2000);   
    }
  }
  //subscreve no tópico
  client.subscribe(mqttTopicSub);
}
 
/**************************************************************
Loop programa principal, verifica status da conexão servidor MQTT, chama a rotina de verificaçao de temperatura.
**************************************************************/
void loop() {
  // verifica se esta conectado  
  if (!client.connected()) {
    reconect();
  }
  // envia a cada 1 segundos
  if ((millis() - ultimoEnvioMQTT) > INTERVALO_ENVIO)
  {
      //efetua calculo da temperatura
      dadosLM35();  
      ultimoEnvioMQTT = millis();
  }
  client.loop();
}

/**************************************************************
         Função pra reconectar ao servido MQTT
**************************************************************/
void reconect() {
  // Enquanto não está conectado irá tentar fazer a conexão 
  while (!client.connected()) {
    #ifdef DEBUG
    Serial.print("Tentando conectar ao servidor MQTT");
    #endif
    // efetua conexão com o MQTT 
    bool conectado = strlen(mqttUser) > 0 ?
                     client.connect("ESP8266Client", mqttUser, mqttPassword) :
                     client.connect("ESP8266Client");
 
    // verifica se efetuou a conexão
    if(conectado) {
      #ifdef DEBUG
      Serial.println("Conectado!");
      #endif
      //subscreve no tópico
      client.subscribe(mqttTopicSub, 1); 
    } else {
      #ifdef DEBUG
      Serial.println("Falha durante a conexão.Code: ");
      Serial.println( String(client.state()).c_str());
      Serial.println("Tentando novamente em 10 s");
      #endif
      //Aguarda 10 segundos
      delay(10000);
    }
  }
}
 

/************************************************************** 
 Função para obter dados do LM35, acender os leds e enviar os dados para o BROKER 
**************************************************************/
void dadosLM35(){
    // efetua o calculo da temperatura para exibição em Celsius
    temperatura = (float(analogRead(LM35))*3/(1023))/0.01;
    // imprime a temperatura
    Serial.print(temperatura); 
    Serial.println(" Celsius "); 
    // formata a temperatura
    sprintf(MsgTemperaturaMQTT,"%f",temperatura);
    // envia dados da temperatura para o MQTT  BROKER
    client.publish(mqttTopicSub, MsgTemperaturaMQTT);

    // temperatura Ruim ascende o led vermelho
    if(temperatura >= 30 || temperatura <= 10 ){
       digitalWrite(greenLED, LOW);
       digitalWrite(yellowLED, LOW);
       digitalWrite(redLED, HIGH);
       // Aciona o buzzer na frequencia relativa ao Dó em Hz
       tone(buzzer,261);    
       delay(200);
       noTone(buzzer); 
       // Aciona o buzzer na frequencia relativa ao Ré em Hz   
       tone(buzzer,293);             
       delay(200);    
       noTone(buzzer); 
       // Aciona o buzzer na frequencia relativa ao Mi em Hz
       tone(buzzer,329);      
       delay(200);
       noTone(buzzer);     
       // Aciona o buzzer na frequencia relativa ao Fá em Hz
       tone(buzzer,349);    
       delay(200);    
       noTone(buzzer); 
       // Aciona o buzzer na frequencia relativa ao Sol em Hz
       tone(buzzer,392);            
       delay(200);
       noTone(buzzer);   
    } //// temperatura Regular ascende o led amarelo
    else if(temperatura >= 26 && temperatura < 30){
            digitalWrite(greenLED, LOW);
            digitalWrite(yellowLED, HIGH);
            digitalWrite(redLED, LOW); 
    }
    else{ //// temperatura Boa ascende o led verde
        digitalWrite(greenLED,HIGH);
        digitalWrite(yellowLED,LOW);
        digitalWrite(redLED,LOW);  
    }
    delay(1000);
}

