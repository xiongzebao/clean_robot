// MyUtils.h

#ifndef _MYUTILS_h
#define _MYUTILS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


// Utils.h

#ifndef _UTILS_h
#define _UTILS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"

#else
#include "WProgram.h"
#endif

#include "MotorController.h"
#include"Constant.h"
class MyMotorClass;
class VelometerClass;

#endif

class MyUtilsClass
{
 
public :
	//第一次开机检测电机最大转速并设置最大转速，耗时5s
	static void testMotorMaxSpeed(MotorControllerClass* const ctrlor) {
		
		//ctrlor->openLeftMotorMaxSpeed();//开启前左轮电机最大功率

		ctrlor->setSpeed(300);
		ctrlor->forward();
		delay(100);
	
		ctrlor->setSpeed(500);
		delay(3000);
		int speed = ctrlor->getSpeed().leftSpeed;//获取当前左轮电机速度
	 
		//Serial.println(ctrlor->velometer.rightSum);
		//Serial.println(ctrlor->velometer.leftSum);
		//Serial.println("max speed:");
		//Serial.println(speed);
		//ctrlor->stopDetectSpeed();
		//ctrlor->stop();
	}

public:
	bool isDigit(String str) {
		for (int i = 0; i < str.length(); i++) {
			char c = str.charAt(i);
			if (48 > c ||c> 57) {
				return false;
			 }
		}
		return true;
	}

	 void println(String s) {
		 if (Constant::isDebug==true) {
			 Serial.println(s);
			 Serial.flush();
		 }
	}

	 void println(int i) {
		 if (Constant::isDebug == true) {
			 Serial.println(i);
			 Serial.flush();
		 }
	 }
	 void print(int i) {
		 if (Constant::isDebug == true) {
			 Serial.print(i);
			 Serial.flush();
		 }
	 }
	 void print(String i) {
		 if (Constant::isDebug == true) {
			 Serial.print(i);
			 Serial.flush();
		 }
	 }

 public:
	void init();

};

extern MyUtilsClass MyUtils;

#endif

