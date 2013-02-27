/*
 * X9313W.cpp
 *
 *  Created on: 2012-7-23
 *      Author: Friskit
 */

#include "X9313W.h"
#include "Arduino.h"
#define MIN		0
#define	MAX		31
#define UP		HIGH	//UD端置上升位
#define DOWN	LOW		//UD端置下降位
#define EA		LOW		//CS端低位使能
#define DA		HIGH	//CS端高位中断保存


X9313W::X9313W(int incP,int udP,int csP,int hcycle){
	this->incPin = incP;
	this->udPin = udP;
	this->csPin = csP;
	this->hCycle = hcycle;
	pinMode(incPin,OUTPUT);
	pinMode(udPin,OUTPUT);
	pinMode(csPin,OUTPUT);
	digitalWrite(incPin,HIGH);
	digitalWrite(csPin,LOW);//默认即使能，易失；
	RLevel = 31;
}

int X9313W::resetToMin(){
	for(int i=0;i<=32;i++){
		turnDown();
	}
	this->RLevel = MIN;

	return this->RLevel;
}

int X9313W::resetToMax(){
	for(int i=0;i<=32;i++){
		turnUp();
	}
	this->RLevel = MAX;

	return this->RLevel;
}


void X9313W::_nop_(){
	delayMicroseconds(hCycle);
	//delay(hCycle);
}

int X9313W::turnUp(){

	//enable();
	_nop_();
	digitalWrite(this->udPin,UP);
	_nop_();
	digitalWrite(this->incPin,LOW);
	_nop_();
	digitalWrite(this->incPin,HIGH);
	_nop_();
	//disable();
	this->RLevel++;
	return RLevel;
}

int X9313W::turnDown(){
	//enable();
	_nop_();
	digitalWrite(this->udPin,DOWN);
	_nop_();
	digitalWrite(this->incPin,LOW);
	_nop_();
	digitalWrite(this->incPin,HIGH);
	_nop_();
	//disable();
	this->RLevel--;
	return RLevel;
}

int X9313W::getRLevel(){
	return this->RLevel;
}

int X9313W::setRLevel(int target){
	if(this->RLevel>target){
		for(int i=RLevel;i>target;i--){
			//enable();
			turnDown();
			//disable();
		}
		return this->RLevel;
	}else if(this->RLevel<target){
		for(int i=RLevel;i<target;i++){
			//enable();
			turnUp();
			//disable();
		}
		return this->RLevel;
	}else{
		return this->RLevel;
	}

}

void X9313W::enable(){
	_nop_();
	digitalWrite(csPin,EA);
	_nop_();
}

void X9313W::disable(){
	_nop_();
	digitalWrite(csPin,DA);
	_nop_();
}
