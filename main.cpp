#include <Arduino.h>
#include "X9313W.h"

const int ledPin = 13;

const int incPinA = 22;
const int udPinA = 24;
const int csPinA = 26;

const int incPinB = 28;
const int udPinB = 30;
const int csPinB = 32;

const int incPinC = 34;
const int udPinC = 36;
const int csPinC = 38;

const int hCycle = 10;

X9313W xA(incPinA,udPinA,csPinA,hCycle);
X9313W xB(incPinB,udPinB,csPinB,hCycle);
X9313W xC(incPinC,udPinC,csPinC,hCycle);


int level=0;
void setup() {
	digitalWrite(ledPin,LOW);
	//遥控器初始化
	xA.setRLevel(0);
	xB.setRLevel(0);
	xC.setRLevel(0);

	//默认档位
	xB.setRLevel(7);
	xC.setRLevel(7);

	digitalWrite(ledPin,HIGH);//指示初始化成功

	//开启串口
	Serial.begin(9600);

}

void loop() {

	int bufferSize = Serial.available();
	if(bufferSize>=2){
		char x=Serial.read();
		if(x!='A'&&x!='B'&&x!='C')
			return;
		char value = Serial.read();
		switch(value){
			case '0':level=0;break;
			case '1':level=1;break;
			case '2':level=2;break;
			case '3':level=3;break;
			case '4':level=4;break;
			case '5':level=5;break;
			case '6':level=6;break;
			case '7':level=7;break;
			case '8':level=8;break;
			case '9':level=9;break;
			case 'a':level=10;break;
			case 'b':level=11;break;
			case 'c':level=12;break;
			case 'd':level=13;break;
			case 'e':level=14;break;
			case 'f':level=15;break;
		}
		switch(x){
			case 'A':
				xA.setRLevel(level);
				break;
			case 'B':
				xB.setRLevel(level);
				break;
			case 'C':
				xC.setRLevel(level);
				break;
		}
		Serial.print("Set ");
		Serial.print(x);
		Serial.print(" To ");
		Serial.println(level);

		Serial.flush();
	}
}

int main(void) {

  init();
  setup();

  for (;;) {
	  loop();
  }
}
