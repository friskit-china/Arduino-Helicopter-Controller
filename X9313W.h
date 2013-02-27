/*
 * X9313W.h
 *
 *  Created on: 2012-7-23
 *      Author: Friskit
 */

#ifndef X9313W_H_
#define X9313W_H_

class X9313W {

private:
	int incPin;
	int udPin;
	int csPin;
	int RLevel;
	int hCycle;
	void _nop_();
	void enable();
	void disable();

public:
	X9313W(int incPin,int udPin,int csPin,int hCycle);
	int setRLevel(int target);
	int resetToMin();
	int resetToMax();
	int turnUp();
	int turnDown();
	int getRLevel();
};

#endif /* X9313W_H_ */
