//Bedroom_Control

//Version:  1.1
//Features: 4 Channel relay control via digital output pins (connected to various appliances)
//          Serial communication via Bluetooth Module to control relay pins using android application
//Updates:  Constant variables changed to #define rather than using integers
//          ie. all integer identities used through serial communication from the Bluetooth Module and 
//          the Arduino and the pin numbers allocated to the various appliances
//Date:     01/2021
//Auther:   Liam Fitzgerald
//------------------------------------------------------------------------------------------

//Assign pin numbers to each external appliance connected to realy board

#define Light_0 8     //Set Light_0 to digital pin 8
#define Light_1 9     //Set Light_1 to digital pin 9
#define Fan 10        //Set Computer power switch to digital pin 10
#define Radio 11      //Set Radio power switch to digital pin 11
//------------------------------------------------------------------------------------------

//Correspond integer value received via serial communication from the Bluetooth Module
//with desired control parameter 
//eg. Serial communication received: 10; Control Parameter: Turn on Light 0

#define Light_0_ON 10
#define Light_0_OFF 15

#define Light_1_ON 20
#define Light_1_OFF 25

#define Fan_ON 30
#define Fan_OFF 35

#define Radio_ON 40
#define Radio_OFF 45

#define All_OFF 50

#define Startup 100
//------------------------------------------------------------------------------------------

//Global variables

unsigned int Serial_Read = 0;
//------------------------------------------------------------------------------------------

void setup() {
  Serial.begin(9600);        //Start Serial Communication between Arduino UNO and Bluetooth Module
  
  pinMode(Light_0,OUTPUT);   //Set Light_0 digital pin to output
  pinMode(Light_1,OUTPUT);   //Set Light_1 digital pin to output
  pinMode(Fan,OUTPUT);       //Set Fan digital pin to output
  pinMode(Radio,OUTPUT);     //Set Radio digital pin to output
}

void loop() {
  if (Serial.available() > 0){                //Check if the bluetooth module is outputting data
  Serial_Read = Serial.read();

                                 
    if (Serial_Read == Light_0_ON){           //Check if the ouput from the bluetooth module is Light_0_ON
      digitalWrite(Light_0,LOW);              //Set Light_0 pin to a Low to turn on the Light_0 if the if statement is met
      Serial.println(1);                      //Send integer to Bluetooth Module indicating Light_0 is on
    }
    else if (Serial_Read == Light_0_OFF){     //Check if the ouput from the bluetooth module is Light_0_OFF
      digitalWrite(Light_0,HIGH);             //Set Light_0 pin to a High to turn off the Light_0
      Serial.println(2);                      //Send integer to Bluetooth Module indicating Light_0 is off
    }

    else if (Serial_Read == Light_1_ON){      //Same as above but for Light_1
      digitalWrite(Light_1,LOW);
      Serial.println(3);
    }
    else if (Serial_Read == Light_1_OFF){
      digitalWrite(Light_1,HIGH);
      Serial.println(4);
    }

    else if (Serial_Read == Fan_ON){          //Same as above but for Fan
      digitalWrite(Fan,LOW);
      Serial.println(5);
    }
    else if (Serial_Read == Fan_OFF){
      digitalWrite(Fan,HIGH);
      Serial.println(6);
    }

    else if (Serial_Read == Radio_ON){        //Same as above but for Radio
      digitalWrite(Radio,LOW);
      Serial.println(7);
    }
    else if (Serial_Read == Radio_OFF){
      digitalWrite(Radio,HIGH);
      Serial.println(8);
    }

    else if (Serial_Read == All_OFF){         //Check if the output from the Bluetooth Module is ALL_OFF
      digitalWrite(Light_0,HIGH);             //Set all pins to a High to turn off all appliances
      digitalWrite(Light_1,HIGH);
      digitalWrite(Fan,HIGH);
      digitalWrite(Radio,HIGH);
    }


    else if (Serial_Read == Startup){         //Initial conditions
      if (digitalRead(Light_0) == LOW){       //Check the state of the Light_0 pin
        Serial.println(1);                    //If Light_0 pin is Low, send integer to Bluetooth Module indicating Light_0 is on
      }
      else if (digitalRead(Light_0) == HIGH){
        Serial.println(2);                    //If Light_0 pin is High, send integer to Bluetooth Module iundicating Light_0 is off
      }

      delay(1500);                            //Delay for 1,5 seconds to allow enough time for the integer to be read once sent by the Bluetooth Module

      if (digitalRead(Light_1) == LOW){       //Same as above for Light_1
        Serial.println(3);
      }
      else if (digitalRead(Light_1) == HIGH){
        Serial.println(4);
      }

      delay(1500);

      if (digitalRead(Fan) == LOW){           //Same as above for Fan
        Serial.println(5);
      }
      else if (digitalRead(Fan) == HIGH){
        Serial.println(6);
      }

      delay(1500);

      if (digitalRead(Radio) == LOW){       //Same as above for Radio
        Serial.println(7);
      }
      else if (digitalRead(Radio) == HIGH){
        Serial.println(8);
      }

      delay(1500);

      Serial.println(9);
    }
  }
}
