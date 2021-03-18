//Infrared remote simulation using Arduino and IR led
//01/2021
//Liam Fitzgerald
//------------------------------------------------------------------------------------------

//Known constants

#define LED_Pin 8   //Set Infrared led to pin 8
//------------------------------------------------------------------------------------------

//Arrays containing lengths of high and low pulses in microseconds for various functions
//
//Structure of array:
//Array[] = {number of cycles, number of remaining elements in the array, 
//          high, low, high...}

long VolumeUp[] = {3,32,
  2480,600,640,580,1260,600,640,580,640,600,1260,580,660,580,640,580,660,580,640,580,1260,600,
  640,600,640,580,640,600,640,580,1260,22640};

long AC_Power[] = {1,68,
  9300,4680,560,600,560,580,600,560,580,600,560,580,600,580,560,600,560,1760,560,1740,600,1740,
  580,1740,580,1720,600,1760,560,1760,560,1740,600,580,560,600,580,580,580,1740,580,1740,560,
  1760,580,580,580,600,560,1740,580,1740,600,1740,560,600,580,580,560,600,560,1760,560,1740,640,
  540,600};
//------------------------------------------------------------------------------------------

void setup() {
  pinMode(LED_Pin,OUTPUT);    //Set IR led pin (Led_Pin) to output
}

void loop() {                 //Testing (Volume is increased by 1 every second)
  IR_Press(VolumeUp);         //Turns sound system volume up by 1
  delay(1000);                //Delay 1 second 
}
//------------------------------------------------------------------------------------------

//Function declarations

void IR38(long usecs){            //Pulses IR led at 38MHz for duration usecs (microseconds)
  while(usecs > 0){                
    digitalWrite(LED_Pin, HIGH);  //Sets IR led pin to HIGH (takes approx. 3 usecs)
    delayMicroseconds(10);        //Delay for 10 usecs

    digitalWrite(LED_Pin, LOW);   //Sets IR led pin to LOW (takes approx. 3 usecs)
    delayMicroseconds(10);        //Delay for 10 usecs

    usecs -= 26;                  //Time remaining for loop to continue - Time of one iteration
  }
}


void IR_Press(long Action[]){         //Create desired infrared pulse sequence
  for(int i=0; i<Action[0];i++){      //Repeat the pulse sequence Action[0] times
    for(int j=2; j<=Action[1];j++){   //Iterate through Action[] from position 2
      IR38(Action[j]);                //Pulse at 38MHz for duration of high pulse (every even position)
      j++;                            
      delayMicroseconds(Action[j]);   //Delay for duration of low pulse
    }
  }
}
