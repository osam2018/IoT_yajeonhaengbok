#include<Servo.h>
Servo servo;

int servo_pin = 8;
int left_LED = 3;
int left_pin = 4;
int right_LED = 13;
int right_pin = 12;
int min_value = 544;
int max_value = 2400;
int now_degree = 90;

void setup() {
    pinMode(left_LED, OUTPUT);
    pinMode(right_LED, OUTPUT);
    pinMode(left_pin, INPUT);
    pinMode(right_pin, INPUT);
  
    servo.attach(servo_pin, min_value, max_value);
    servo.write(90);

    Serial.begin(9600);
}

void loop() {
    bool left_sensor = digitalRead(left_pin);
    bool right_sensor = digitalRead(right_pin);
    
    if(left_sensor == LOW && right_sensor == HIGH){
       now_degree = now_degree + 8;
       servo.write(now_degree);
       digitalWrite(left_LED, HIGH);
       digitalWrite(right_LED, LOW);
       Serial.println("left");
    }
    
    if(left_sensor == HIGH && right_sensor == LOW){
      now_degree = now_degree - 8;
      servo.write(now_degree);
      digitalWrite(left_LED, LOW);
      digitalWrite(right_LED, HIGH);
      Serial.println("right");
    }
    
    if(left_sensor == HIGH && right_sensor == HIGH){
      servo.write(now_degree);
      digitalWrite(left_LED, HIGH);
      digitalWrite(right_LED, HIGH);
      Serial.println("alright");
    }
    
    if(left_sensor == LOW && right_sensor == LOW){
      servo.write(now_degree + 15);
      servo.write(now_degree - 15);
      servo.write(now_degree);
      digitalWrite(left_LED, HIGH);
      digitalWrite(right_LED, HIGH);
      Serial.println("strange");
    }
    
    delay(300);
}
