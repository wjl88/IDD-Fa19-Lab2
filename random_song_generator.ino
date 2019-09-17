#include <LiquidCrystal.h>
#include "pitches.h"

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_D3, NOTE_E3, NOTE_F3, NOTE_G3, NOTE_A3, NOTE_B3
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 4, 4, 4, 4, 4, 4
};

// intialize delta time
long del0 = 300;
// intialize elapsed time
unsigned long elap0 = 0;
// initalize counter variable
static unsigned int counter = 0;
static unsigned int prevCounter = 0;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


int rVal() {
  return random(0,9);
}

void writePosition() {
  int col = random(0,16);
  int row = random(0,2);

  lcd.setCursor(col, row);
  lcd.print(rVal());
}


unsigned long elapsed[] = {0,30,60,80,100,120};
long deltas[] = {300,300,300,300,300,300};
long shift[] = {40,40,40,40,40,40};

int timer(int i) {
  unsigned long timenow = millis();
  if ( (timenow-elapsed[i]) >= deltas[i] ) {
    // reset elapsed time
    elapsed[i] = timenow;
    return 1;
  }
  else {
    return 0;
  }
}

void playMel() {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(1, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(1);
  }
}

void playRandNote() {
  int noteDuration = 1000 / noteDurations[0];
  tone(1, melody[random(0,7)], noteDuration);
}

void debug( long i, int r ) {
  lcd.setCursor(0, r);
  lcd.print(i);
}

int but0_currState = 0;
int but0_prevState = 0;

void buttonPressed() {
  unsigned long timenow = millis();
  unsigned long elapsed;
}

void f_readVolts() {
  int val = analogRead(A0);
  lcd.clear();
  debug(val,1);
  delay(300);
}

int f_readEncoder() {
  static int enc_states[] = {
    0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0  };
  static byte ABab = 0;
  ABab *= 4;                   //shift the old values over 2 bits
  ABab = ABab%16;      //keeps only bits 0-3
  ABab += 2*digitalRead(6)+digitalRead(7); //adds enc_a and enc_b values to bits 1 and 0
  return ( enc_states[ABab]);
}

int f_updateEncoder() {
// Chase the val from the f_readEncoder block
// ... and push to the public counter var
  static unsigned int counter4x = 0;      //the SparkFun encoders jump by 4 states from detent to detent
  //   static unsigned int counter = 0; // this var was pushed to public
  int tmpdata;
  tmpdata = f_readEncoder();
  if( tmpdata) {
    counter4x += tmpdata;
    counter = counter4x/4;
  }
}

void add_arrays(int array_len,long array1[],long array2[], int j) {
   int i;
   if ( j ) {
      for (i = 0; i < array_len; ++i) {
        array1[i] = array1[i] - array2[i];
      }
   }
   else if ( !j ) {
      for (i = 0; i < array_len; ++i)
        array1[i] = array1[i] + array2[i];
   }
}

void randomNotes() {
  for ( int j = 0 ; j < 6 ; j++ ) {
    deltas[j] = random(500,1000);
  }
}

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("deterministic");
  //playMel();
  for ( int j = 0 ; j < 6 ; j++ ) {
    deltas[j] = random(900,1000);
  }

// encoder pins
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
 
  pinMode(10,INPUT);
  
}



int ind=0;
void loop() {
  f_updateEncoder();
  if (prevCounter > counter) {
    add_arrays(6,deltas,shift,1);
    prevCounter = counter;
  }
  else if (prevCounter < counter) {
    add_arrays(6,deltas,shift,0);
    prevCounter = counter;
  }
  if (!digitalRead(10)) {
  for ( int i = 0 ; i < 6 ; i++ ) {
    if ( timer(i) ) {
     //writePosition();
     playRandNote();
     //lcd.clear();
     lcd.setCursor(ind,0);
     ind=ind+1;
     lcd.print(i); 
     lcd.setCursor(0,1);
     lcd.print(deltas[0]); 
     if (ind > 16) {ind = 0;}
    }
  }
  } 
  if (digitalRead(10)) {
    //f_readVolts();
    lcd.clear();
    randomNotes();
  }
}
