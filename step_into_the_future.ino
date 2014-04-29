volatile long last_micros = 0;
volatile float current_speed = 0;
volatile float rev_micros = 0;
float display_speed = 0;
long count = 0;

// this function is the interrupt executed on each rising edge coming from the hall sensor
void update_speed() {
  // get current time
  long current_micros = micros();
  // caculate difference
  rev_micros = current_micros - last_micros;
  // store current time for next time
  last_micros = current_micros;

  // sanity check (will fail when the sketch had just started, and also debounces the input)
  if(rev_micros > 10000 && rev_micros < 1000000) {
    // magic calulation happens here
    current_speed = 1 / rev_micros * 2206000;
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
  display_speed += (current_speed - display_speed)/2000;

  // get the current time
  long current_micros = micros();
  // calculate difference
  long idle_micros = current_micros - last_micros;

  // if the last interrupt is longer ago than 2 revolutions (with a maximum of 2 seconds)
  if(idle_micros > max(1000, rev_micros*2)) {
    // assume we are not moving, set current speed to 0
    current_speed = 0;
  }

  // start debug code
  count++;
  if(count > 500)
  {
    count = 0;
    Serial.print(display_speed);
    Serial.print("\n");
  }
  // end debug code
}
