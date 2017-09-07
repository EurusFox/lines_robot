#include <Servo.h>

void Avancer (float distance);
void TournerD(float angle);
void TournerG(float angle);
Servo servoL; //zero at 1516
Servo servoR; //zero at 1504
float distance1 = 30;

float dluz;
float gluz;
float dluz2;
float gluz2; 

void setup(){
  delay(1000);
  Serial.begin(9600);
  servoL.attach(13);
  servoR.attach(12);
  pinMode(6, INPUT);
  pinMode(8, INPUT);
  pinMode(4, INPUT);
  pinMode(10, INPUT);

  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
}

void loop(){
  int cpt = 0;
  float SumLeft = 0;
  float SumRight = 0;
  float SumLeft2 = 0;
  float SumRight2 = 0;
  while(cpt < 10){
    float PartLeft = float(tps(8));
    SumLeft = SumLeft + PartLeft;
    float PartRight = float(tps(6));
    SumRight = SumRight + PartRight;
    float PartLeft2 = float(tps(10));
    SumLeft2 = SumLeft2 + PartLeft2;
    float PartRight2 = float(tps(4));
    SumRight2 = SumRight2 + PartRight2;
    cpt++;
  }
  
  float tLeft = (SumLeft/cpt + SumLeft2/cpt)/2;
  float tRight = (SumRight/cpt + SumRight2/cpt)/2;

  float diff = (tRight/(tRight+tLeft))-0.5;

  if(diff>0.01){
    TournerD(1);
  }else if(diff < -0.05){
    TournerG(1);
  }else{
    Avancer(1);
  }

  Serial.println(diff);
}

void Avancer(float distance){
  servoL.writeMicroseconds(1535);
  servoR.writeMicroseconds(1485);
}

void TournerD(float angle){
  servoL.writeMicroseconds(1535);
  servoR.writeMicroseconds(1504);
  delay (angle);
}

void TournerG(float angle){
  servoL.writeMicroseconds(1516);
  servoR.writeMicroseconds(1485);
  delay (angle);
}

long tps(int pin){//calcule tps donc lumino
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
  delay(1);
  pinMode(pin, INPUT);
  digitalWrite(pin, LOW);
  long time = micros();
  while(digitalRead(pin));
  time = micros() - time;
  return time;  
}
