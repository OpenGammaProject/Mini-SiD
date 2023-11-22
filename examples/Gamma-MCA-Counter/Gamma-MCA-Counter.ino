/*

  Simple scintillation counter sketch for an
  Arduino Uno + Mini SiD + Buzzer

  Triggers on newly detected pulses and outputs events
  compatible with Gamma MCA: https://spectrum.nuclearphoenix.xyz/
  Compatible with an external buzzer for clicking.

  2023, NuclearPhoenix. Open Gamma Project.
  https://github.com/OpenGammaProject/Mini-SiD

  Initial Hackaday log:
  https://hackaday.io/project/188090-mini-sipm-driver-board/log/213532-simple-scintillation-counter-example

*/

volatile uint32_t counts = 0;  // How many pulses have been registered

void eventInt() {
  digitalWrite(LED_BUILTIN, HIGH);
  counts++;
  // Use Buzzer to click for every count
  // Slows down the counter (much higher dead time) a lot, especially the ancient UNO
  tone(9, 3000, 3);
  digitalWrite(LED_BUILTIN, LOW);
}


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(9, OUTPUT);  // Use Pin 9 as PWM buzzer output
  pinMode(10, INPUT);  // Use Pin 10 as INT input

  attachInterrupt(digitalPinToInterrupt(2), eventInt, RISING);

  Serial.begin(2000000);  // Basically as fast as possible
  Serial.println("Hello World!");
}


void loop() {
  unsigned long start = millis();

  static uint32_t old = 0;

  for (uint16_t index = 0; index < counts - old; index++) {
    Serial.print("0;");
  }
  Serial.println();

  old = counts;

  delay(1000 - (millis() - start));  // Clock out new events exactly every second
}
