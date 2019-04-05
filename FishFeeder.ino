#include <Servo.h>

Servo servo; // create servo object

//Constants
const int FEED = 2;       // FEED pin
const int RESET = 3;      // RESET pin
const int LEDG =  8;      // green led pin
const int LEDR = 9;       // red led pin
const int POTPIN = 0;     // potentiometer input pin
const int SERVOPIN = 5;   // servo output pin
const int FEEDPOS = 0;
const int STARTPOS = 180;
const int FEEDDELAY = 10000; // delay between feeding


// variables will change:
int FEEDSTATE = 0;         // variable for reading the FEED button state
int RESETSTATE = 0;        // variable for reading the RESET button state
int FEEDCYCLE;
unsigned long TIMER;
unsigned long PREVFEED;

void setup() {
  // initialize the LED pins as an output:
  pinMode(LEDG, OUTPUT);
  pinMode(LEDR, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(FEED, INPUT);
  pinMode(RESET, INPUT);
  servo.attach(SERVOPIN);
  servo.write(STARTPOS);
  Serial.begin(9600);
}

void loop() {
  // read the state of the pushbutton value:
  digitalWrite(LEDG, HIGH);
    FEEDCYCLE = analogRead(POTPIN);                   // reads the value of the potentiometer (value between 0 and 1023)
    FEEDCYCLE = map(FEEDCYCLE, 0, 1023, 1, 10);       // map value of potentiometer to between 1 and 10
    FEEDSTATE = digitalRead(FEED);
    RESETSTATE = digitalRead(RESET);
    TIMER = millis();
    Serial.println(PREVFEED); 
    Serial.println(TIMER);
    Serial.println(FEEDCYCLE);
  // Feed Button
      if (FEEDSTATE == HIGH || TIMER - PREVFEED > FEEDDELAY) {
        delay(100);
        PREVFEED = TIMER;
        for (int i = FEEDCYCLE; i > 0; i=i-1){
        servo.write(FEEDPOS);
        delay(2000);
        servo.write(STARTPOS);
        delay(2000);
      }
      }
      else{}
  // Reset Button
      if (RESETSTATE == HIGH & FEEDSTATE == LOW) {
           //blink LEDs twice
               digitalWrite(LEDG, LOW); 
            delay(100);
               digitalWrite(LEDR, HIGH);
               digitalWrite(LEDG, HIGH);
            delay(100);
              digitalWrite(LEDR, LOW);
              digitalWrite(LEDG, LOW);
            delay(100);
              digitalWrite(LEDR, HIGH);
              digitalWrite(LEDG, HIGH);
            delay(100);
              digitalWrite(LEDR, LOW);
              digitalWrite(LEDG, LOW);
            delay(100);
            PREVFEED = TIMER;
            servo.write(STARTPOS);
  } else {
 
  }
}
