#include "Controller.h"

void Controller::initPort()
{
		pinMode(down_forward, INPUT);
		pinMode(down_back, INPUT);
		pinMode(down_right, INPUT);
		pinMode(down_left, INPUT);
		pinMode(back_left, INPUT);
		pinMode(back_right, INPUT);
		pinMode(left_back, INPUT);
		pinMode(left_forward, INPUT);
		pinMode(right_back, INPUT);
		pinMode(right_forward, INPUT);
}

Controller::Controller(MotorControllerClass* mc)
{
	this->mc = mc;
}

 



void Controller::loop()
{////红外亮0，灭1
	switch (mc->state)
	{
	case MotorControllerClass::FORWARD:
		forward();
		break;
	case MotorControllerClass::BACK:
		back();
		break;
	case MotorControllerClass::RIGHT:
		break;
	case MotorControllerClass::LEFT:
		break;
	default:
		break;
	}
}



void Controller::forward()
{

	if (isLeftHover()||isRightHover()) {
		mc->stop();
		return;
	}

	if (isForwardHover()) {//如果前面有悬崖
		mc->stop();
	}else {
		//判断前面是否有障碍物,传感器缺失，暂时不实现，仅前进
		mc->forward();
		Serial.println("forward");
		return;
	}
	if (isBackHover()){
		mc->stop();
		return;//前后都是悬崖，即停止
	}else {
		//if (getBackState() != 3) {//后面有障碍物
			mc->back();
		
	}
}



void Controller::back()
{
	if (isRightHover()) {
		mc->turnLeft(90);
		
		return;
	}
	Serial.println("back");
	if (isBackHover()) { 
		mc->stop();
		if (!isForwardHover()) {
			mc->forward();
		}
	}else {
		//判断前面是否有障碍物 
		if (getForwardState()!=3 ){//前面有障碍物
			mc->back();
		}
		return;
	}
}

void Controller::left()
{
}

void Controller::right()
{
}

void Controller::stop()
{
	 
}


//0;左右都堵，1：左堵，2：右堵，3，畅通
int Controller::getBackState()
{
 
	int back_left_level = digitalRead(back_left);
	int back_right_level = digitalRead(back_right);
	if (back_left_level == 0 && back_right_level == 0) {//后面有障碍物
		return 0;
	}
	if (back_left_level == 0&& back_right_level==1) {
		return 1;
	}
	if (back_left_level == 1 && back_right_level == 0) {
		return 2;
	}
	return 3;
}

int Controller::getForwardState()
{
	 

}

bool Controller::isBackHover()
{
	if (digitalRead(down_back) == 1)
		return true;
	return false;
}

bool Controller::isForwardHover()
{
	if (digitalRead(down_forward) == 1)
		return true;
	return false;
}

bool Controller::isLeftHover()
{
	if (digitalRead(down_left) == 1)
		return true;
	return false;
}

bool Controller::isRightHover()
{
	if (digitalRead(down_right) == 1)
		return true;
	return false;
}
