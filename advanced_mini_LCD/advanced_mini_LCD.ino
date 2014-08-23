/* PCrazy shit 8-bit symphony generator                   */
/*     */

/*
 * inspired by:
 *  http://countercomplex.blogspot.com/2011/10/algorithmic-symphonies-from-one-line-of.html
 *
 *  http://wurstcaptures.untergrund.net/music/
 *
 */


#include <SoftwareSerial.h>

#define txPin 7

SoftwareSerial LCD = SoftwareSerial(7, txPin);
// since the LCD does not send data back to the Arduino, we should only define the txPin
const int LCDdelay=2;  // conservative, 2 actually works

int speakerPin = 11;
int speakerPin2 = 3;
int buttonPin = 12;
int switchPin = 8;

int pot0 = 0;
int pot1 = 1;
int pot2 = 2;
int pot3 = 3;

int buttonState = 0; 
int lastButtonState = 0;
int count = -1;
 
long t = 0; 

unsigned int p0 = 10;
unsigned int p1 = 4;
unsigned int p2 = 4;
unsigned int delta_T = 4;

int v = 0; 
 
// wbp: goto with row & column
void lcdPosition(int row, int col) {
  LCD.write(0xFE);   //command flag
  LCD.write((col + row*64 + 128));    //position 
  delay(LCDdelay);
}
void clearLCD(){
  LCD.write(0xFE);   //command flag
  LCD.write(0x01);   //clear command.
  delay(LCDdelay);
}
void backlightOn() {  //turns on the backlight
  LCD.write(0x7C);   //command flag for backlight stuff
  LCD.write(157);    //light level.
  delay(LCDdelay);
}
void backlightOff(){  //turns off the backlight
  LCD.write(0x7C);   //command flag for backlight stuff
  LCD.write(128);     //light level for off.
   delay(LCDdelay);
}
void serCommand(){   //a general function to call the command flag for issuing all other commands   
  LCD.write(0xFE);
}
void selectLineOne(){  //puts the cursor at line 0 char 0.
   LCD.write(0xFE);   //command flag
   LCD.write(128);    //position
   delay(500);
}
void selectLineTwo(){  //puts the cursor at line 0 char 0.
   LCD.write(0xFE);   //command flag
   LCD.write(192);    //position
   delay(10);
}




 
void setup () {
 
  //TCCR0B = TCCR0B & 0b11111001; //no timer pre-scaler, fast PWM
  
  TCCR2B = TCCR2B & B11111000 | B00000001;    // set timer 2 divisor to     1 for PWM frequency of 31372.55 Hz

  //2CCR1B = TCCR1B & B11111000 | B00000001;
 
  pinMode (speakerPin, OUTPUT);
  pinMode (speakerPin2, OUTPUT);
    
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(switchPin, INPUT_PULLUP);

  pinMode (pot0, INPUT);
  pinMode (pot1, INPUT);
  pinMode (pot2, INPUT);
  pinMode (pot3, INPUT);

  
  pinMode(txPin, OUTPUT);
  LCD.begin(9600);
  clearLCD();
  lcdPosition(0,0);
  selectLineOne();
  LCD.print("8bit MixTape Pro");
  selectLineTwo();
  LCD.print("  Advanced 1980");
  delay(500);
  clearLCD();

 
}
 
void loop ()
{
  
// read the state of the switch into a local variable:
  buttonState = digitalRead(buttonPin);
  
  if (buttonState != lastButtonState && buttonState == HIGH) {
    // if the state has changed, increment the counter
    count++;
    t = 0; 
    delay(20); 
    
    if (count > 6) {
      count = 0;
    } 
      
    clearLCD();
    selectLineOne();
    LCD.print("8bit MixTape Pro");
      
      if (count == 0){
        selectLineTwo();
        LCD.print(count);
        LCD.print("-TEST"); 
      }  
      if (count == 1){
        selectLineTwo();
        LCD.print(count);
        LCD.print("-Zagreb6");
      }  
      if (count == 2){
        selectLineTwo();
        LCD.print(count);
        LCD.print("-classic");
      }
      if (count == 3){
        selectLineTwo();
        LCD.print(count);
        LCD.print("-Ficken");
      }
      if (count == 4){
        selectLineTwo();
        LCD.print(count);
        LCD.print("-Sausiech");
      }     
      if (count == 5){
        selectLineTwo();
        LCD.print(count);
        LCD.print("-lo mas");
      }     
      if (count == 6){
        selectLineTwo();
        LCD.print(count);
        LCD.print("-silence");
      }     
  } 
  
  lastButtonState = buttonState;
    
  switch(count) {
    
  case 0: // test
 
    p0 = ((analogRead(pot0)>>4)+0);
    p1 = (analogRead(pot1)>>4);
    p2 = ((analogRead(pot2)>>0)+0);
    delta_T = ((1023 - (analogRead(pot3)))>>0);
    
    v = ((((p0*t)/50)*(((p1*t)/50)>>8|t>>9)&((p2*46)/50)&t>>8))^(t&t>>13|t>>6);
    //v = t>>p2&1?t>>p1:-t>>p0;
    // v = (t|p2) * ((t>>p1|t>>11)&p0&t>>3);
    // bitMeat v = t*(((t>>(12+(p1/2)))|(t>>8))&((p0-(p2/2))&(t>>4)));

    analogWrite (speakerPin2, v);
    digitalWrite (speakerPin, v);
    delayMicroseconds((delta_T+1));
    t++;
    
  break; 
  
  case 6: // test
 
    p0 = ((analogRead(pot0)>>4)+0);
    p1 = (analogRead(pot1)>>4);
    p2 = ((analogRead(pot2)>>0)+0);
    delta_T = ((1023 - (analogRead(pot3)))>>0);
    
    v = t*(t^t+(t>>15|1)^(t-(p2-(p1/2))^t)>>(10-(pot0/5)));
    //v = t>>p2&1?t>>p1:-t>>p0;
    // v = (t|p2) * ((t>>p1|t>>11)&p0&t>>3);
    // bitMeat v = t*(((t>>(12+(p1/2)))|(t>>8))&((p0-(p2/2))&(t>>4)));

    analogWrite (speakerPin2, v);
    digitalWrite (speakerPin, v);
    delayMicroseconds((delta_T+1));
    t++;
    
  break; 
  
  case 1: // dubStep
 
    p0 = (analogRead(pot0)>>4);
    p1 = (analogRead(pot1)>>4);
    p2 = (analogRead(pot2)>>4);
    delta_T = ((1023 - (analogRead(pot3)))<<0);
    
    v = (t|p2) * ((t>>p1|t>>11)&p0&t>>3);

    analogWrite (speakerPin2, v);
    digitalWrite (speakerPin, v);
    delayMicroseconds((delta_T+1));
    t++;
    
  break;
    
  case 2: // a classic
 
    p0 = ((analogRead(pot0)>>5)+0);
    p1 = (analogRead(pot1)>>6);
    p2 = ((analogRead(pot2)>>5)+1);
    delta_T = ((1023 - (analogRead(pot3)))>>0);
     
    v = t * ((t>>p1|t>>p0)&p2&t>>(13>>3));

    analogWrite (speakerPin2, v);
    digitalWrite (speakerPin, v);
    delayMicroseconds((delta_T+1));
    t++;
    
  break;
  
  
  case 3: // a single
 
    p0 = ((analogRead(pot0)>>5)+0);
    p1 = (analogRead(pot1)>>6);
    p2 = ((analogRead(pot2)>>7)+1);
    delta_T = ((1023 - (analogRead(pot3)))>>0);
     
    v = t * ((t>>p2|t>>p0)&77&t>>(p1>>3));

    analogWrite (speakerPin2, v);
    digitalWrite (speakerPin, v);
    delayMicroseconds((delta_T+1));
    t++;
    
  break;
  
  case 5: // dubStep
 
    p0 = (analogRead(pot0)>>4);
    p1 = (analogRead(pot1)>>4);
    p2 = (analogRead(pot2)>>4);
    delta_T = ((1023 - (analogRead(pot3)))<<0);
    
    v = t>>p0&1?t>>p2:-t>>p1;

    analogWrite (speakerPin2, v);
    digitalWrite (speakerPin, v);
    delayMicroseconds((delta_T+1));
    t++;
    
  break;
  
  }  
 
  if ( digitalRead(switchPin) ==  HIGH){
    
    //clearLCD();
    selectLineOne();
    LCD.print("p2 ");  
    LCD.print(p2);
    LCD.print(" p1 "); 
    LCD.print(p1);
    LCD.print(" p0 "); 
    LCD.print(p0);
    LCD.print("     ");
    selectLineTwo();
    LCD.print("Speed ");  
    LCD.print(delta_T);
    LCD.print(" Song:");
    LCD.print(count);
  }
 
}

/*
     v = (t|3) * ((t>>1|t>>6)&c4&t>>3);
   v = t * ((t>>12|t>>7)&47&t>>(13>>3))  
     
     //v = (t*(t>>8|t>>4))>>(t>>p0);
     
     v = t * ((t>>p1|t>>p0)&p2&t>>(p0>>3));
     
     
     
     //v = (t|p0) * ((t>>p0|t>>11)&47&t>>3);
     
   // v = t * ((t>>p0|t>>p1)&p2&t>>5);
     
     //v = t * ((t>>p0|t>>3)&p1&t>>p2);
     
     //v =    t * ((t>>12|t>>p0)&p1&t>>p2);
    
    //v = t * ((t>>p0|t>>7)&p1&t>>(p2>>3));
    
    //v = t * ((t>>p1|t>>3)&17&t>>9);
    
    //v = (t|p1) * ((t>>p2|t>>11)&p0&t>>3);
    
    //v = t>>p0&1?t>>p2:-t>>p1;
    
    //v = (t|p0) * ((t>>1|t>>p1)&47&t>>p2);
    
    //v = t*t/p0;
    
    //v = t * ((t>>p0|t>>83)&7&t>>5);

    analogWrite (speakerPin2, v);
    digitalWrite (speakerPin, v);

    //delayMicroseconds(delta_T);
    
    delayMicroseconds((delta_T+1));
    
*/    
