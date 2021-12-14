#define BLYNK_PRINT Serial
#include<ESP8266WiFi.h>
#include<Servo.h>
#include<BlynkSimpleEsp8266.h>

char auth[]="MaZnI9H77RV7Xqkw6vriKXhPKivSCBKG";
char ssid[]="P@in";
char pass[]="pankaj1@";

Servo servo;
#define IR D0
bool ir;


BLYNK_WRITE(V0){
  int button1 =param.asInt();
  Serial.print("button:");
  Serial.print(button1);
  Serial.print("\n");
  if(button1==1)
  {
    servo.write(180);
    delay(500);
    servo.write(0);
    delay(1000);
  }
}

BLYNK_WRITE(V1){
  int button2 =param.asInt();
  Serial.print("button:");
  Serial.print(button2);
  Serial.print("\n");
  if(button2==1)
  {
    //set=1;
    digitalWrite(D1,1);
  }
  else
  {
    digitalWrite(D1,0);
  }
}

BLYNK_WRITE(V2){
  int button3 =param.asInt();
  Serial.print("button:");
  Serial.print(button3);
  Serial.print("\n");
  if(button3==1)
  {
    //set=1;
    digitalWrite(D2,1);
  }
  else
  {
    digitalWrite(D2,0);
  }
}


void setup() {
  Serial.begin(115200);
  pinMode(IR,INPUT);
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  servo.attach(2); //D4 
  Blynk.begin(auth,ssid,pass);
  delay(1000);
  
}

void loop() {
   Blynk.run();
  static int set=0;
  ir = digitalRead(IR);
  if(ir==0)
  {
    Serial.println("present!!");
    Serial.println(set);
   
    if (set==0)
      {
        digitalWrite(D1,1);
        digitalWrite(D2,1);
        set=1;
        servo.write(180);
        delay(300);
        servo.write(0);
        delay(300);  
      }
    else
      {
        digitalWrite(D1,0);
        digitalWrite(D2,0);
        set=0;
        //servo
        servo.write(0);
        delay(300);
       }
  }
else
  {
    Serial.println("not present");
    if(set==1)
        {
          servo.write(180);
          delay(300);
          servo.write(0);
          delay(300);
        }
        else
        {
          //do nothing
        }
  }
  

  
  
}
