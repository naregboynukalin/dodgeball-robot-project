const int trigPin = 11;
const int echoPin = 12;
long duration;
int distance;
String position;


int enA = 9;
int IN1 = 2;
int IN2 = 3;

int enB = 10;
int IN3 = 4;
int IN4 = 5;

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  analogWrite(enA, 150);
  analogWrite(enB, 150);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

   if (Serial.available() > 0) {
     String temp;
     temp = Serial.readString();
     if (temp.equals("1") or temp.equals("0") or temp.equals("-1")){
        position = temp;
     }
    }

 if (distance <= 65 and position.equals("1"))
   {
     right();
   }

 else if (distance <= 65 and position.equals("0"))
  {
     left();
  }

  if (position.equals("-1")){
    STOP();
  }

}

void right(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
}

void left(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void STOP(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
