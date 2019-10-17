// 
// 
// 

#include "SerialController.h"
#include "Constant.h"
#include"MyUtils.h"

 
void SerialControllerClass::init(MotorControllerClass* mc)
{
	Serial.begin(115200);
	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB
	}
	this->mc = mc;

}

void SerialControllerClass::onSerialEvent()
{
	int forward_pin = digitalRead(19);//前面避障端口
	int back_pin = digitalRead(18);//后面避障端口

	if (forward_pin == 0&&mc->state==MotorControllerClass::FORWARD) {
		mc->stop();
		return;
	}
	if (back_pin == 0 && mc->state == MotorControllerClass::BACK) {
		mc->stop();
		return;
	}
	if (Serial.available() > 0) {
		String data = Serial.readStringUntil(';');//读一条指令 “；”分割
	
		if (data.length() == 0) {
			return;
		}
		if (Constant::isDebug == true) {
			Serial.println(data);
		}
		int index = data.indexOf(':');
		String k = "";
		String v = "";
		if (index != -1) {//如果有冒号，说明是指令带值
			k = data.substring(0, index);
			v = data.substring(index + 1, data.length());
		}
		else {//否则只有指令
			k = data;
		}
		if (mc == NULL) {
			return;
		}
		
		if (k.compareTo(Constant::FORWARD)==0) {

			mc->forward();

			return;
		}
		if (k.compareTo(Constant::BACK)==0) {
			mc->back();
			return;
		}
		if (k.compareTo(Constant::TURN_LEFT)==0) {
			mc->left();
			return;
		}

		if (k.compareTo(Constant::TURN_RIGHT)==0) {
			mc->right();
			return;
		}
		if (k.compareTo(Constant::STOP)==0) {
			mc->stop();
			return;
		}
		if (k.compareTo(Constant::SPEED_UP) == 0) {
		 
			return;
		}
		if (k.compareTo(Constant::SPEED_AT) == 0) {
			if (MyUtils.isDigit(v)) {
				MyUtils.println(v);
				mc->setSpeed(v.toInt());
			}
			return;
		}

		if (k.compareTo(Constant::TURN_LEFT_AT) == 0) {
			if (MyUtils.isDigit(v)) {
				MyUtils.println(v);
				mc->turnLeft(v.toInt());
			}
			return;
		}

		if (k.compareTo(Constant::TURN_RIGHT_AT) == 0) {
			if (MyUtils.isDigit(v)) {
				MyUtils.println("sfdsfsd");
				mc->turnRight(v.toInt());
			}
			return;
		}

	}
}


SerialControllerClass SerialController;

