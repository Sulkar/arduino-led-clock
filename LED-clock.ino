#include <DS3231.h>
#include "IRremote.h"

// Init clock
DS3231  rtc(SDA, SCL);
Time  t;
// Init receiver
int receiver = 13;
IRrecv irrecv(receiver);     
decode_results results;     

byte tempNumber = 0;
int myTime[4];
boolean TimeSet = false;
String Hours;
String Minutes;

byte checkMin;

void setup()
{
  //setup LED pins
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);

  //clearAll();
  
  // Setup Serial connection
  Serial.begin(9600);
  // init clock - receiver
  rtc.begin();
  irrecv.enableIRIn();
}

void loop()
{

  if (irrecv.decode(&results)) // have we received an IR signal?
  {
    translateIR(); 
    irrecv.resume();
  } 
  
  if(TimeSet == false){
    
   
    t=rtc.getTime();
    getMyTime(t.hour, t.min);    
    //Wait one second before repeating :)
    //Send time
    //Serial.println(rtc.getTimeStr()); //test
  }
}

/////////////
//function: clear all
void clearAll(){
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);

  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(11,HIGH);
  digitalWrite(12,HIGH);
}

//function: setTime
void translateIR() // takes action based on IR code received
{
  Serial.println(results.value);
  if(results.value ==16753245){
    TimeSet = true;
    tempNumber = 0;
    Hours = "";
    Minutes = "";
  }else if(results.value == 16769565){
    TimeSet = false;
    rtc.setTime(Hours.toInt(), Minutes.toInt(), 00);
  }
  if(TimeSet == true){
    switch(results.value)
    {      
      case 16724175: Serial.println(" 1"); myTime[tempNumber]=1; if(tempNumber<4){tempNumber++;} break;
      case 16718055: Serial.println(" 2"); myTime[tempNumber]=2; if(tempNumber<4){tempNumber++;} break;
      case 16743045: Serial.println(" 3"); myTime[tempNumber]=3; if(tempNumber<4){tempNumber++;} break;
      case 16716015: Serial.println(" 4"); myTime[tempNumber]=4; if(tempNumber<4){tempNumber++;} break;
      case 16726215: Serial.println(" 5"); myTime[tempNumber]=5; if(tempNumber<4){tempNumber++;} break;
      case 16734885: Serial.println(" 6"); myTime[tempNumber]=6; if(tempNumber<4){tempNumber++;} break;
      case 16728765: Serial.println(" 7"); myTime[tempNumber]=7; if(tempNumber<4){tempNumber++;} break;
      case 16730805: Serial.println(" 8"); myTime[tempNumber]=8; if(tempNumber<4){tempNumber++;} break;
      case 16732845: Serial.println(" 9"); myTime[tempNumber]=9; if(tempNumber<4){tempNumber++;} break;
      case 16738455: Serial.println(" 0"); myTime[tempNumber]=0; if(tempNumber<4){tempNumber++;} break;     
      default: Serial.println("other button");
    }
  }
  delay(200); // Do not get immediate repeat
  Hours = String(myTime[0]) + "" + String(myTime[1]);
  Minutes = String(myTime[2]) + "" + String(myTime[3]);
}

//function: getMyTime
void getMyTime(int _hour, int _min){
  String tHour = String(_hour);
  String tMin = String(_min);
  String nrLED1, nrLED2, nrLED3, nrLED4;
  
  if(tHour.length()<2){
    nrLED1 = "0"; 
    nrLED2 = tHour[0];
  }else{
    nrLED1 = tHour[0]; 
    nrLED2 = tHour[1];
  }
  if(tMin.length()<2){
    nrLED3 = "0"; 
    nrLED4 = tMin[0];
  }else{
    nrLED3 = tMin[0]; 
    nrLED4 = tMin[1];
  }
  /*Serial.print(nrLED1);
  Serial.print(nrLED2);
  Serial.print(":");
  Serial.print(nrLED3);
  Serial.println(nrLED4);*/
  //write Numbers
  writeMyTime(nrLED1,1);
  writeMyTime(nrLED2,2);
  writeMyTime(nrLED3,3);
  writeMyTime(nrLED4,4);
}

//function: writeMyTime
void writeMyTime(String _numb, byte _ledNr){
  int tempNumber = _numb.toInt();
  clearAll();
  digitalWrite(_ledNr+1,HIGH);
  switch (tempNumber){
    case 0:  
      digitalWrite(6,LOW);
      digitalWrite(7,LOW);
      digitalWrite(8,LOW);
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);   
      digitalWrite(11,LOW); 
      break;
    case 1:
      digitalWrite(7,LOW);
      digitalWrite(8,LOW);
      break;
    case 2:
      digitalWrite(9,LOW);
      digitalWrite(8,LOW);
      digitalWrite(12,LOW);
      digitalWrite(11,LOW);
      digitalWrite(6,LOW);   
      break;
    case 3:
      digitalWrite(9,LOW);
      digitalWrite(8,LOW);
      digitalWrite(12,LOW);
      digitalWrite(7,LOW);
      digitalWrite(6,LOW);  
      break;
    case 4:
      digitalWrite(10,LOW);
      digitalWrite(12,LOW);
      digitalWrite(8,LOW);
      digitalWrite(7,LOW);
      break;
    case 5:
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);
      digitalWrite(12,LOW);
      digitalWrite(7,LOW);
      digitalWrite(6,LOW);
      break;
    case 6:
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);
      digitalWrite(12,LOW);
      digitalWrite(7,LOW);
      digitalWrite(6,LOW); 
      digitalWrite(11,LOW);   
      break;
    case 7:
      digitalWrite(9,LOW);
      digitalWrite(8,LOW);
      digitalWrite(7,LOW);
      break;
    case 8:
      digitalWrite(6,LOW);
      digitalWrite(7,LOW);
      digitalWrite(8,LOW);
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);   
      digitalWrite(11,LOW); 
      digitalWrite(12,LOW); 
      break;
    case 9:
      digitalWrite(6,LOW);
      digitalWrite(7,LOW);
      digitalWrite(8,LOW);
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);   
      digitalWrite(12,LOW);
      break;
 
    default: 
      // default is optional
      break;
  }
  delay(1);
}


