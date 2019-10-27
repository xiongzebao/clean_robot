#include "Controller.h"
#include"MyUtils.h"

boolean is_going = false;
boolean isForwarding = false;
boolean isBacking = false;

Controller* Controller::instance = nullptr;

void Controller::on_forward_right_crash()
{
	MyUtils.println("on_forward_right_crash");
	auto a_lambda_func = [](int x) {
		 
		instance->left(60);
	};
	instance->mc->back(350, a_lambda_func);

}

int i = 0;
void Controller::on_forward_left_crash()
{
	MyUtils.println("on_forward_left_crash ");
	int level = digitalRead(forward_left_crash);
	auto a_lambda_func = [](int x) {
		MyUtils.println("on_forward_left_crash finish");
		instance->left(50);
	};
	instance->mc->back(300, a_lambda_func);
}

int j = 0;
void Controller::on_back_right_crash()
{
	j++;
	MyUtils.println("on_back_right_crash");
	MyUtils.println(j);
	/*auto a_lambda_func = [](int x) {
	
		instance->left(100);
	};
	instance->mc->forward(200, a_lambda_func);*/
	instance->mc->forward();
}

void Controller::on_back_left_crash()
{
	int level = digitalRead(forward_left_crash);
	String ls = String(level);
	MyUtils.println("on_back_left_crash:"+level);
	//auto a_lambda_func = [](int x) {
	//
	//	instance->right(100);
	//};
	//instance->mc->forward(200, a_lambda_func);
	instance->mc->forward();
}

void Controller::initPort()
{
	pinMode(down_forward_gd, INPUT);
	pinMode(down_back_gd, INPUT);
	pinMode(down_right_gd, INPUT);
	pinMode(down_left_gd, INPUT);
	pinMode(back_left_gd, INPUT);
	pinMode(back_right_gd, INPUT);
	pinMode(left_back_gd, INPUT);
	pinMode(left_forward_gd, INPUT);
	pinMode(right_back_gd, INPUT);
	pinMode(right_forward_gd, INPUT);

	pinMode(back_left_crash, INPUT_PULLUP);
	pinMode(back_right_crash, INPUT_PULLUP);
	pinMode(forward_left_crash, INPUT_PULLUP);
	pinMode(forward_right_crash, INPUT_PULLUP);

 
	attachInterrupt(digitalPinToInterrupt(back_left_crash), Controller::on_back_left_crash, FALLING);
	attachInterrupt(digitalPinToInterrupt(back_right_crash), Controller::on_back_right_crash, FALLING);
	attachInterrupt(digitalPinToInterrupt(forward_left_crash), Controller::on_forward_left_crash, FALLING);
	attachInterrupt(digitalPinToInterrupt(forward_right_crash), Controller::on_forward_right_crash, FALLING);

}

Controller::Controller(MotorControllerClass* mc)
{
	this->mc = mc;
}

//void Controller::loop() {
//
//}


void Controller::loop() {////红外亮0，灭1
 
	 

	/*
	//前方悬空,后退5cm，右转30度
	if (digitalRead(down_forward_gd) == 1) {
		auto a_lambda_func = [](int x) {
			instance->right(30);
		};
		mc->back(5, a_lambda_func);
		return;
	
	}
	//后方悬空,前进5cm，左转30度
	if (digitalRead(down_forward_gd) == 1) {
		auto a_lambda_func = [](int x) {
			instance->left(30);
		};
		mc->forward(5, a_lambda_func);
		return;
	}
	//左边悬空,后退5cm，右转30度
	if (digitalRead(down_left_gd) == 1) {
		auto a_lambda_func = [](int x) {
			instance->right(30);
		};
		mc->back(5, a_lambda_func);
		return;
	}


	//右边悬空,后退5cm，左转30度
	if (digitalRead(down_right_gd) == 0) {
		auto a_lambda_func = [](int x) {
			instance->left(30);
		};
		MyUtils.println("d");
		mc->back(5, a_lambda_func);
		return;
	}
	*/
	 
	int p_forward_left_crash = digitalRead(forward_left_crash);
	int p_forward_right_crash = digitalRead(forward_right_crash);

	////左前方红外触发，后退5cm，右转30，前进
	MyUtils.println(p_forward_left_crash);
	if (p_forward_left_crash == 0) {
		//auto a_lambda_func = [](int x) {
		//	MyUtils.println("callback");
		//	instance->right(30);
		//};
		//mc->back(5, a_lambda_func);
		mc->left();
		return;
	}
	

	/*
	////右后方红外触发，前进5cm，左转30，前进
	if (digitalRead(right_back_gd) == 0) {
		auto a_lambda_func = [](int x) {
			instance->left(30);
		};
		mc->forward(5, a_lambda_func);
	}

	////左后方红外触发，前进5cm，右转30，前进
	if (digitalRead(left_back_gd) == 0) {
		auto a_lambda_func = [](int x) {
			instance->right(30);
		};
		mc->forward(5, a_lambda_func);
	}
	*/
}






void Controller::forward()
{
	mc->forward();
	//if (isLeftHover()||isRightHover()) {
	// 
	//	return;
	//}

	//if (isForwardHover()) {//如果前面有悬崖
	//	mc->stop();
	//}else {
	//	//判断前面是否有障碍物,传感器缺失，暂时不实现，仅前进
	//	mc->forward();
	//	Serial.println("forward");
	//	return;
	//}
	//if (isBackHover()){
	//	mc->stop();
	//	return;//前后都是悬崖，即停止
	//}else {
	//	//if (getBackState() != 3) {//后面有障碍物
	//		mc->back();
	//	
	//}
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
	}
	else {
		//判断前面是否有障碍物 
		if (getForwardState() != 3) {//前面有障碍物
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

void Controller::left(int degree)
{
	mc->turnLeft(degree);
}

void Controller::right(int degree)
{
	mc->turnRight(degree);
}

void Controller::stop()
{

}


//0;左右都堵，1：左堵，2：右堵，3，畅通
int Controller::getBackState()
{

	int back_left_level = digitalRead(back_left_gd);
	int back_right_level = digitalRead(back_right_gd);
	if (back_left_level == 0 && back_right_level == 0) {//后面有障碍物
		return 0;
	}
	if (back_left_level == 0 && back_right_level == 1) {
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
	if (digitalRead(down_back_gd) == 1)
		return true;
	return false;
}

bool Controller::isForwardHover()
{
	if (digitalRead(down_forward_gd) == 1)
		return true;
	return false;
}

bool Controller::isLeftHover()
{
	if (digitalRead(down_left_gd) == 1)
		return true;
	return false;
}

bool Controller::isRightHover()
{
	if (digitalRead(down_right_gd) == 1)
		return true;
	return false;
}
