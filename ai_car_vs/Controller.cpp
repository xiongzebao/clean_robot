#include "Controller.h"
#include"MyUtils.h"

boolean is_going = false;
boolean isForwarding = false;
boolean isBacking = false;

int turn_resulution = 10;
unsigned long last_back_crash_time = 0;
int fast_back_crash_times = 0;

Controller* Controller::instance = nullptr;

auto cb = [](int x) {
	Controller::instance->is_interrupt = false;
};

void Controller::on_forward_right_crash()
{
	MyUtils.println("on_forward_right_crash");
	instance->is_finish_forward_back = true;
	instance->is_interrupt = true;
	int level_forward_right = digitalRead(forward_right_gd);
	int level_forward_left = digitalRead(forward_left_gd);

	int level_left_forward = digitalRead(left_forward_gd);
	int level_left_back = digitalRead(left_back_gd);

	int level_right_forward = digitalRead(right_forward_gd);
	int level_right_back = digitalRead(right_back_gd);


	if (level_forward_right == 0) {
		if (digitalRead(level_forward_left) == 0) {
			if (level_left_forward == 1
				&& level_left_back == 1
				&& level_right_forward == 1
				&& level_right_back == 1
				) {
				instance->turn_left_right_random(90);
				return;
			}

			if (level_left_forward == 0 || level_left_back == 0) {
				auto a_lambda_func = [](int x) {
					instance->right(90, cb);
				};
				instance->back(100, a_lambda_func);
				return;
			}
			if (level_right_forward == 0 || level_right_back == 0) {

				auto a_lambda_func = [](int x) {
					instance->left(90, cb);
				};
				instance->back(100, a_lambda_func);
				return;
			}

			return;
		}
		instance->right();
		return;
	}

	auto a_lambda_func = [](int x) {
		instance->left(60, cb);
	};
	instance->mc->back(350, a_lambda_func);
}


void Controller::on_forward_left_crash()
{
	MyUtils.println("on_forward_left_crash ");
	instance->is_finish_forward_back = true;
	instance->is_interrupt = true;

	int level_forward_right = digitalRead(forward_right_gd);
	int level_forward_left = digitalRead(forward_left_gd);

	int level_left_forward = digitalRead(left_forward_gd);
	int level_left_back = digitalRead(left_back_gd);

	int level_right_forward = digitalRead(right_forward_gd);
	int level_right_back = digitalRead(right_back_gd);


	if (level_forward_left == 0) {//如果左边撞墙
		if (level_forward_right == 0) {
			if (level_left_forward == 1
				&& level_left_back == 1
				&& level_right_forward == 1
				&& level_right_back == 1
				) {
				instance->turn_left_right_random(90);
				return;
			}

			if (level_left_forward == 0 || level_left_back == 0) {
				auto a_lambda_func = [](int x) {
					instance->right(90, cb);
				};
				instance->back(100, a_lambda_func);
				return;
			}
			if (level_right_forward == 0 || level_right_back == 0) {

				auto a_lambda_func = [](int x) {
					instance->left(90, cb);
				};
				instance->back(100, a_lambda_func);
				return;
			}


		}
		else {
			instance->right();

		}
	}

		auto a_lambda_func = [](int x) {
			instance->right(60, cb);
		};
		instance->mc->back(350, a_lambda_func);
		return;
	}


void Controller::on_back_right_crash()
{
	MyUtils.println("on_back_right_crash");
	instance->is_finish_forward_back = true;
	instance->is_interrupt = true;
	unsigned cur_time = millis();
	unsigned interval = cur_time - last_back_crash_time;
	if (interval <= 1000) {
		fast_back_crash_times++;
	}
	else {
		fast_back_crash_times = 0;
	}
	last_back_crash_time = cur_time;

	auto a_lambda_func = [](int x) {
		if (fast_back_crash_times >= 2) {
			instance->left(turn_resulution * 5, cb);
		}
		instance->left(turn_resulution, cb);
	};
	instance->mc->forward(200, a_lambda_func);

}

void Controller::on_back_left_crash()
{
	instance->is_finish_forward_back = true;
	instance->is_interrupt = true;
	unsigned cur_time = millis();
	unsigned interval = cur_time - last_back_crash_time;
	if (interval <= 1000) {
		fast_back_crash_times++;
	}
	else {
		fast_back_crash_times = 0;
	}
	last_back_crash_time = cur_time;
	auto a_lambda_func = [](int x) {

		if (fast_back_crash_times >= 2) {
			instance->left(turn_resulution * 5, cb);
		}
		instance->left(turn_resulution, cb);
	};
	instance->mc->forward(200, a_lambda_func);
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


void Controller::forward_back()
{
	if (is_interrupt || !is_finish_forward_back) {
		return;
	}
	is_finish_forward_back = false;
	auto a_lambda_func = [](int x) {
		auto f = [](int x) {
			instance->is_finish_forward_back = true;
		};
		instance->back(200, f);
	};
	mc->forward(400, a_lambda_func);
}

void Controller::loop() {
	delay(10);
	forward_back();

}


//void Controller::loop() {////红外亮0，灭1
//
//
//
//	/*
//	//前方悬空,后退5cm，右转30度
//	if (digitalRead(down_forward_gd) == 1) {
//		auto a_lambda_func = [](int x) {
//			instance->right(30);
//		};
//		mc->back(5, a_lambda_func);
//		return;
//
//	}
//	//后方悬空,前进5cm，左转30度
//	if (digitalRead(down_forward_gd) == 1) {
//		auto a_lambda_func = [](int x) {
//			instance->left(30);
//		};
//		mc->forward(5, a_lambda_func);
//		return;
//	}
//	//左边悬空,后退5cm，右转30度
//	if (digitalRead(down_left_gd) == 1) {
//		auto a_lambda_func = [](int x) {
//			instance->right(30);
//		};
//		mc->back(5, a_lambda_func);
//		return;
//	}
//
//
//	//右边悬空,后退5cm，左转30度
//	if (digitalRead(down_right_gd) == 0) {
//		auto a_lambda_func = [](int x) {
//			instance->left(30);
//		};
//		MyUtils.println("d");
//		mc->back(5, a_lambda_func);
//		return;
//	}
//	*/
//
//	int p_forward_left_crash = digitalRead(forward_left_crash);
//	int p_forward_right_crash = digitalRead(forward_right_crash);
//
//	////左前方红外触发，后退5cm，右转30，前进
//	MyUtils.println(p_forward_left_crash);
//	if (p_forward_left_crash == 0) {
//		//auto a_lambda_func = [](int x) {
//		//	MyUtils.println("callback");
//		//	instance->right(30);
//		//};
//		//mc->back(5, a_lambda_func);
//		mc->left();
//		return;
//	}
//
//
//	/*
//	////右后方红外触发，前进5cm，左转30，前进
//	if (digitalRead(right_back_gd) == 0) {
//		auto a_lambda_func = [](int x) {
//			instance->left(30);
//		};
//		mc->forward(5, a_lambda_func);
//	}
//
//	////左后方红外触发，前进5cm，右转30，前进
//	if (digitalRead(left_back_gd) == 0) {
//		auto a_lambda_func = [](int x) {
//			instance->right(30);
//		};
//		mc->forward(5, a_lambda_func);
//	}
//	*/
//}






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

void Controller::back_right()
{
	auto a_lambda_func = [](int x) {

		instance->right(90, cb);

	};

	instance->back(100, a_lambda_func);
}

void Controller::back_left()
{
	auto a_lambda_func = [](int x) {

		instance->left(90, cb);

	};

	instance->back(100, a_lambda_func);
}

void Controller::turn_left_right_random(const int degree)
{

	auto a_lambda_func = [](int x) {
		long randNumber = random(1000);

		if (randNumber % 2 == 0) {
			instance->left(90, cb);
		}
		else {
			instance->right(90, cb);
		}
	};

	instance->back(100, a_lambda_func);
}



void Controller::left(int degree)
{
	mc->turnLeft(degree);
}

void Controller::right(int degree)
{
	mc->turnRight(degree);
}

void Controller::left(int degree, void(*f)(int))
{
	mc->turnLeft(degree, f);
}

void Controller::right(int degree, void(*f)(int))
{
	mc->turnRight(degree, f);
}

void Controller::back(int degree, void(*f)(int))
{
	mc->back(degree, f);
}

void Controller::forward(int degree, void(*f)(int))
{
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
