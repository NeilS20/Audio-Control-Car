const int pwmPinA = 9;  // OC1A or Throttle
const int pwmPinB = 10; // OC1B or Steer
const int PWM_FREQUENCY = 800000; 

void setupTimer1(int frequency) {
  pinMode(pwmPinA, OUTPUT);
  pinMode(pwmPinB, OUTPUT);

  // Calculate TOP value for desired frequency
  int top = F_CPU / frequency; // No prescaler

  // Configure Timer1
  TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11); // Non-inverting, Fast PWM
  TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS10);    // Fast PWM, no prescaler
  ICR1 = top; // Set TOP value
}

void setPWM_OC1A(int percent) {
  percent = constrain(percent, 0, 100);
  OCR1A = map(percent, 0, 100, 0, ICR1);
}

void setPWM_OC1B(int percent) {
  percent = constrain(percent, 0, 100);
  OCR1B = map(percent, 0, 100, 0, ICR1);
}

void setup() {
  Serial.begin(9600);
  setupTimer1(PWM_FREQUENCY);

  setPWM_OC1A(50); // Initialize at 50%
  setPWM_OC1B(50);

  Serial.println("Enter PWM as 'pin:percentage' (e.g., 9:75 or 10:40)");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    int colonIndex = input.indexOf(':');
    if (colonIndex > 0) {
      int pin = input.substring(0, colonIndex).toInt();
      int percent = input.substring(colonIndex + 1).toInt();

      if (pin == pwmPinA) {
        setPWM_OC1A(percent);
        Serial.print("Pin 9 set to ");
        Serial.print(percent);
        Serial.println("% duty cycle");
      } else if (pin == pwmPinB) {
        setPWM_OC1B(percent);
        Serial.print("Pin 10 set to ");
        Serial.print(percent);
        Serial.println("% duty cycle");
      } else {
        Serial.println("Invalid pin. Use 9 or 10.");
      }
    } else {
      Serial.println("Invalid format. Use 'pin:percentage'");
    }
  }
}
