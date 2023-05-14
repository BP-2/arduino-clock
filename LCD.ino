/**
 * @BRIEF: The following program is a clock display on an LCD screen using an Arduino Uno.  This features capabilities such as increment and decrement time functions.
 * @CREDIT: Part of the design was drawn from https://howtomechatronics.com/tutorials/arduino/lcd-tutorial/, https://projecthub.arduino.cc/plouc68000/03c1850e-eb95-450c-9fd3-8b6f810054d3, and https://docs.arduino.cc/built-in-examples/digital/Button
 * @AUTHOR: BP-2
 */

#include <LiquidCrystal.h> // includes the LiquidCrystal Library 
LiquidCrystal lcd(1, 2, 4, 5, 6, 7); // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7) 
const int buttonPin = 3;  // the number of the pushbutton pin
const int buttonPin2 = 8; // number of pushbutton2 pin
int buttonState = 0;  // variable for reading the pushbutton status
int buttonState2 = 0; // variable for second button
bool flip = false; // flag for flipping the clock numbers
unsigned long startMillis; // this variable will hold the starting milliseconds at each loop
unsigned long currentMillis; // this variable will hold current milliseconds used to measure length of each loop



// Digital LCD Constrast setting
int cs=9;// pin 9 for contrast PWM
const int contrast = 100;// default contrast

// initial Time display is 12:59:45 PM
int h=12;
int m=59;
int s=45;
int flag=1; //PM


void setup() { 
 lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display } 
  pinMode(buttonPin, INPUT); // initialize to input
  pinMode(buttonPin2, INPUT); // initialize to input

}

void loop() { 
  s = s + 1; // increment the second counter each iteration

  // logic for flow of numbers on clock
  if(s>59){
    s=0;
    m=m+1;
  }
  if(m>=60)
  {
    m=0;
    h=h+1;
  }
  if(h>=13)
  {
    h=1;
    flag=flag+1;
    if(flag==2){
      flag=0;
    }
  } 
  // read the state of the buttons:
  buttonState = digitalRead(buttonPin);
  buttonState2 = digitalRead(buttonPin2);
  // display to screen correctly
  lcd.setCursor(0,0);
  lcd.print("Time ");
  if(h<10){
    lcd.print("0");// always 2 digits
  }
  lcd.print(h);
  lcd.print(":");
  if(m<10){
    lcd.print("0");
  }
  lcd.print(m);
  lcd.print(":");
  if(s<10){
    lcd.print("0");
  }
  lcd.print(s);
  if(flag==0){
    lcd.print(" AM");
  }
  if(flag==1){
    lcd.print(" PM");
  }
  lcd.setCursor(0,1);// for Line 2
  lcd.print("User's Clock!");

  // initialize the starting time of this loop
  startMillis = millis();
  currentMillis = startMillis;
  // these will temporarily hold vallues so when we are in loop we only increment or decrement once
  int tempM = m;
  int tempS = s;
  while(currentMillis - startMillis <= 987 ){ // waiting for 987 milliseconds to account for 1 full second elapsed (taking into account execution time)
    // special statement if both buttons are pressed
    if(buttonState2 == HIGH && buttonState == HIGH){ 
      lcd.setCursor(0,0);
      lcd.clear();
      lcd.print("Hi User!");
      flip = !flip;
      delay(2000); 
      lcd.setCursor(0,1);
      lcd.print("Arduino is fun!");
      delay(4846);
      s = tempS + 7;
    }
    // increment button
    else if (buttonState2 == HIGH){ 
      m = tempM + 1;
    }
    // decrement button
    else if (buttonState == HIGH) {
      m = tempM - 1;
    } 
  currentMillis = millis(); // count time elapsed
  }
}
