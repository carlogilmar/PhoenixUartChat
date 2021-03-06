#include <LedControl.h>
#include <Keypad.h>

/* Keypad */
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

/* Matrix LED */
int DIN = 13;
int CS =  12;
int CLK = 11;
int incomingByte = 0;
int sensorPin = 0;

int photoState = 0;// 0 apagado 1 prendido

const int led1 = 22;
const int led2 = 23;
const int led3 = 24;
const int led4 = 25;

const int led5 = 26;
const int led6 = 27;
const int led7 = 28;
const int led8 = 29;

LedControl lc=LedControl(DIN,CLK,CS,0);

    //https://gurgleapps.com/tools/matrix

    byte a[8] = {0x83,0xc6,0x6c,0x38,0x1c,0x36,0x63,0xc1};
    byte b[8] = {0x18,0x18,0x18,0xff,0xff,0x18,0x18,0x18};
    byte c[8] = {0x3c,0x08,0x89,0xf9,0x9f,0x11,0x10,0x38};
    byte d[8] = {0x70,0x11,0x11,0x1f,0xf8,0x88,0x88,0x0e};

    //pacman
    byte pacman1[8] = {0x3c,0x7e,0xf4,0xf8,0xf0,0xf8,0x7c,0x3e};
    byte pacman2[8] = {0x3c,0x7e,0xf6,0xff,0xff,0xfe,0x7e,0x3c};

    //hi!
    byte hi1[8] = {0xc3,0xc3,0xc3,0xff,0xff,0xc3,0xc3,0xc3};
    byte hi2[8] = {0x3c,0x7e,0xe7,0xc3,0xc3,0xe7,0x7e,0x3c};
    byte hi3[8] = {0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xff,0xff};
    byte hi4[8] = {0x18,0x3c,0x66,0x66,0x7e,0x7e,0x66,0x66};

    byte song1[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    byte song2[8] = {0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00};
    byte song3[8] = {0x00,0x3c,0x42,0x5a,0x5a,0x42,0x3c,0x00};
    byte song4[8] = {0x42,0xbd,0x42,0x5a,0x5a,0x42,0xbd,0x42};
    byte song5[8] = {0xc3,0xbd,0x42,0x5a,0x5a,0x42,0xbd,0xc3};
    byte song6[8] = {0xff,0xff,0xff,0xe7,0xe7,0xff,0xff,0xff};
    byte song7[8] = {0xff,0xff,0xdb,0xe7,0xe7,0xdb,0xff,0xff};
    byte song8[8] = {0xff,0xff,0xc3,0xc3,0xc3,0xc3,0xff,0xff};
    byte song9[8] = {0xff,0x81,0x81,0x81,0x81,0x81,0x81,0xff};
    byte song10[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

        
void setup(){
 Serial.begin(9600);
 lc.shutdown(0,false);       //The MAX72XX is in power-saving mode on startup
 lc.setIntensity(0,15);      // Set the br1ightness to maximum value
 lc.clearDisplay(0);         // and clear the display
 pinMode( led1, OUTPUT);
 pinMode( led2, OUTPUT);
 pinMode( led3, OUTPUT);
 pinMode( led4, OUTPUT);
 pinMode( led5, OUTPUT);
 pinMode( led6, OUTPUT);
 pinMode( led7, OUTPUT);
 pinMode( led8, OUTPUT);
}

void loop(){ 
   
   int valueAnalog = analogRead(sensorPin);
   int key = keypad.getKey();
    
   if (Serial.available() > 0) {
    incomingByte = Serial.read(); // read the incoming byte:
    if( incomingByte == 49 ) { playPacman(); }
   }
  
  if (key){
    Serial.println(key);
  }

  
  if( valueAnalog < 500 ){
    //Luz apagada
    if( photoState == 1 ){
      photoState = 0;   
      Serial.println("play");
    }
    
    playSong1();
    playLeds
    ();
    //digitalWrite(led1 , HIGH);
    
  } else {
    // luz encendida
    if( photoState == 0 ){
      photoState = 1;
      Serial.println("stop");
      leds_off();  
    }  
    //digitalWrite(ledPin , LOW);
  }
  
}

void playLeds(){
  leds_on();
  delay(50);
  leds_off();
  delay(50);
  leds_on();
  delay(50);
  leds_off();
  delay(50);
  leds_on();
  delay(50);
  leds_off();
  delay(50);
}


void leds_on(){
  digitalWrite(led1 , HIGH);
  digitalWrite(led2 , HIGH);
  digitalWrite(led3 , HIGH);
  digitalWrite(led4 , HIGH);
  digitalWrite(led5 , HIGH);
  digitalWrite(led6 , HIGH);
  digitalWrite(led7 , HIGH);
  digitalWrite(led8 , HIGH);
}

void leds_off(){
  digitalWrite(led1 , LOW);
  digitalWrite(led2 , LOW);
  digitalWrite(led3 , LOW);
  digitalWrite(led4 , LOW);
  digitalWrite(led5 , LOW);
  digitalWrite(led6 , LOW);
  digitalWrite(led7 , LOW);
  digitalWrite(led8 , LOW);
}

void playMessage(){
    printByte(a);    
    delay(150);
    printByte(b);    
    delay(150);
    printByte(c);    
    delay(150);
    printByte(d);    
    delay(150);
    lc.clearDisplay(0);
}

void playPacman(){
    printByte(pacman1);    
    delay(250);
    printByte(pacman2);    
    delay(250);
    printByte(pacman1);    
    delay(250);
    printByte(pacman2);    
    delay(250);
    lc.clearDisplay(0);
}

void playHi(){
    printByte(hi1);    
    delay(250);
    printByte(hi2);    
    delay(250);
    printByte(hi3);    
    delay(250);
    printByte(hi4);    
    delay(250);
    lc.clearDisplay(0);
}

void playSong1(){
    printByte(song1);    
    delay(250);
    printByte(song2);    
    delay(250);
    printByte(song3);    
    delay(250);
    printByte(song4);    
    delay(250);
    printByte(song5);    
    delay(250);
    printByte(song6);    
    delay(250);
    printByte(song7);    
    delay(250);
    printByte(song8);    
    delay(250);
    printByte(song9);    
    delay(250);
    printByte(song10);    
    delay(250);
    lc.clearDisplay(0);
}

void printByte(byte character [])
{
  int i = 0;
  for(i=0;i<8;i++)
  {
    lc.setRow(0,i,character[i]);
  }
}

