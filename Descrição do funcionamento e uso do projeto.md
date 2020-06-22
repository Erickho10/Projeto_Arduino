# Descrição do funcionamento e uso para quem quiser reproduzir

<h3>O funcionamento do projeto é realizar a monitoração da temperatura ambiente de um local, mostrando se ela está boa, regular, ruim com os leds. Para temperatura boa mostrará no led verde, para regular o led amarelo e para ruim o led vermelho. Quando estiver ruim a temperatura, tocará um buzzer para alertar.
Os dados da temperatura serão enviados para o broker que é o CloudMQTT. Ele enviará o dado para o MQTT Dash (um aplicativo no celular Android) que exibirá em uma dashboard a temperatura.
<br><br>
Para quem quiser reproduzir:
<br>- Colocar todos os periféricos na protoboard. 
 <br> - No NodeMCU, colocar um cabo jumper macho-macho no GND para a protoboard, que alimentará todos os periféricos. 
 <br>- Para cada LED no lado do ânodo, colocar um cabo jumper macho-macho em um pino digital do NodeMCU, com um resistor de 220 ohms, e no lado do cátodo, colocar um jumper macho-macho na GND da protoboard. 
<br>- Para fazer conexão do buzzer, colocar um cabo jumper macho-macho em um pino digital do NodeMCU na parte positiva do buzzer, e na parte negativa do buzzer, colocar um cabo jumper macho-macho no GND da protoboard. 
<br> - Para o sensor LM35, colocar na potência um cabo jumper macho-macho no 5V do NodeMCU; no Vout, colocar um cabo jumper macho-macho em uma entrada analógica do NodeMCU e um cabo jumper macho-macho no GND da protoboard.</h3>
