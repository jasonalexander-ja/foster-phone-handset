#include <songs.h>
#include <PlayRtttl.hpp>

#define PIEZO_PIN 2
#define HALL_READ 26
#define HALL_PULSE 27


void setup() {
  analogReadResolution(12);
  delay(1000);
  pinMode(PIEZO_PIN, OUTPUT);
  pinMode(HALL_PULSE, OUTPUT);
  digitalWrite(HALL_PULSE, HIGH);
  randomSeed(analogRead(28));
}

void loop() {
  while (true) {
    long int reads = readHall();
    if (reads > 1000) break;
  }
  delay(750);
  int songNo = random(0, 26);
  startPlayRtttlPGM(PIEZO_PIN, song[songNo]);

  while (updatePlayRtttl()) {
    long int reads = readHall();
    if (reads < 200) {
      stopPlayRtttl();
      return;
    }
  }
  while (true) {
    long int reads = readHall();
    if (reads < 200) break;
  }
}

long int readHall() {
    long int reads = 0;

    for (int i = 0; i < 10; i++) {

      digitalWrite(HALL_PULSE, LOW);
      delay(10);
      digitalWrite(HALL_PULSE, HIGH);
      delay(10);
      reads += analogRead(HALL_READ);
    }

    return reads / 10;
}
