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
	static 	 const int PATH_MAX_SIZE = 100;
	boolean is_interrupt = false;
	boolean is_finish_forward_back = false;
	String path_array[PATH_MAX_SIZE];
	int path_array_index = -1;
	int state = 0;

public:
	static const int FORWARD = 1;
	static const int BACK = 2;
	static const int LEFT = 3;
	static const int RIGHT = 4;
	static const int FORWARD_BACK = 5;
 
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
	void back_right();
	void back_left();
	void turn_left_right_random(int degree);
	void left(int degree);
	void right(int degree);
	void left(int degree, void(*f)(int));
	void right(int degree, void(*f)(int));
	void back(int degree, void(*f)(int));
	void forward(int degree, void(*f)(int));
	void stop();
	void forward_back();
	void add_path(String path_str) {
		if (path_array_index == PATH_MAX_SIZE - 1) {
			path_array_index = -1;
		}
		path_array_index++;
		path_array[path_array_index] = path_str;

	}

	bool is_circle();

	int getBackState();
	int getForwardState();
	bool isBackHover();
	bool isForwardHover();
	bool isLeftHover();
	bool isRightHover();
};

#endif