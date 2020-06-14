# Projeto – monitorar temperatura ambiente de um local

Descrição do funcionamento e uso para quem quiser reproduzir

O funcionamento do projeto seria exibir a temperatura ambiente de um local, mostrando se ela está boa, regular, ruim com os leds.Para temperatura boa mostrará no led verde, para regular o led amarelo e para ruim o led vermelho. Quando estiver ruim a temperatura tocará um buzzer para alertar.Os dados da temperatura serão enviados para o cloudMQTT que é o broker. Ele poderá enviar esse dado em qualquer dispositivo. Para visualizar precisará utilizar uma dashboard.
<br><br>
Para quem quiser reproduzir precisará colocar todos os periféricos na protoboard e um GND na protoboard colocado no NODEMCU que alimentará todos periféricos colocados. Para cada led no lado do anodo colocar um cabo jumper com um resistor de 220 ohms e no lado do catodo colocar um jumper colocado no GND da protoboard. Para fazer conexão do buzzer precisará colocar um jumper em um pino digital do NodeMCU na parte positiva do buzzer e na parte negativa do buzzer colocar um jumper no GND da protoboard. Para o sensor LM35 colocar na potência um jumper no 5V do NodeMCU, no Vout colocar um jumper em uma entrada analógica e colocar um cabo jumper no GND da protoboard.
