
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define echopin 2
#define trigpin 13

long duration;
int distance;

//Motor A
const int inputPin1  = 5;    // Pin 15 of L293D IC, D1 Pin of NodeMCU
const int inputPin2  = 16;    // Pin 10 of L293D IC, D0 Pin of NodeMCU
//Motor B
const int inputPin3  = 4;    // Pin  7 of L293D IC, D2 Pin of NodeMCU
const int inputPin4  = 0;    // Pin  2 of L293D IC, D3 Pin of NodeMCU
int EN1 = 12;                 // Pin 1 of L293D IC, D6 Pin of NodeMCU
int EN2 = 14;                 // Pin 9 of L293D IC, D5 Pin of NodeMCU


char auth[] = "Ud8zxRNWwAPuRQt99MkrS6n1WrAwupwV";
char ssid[] = "P@in";
char pass[] = "";


BLYNK_WRITE(V1)
{
  int x = param[0].asInt();
  int y = param[1].asInt();
  
  // Do something with x and y
  Serial.print("X = ");
  Serial.print(x);
  Serial.print("; Y = ");
  Serial.println(y);

// Joystick Movement
  if (y>350)
  {
    Serial.print("forward");
    forward();
  }

  if (y<170) 
    {
      Serial.print("backward");
      backward();
    }

   if (x<130)
    {
      Serial.print("left");
      left();
    }
 
  if (x>380) 
    {
      Serial.print("tight");
      right();
    }

  if ((y==256) && (x==256))
    {
      Serial.print("stop");
      stop();
     }
}

BLYNK_WRITE(V2)
{
   int speed = param.asInt(); // assigning incoming value from pin V2 to a variable
    analogWrite(EN1, speed);//sets the motors speed
    analogWrite(EN2, speed);//sets the motors speed

}

void setup()
{
    pinMode(EN1, OUTPUT);   // where the motor is connected to
    pinMode(EN2, OUTPUT);   // where the motor is connected to
    pinMode(inputPin1, OUTPUT);
    pinMode(inputPin2, OUTPUT);
    pinMode(inputPin3, OUTPUT);
    pinMode(inputPin4, OUTPUT);  
    pinMode(trigpin,OUTPUT);
    pinMode(echopin,INPUT);
    Serial.begin(9600);
    Blynk.begin(auth, ssid, pass);
}
void right(void)
{
    digitalWrite(inputPin1, HIGH);
    digitalWrite(inputPin2, LOW);
    digitalWrite(inputPin3, HIGH);
    digitalWrite(inputPin4, LOW);  
}

void left(void)
{
    digitalWrite(inputPin1, LOW);
    digitalWrite(inputPin2, HIGH);
    digitalWrite(inputPin3, LOW);
    digitalWrite(inputPin4, HIGH); 
}

void stop(void)
{ 
    digitalWrite(inputPin1, LOW);
    digitalWrite(inputPin2, LOW);
    digitalWrite(inputPin3, LOW);
    digitalWrite(inputPin4, LOW);
}

void forward(void)
{   
    digitalWrite(inputPin1, LOW);
    digitalWrite(inputPin2, HIGH);
    digitalWrite(inputPin3, HIGH);
    digitalWrite(inputPin4, LOW); 
}

void backward(void)
{ 
    digitalWrite(inputPin1, HIGH);
    digitalWrite(inputPin2, LOW);
    digitalWrite(inputPin3, LOW);
    digitalWrite(inputPin4, HIGH); 
}
void loop()
{
  Blynk.run();
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);
  duration = pulseIn(echopin, HIGH);
  distance = duration /58.2;

  if(distance<15)
  {
    stop();
    backward();
    delay(100);
    stop();
  }
}
