volatile int last_millis = 0;
volatile float current_speed = 0;
float display_speed = 0;
int count = 0;

void update_speed() {
  int current_millis = millis();
  float rev_millis = current_millis - last_millis;
  last_millis = current_millis;
  if(rev_millis > 10 && rev_millis < 1000) {
    current_speed = 1 / rev_millis * 2206;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(0, update_speed, RISING);
}

void loop() {
  display_speed += (current_speed - display_speed)/2000;

  long current_millis = millis();
  long idle_millis = current_millis - last_millis;
  if(idle_millis > 1000) {
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
