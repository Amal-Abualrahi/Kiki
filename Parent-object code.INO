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
// the setup routine runs once when you press reset: 
void setup() { 
  // initialize serial communication at 9600 bits per second: 
  Serial.begin(9600); 
  pinMode(sensor_pin, INPUT); 
  pinMode(output_pin, OUTPUT); 
  radio.begin(); //Starting the radio communication radio.openWritingPipe(addresses[1]); //Setting the address at which we will  send the data 
  radio.openReadingPipe(1, addresses[0]); //Setting the address at which we will  receive the data 
  radio.setPALevel(RF24_PA_MIN); //You can set it as minimum or maximum  depending on the distance between the transmitter and receiver. 
} 
// the loop routine runs over and over again forever: 
void loop() { 
  radio.startListening(); //This sets the module as receiver while(!radio.available()); //Looking for incoming data radio.read(&otherSensor_status, sizeof(otherSensor_status)); //Reading the  data 
  if (otherSensor_status == HIGH) 
  { 
    sensor_status = digitalRead(sensor_pin); 
    while (sensor_status == LOW){ 
      digitalWrite(output_pin, HIGH); // turn the LED on 
      delay(200); // wait for a second 
      digitalWrite(output_pin, LOW); // turn the LED off 
      delay(200); // wait for a second 
    } 
    delay(5); 
    if (sensor_status == 1) 
    { 
      radio.stopListening(); //This sets the module as  transmitter 
      radio.write(&sensor_status, sizeof(sensor_status)); //Sending the data delay(5); 
    } 
  } 
}
