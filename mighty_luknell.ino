#include <TimerOne.h>

const int echoPin = 3;
const int trigPin = 2;
const int pins[4] = {4, 5, 7, trigPin};
int t1;
int quarter_second_flag = 0;
long count = 0;
double distance1, d2, d1, duration;
bool off = false;


void isrTimer()
{
  count++;
  quarter_second_flag = 1;
}
void redLight()
{
  if (!off)
  { digitalWrite(4, HIGH);
    digitalWrite(5, LOW);         //red light on
    digitalWrite(7, LOW);
    Serial.println("redlight");
  }
}
void yellowLight()
{
  if (!off)
  { digitalWrite(4, LOW);
    digitalWrite(7, HIGH);         //yellow light on
    digitalWrite(5, LOW);
    Serial.println("yellowlight");
  }
}
void greenLight()
{
  if (!off)
  { digitalWrite(4, LOW);
    digitalWrite(7, LOW);         //green light on
    digitalWrite(5, HIGH);
    Serial.println("greenlight");
  }
}
void lightsOut(double distance)
{
  int count_flag;
  if (distance1 - distance > .04)
  {
    off = false;
  }
  if (count % 60 == 0)
  {
   // delay(55000000);
    count_flag = 1;
    count =1;
  }
  else
  { count_flag = 0;
  }
  if (distance == distance1 && count_flag && distance!=0) {
    digitalWrite(4, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(5, LOW);
    Serial.println("Lights out");
    off = true;
  }
  else
  {
    distance1 = distance;
    Serial.println("else");
    Serial.println(distance);
  }
}
void setup() {
  for (int i = 0; i < 4; i++)
  {
    pinMode(pins[i], OUTPUT);
  }
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
  Timer1.initialize(250000);         // initialize timer1, and set a 1/4 second period
  Timer1.attachInterrupt(isrTimer);  // attaches isrTimer() as a timer overflow interrupt
  redLight();
  delay(500);
  yellowLight();
  delay(500);
  greenLight();
  delay(500);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(7, LOW);
}
void loop() {
 // if (quarter_second_flag) {
    // quarter_second_flag = 0;
    digitalWrite(trigPin, LOW); // Clears the trigPin
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    d1 = duration * 340 / 2000000;
  //}
  if (d1 < d2 || t1 == 50) {
    d2 = d1;
    t1 = 0;
  }

  if (d2 > 1.6 && d2 < 3.5) {
    greenLight();
  }
  if (d2 < 1.5 && d2 > .06) {
    yellowLight();
  }
  if (d2 <= .05 && d2 >= 0.0) {
    redLight();
  }
  t1++;
  if (quarter_second_flag) {
    quarter_second_flag = 0;
    lightsOut(d2);
  }
  //Serial.println("count " + count);
}

