const int throttlePin = 5;
const int steerPin = 6;

void setup() {
  pinMode(throttlePin, OUTPUT);
  pinMode(steerPin, OUTPUT);
  Serial.begin(9600);

  //Initalize both pins at 50%
  analogWrite(throttlePin, 127);
  analogWrite(steerPin, 127);

  delay(50);

  Serial.println("Enter PWM as 'pin:percentage' (e.g., 5:75)");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    int colonIndex = input.indexOf(':');
    if (colonIndex > 0) {
      int pin = input.substring(0, colonIndex).toInt();
      int percent = input.substring(colonIndex + 1).toInt();

      percent = constrain(percent, 0, 100);  // Clamp to valid range
      int pwmValue = map(percent, 0, 100, 0, 255);  // Convert to 0–255

      if (pin == throttlePin || pin == steerPin) {
        analogWrite(pin, pwmValue);
        Serial.print("Pin ");
        Serial.print(pin);
        Serial.print(" set to ");
        Serial.print(percent);
        Serial.print("% (PWM = ");
        Serial.print(pwmValue);
        Serial.println(")");
      } else {
        Serial.println("Invalid pin. Use 5 or 6.");
      }
    } else {
      Serial.println("Invalid format. Use 'pin:percentage'");
    }
  }
}
