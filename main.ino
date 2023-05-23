#define PRI_VERM 13
#define PRI_AMAR 12
#define PRI_VERD 11

#define SEC_VERM 10
#define SEC_AMAR 9
#define SEC_VERD 8

#define PRI_SENSOR 7
#define SEC_SENSOR 6

bool pri_semaforo = false;
bool sec_semaforo = false;

void setup()
{
  pinMode(PRI_VERM, OUTPUT);
  pinMode(PRI_AMAR, OUTPUT);
  pinMode(PRI_VERD, OUTPUT);

  pinMode(SEC_VERM, OUTPUT);
  pinMode(SEC_AMAR, OUTPUT);
  pinMode(SEC_VERD, OUTPUT);
  
  pinMode(PRI_SENSOR, INPUT);
  pinMode(SEC_SENSOR, INPUT);
}

void loop()
{
  int pri_sensor = !digitalRead(PRI_SENSOR);
  int sec_sensor = !digitalRead(SEC_SENSOR);
  
  if (!pri_sensor && !sec_sensor) {
    liga_sec_semaforo(false);
	liga_pri_semaforo(true);
    pri_semaforo = true;
    sec_semaforo = false;
  } else if (pri_sensor && !sec_sensor) {
    liga_sec_semaforo(false);
    liga_pri_semaforo(true);
    pri_semaforo = true;
    sec_semaforo = false;
  } else if (!pri_sensor && sec_sensor) {
    liga_pri_semaforo(false);
	liga_sec_semaforo(true);
    pri_semaforo = false;
    sec_semaforo = true;
  } else {
    if (pri_semaforo) {
      liga_pri_semaforo(false);
	  liga_sec_semaforo(true);
      pri_semaforo = false;
      sec_semaforo = true;
      delay(30 * 1000);
    } else {
      liga_sec_semaforo(false);
      liga_pri_semaforo(true);
      pri_semaforo = true;
      sec_semaforo = false;
      delay(30 * 1000);
    }
  }
}

void liga_pri_semaforo(bool liga) {
  if (!liga) {
    if (pri_semaforo) {
      delay(2000);
      digitalWrite(PRI_VERD, LOW);
      digitalWrite(PRI_AMAR, HIGH);
      delay(2000);
      digitalWrite(PRI_AMAR, LOW);
    }
    digitalWrite(PRI_VERM, HIGH);
  } else {
  	digitalWrite(PRI_VERM, LOW);
    digitalWrite(PRI_AMAR, LOW);
    digitalWrite(PRI_VERD, HIGH);
  }
}

void liga_sec_semaforo(bool liga) {
  if (!liga) {
    if (sec_semaforo) {
      delay(2000);
      digitalWrite(SEC_VERD, LOW);
      digitalWrite(SEC_AMAR, HIGH);
      delay(2000);
      digitalWrite(SEC_AMAR, LOW);
    }
    digitalWrite(SEC_VERM, HIGH);
  } else {
  	digitalWrite(SEC_VERM, LOW);
    digitalWrite(SEC_AMAR, LOW);
    digitalWrite(SEC_VERD, HIGH);
  }
}
