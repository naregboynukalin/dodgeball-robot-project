const int trigPin_1 = 6;
const int echoPin_1 = 7;
long duration_1;
int distance_1;
String position;

const int trigPin_2 = 11;
const int echoPin_2 = 12;
long duration_2;
int distance_2;


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
  pinMode(trigPin_1, OUTPUT);
  pinMode(echoPin_1, INPUT);
  pinMode(trigPin_2, OUTPUT);
  pinMode(echoPin_2, INPUT);
}

void loop() {
analogWrite(enA, 150);
analogWrite(enB, 150);


  digitalWrite(trigPin_1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_1, LOW);
  duration_1 = pulseIn(echoPin_1, HIGH);
  distance_1 = duration_1 * 0.034 / 2;

  digitalWrite(trigPin_2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_2, LOW);
  duration_2 = pulseIn(echoPin_2, HIGH);
  distance_2 = duration_2 * 0.034 / 2;

   if (Serial.available() > 0) {
     String temp;
     temp = Serial.readString();
     if (temp.equals("1") or temp.equals("0") or temp.equals("-1")){
        position = temp;
     }
    }

 if ((distance_1 <= 65 or distance_2<=65) and position.equals("1"))
   {
     right();
   }

 else if ((distance_1 <= 65 or distance_2<=65) and position.equals("0"))
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
