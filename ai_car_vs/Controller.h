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
	static  Controller *instance;
	static  Controller* newInstance(MotorControllerClass* mc) {
		instance = new Controller( mc);
		instance->initPort();
	}
	static void on_forward_right_crash();
	static void on_forward_left_crash();
	static void on_back_right_crash();
	static void on_back_left_crash();

	void initPort();
	Controller(MotorControllerClass *mc);
	void loop();
	void forward();
	void back();
	void left();
	void right();
	void left(int degree);
	void right(int degree);
	void stop();


	int getBackState();
	int getForwardState();
	bool isBackHover();
	bool isForwardHover();
	bool isLeftHover();
	bool isRightHover();
};

#endif