int pin_led = 13;
int pin_hall = 2;

volatile int last_millis = 0;

void update_speed() {
  int current_millis = millis();
  float rev_millis = current_millis - last_millis;
  last_millis = current_millis;
  if(rev_millis > 5 && rev_millis < 5000) {
    float speed_kph = 1 / rev_millis * 2206;
    Serial.print(speed_kph);
    Serial.print(" km/h\n");
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(13, OUTPUT); 
  attachInterrupt(0, update_speed, RISING);
}

void loop() {
  delay(1000);
}
