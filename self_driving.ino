int RM_E_pin=5;
int LM_E_pin=6;
int RM_1_pin=8;
int LM_1_pin=10;
int RM_2_pin=9;
int LM_2_pin=11;
#define sensor1 A3
#define sensor2 A4
#define sensor3 A5
int Rmotor_dir=1;
int Lmotor_dir=1;
int motor_s=240;
int Ultrasonic();
int distance=0;
int triggerPin=12;
int echoPin=13;

void setup(){
  Serial.begin(9600);
  pinMode(RM_E_pin, OUTPUT);
  pinMode(RM_1_pin, OUTPUT);
  pinMode(RM_2_pin, OUTPUT);
  pinMode(LM_E_pin, OUTPUT);
  pinMode(LM_1_pin, OUTPUT);
  pinMode(LM_2_pin, OUTPUT);
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  delay(3000);
}

void loop(){
  distance=Ultrasonic();
  //motor_s=distance*5;
  int L=digitalRead(sensor1);
  int C=digitalRead(sensor2);
  int R=digitalRead(sensor3);
  if (distance>=10){
    if(R==LOW && C==HIGH && L==LOW){
      motor_role(motor_s, motor_s);
      Serial.println("직진");
    }
    if(R==LOW && C==LOW && L==HIGH){
      motor_role(-(motor_s/2), motor_s);
      Serial.println("우회전");
    }
    if(R==LOW && C==HIGH && L==HIGH){
      motor_role(-(motor_s/2), motor_s);
      Serial.println("우회전");
    }
    if(R==HIGH && C==LOW && L==LOW){
      motor_role(motor_s, motor_s/2);
      Serial.println("좌회전");
    }
    if(R==HIGH && C==HIGH && L==LOW){
      motor_role(motor_s, motor_s/2);
      Serial.println("좌회전");
    }
    if(R==HIGH && C==HIGH && L==HIGH){
      motor_role(motor_s, motor_s);
      Serial.println("직진");
    }
    if(R==LOW && C==LOW && L==LOW){
      motor_role(motor_s, motor_s);
      Serial.println("직진");
    }
  }
  else{
    motor_role(0, 0);
    Serial.println("정지");
  }
}

void motor_role(int R_motor, int L_motor){
  if (R_motor>0){
    digitalWrite(RM_1_pin, Rmotor_dir);
    digitalWrite(RM_2_pin, !Rmotor_dir);
  }
  else if (R_motor<0){
    digitalWrite(RM_1_pin, !Rmotor_dir);
    digitalWrite(RM_2_pin, Rmotor_dir);
  }
  else{
    digitalWrite(RM_1_pin, LOW);
    digitalWrite(RM_2_pin, LOW);
  }
  if (L_motor>0){
    digitalWrite(LM_1_pin, Lmotor_dir);
    digitalWrite(LM_2_pin, !Lmotor_dir);
  }
  else if (L_motor<0){
    digitalWrite(LM_1_pin, !Lmotor_dir);
    digitalWrite(LM_2_pin, Lmotor_dir);
  }
  else{
    digitalWrite(LM_1_pin, LOW);
    digitalWrite(LM_2_pin, LOW);
  }
  analogWrite(RM_E_pin, abs(R_motor));
  analogWrite(LM_E_pin, abs(L_motor));
}

int Ultrasonic(){
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  int distances=pulseIn(echoPin, HIGH)/58;
  delay(10);
  return distances;
}
