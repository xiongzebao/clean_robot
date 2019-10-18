/*
 Name:		ai_car_vs.ino
 Created:	2019/6/4 14:41:08
 Author:	xiongbin
*/
#include "MyUtils.h"
#include "Velometer.h"
#include "MyMotor.h"
#include "MotorController.h"
#include "SerialController.h"
#include "port.h"
#include "Controller.h"
MyMotorClass leftMotor = MyMotorClass(motorA2, motorA1, pwdA);
MyMotorClass rightMotor = MyMotorClass(motorB1, motorB2, pwdB);
MotorControllerClass mc = MotorControllerClass(&rightMotor,&leftMotor);
Controller* ctrl = Controller::newInstance(&mc);
void setup() 
{
	Serial.begin(9600);
	while (!Serial) {
		; 
	}
	MyUtils.println("welcome to clean robot");
	mc.setSpeed(500);
	mc.forward();
}

void loop()
{
	ctrl->loop();
}
