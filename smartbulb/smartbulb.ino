#include <WiFi.h>
#include <WebServer.h>

#define LDR 35 // (ADC1 PIN)
#define LED 21
//#define PIRout 19 // OUT 
//#define PIRin 18 // INSIDE

const char* ssid = "IOT40";
const char* pass = "password";
WebServer server(80);
int S_OUT[2]={19,23}; // setting trigger and echo pins
int S_IN[2]={22, 18}; // 0 index echo 1 index trig

int OUTinitial, INinitial, OUTval, INval;

String seq="";

int timeout=0;
long duration;

const int frequency= 5000;
const int led= 0;
const int bits=2;
int persons = 0;

int Read(int s[]){
  digitalWrite(s[1], LOW);
  delayMicroseconds(2);
  digitalWrite(s[1], HIGH);
  delayMicroseconds(10);
  digitalWrite(s[1], LOW);
  duration=pulseIn(s[0], HIGH);
  return( duration*0.034)/2; // time to dist in cms
}

void setup() {
  Serial.begin(9600);
  pinMode(LDR, INPUT);
  pinMode(LED, OUTPUT);

  ledcSetup(led, frequency, bits);
  ledcAttachPin(LED, led);
  //WiFi.mode(WiFi_STA);
  
  pinMode(S_OUT[1], OUTPUT);
  pinMode(S_IN[1], OUTPUT);
  pinMode(S_OUT[0], INPUT);
  pinMode(S_IN[0], INPUT);
  delay(500);
  OUTinitial= Read(S_OUT);
  INinitial = Read(S_IN);
  
}



void loop() {
  int light = analogRead(LDR);

  OUTval=Read(S_OUT);
  INval=Read(S_IN);

  
  //Serial.println(OUTinitial);
  //Serial.println(INinitial);

  if(OUTval < 15   && seq.charAt(0) != '1'){
    seq+="1";
  }
  else if(INval < 10 && seq.charAt(0) != '2'){
    seq+="2";
  }

  if(seq.equals("12")){
    persons++;  
    seq="";
    delay(550);
  }else if(seq.equals("21")){
    if(persons>0)
      persons--;
    seq="";
    delay(550);
  }

  if(seq.length() > 2 || seq.equals("11") || seq.equals("22") || timeout > 2){
    seq="";  
  }

  if(seq.length() == 1){ //
    timeout++;
  }else{
    timeout=0;
  }

  Serial.print("No. of people: ");
  Serial.println(persons);
  //Serial.print("Distance outside = ");
  //Serial.println(OUTval);
  //Serial.print("Distance inside = ");
  //Serial.println(INval);
  Serial.println(seq);
  
  if(persons>0){
    //Serial.println("Motion Detected");
    //Serial.print("LIGHT: ");
    //Serial.println(light);
    //Serial.print("LED STATE: ");
    if (light < 1023) {
      //BANG BANG ON
      //Serial.println("3");
      ledcWrite(led, 3);
      delay(250);
    } 
    else if (light < 2046) {
      //lil more light
      //Serial.println("2");
      ledcWrite(led, 2);
      delay(250);
    } 
    else if (light < 3069) {
      //lil light
      //Serial.println("1");
      ledcWrite(led, 1);
      delay(250);
    }
    else {   // < 4095
      //OFF
      //Serial.println("0");
      ledcWrite(led, 0);
      delay(250);
    }
  }
  else{
    //Serial.println("Motion Stopped");
    ledcWrite(led, 0);
  }
  Serial.println(OUTval);
  Serial.println(INval);
  delay(750);
  

}


/*long unsigned int lowIn;
long unsigned int p = 1000;
boolean lockLow = true;
boolean takeLowTime;
int PIRValue = 0;

void PIRSensor() {
   if(digitalRead(PIRout) == HIGH) {
      if(lockLow) {
         PIRValue = 1;
         lockLow = false;
         //Serial.println("Motion detected.");
         delay(50);
      }
      takeLowTime = true;
   }
   if(digitalRead(PIRout) == LOW) {
      if(takeLowTime){
         lowIn = millis();takeLowTime = false;
      }
      if(!lockLow && millis() - lowIn > p) {
         PIRValue = 0;
         lockLow = true;
         //Serial.println("Motion ended.");
         delay(50);
      }
   }
}*/

/*PIRSensor();
  int outside = PIRValue;//digitalRead(PIRout);
  int inside = digitalRead(PIRin);
  if(outside){
    outsideOn = 1;
  }
  if(inside && outsideOn){
    //Serial.println("Person entered");
    person++;
    insideOn = 0;
    outsideOn = 0;
  }
  if(inside){
    insideOn = 1;
  }
  if(outside && insideOn){
    //Serial.println("Person exited");
    person--;
    insideOn = 0;
    outsideOn = 0;
  }
  Serial.println(person);
  Serial.print("Inside ");
  Serial.println(inside);
  Serial.print("Outside ");
  Serial.println(outside);*/
  
  /*Serial.print("Outside ");
  Serial.println(movement2);
  Serial.print("Inside ");
  Serial.println(movement);*/
