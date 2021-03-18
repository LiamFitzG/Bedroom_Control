//Infrared Reader and Recorder

//Version:  1
//Features: Uses an infrared receiver to receive an infrared signal transmitted by an infrared
//          remote. The Arduino samples the signal at a given sample rate and records the length
//          of the high and low pulses. This information can then be used by the Arduino in 
//          another program to simulate the infrared signal without the need of the remote.
//Updates:  /
//Date:     01/2021
//Auther:   Liam Fitzgerald
//------------------------------------------------------------------------------------------

//Known constants

#define Pin_Read PIND     //PIND used for direct digital reading of the digital pins
#define IR_Pin 2          //Infrared receiver pin
#define Timeout 7000      //Timout condition ie. end of pulse sequence or an error (7000*Rate)
#define Rate 20           //Sample rate of IR pin in Microseconds
//------------------------------------------------------------------------------------------

//Global variables

uint16_t Result[100][2];  //Final resulting sequence of pairs of high and low pulses
uint16_t Temp = 0;        //Temporary index integer to determine the current pulse pair
//------------------------------------------------------------------------------------------

//Main functions

void setup() {
  Serial.begin(9600);
}

void loop() {
  uint16_t Temp_High = 0;   //Temporary integer storing length of each high pulse
  uint16_t Temp_Low = 0;    //Temporary integer storing length of each low pulse

  while(Pin_Read & (1<<IR_Pin)){    //Check if digital pin 2 in PIND is high (IR pulse is high)
    Temp_High++;                    //Increment Temp_High (increases at sample rate until pulse is finished)
    delayMicroseconds(Rate);        //Delay by the sample rate to reduce number of samples and provide known resolution

    if((Temp_High >= Timeout) && (Temp != 0)){    //If the pulse length exceeds the maximum required for timout
      Print_Result();                             //Print the final sequence array
      Temp = 0;                                   //Reset temp because sequence is over (ready for next sequence of infrsred pulses)
      return;
    }
  }
  Result[Temp][0] = Temp_High;        //Write the length of the current high pulse to the current pulse pair

  while(!(Pin_Read & (1<<IR_Pin))){   //Check if digital pin 2 in PIND is low (IR pulse is low)
    Temp_Low++;                       //Increment Temp_Low (increases at sample rate until pulse is finished)
    delayMicroseconds(Rate);          //Delay by the sample rate to reduce the number of samples and provide known resolution

    if((Temp_Low >= Timeout) && (Temp != 0)){     //If the pulse length exceeds the maximum required for timout
      Print_Result();                             //Print the final sequence array
      Temp = 0;                                   //Reset temp because sequence is over (ready for next sequence of infrared pulses)
      return;
    }
  }
  Result[Temp][1] = Temp_Low;     //Write the length of the current low pulse to the current pulse pair

  Temp++;             //Increment Temp to move on to the next high low pulse pair
  if(Temp == 100){    //If maximum storage in the Result array is reached...
    Print_Result();   //...print the pulse pairs currently recorded...
    Temp = 0;         //...and reset Temp to be ready for the next sequence of infrared pulses
    return;
  }
}
//------------------------------------------------------------------------------------------

//Function declarations

void Print_Result(){                        //Function to Print the recorded lengths of high low pulse pairs
  Serial.println("Result");
  for(int i = 0; i < Temp; i++){            //Iterate through recorded number of pulse pairs
    Serial.print(Result[i][0] * Rate);      //Print high pulse length (Number of samples * Sample rate [microseconds])
    Serial.print("  ");
    Serial.println(Result[i][1] * Rate);    //Print low pulse length (Number of samples * Sample rate [microseconds])
  }

  Serial.println(Temp + 1);                 //Print the number of elements in the array
  for(int i = 0; i < Temp; i++){            //The above for loop prints each pulse pair on a new line to easily distinguish...
    Serial.print(Result[i][0] * Rate);      //...between high and low pulses. Whereas, this for loop prints the pulse pairs...
    Serial.print(",");                      //...on the same line separated by a comma to allow for copy and pasting into an array...
    Serial.print(Result[i][1]*Rate);        //...to be used in the IR simulating function in another program which uses the Arduino...
    Serial.print(",");                      //...to simulate the infrared remote buttons that were recorded using this program
  }
  
}
