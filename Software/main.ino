const int ledPin = 1;
const int digitalIn = 0

unsigned long previousMillis = 0;// will store last time LED was updated
int frequency = 2; // 2 Hz
long interval = 1000/frequency; // pause time

// Intensity specifications
int highState = 255;
int midState = 155;
int lowState = 55;
int offState = 0;

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

void setup() {

    Serial.begin(9600);

    // set the digital pin as output:
    pinMode(ledPin, OUTPUT);
    pinMode(digitalIn, INPUT)
}

void loop() {

    // digital in value
    int sensorVal = digitalRead(digitalIn);
    if buttonPressed(signal) {
        currentMode = incrementMode(currentMode)
    }

    switch (currentMode) {
    case 0:
        digitalWrite(ledPin, offState);
    case 1:
        digitalWrite(ledPin, highState);
    case 2:
        digitalWrite(ledPin, midState);
    case 3:
        digitalWrite(ledPin, lowState);
    case 4:
        unsigned long currentMillis = millis();
        if (currentMillis  previousMillis >= interval) {
            previousMillis = currentMillis;
            // if the LED is off turn it on and vice-versa:
            if (currentState == offState) {
                currentState = highState;
            } else {
                currentState = offState;
            }
            digitalWrite(ledPin, currentState);
        }
    default:
        digitalWrite(ledPin, offState);
    }
}


bool buttonPressed(int signal) {

    // going to make it simple for now
    if (signal > 150) // instead of 255...
        return true
    return false
}

int incrementMode(int currentMode) {

    if (currentMode <= maxModes-2) {
        return currentMode += 1
    }
    return 0
}
