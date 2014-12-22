// Arduino Photoresistor Skull

#include <Servo.h>
Servo myservo;      // create servo object to control a servo

int onLED = 3;      // LED to indicate that the skull is on
int waitLED = 4;    // LED to blink during calibration

// degree positions to move the skull towards
int pos1 = 75;
int pos2 = 56.25;
int pos3 = 37.5;
int pos4 = 18.75;
int pos5 = 0;

// current position to start with
int currentPos = pos3;

// pin locations on the Arduino
int PinOne = 1;
int PinTwo = 2;
int PinThree = 3;
int PinFour = 4;
int PinFive = 5;

// for storing the values of each pin
int PinOneVal;
int PinTwoVal;
int PinThreeVal;
int PinFourVal;
int PinFiveVal;

// for storing the pin average after calibration
int PinOneAverage = 0;
int PinTwoAverage = 0;
int PinThreeAverage = 0;
int PinFourAverage = 0;
int PinFiveAverage = 0;

// for storing pin totals during calibration
int PinOneTotal = 0;
int PinTwoTotal = 0;
int PinThreeTotal = 0;
int PinFourTotal = 0;
int PinFiveTotal = 0;

// how many times to test pin values
int AverageCount = 10;

// initialize arrays for storing pin values for calibration
int PinOneValues[10];
int PinTwoValues[10];
int PinThreeValues[10];
int PinFourValues[10];
int PinFiveValues[10];

void setup()
{
  myservo.attach(12);         // attaches servo to digital pin 12
  myservo.write(currentPos);  // spin servo to current position
  pinMode(onLED, OUTPUT);     // setup onLED
  pinMode(waitLED, OUTPUT);   // setup waitLED
  
  digitalWrite(onLED, HIGH);  // turn on onLED to indicate that skull has turned on
  delay(1750);                // allow time to move out of the way of photoresistors
  digitalWrite(onLED, LOW);   // turn off onLED
  delay(250);                 // wait before starting calibration
  
  // gather data for calibration
  for (int i = 0; i < AverageCount; i++) {
    
    // read and store pin values
    PinOneValues[i] = analogRead(PinOne);
    PinTwoValues[i] = analogRead(PinTwo);
    PinThreeValues[i] = analogRead(PinThree);
    PinFourValues[i] = analogRead(PinFour);
    PinFiveValues[i] = analogRead(PinFive);    
    
    // add current value to pin totals
    PinOneTotal = PinOneTotal + PinOneValues[i];
    PinTwoTotal = PinTwoTotal + PinTwoValues[i];
    PinThreeTotal = PinThreeTotal + PinThreeValues[i];
    PinFourTotal = PinFourTotal + PinFourValues[i];
    PinFiveTotal = PinFiveTotal + PinFiveValues[i];

    // blink waitLED to indicate calibration
    digitalWrite(waitLED, HIGH);
    delay(250);
    digitalWrite(waitLED, LOW);
    delay(250);
  }
  
  // finish calibration by finding averages
  for (int j = 0; j < AverageCount; j++) {
    PinOneAverage = PinOneTotal / AverageCount;
    PinTwoAverage = PinTwoTotal / AverageCount;
    PinThreeAverage = PinThreeTotal / AverageCount;
    PinFourAverage = PinFourTotal / AverageCount;
    PinFiveAverage = PinFiveTotal / AverageCount;
  }
  
  // display onLED to indicate ready state
  digitalWrite(onLED, HIGH);
}

void loop()
{
  // read current pin values
  PinOneVal = analogRead(PinOne);
  PinTwoVal = analogRead(PinTwo);
  PinThreeVal = analogRead(PinThree);
  PinFourVal = analogRead(PinFour);
  PinFiveVal = analogRead(PinFive);
  
  // adjust skull position accordingly
  if (PinOneVal > (PinOneAverage + 100)) { currentPos = pos1; }
  if (PinTwoVal > (PinTwoAverage + 100) ) { currentPos = pos2; }
  if (PinThreeVal > (PinThreeAverage + 100)) { currentPos = pos3; }
  if (PinFourVal > (PinFourAverage + 100)) { currentPos = pos4; }
  if (PinFiveVal > (PinFiveAverage + 100)) { currentPos = pos5; }
  
  myservo.write(currentPos);  // sets the servo position to current position
  delay(250);                 // delay between pin readings and skull adjustment
}
