#define BLYNK_PRINT Serial
#include<ESP8266WiFi.h>
#include <Servo.h>
#include<BlynkSimpleEsp8266.h>

// Initializing two Servo motors
Servo servo1;
Servo servo2;

// Authorization key of Blynk , wifi name and its password
char auth[] = "Auth key provided by Blynk";
char ssid[] = "WiFi name";
char pass[] = "WiFi password";

// Initializing blynk led and lcd and some variables
WidgetLED slot1(V1);
WidgetLED slot2(V2);
WidgetLED slot3(V3);
WidgetLCD lcd(V0);
int a,b,c,d,e,X,total=0;
String p ="", q="";

// Blynk button1 control code
BLYNK_WRITE(V4){
  int button1 =param.asInt();
  Serial.print("button:");
  Serial.print(button1);
  Serial.print("\n");
  if(button1==1)
  {
    servo1.write(90);
  }
}

// Blynk button2 control code
BLYNK_WRITE(V5){
  int button2 =param.asInt();
  Serial.print("button:");
  Serial.print(button2);
  Serial.print("\n");
  if(button2==1)
  {
    servo2.write(90);
  }
}


void setup(){
  Serial.begin(115200);
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D5, INPUT);
  pinMode(D6, INPUT);
  pinMode(D7, INPUT);
  servo1.attach(0); //D3
  servo2.attach(2);//D4
  Blynk.begin(auth,ssid,pass);
}

void loop(){

  Blynk.run();
  // a, b for entry exit sensors
  a = digitalRead(D1);
  b = digitalRead(D2);

  // d,e,f for parking slot sensors
  c = digitalRead(D5);
  d = digitalRead(D6);
  e = digitalRead(D7);
  String(x) = String("Will show 1 when obstacle detected and 0 for clear ...\n");
  String data = String("D5 DATA:")+String(c)+String("  ")+String("D6 DATA:")+String(d)+String("  ")+String("D7 DATA:")+String(e);
  Serial.print(x);
  Serial.print(data);
  Serial.print("\n");
  
  if(a==0)
  {p= "OBSTACLE ALERT";delay(250);servo1.write(90);}
  if(a==1)
  {p= "Clear";delay(1000);servo1.write(0);}
  if(b==1)
  {q = "OBSTACLE ALERT";delay(250);servo2.write(90);}
  if(b==0)
  {q = "Clear";delay(500);servo2.write(0);}
  if(c==1)
  {p= "OBSTACLE ALERT"; slot1.on();}
  if(c==0)
  {p= "Clear";slot1.off();}
  if(d==1)
  {p= "OBSTACLE ALERT";slot2.on();}
  if(d==0)
  {p= "Clear";slot2.off();}
  if(e==1)
  {p= "OBSTACLE ALERT";slot3.on();}
  if(e==0)
  {p= "Clear";slot3.off();}

  total=c+d+e;
  
  Serial.print("total cars:");
  Serial.print(total);
  Serial.print("\n");
  
  // To show in Virtual Blynk lcd
  lcd.print(0,0,"total no of cars");
  lcd.print(0,1,"parked:");
  lcd.print(8,1,total);
  delay(500);
}
