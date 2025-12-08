// Arduino UNO - HC-SR04 + Buzzer + Serial
const int trigPin = 7;
const int echoPin = 6;
const int buzzerPin = 9;

unsigned long lastMeasureMs = 0;
const unsigned long measureInterval = 2000; // 2s entre mesures

void setup() {
  Serial.begin(9600); // communique avec Qt (COM5)
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);
}

long measureDistanceCm() {
  // Envoyer impulsion
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // timeout 30ms
  if (duration == 0) return -1; // erreur
  long distanceCm = duration / 29 / 2;
  return distanceCm;
}

void loop() {
  // Lecture du port série (commands from Qt)
  if (Serial.available() > 0) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    if (cmd.equalsIgnoreCase("BUZZER_ON")) {
      digitalWrite(buzzerPin, HIGH);
      Serial.println("ACK_BUZZER_ON");
    } else if (cmd.equalsIgnoreCase("BUZZER_OFF")) {
      digitalWrite(buzzerPin, LOW);
      Serial.println("ACK_BUZZER_OFF");
    } else if (cmd.equalsIgnoreCase("PING")) {
      Serial.println("PONG");
    }
    // ignore other commands
  }

  // Mesures périodiques
  if (millis() - lastMeasureMs >= measureInterval) {
    lastMeasureMs = millis();
    long d = measureDistanceCm();
    if (d < 0) {
      // capteur n'a pas répondu, on peut ignorer ou envoyer une erreur
      Serial.println("ERROR_SENSOR");
    } else {
      // seuil 20 cm : >20 => insuffisant
      if (d > 20) {
        Serial.println("insuffisant");
      } else {
        Serial.println("suffisant");
      }
      // Optionnel : envoyer aussi la valeur numérique
      // Serial.print("DIST:");
      // Serial.println(d);
    }
  }
}
