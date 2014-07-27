/* PCrazy shit 8-bit symphony generator                   */
/*     */
 
/*
 * inspired by:
 *  http://countercomplex.blogspot.com/2011/10/algorithmic-symphonies-from-one-line-of.html
 *
 *  http://wurstcaptures.untergrund.net/music/
 *
 */


int speakerPin = 11;
int speakerPin2 = 3;
int buttonPin = 12;

int pot0 = 0;
int pot1 = 1;
int pot2 = 2;
int pot3 = 3;

 
long t = 0; 

unsigned int p0 = 10;
unsigned int p1 = 4;
unsigned int p2 = 4;
unsigned int delta_T = 4;

int v = 0; 
 
void setup () {
 
  //TCCR0B = TCCR0B & 0b11111001; //no timer pre-scaler, fast PWM
  
  TCCR2B = TCCR2B & B11111000 | B00000001;    // set timer 2 divisor to     1 for PWM frequency of 31372.55 Hz

  //2CCR1B = TCCR1B & B11111000 | B00000001;
 
  pinMode (speakerPin, OUTPUT);
  pinMode (speakerPin2, OUTPUT);

  pinMode(buttonPin, INPUT);

  digitalWrite(buttonPin, HIGH);

  pinMode (pot0, INPUT);
  pinMode (pot1, INPUT);
  pinMode (pot2, INPUT);
  pinMode (pot3, INPUT);
  
  pinMode(buttonPin, INPUT_PULLUP);

 
}
 
void loop ()
{
 
    p0 = (analogRead(pot0)>>2);
    p1 = (analogRead(pot1)>>2);
    p2 = (analogRead(pot2)>>2);
    delta_T = ((1023 - (analogRead(pot3)))<<0);

     //v = (t*(t>>8|t>>4))>>(t>>p0);
     
     v = t * ((t>>p1|t>>p0)&p2&t>>(p0>>3));
     
     //v = (t|p0) * ((t>>p0|t>>11)&47&t>>3);
     
   // v = t * ((t>>p0|t>>p1)&p2&t>>5);
     
     //v = t * ((t>>p0|t>>3)&p1&t>>p2);
     
     //v =    t * ((t>>12|t>>p0)&p1&t>>p2);
    
    //v = t * ((t>>p0|t>>7)&p1&t>>(p2>>3));
    
    //v = t * ((t>>p1|t>>3)&17&t>>9);
    
    //v = (t|p1) * ((t>>p2|t>>11)&p0&t>>3);
    
    //v = t>>p0&1?t>>p2:-t>>p1 ;
    
    //v = (t|p0) * ((t>>1|t>>p1)&47&t>>p2);
    
    //v = t*t/p0;
    
    //v = t * ((t>>p0|t>>83)&7&t>>5);

    analogWrite (speakerPin2, v);
    digitalWrite (speakerPin, v);

    //delayMicroseconds(delta_T);
    
    delayMicroseconds((delta_T+1));

    t++;

}
