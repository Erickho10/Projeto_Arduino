# Descrição do funcionamento e uso para quem quiser reproduzir

<h3>O funcionamento do projeto é realizar a monitoração da temperatura ambiente de um local, mostrando se ela está boa, regular, ruim com os leds.Para temperatura boa mostrará no led verde, para regular o led amarelo e para ruim o led vermelho. Quando estiver ruim a temperatura tocará um buzzer para alertar.
Os dados da temperatura serão enviados para o CloudMQTT que é o broker. Ele poderá enviar esse dado em qualquer dispositivo. Para visualizar precisará utilizar uma dashboard em um aplicativo.
<br><br>
Para quem quiser reproduzir, colocar todos os periféricos na protoboard. No NodeMCU colocar um cabo jumper no GND para a protoboard  que alimentará todos periféricos. Para cada LED no lado do ânodo colocar um cabo jumper em um pino digital do NodeMCU com um resistor de 220 ohms e no lado do cátodo colocar um jumper na GND da protoboard. 
Para fazer conexão do buzzer colocar um jumper em um pino digital do NodeMCU na parte positiva do buzzer e na parte negativa do buzzer colocar um jumper no GND da protoboard. 
Para o sensor LM35 colocar na potência um jumper no 5V do NodeMCU, no Vout colocar um jumper em uma entrada analógica e colocar um cabo jumper no GND da protoboard.</h3>
