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
  startPlayRtttlPGM(PIEZO_PIN, getSong(songNo));

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

char* getSong(int number) {
  switch (number) {
    case 0: return "Imperial:d=4,o=5,b=80:8d.,8d.,8d.,8a#4,16f,8d.,8a#4,16f,d.,32p,8a.,8a.,8a.,8a#,16f,8c#.,8a#4,16f,d.,32p,8d.6,8d,16d,8d6,32p,8c#6,16c6,16b,16a#,8b,32p,16d#,8g#,32p,8g,16f#,16f,16e,8f,32p,16a#4,8c#,32p,8a#4,16c#,8f.,8d,16f,a.,32p,8d.6,8d,16d,8d6,32p,8c#6,16c6,16b,16a#,8b,32p,16d#,8g#";
    case 1: return "Mission:d=4,o=6,b=100:32d,32d#,32d,32d#,32d,32d#,32d,32d#,32d,32d,32d#,32e,32f,32f#,32g,16g,8p,16g,8p,16a#,16p,16c,16p,16g,8p,16g,8p,16f,16p,16f#,16p,16g,8p,16g,8p,16a#,16p,16c,16p,16g,8p,16g,8p,16f,16p,16f#,16p,16a#,16g,2d,32p,16a#,16g,2c#,32p,16a#,16g,2c,16p,16a#5,16c";
    case 2: return "Poison:d=4,o=5,b=112:8d,8d,8a,8d,8e6,8d,8d6,8d,8f#,8g,8c6,8f#,8g,8c6,8e,8d,8d,8d,8a,8d,8e6,8d,8d6,8d,8f#,8g,8c6,8f#,8g,8c6,8e,8d,8c,8d,8a,8d,8e6,8d,8d6,8d,8f#,8g,8c6,8f#,8g,8c6,8e,8d,8c,8d,8a,8d,8e6,8d,8d6,8d,8a,8d,8e6,8d,8d6,8d,2a,8d";
    case 3: return "Postman Pat:d=4,o=5,b=100:16f#,16p,16a,16p,8b,8p,16f#,16p,16a,16p,8b,8p,16f#,16p,16a,16p,16b,16p,16d6,16d6,16c#6,16c#6,16a,16p,b.,8p,32f#,16g,16p,16a,16p,16b,16p,16g,16p,8f#.,8e,8p,32f#,16g,16p,16a,16p,32b.,32b.,16g,16p,8f#.,8e,8p,32f#,16g,16p,16a,16p,16b,16p,16g,16p,16f#,16p,16e,16p,16d,16p,16c#,16p,2d";
    case 4: return "StarWars:d=4,o=5,b=180:8f,8f,8f,2a#.,2f.6,8d#6,8d6,8c6,2a#.6,f.6,8d#6,8d6,8c6,2a#.6,f.6,8d#6,8d6,8d#6,2c6,p,8f,8f,8f,2a#.,2f.6,8d#6,8d6,8c6,2a#.6,f.6,8d#6,8d6,8c6,2a#.6,f.6,8d#6,8d6,8d#6,2c6";
    case 5: return "Under The sea:d=4,o=5,b=200:8d,8f,8a#,d6,d6,8a#,c6,d#6,d6,a#,8a#4,8d,8f,a#,a#,8c,a,c6,a#,p,8d,8f,8a#,d6,d6,8a#,c6,d#6,d6,a#,8a#4,8d,8f,a#,a#,8c,a,c6,16a#,16d,16a#,16d,16a#,16d,16a#";
    case 6: return "Verve:d=4,o=5,b=125:8b4,8d,8b4,8c,8a4,8c,8p,8f,8c,8f,8p,8e,8c,8e,8p,8b4,8d,8b4,8c,8a4,8c,8p,8f,8c,8f,8p,8e,8c,8e,8p,8d,8b4,8d,8b4,8p,8c,8c,8p,8f,8c,8f,8g,8e,8c,8e,8p,8b4,8d,8b4,8c,8a4,8c,8p,8f,8c,8f,8p,8e,8c,8e";
    case 7: return "Alice Deejay - Better Off Alone : d=4,o=5,b=125:a,8a,f#,a,a,g#,8e,8e.6,8e.6,8c#6,a,8a,f#,a,a,g#,8e,8d.6,8d.6,8c#6,a,8a,f#,a,a,g#,8e,8e.6,8e.6,8c#6,a,8a,f#,a,a,g#,8d,8d.6,8d.6,8c#6";
    case 8: return "ATC - Around The World : d=4,o=5,b=140:8e6,8a,8c6,8e6,8b,8e,8g,8b,8c6,8f,8a,8c6,8d6,8g,8b,8d6,8e6,8a,8c6,8e6,8b,8e,8g,8b,8c6,8f,8a,8c6,8d6,8g,8b,8d6,8e6,8a,8c6,8e6,8b,8e,8g,8b,8c6,8f,8a,8c6,8d6,8g,8b,8d6";
    case 9: return "Eiffel 65 - Blue : d=4,o=5,b=125:a,8a#,8d,8g,8a#,8c6,8f,8a,a#,8g,8a#,8d6,8d#6,8g,8d6,8c6,8a#,8d,8g,8a#,8c6,8f,8a,a#,8g,8a#,8d6,8d#6,8g,8d6,8c6,8a#,8d,8g,8a#,8a,8c,8f,g.";
    case 10: return "Darude - Sandstorm : d=4,o=5,b=225:8e,8e,8e,8e,8e.,8e,8e,8e,8e,8e,8e,8e.,8a,8a,8a,8a,8a,8a,8a.,8g,8g,8g,8g,8g,8g,8g.,8d,8d,8d,8d,8d,8d,8d.,8e,8e,8e,8e,8e,8e,8e.,8a,8a,8e,8e,8e,8e,8e,8e,8e.";
    case 11: return "Together:d=8,o=5,b=225:4d#,f.,c#.,c.6,4a#.,4g.,f.,d#.,c.,4a#,2g#,4d#,f.,c#.,c.6,2a#,g.,f.,1d#.,d#.,4f,c#.,c.6,2a#,4g.,4f,d#.,f.,g.,4g#.,g#.,4a#,c.6,4c#6,4c6,4a#,4g.,4g#,4a#,2g#";
    case 12: return "Layla:d=4,o=5,b=125:4p,16a5,16c6,16d6,16f6,16d6,16c6,4d6,8p,4g6,4f6,4e6,4c6,4d6,16p,16a5,16c6,16d6,16f6,16d6,16c6,4d6,8p,4a6,4g6,4e6,4c6,4d6";
    case 13: return "Gay Bar:d=16,o=5,b=180:8d.,p,d,p,f,p,g,p,f,p,32d,p.,32c#,p.,8c.,p,32c,p.,8a.4,p,32c,p.,32c#,p.,32c,p.,8d.,p,d,p,f,p,g,p,f,p,d,p,32c#,p.,8c.,p,32c,p.,8a.4,p,c,p,32c#,p.,32c,p.,8d.,p,d,p,f,p,g,p,f,p,d,p,32c#,p.,8c.,p,32c,p.,8a.4,p,c,p,32c#,p.,32c,p.,8d.,p,d,p,f,p,g,p,f,p,d,p,32c#,p.,8c.,p,32c,p.,8a.4,p,c,p,32c#,p.,32c,p.,8d.,p,d,p,f,p,g,p,f,p,d,p,32c#,p.,8c.,p,32c,p.,8a.4,p,c,p,32c#,p.,32c";
    case 14: return "JustCant:d=4,o=5,b=63:16c,16p,16c,16p,32c,32p,32c,16c,16d,16e,16c,16p,16c,16p,32c,32p,32c,16c,16d,16e,16c,16p,16c,16p,32c,32p,32c,16c,16d,16e,16f,16p,16e,16p,16d,16p,16e,16p,16c,16p,16c,16p,32c,32p,32c,16c,16d,16e,16c,16p,16c,16p,32c,32p,32c,16c,16d,16e,16c,16p,16c,16p,32c,32p,32c,16c,16d,16e,16f,16p,16e,16p,16d,16p,16e,16p";
    case 15: return "Sandstor:d=4,o=5,b=125:16e,16e,16e,16e,8e,16e,16e,16e,16e,16e,16e,8e,16a,16a,16a,16a,16a,16a,8a,16g,16g,16g,16g,16g,16g,8g,16d,16d,16e,16e,16e,16e,8e,16e,16e,16e,16e,16e,16e,8e,16a,16a,16e,16e,16e,16e,8e,16e,16e,16e,16e,16e,16e,8e";
    case 16: return "WeLikeTo:d=4,o=5,b=25:32p,16c#6,32a#,32g#,16c#6,32a#,32g#.,32c#6,32a#,32g#,32c#.6,32a#,32g#,32c.6,32d#.6,32c.6,32g#,32c.6,32c6,32d#6,32d#6,32c.6,32a#,32g#,32c#.6,32a#,32g#,32c#.6,32a#,32g#.,32c#6,32a#,32g#,32c#.6,32a#,32g#,32c.6,32d#.6,32c.6,32a#,16g#";
    case 17: return "BoomBoom:d=4,o=5,b=138:16a#6,16p,16a#6,16p,16g#6,16p,8f#6,8p,16c#6,16c#6,16p,16c#6,16p,16g#6,16p,8f#6,8p,16c#6,16c#6,16c#6,16p,16c#6,16p,16f#6,16p,16f#6,8p,16f#6,16p,8a#6,16p,8g#6,16p,8f#6";
    case 18: return "Ghostbus:d=16,o=5,b=112:g,g,8b,8g,8a,4f.,g,g,g,g,8f,4g.,g,g,8b,8g,8a,4f.,g,g,g,g,8f,8a,8g,4d.,g,g,8b,8g,8a,4f.,g,g,g,g,8f,4g.";
    case 19: return "ClubbedT:d=8,o=5,b=125:p,d,g,d,a#,d,g,d,c6,d,f#,d,a,d,f#,d,p,d,g,d,d6,d,a#,d,a#,c,d#,c,a,d#,c6,d#,p,d,g,d,a#,g,d6,a#,g6,g,a#,g,d#6,a#,g6,a#,g6,g,b,g,d6,b,f6,b,f6,g,c6,f6,d#6,g,c6,d#6,d6,d,g,d,a#,d,g,d,a#,c,d#,a#,a,c,d,f#,g,g4,a#4,d,g,d,a#,g,d6,a#,g6,d6,a#6,g6,d7,d7";
    case 20: return "HamsterD:d=16,o=6,b=140:g#,g,8g#,8e,8e,e,8b5.,4b5,4g#,8b5,g#,8a,2b.,e7,c#7,b,c#7,b,g#,b,g#,f#,e,c#,e,f#,e,g#,b,g#,b,f#,e,8c#,2e";
    case 21: return "KnightRider:d=4,o=5,b=63:16e,32f,32e,8b,16e6,32f6,32e6,8b,16e,32f,32e,16b,16e6,d6,8p,p,16e,32f,32e,8b,16e6,32f6,32e6,8b,16e,32f,32e,16b,16e6,f6,p";
    case 22: return "Aqua Barbie girl I:d=4,o=5,b=125:32e,32f#,8g#,8e,8g#,8c#6,a,8p,16p,16g#,8f#,8d#,8f#,8b,g#,8f#,8e,p,8e,8c#,f#,c#,p,8f#,8e,g#,f#,16e,16p,16e,16p,8c#4,8b4,16e,16p,16e,16p,8c#4,8b4,b,g#,e,c#4,16e,16p,16e,16p,8c#4,8b4,16e,16p,16e,16p,8c#4,8b4,8p,8c#6,8b,8c#6,8p,8c#6,8b,8c#6";
    case 23: return "Axel-F:d=4,o=5,b=125:g,8a#.,16g,16p,16g,8c6,8g,8f,g,8d.6,16g,16p,16g,8d#6,8d6,8a#,8g,8d6,8g6,16g,16f,16p,16f,8d,8a#,2g,p,16f6,8d6,8c6,8a#,g,8a#.,16g,16p,16g,8c6,8g,8f,g,8d.6,16g,16p,16g,8d#6,8d6,8a#,8g,8d6,8g6,16g,16f,16p,16f,8d,8a#,2g";
    case 24: return "we-rock:d=4,o=6,b=80:32f#6,32f#6,16f#6,16f#6,16e6,16e6,16d.6,16a.5,32a5,32a5,16a5,16a5,16e6,16e6,16d.6,16b.5,32d6,32d6,16d6,16d6,16d6,16e6,16f#.6,16d.6,16g5,16g5,16g5,16g5,16g5,16f#.5,16d.6,32f#6,32f#6,16f#6,16f#6,16e6,16e6,16d.6,16a.5,16a5,16a5,16a5,16e6,16e6,16d.6,16b.5,32d6,32d6,16d6,16d6,16d6,16e6,16f#.6,16d.6,16g5,16g5,16g5,16g5,16g5,16f#.5,32d6";
    case 25: return "Rick Astley:d=8,o=5,b=225:4d#,f.,c#.,c.6,4a#.,4g.,f.,d#.,c.,4a#,2g#,4d#,f.,c#.,c.6,2a#,g.,f.,1d#.,d#.,4f,c#.,c.6,2a#,4g.,4f,d#.,f.,g.,4g#.,g#.,4a#,c.6,4c#6,4c6,4a#,4g.,4g#,4a#,2g#";
  }
}
