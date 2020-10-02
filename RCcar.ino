#include <Servo.h>
#include <SoftwareSerial.h>
#include <IRremote.h>
#define BT_RXD 3
#define BT_TXD 4
int RECV_PIN=A0;
IRrecv irrecv(RECV_PIN);
decode_results results;
SoftwareSerial bluetooth(BT_RXD, BT_TXD);
Servo servo;
int servo_pin=2;
int distance;
int triggerPin=12;
int echoPin=13;
int RM_E_pin=5;
int LM_E_pin=6;
int RM_1_pin=8;
int LM_1_pin=10;
int RM_2_pin=9;
int LM_2_pin=11;
int PWM=0;
int motor_s=153;
int sensor1=A3;
int sensor2=A4;
int sensor3=A5;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  bluetooth.begin(9600);
  servo.attach(servo_pin);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(RM_E_pin, OUTPUT);
  pinMode(RM_1_pin, OUTPUT);
  pinMode(RM_2_pin, OUTPUT);
  pinMode(LM_E_pin, OUTPUT);
  pinMode(LM_1_pin, OUTPUT);
  pinMode(LM_2_pin, OUTPUT);
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  irrecv.enableIRIn();
}

void motor_role(int R_motor, int L_motor, int Speed){
  digitalWrite(RM_1_pin, R_motor);
  digitalWrite(RM_2_pin, !R_motor);
  digitalWrite(LM_1_pin, L_motor);
  digitalWrite(LM_2_pin, !L_motor);

  analogWrite(RM_E_pin, Speed);
  analogWrite(LM_E_pin, Speed);
}

void loop() {
  // put your main code here, to run repeatedly:
 // if (bluetooth.available()){
  //  Serial.write(bluetooth.read());
  //if (irrecv.decode(&results)){
  //  Serial.println(results.value, HEX);
    //switch(results.value){
     // case 0xFF6897:
        int val1=digitalRead(sensor1);
        int val2=digitalRead(sensor2);
        int val3=digitalRead(sensor3);
        Serial.print(val1 );
        Serial.print(val2 );
        Serial.println(val3);
        
        digitalWrite(triggerPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(triggerPin, LOW);
        distance=pulseIn(echoPin, HIGH)/58;
        Serial.println("Distance(cm) = " + String(distance));
  
  
        if (PWM>255)
          PWM=255;
        else if (PWM<50)
          PWM=0;
    
        analogWrite(RM_E_pin, PWM);
        analogWrite(LM_E_pin, PWM);
        
        motor_role(HIGH, HIGH, motor_s);
        Serial.println("직진");
        
        if (val1==1 && val2==0 && val3==0){
          PWM=PWM/2;
          motor_role(LOW, HIGH, motor_s);
          Serial.println("좌회전");
        }
        else if (val3==1 && val2==0 && val1==0){
          PWM=PWM/2;
          motor_role(HIGH, LOW, motor_s);
          Serial.println("우회전");
        }
        //if (Serial.available()){
        char command=Serial.read();
        if (command=='g'){
          motor_role(HIGH, HIGH, motor_s);
          Serial.println("직진");
        }
        else if (command=='b'){
          motor_role(LOW, LOW, motor_s);
          Serial.println("후진");
        }
        else if (command=='s'){
          motor_role(HIGH, HIGH, PWM);
          Serial.println("정지");
        }
        else{
          Serial.println("wrong command");
        }
        if(command=='s'){
          PWM=0;
        }
        else{
          PWM=distance*5;
        }
      }
   //   case 0xFF30CF: 
   //     motor_role(HIGH, HIGH, PWM);
    //    Serial.println("정지");
//  / irrecv.resume();

//  }
 // if (Serial.available()){
 //   bluetooth.write(Serial.read());
 // }
