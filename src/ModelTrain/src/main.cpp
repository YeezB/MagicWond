#include "unihiker_k10.h"

volatile float mind_n_test;

UNIHIKER_K10 k10;

void setup() {
	k10.begin();
	Serial.begin(9600);
}
void loop() {
	if ((k10.isGesture(TiltForward))) {
		mind_n_test = 1;
	}
	else {
		if ((k10.isGesture(TiltBack))) {
			mind_n_test = 2;
		}
		else {
			if ((k10.isGesture(TiltLeft))) {
				mind_n_test = 3;
			}
			else {
				if ((k10.isGesture(TiltRight))) {
					mind_n_test = 4;
				}
				else {
					if ((k10.isGesture(ScreenUp))) {
						mind_n_test = 5;
					}
					else {
						if ((k10.isGesture(ScreenDown))) {
							mind_n_test = 6;
						}
						else {
							mind_n_test = 0;
						}
					}
				}
			}
		}
	}
	Serial.print(mind_n_test);
	Serial.print(",");
	Serial.print((k10.getAccelerometerX()));
	Serial.print(",");
	Serial.print((k10.getAccelerometerY()));
	Serial.print(",");
	Serial.print((k10.getAccelerometerZ()));
	Serial.print(",");
	Serial.println((k10.getStrength()));
	delay(100);
}