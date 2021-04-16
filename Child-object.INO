#include <SPI.h> 
#include <nRF24L01.h> 
#include <RF24.h> 
RF24 radio(9, 10); // CE, CSN 
const byte addresses [][6] = {"00001", "00002"}; //Setting the two addresses.  One for transmitting and one for receiving 
int sensor_pin = 7; 
int output_pin = 4; 
boolean sensor_status = 0; 
boolean otherSensor_status = 0; 
boolean send_result = 0; 
int counter = 0; 
void setup() { 
  pinMode(sensor_pin, INPUT); 
  pinMode(output_pin, OUTPUT); 
  radio.begin(); //Starting the radio communication radio.openWritingPipe(addresses[1]); //Setting the address at which we will  send the data 
  radio.openReadingPipe(1, addresses[0]); //Setting the address at which we will  receive the data 
  radio.setPALevel(RF24_PA_MIN); //You can set it as minimum or maximum  depending on the distance between the transmitter and receiver.
} 
void loop() 
{  
  delay(5); 
  radio.stopListening(); //This sets the module as transmitter sensor_status = digitalRead(sensor_pin); 
  if (sensor_status == 1) 
  { 
    send_result = radio.write(&sensor_status, sizeof(sensor_status)); //Sending the  data 
    delay(5); 
    if (send_result){ //successful message was sent 
    //blink 
      digitalWrite(output_pin, HIGH); 
      delay(1000); // wait for a second 
      digitalWrite(LED_BUILTIN, LOW); 
      radio.startListening(); //This sets the module as receiver while(!radio.available()); //Looking for incoming data radio.read(&otherSensor_status, sizeof(otherSensor_status)); //Reading the  data 
      if (otherSensor_status == HIGH) 
      { 
          //blink fast 4 times 
          digitalWrite(output_pin, HIGH); // turn the LED on 
          delay(200); // wait for a second 
          digitalWrite(output_pin, LOW); // turn the LED off 
          delay(200); // wait for a second 
          counter++; 
          if (counter > 3) { 
          digitalWrite(output_pin, LOW); // turn the LED off and keep it off (why isn't  this working?) 
          } 
      } 
     } 
  } 
} 
