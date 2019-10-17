#pragma once
#ifndef _CONTROLLER_h
#define _CONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"

#else
#include "WProgram.h"
#endif

#include "port.h"
#include "MotorController.h"
class Controller
{
	MotorControllerClass* mc;
public:

	void initPort();
	Controller(MotorControllerClass *mc);


	void loop();

	void forward();
	void back();
	void left();
	void right();
	void stop();
	int getBackState();
	int getForwardState();
	bool isBackHover();
	bool isForwardHover();
	bool isLeftHover();
	bool isRightHover();
};

#endif