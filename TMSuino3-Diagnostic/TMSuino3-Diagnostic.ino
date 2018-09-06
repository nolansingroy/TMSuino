
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

const int outpins[6] = { O1, O2, O3, O4, O5, O6 };
const int inpins[6] = { I1, I2, I3, I4, I5, I6 };
const int infopins[6] = { 1, 2, 3, 4, 5, 6 };
int values[6] = { 0,0,0,0,0,0 };
int value = 0;
const int threshold = 1015;
const int offthd = 10;

void beeeep() {
    digitalWrite(BUZZER, HIGH);
    delay(300);
    digitalWrite(BUZZER, LOW);
    delay(150);
}

void printNameOfPin(int p) {
    switch(p) {
        case A0 : Serial.print("A0"); break;
        case A1 : Serial.print("A1"); break;
        case A2 : Serial.print("A2"); break;
        case A3 : Serial.print("A3"); break;
        case A4 : Serial.print("A4"); break;
        case A5 : Serial.print("A5"); break;
        default : Serial.print(p); break;
    }
}

void checkAllOff() {
    for (int i=0; i < 13; i++) {
        digitalWrite(i, LOW);
    }  
    Serial.println("All outputs switched off, now checking inputs...");
    for (int i=0; i < 6; i++) {
        value = analogRead(inpins[i]);
        if (value > 5) {
            Serial.print("  There is incoming voltage on pin A");
            Serial.print(i);
            Serial.print(" value ");
            Serial.print(value);
            Serial.println(" but all outputs have been turned off. This is wrong!");
        }
    }
    Serial.println("...done");
    Serial.println();
}

//parameter is 1..6 !!!
void checkCoil(int coil) {
    Serial.print("  Testing coil ");
    Serial.print(coil);
    Serial.print(", it should be connected to ");
    Serial.print(outpins[coil-1]);
    Serial.print(" and ");
    printNameOfPin(inpins[coil-1]); 
    Serial.print(": ");
    digitalWrite(outpins[coil-1],HIGH);
    delay(20);
    for (int i=0; i < 6; i++) values[i] = analogRead(inpins[i]);
    
    delay(40);
    for (int i=0; i < 6; i++) {
        value = values[i];
        if (i == coil-1) {
            if (value > threshold) Serial.println("OK");
            else Serial.println("ERROR");
        }
    }
    Serial.println();
    digitalWrite(outpins[coil-1], LOW);
    delay(200);
}

void test() {
    digitalWrite(BUZZER, LOW);
    //checkAllOff();
    Serial.println("\nStarting test:\n");
    for (int i=0; i < 6; i++) checkCoil(i+1);
    Serial.println("Test sequence done.\n");
    //digitalWrite(LED, HIGH); 
    Serial.println("This test will be repeated in 60 seconds...\n");
}



void setup() {
    Serial.begin(9600);
  

  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);
  
  for (int i=0; i < 6; i++) {
      pinMode(outpins[i], OUTPUT);
      pinMode(inpins[i], INPUT);
      pinMode(infopins[i], OUTPUT);
      digitalWrite(outpins[i], LOW);
      digitalWrite(infopins[i], LOW);
  }
  
  beeeep(); beeeep(); beeeep(); beeeep();
}

void loop() {
    test();
    beeeep(); beeeep(); beeeep(); beeeep();
    delay(60000);
}
