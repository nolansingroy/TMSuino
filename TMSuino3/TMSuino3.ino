

#define O1  (7)
#define O2  (8)
#define O3  (9)
#define O4 (10)
#define O5 (11)
#define O6 (12)

#define I1 (A0)
#define I2 (A1)
#define I3 (A2)
#define I4 (A3)
#define I5 (A4)
#define I6 (A5)

#define BUZZER (13)

#define INTENSITY_LOW       (200)    //overall delay should be close to 220ms
#define INTENSITY_MIDDLE    (100)
#define INTENSITY_HIGH       (50)
#define INTENSITY_VERY_HIGH  (10)
#define USED_INTENSITY       (INTENSITY_VERY_HIGH)
//note: 20ms delay are always added to set intensity delay,
//      this is waiting time for the voltage to pull up.

//#define DEBUG_ON

#ifdef DEBUG_ON
  #define DEBUG_PRINT_INIT Serial.begin(9600);
  #define DEBUG_PRINT Serial.println(value)
#else
  #define DEBUG_PRINT_INIT 
  #define DEBUG_PRINT 
#endif


const int outpins[6] = { O1, O2, O3, O4, O5, O6 };
const int inpins[6] = { I1, I2, I3, I4, I5, I6 };
const int infopins[6] = { 1, 2, 3, 4, 5, 6 };
int value = 0;
const int threshold = 1015;
int buzState = 0;
int loopCnt = 0;
int loopNum = 480;
long fastCnt = 0L;

void beep() {
    digitalWrite(BUZZER, HIGH);
    delay(60);
    digitalWrite(BUZZER, LOW);
    delay(100);
}

void beeeep() {
    digitalWrite(BUZZER, HIGH);
    delay(300);
    digitalWrite(BUZZER, LOW);
    delay(150);
}

void toggleBUZZER() {
    buzState = 1 - buzState;
    digitalWrite(BUZZER, buzState);
}

void infoLeds(int coil) {
  for (int i=0; i < 6; i++) {
      digitalWrite(infopins[i], HIGH);
  }
  digitalWrite(infopins[coil-1], LOW);
}

void error(int coil) {
    infoLeds(coil);
    //endless loop toggling BUZZER on/off
    while (true) {
        toggleBUZZER();
        delay(100);  
    }
}

//parameter is 1..6, *not* 0..5
inline void deactivate(int coil) {
    digitalWrite(outpins[coil-1], LOW);
}

//parameter is 1..6, *not* 0..5
inline void activate(int coil) {
    digitalWrite(outpins[coil-1], HIGH);
}

//parameter is 1..6, *not* 0..5
void writeAndCheckInput(int coil) {
    activate(coil);
    delay(20); //wait for the inpin to pull up
    
    value = analogRead(inpins[coil-1]);
    DEBUG_PRINT;
    if (value < threshold) error(coil);
    
    value = analogRead(I1);
    DEBUG_PRINT;
    if (value < threshold) error(1);
    
    value = analogRead(I4);
    DEBUG_PRINT;
    if (value < threshold) error(4);
}

void setup() {
  DEBUG_PRINT_INIT;

  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);
  
  for (int i=0; i < 6; i++) {
      pinMode(outpins[i], OUTPUT);
      pinMode(inpins[i], INPUT);
      pinMode(infopins[i], OUTPUT);
      digitalWrite(outpins[i], LOW);
      digitalWrite(infopins[i], LOW);
  }
  
  activate(1);
  activate(4);

  beeeep(); beep(); beeeep();
}

void fastloop() {
  #define MU_DELAY (100)
  fastCnt = 0L;
  while (fastCnt < 140000L) { //for approx. 1 minute do fastloop without tests
    deactivate(6);
    activate(2);
    delayMicroseconds(MU_DELAY);

    deactivate(2);
    activate(3);
    delayMicroseconds(MU_DELAY);
    fastCnt++;
    deactivate(3);
    activate(5);
    delayMicroseconds(MU_DELAY);

    deactivate(5);
    activate(6);
    delayMicroseconds(MU_DELAY);
  }
}

void loop() {
  deactivate(6);
  writeAndCheckInput(2);
  delay(USED_INTENSITY);

  deactivate(2);
  writeAndCheckInput(3);
  delay(USED_INTENSITY);
  loopCnt++;

  deactivate(3);
  writeAndCheckInput(5);
  delay(USED_INTENSITY);

  deactivate(5);
  writeAndCheckInput(6);
  delay(USED_INTENSITY);

  if (loopCnt > loopNum) {
      beep();
      fastloop(); //switch to fastloop after approx 10 seconds
      beep();
      loopCnt = 0;
      loopNum = 80;
  }
}

