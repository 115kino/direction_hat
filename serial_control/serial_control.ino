#define N_PINS 5
int pins[N_PINS] = {12, 11, 10, 9, 8};

unsigned int default_cpin_map = (1 << 0) & (1 << 2) & (1 << 4);
unsigned int cpin_map = default_cpin_map;
boolean blink_value = true;

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete


void light_leds(unsigned int pin_map) {
  for (int i = 0; i < N_PINS; ++i) {
    boolean pin_on = boolean(pin_map & (1<<i));
    digitalWrite(pins[i], pin_on?HIGH:LOW);
  }
}

void setup() {
  for (int i = 0; i < N_PINS; ++i) {
    pinMode(pins[i], OUTPUT);
  }
  
  light_leds(cpin_map);
  Serial.begin(9600);
}

void loop() {
  if (stringComplete) {
    cpin_map = atoi(inputString.c_str());
    inputString = "";
    stringComplete = false;
    Serial.println(inputString);
  }
  light_leds(cpin_map);;
  delay(100);
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
}
