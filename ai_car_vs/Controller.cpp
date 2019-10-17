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
{////������0����1
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

	if (isForwardHover()) {//���ǰ��������
		mc->stop();
	}else {
		//�ж�ǰ���Ƿ����ϰ���,������ȱʧ����ʱ��ʵ�֣���ǰ��
		mc->forward();
		Serial.println("forward");
		return;
	}
	if (isBackHover()){
		mc->stop();
		return;//ǰ�������£���ֹͣ
	}else {
		//if (getBackState() != 3) {//�������ϰ���
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
		//�ж�ǰ���Ƿ����ϰ��� 
		if (getForwardState()!=3 ){//ǰ�����ϰ���
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


//0;���Ҷ��£�1����£�2���Ҷ£�3����ͨ
int Controller::getBackState()
{
 
	int back_left_level = digitalRead(back_left);
	int back_right_level = digitalRead(back_right);
	if (back_left_level == 0 && back_right_level == 0) {//�������ϰ���
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
