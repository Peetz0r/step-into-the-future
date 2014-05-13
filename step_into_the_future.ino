volatile long last_millis = 0;
volatile float current_speed = 0;
volatile float rev_millis = 0;
float display_speed = 0;
long count = 0;

// this function is the interrupt executed on each rising edge coming from the hall sensor
void update_speed() {
  // get current time
  long current_millis = millis();
  // caculate difference
  rev_millis = current_millis - last_millis;
  // store current time for next time
  last_millis = current_millis;

  // sanity check (will fail when the sketch had just started, and also debounces the input)
  if (rev_millis > 10 && rev_millis < 1000) {
    // magic calulation happens here
    current_speed = 1 / rev_millis * 2206;
  }
}

void setup() {
  // Serial is only used for debugging
  Serial.begin(115200);
  // our sensor requires a pullup resistor
  pinMode(2, INPUT_PULLUP);
  // register the interrupt handle
  attachInterrupt(0, update_speed, RISING);
}

// the loop function is supposed to smooth the readings
void loop() {
  // adjust the display speed a little bit towards the actual value
  display_speed += (current_speed - display_speed) / 100;

  // get the current time
  long current_millis = millis();
  // calculate difference
  long idle_millis = current_millis - last_millis;
  
  int value = max(0, (255-(display_speed*10)));
  analogWrite(11, value);

  // if the last interrupt is more than 500 milliseconds ago
  if (idle_millis > 500) {
    // assume we are not moving, set current speed to 0
    current_speed = 0;
  }

  count++;
  if (count > 500) {
    if (display_speed > 0.1) {
      count = 0;
      Serial.print(display_speed);
      Serial.print(" km/h\n");
    }
  }
  delay(10);
}
