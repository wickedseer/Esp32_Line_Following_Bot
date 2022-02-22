// Motor A
int motor1Pin1 = 18; //direction
int motor1Pin2 = 5;  //direction
int enable1Pin = 19; //speed

// Motor B
int motor2Pin1 = 17; //direction
int motor2Pin2 = 16; //direction
int enable2Pin = 4; //speed

int motor1_speed = 200;
int motor2_speed = 255;

// Setting PWM properties
const int freq = 30000; //hz
const int pwmChannel1 = 0;
const int pwmChannel2 = 1;
const int resolution = 8;
int dutyCycle = 50;

int left_sensor_pin = 13;
int right_sensor_pin = 12;

int left_state = HIGH; // HIGH means white
int right_state = HIGH;

void setup()
{
  //set IR sensor pins as inputs
  pinMode(left_sensor_pin, INPUT);
  pinMode(right_sensor_pin, INPUT);

  // sets the pins as outputs:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);

  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable2Pin, OUTPUT);

  // configure LED PWM functionalitites
  ledcSetup(pwmChannel1, freq, resolution);
  ledcSetup(pwmChannel2, freq, resolution);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(enable1Pin, pwmChannel1); //motor 1
  ledcAttachPin(enable2Pin, pwmChannel2); //motor 2


}

void loop() {
  left_state = digitalRead(left_sensor_pin);
  right_state = digitalRead(right_sensor_pin);

  if(left_state == HIGH && right_state == HIGH){
        // Move DC motor forward with increasing speed
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);

      while (dutyCycle <= 200) {
        ledcWrite(pwmChannel1, dutyCycle);
        Serial.print("Forward with duty cycle: ");
        Serial.println(dutyCycle);
        dutyCycle = dutyCycle + 5;
        delay(50);
      }
      
      digitalWrite(motor2Pin1, HIGH);
      digitalWrite(motor2Pin2, LOW);
      
      while (dutyCycle <= 255) {
        ledcWrite(pwmChannel2, dutyCycle);
        Serial.print("Forward with duty cycle: ");
        Serial.println(dutyCycle);
        dutyCycle = dutyCycle + 5;
        delay(50);
      }
  }

  if (left_state == LOW && right_state == HIGH) {
    //Turning left
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    ledcWrite(pwmChannel1, motor1_speed);

    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, LOW);
    delay(100);
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);
    ledcWrite(pwmChannel2, motor2_speed);

  }

  if (left_state == HIGH && right_state == LOW) {
    // Turning right
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);
    ledcWrite(pwmChannel2, motor2_speed);

    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);
    delay(100);
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    ledcWrite(pwmChannel1, motor1_speed);

  }

  if (left_state == LOW && right_state == HIGH) {
    //STOP
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, LOW);
  }

}
