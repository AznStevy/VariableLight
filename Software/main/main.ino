const int ledPin = 6;
const int digitalIn = 3;

unsigned long currentMillis = millis();
unsigned long previousMillis = 0;// will store last time LED was updated
int frequency = 4; // 2 Hz
long interval = 1000/frequency; // pause time

// Intensity specifications
int highState = 255;
int midState = (int) highState/4;
int lowState = (int) highState/8;
int offState = 0;

int pwd_out = offState;
int currentState = 0; // mainly for blinking

/* Current mode (default off (0))
0: off
1: highState
2: midState
3: lowState
4: blinking
*/
int maxModes = 5;
int currentMode = 0;
unsigned long lastPress = millis();

/* Button */
int currentButtonState = 0;
int previousButtonState = 0;

void setup() {
    Serial.begin(9600);

    // set the digital pin as output:
    pinMode(ledPin, OUTPUT);
    pinMode(digitalIn, INPUT);
    attachInterrupt(digitalPinToInterrupt(digitalIn), incrementMode, RISING);
}

void loop() {
    // digital in value
    if (currentMode != 4) {
        analogWrite(ledPin, pwd_out);
    }
    
    if (currentMode == 0)
        pwd_out = offState;
    else if (currentMode == 1)
        pwd_out = highState;
    else if (currentMode == 2)
        pwd_out = midState;
    else if (currentMode == 3)
        pwd_out = lowState;
    
    if (currentMode == 4) {
        currentMillis = millis();
        if (currentMillis - previousMillis >= interval) {
            previousMillis = currentMillis;
            // if the LED is off turn it on and vice-versa:
            if (currentState == offState) {
                currentState = highState;
            } else {
                currentState = offState;
            }
            analogWrite(ledPin, currentState);
        }
    }
}


int incrementMode() {
    if ((millis() - lastPress) >= 500) {
        Serial.println(millis() - lastPress);
        if (currentMode <= maxModes-2) {
            currentMode += 1;
        } else {
            currentMode = 0;
        }
        lastPress = millis();
        Serial.println(currentMode);
    }
    
}
