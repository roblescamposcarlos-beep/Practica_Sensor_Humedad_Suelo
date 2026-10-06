const int PIN_SENSOR = A0;
const int LED_PIN    = 13;

// ===== CALIBRACIÓN =====
// Anota la "Lectura" cruda en cada caso y pon los números aquí:
const int VALOR_AIRE = 850;   // sensor al aire / tierra seca (lectura ALTA)
const int VALOR_AGUA = 350;   // sensor en tierra muy mojada (lectura BAJA)

// Debajo de este porcentaje se considera tierra seca
const int UMBRAL_PORCENTAJE = 40;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  Serial.println("=== Monitor de humedad del suelo ===");
}

void loop() {
  int lectura = analogRead(PIN_SENSOR);

  // Lectura alta -> 0% ; lectura baja -> 100%
  int porcentaje = map(lectura, VALOR_AIRE, VALOR_AGUA, 0, 100);
  porcentaje = constrain(porcentaje, 0, 100);

  Serial.print("Lectura: ");
  Serial.print(lectura);
  Serial.print("  |  Humedad: ");
  Serial.print(porcentaje);
  Serial.print("%  |  Estado: ");

  if (porcentaje >= UMBRAL_PORCENTAJE) {
    Serial.println("TIERRA HUMEDA -> No necesita riego");
    digitalWrite(LED_PIN, LOW);
  } else {
    Serial.println("TIERRA SECA -> Se recomienda regar");
    digitalWrite(LED_PIN, HIGH);
  }

  delay(1000);
}
