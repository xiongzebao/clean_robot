// SerialController.h

#ifndef _SERIALCONTROLLER_h
#define _SERIALCONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
	#include "MotorController.h"
#else
	#include "WProgram.h"
#endif


class SerialControllerClass
{

 protected:
	 MotorControllerClass* mc;

 public:
	void init(MotorControllerClass* mc);
	void onSerialEvent();


};

extern SerialControllerClass SerialController;

#endif

