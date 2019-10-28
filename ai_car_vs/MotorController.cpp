#include "MotorController.h"
#include"Constant.h"
#include"MyUtils.h"



typedef void (*func_type)(int);
boolean MotorControllerClass::left_finished = false;
boolean MotorControllerClass::right_finished = false;



MotorControllerClass* MotorControllerClass::instance = nullptr;
//speed是当前实时车速，由测速器实时更新speed的值，更新频率默认1000ms
void MotorControllerClass::adjustSpeed(VehicleSpeed* speed)
{

	return;
 
	//如果行进方向是前进后退
 
	if (this->state == FORWARD || this->state == BACK) {
	 
		//校准右边
		if (m1->currentSpeed >m1->speed) {//右前比指定速度大并且大于允许误差
			m1->decreaseSpeed();//右前减速
			if (mode == FOUR_WHEEL_DRIVER) {
				m4->decreaseSpeed();//右后减速
			}
	 
		}
		if ( m1->currentSpeed< m1->speed ) { //右后比指定速度小并且大于允许误差
			m1->increaseSpeed();// 右前加速
			if (mode == FOUR_WHEEL_DRIVER) {
				m4->increaseSpeed();//右后加速
			}
		}

		//校准左边
		if (m2->currentSpeed >m2->speed ) {//左前比指定速度大并且大于允许误差


			m2->decreaseSpeed();//左前减速
			if (mode == FOUR_WHEEL_DRIVER) {
				m3->decreaseSpeed();//左后减速
			}
		}
		if (m2->speed > m2->currentSpeed  ) { //左后比指定速度小并且大于允许误差
			m2->increaseSpeed();//左前加速
			if (mode == FOUR_WHEEL_DRIVER) {
				m3->increaseSpeed();//左后加速
			}
		}

		return;
	}
	if (state == TURN_LEFT) {
		if (m1->currentSpeed < m1->speed) {
			m1->increaseSpeed();
			m2->increaseSpeed();
			if (mode == FOUR_WHEEL_DRIVER) {
				m3->increaseSpeed();
				m4->increaseSpeed();
			}
		}else {
			m1->decreaseSpeed();
			m2->decreaseSpeed();
			if (mode == FOUR_WHEEL_DRIVER) {
				m3->decreaseSpeed();
				m4->decreaseSpeed();
			}
		}
	}
	if (state == TURN_RIGHT) {
		if (m2->currentSpeed < m2->speed) {
			m1->increaseSpeed();
			m2->increaseSpeed();
			if (mode == FOUR_WHEEL_DRIVER) {
				m3->increaseSpeed();
				m4->increaseSpeed();
			}
		}
		else {
			m1->decreaseSpeed();
			m2->decreaseSpeed();
			if (mode == FOUR_WHEEL_DRIVER) {
				m3->decreaseSpeed();
				m4->decreaseSpeed();
			}
		 
		}
	}


	//TODO:目前只实现校准前进和后退校准
}

void MotorControllerClass::turnLeft(int degree)
{
	if (this->state == TURN_LEFT) {
		return;
	}
	auto a_lambda_func = [](int x) { 
		MyUtils.println("turnLeft finish");
		instance->forward();
	};
	turnLeft(degree, a_lambda_func);
	MyUtils.println("turnLeft");
}


boolean left_finished = false;
boolean right_finished = false;


void MotorControllerClass::turnRight(int degree)
{
	if (this->state == TURN_RIGHT) {
		return;
	}
	auto a_lambda_func = [](int x) {
		MyUtils.println("turnRight finish");
		instance->forward();
	};
	turnRight(degree, a_lambda_func);
}

void MotorControllerClass::turnLeft(int degree, void(*f)(int))
{
	if (this->state == TURN_LEFT) {
		return;
	}
	this->velometer.removePedometer();
	this->state = TURN_LEFT;

	this->velometer.addRightPedometer(degree, f);
	m1->forward();
	m2->back();
	if (mode == FOUR_WHEEL_DRIVER) {
		m3->forward();
		m4->back();
	}
	setSpeed(this->speed);

}

void MotorControllerClass::turnRight(int degree, void(*f)(int))
{
	if (this->state == TURN_RIGHT) {
		return;
	}
	this->velometer.removePedometer();
	this->state = TURN_RIGHT;
	this->velometer.addRightPedometer(degree, f);//搞不清楚为什么addLeftPedometer不行！
	m1->back();
	m2->forward();
	if (mode == FOUR_WHEEL_DRIVER) {
		m3->forward();
		m4->stop();
	}
	setSpeed(this->speed);
	MyUtils.println("turnRight");
}

void MotorControllerClass::back(int distance, void(*f)(int))
{
 
 

	if (this->state == BACK) {
		return;
	}

	this->velometer.removePedometer();
	int step_count = distance;
	this->velometer.addLeltPedometer(step_count, f);
	this->state = BACK;
	m1->back();
	m2->back();
	if (mode == FOUR_WHEEL_DRIVER) {
		m3->back();
		m4->back();
	}
	//setSpeed(this->speed);
}

void MotorControllerClass::back(int distance)
{
	if (this->state == BACK) {
		return;
	}
	this->velometer.removePedometer();
	int step_count = distance;
	auto a_lambda_func = [](int x) {
		MyUtils.println("turnRight finish");
		instance->turnLeft(30);
	};
	this->velometer.addLeltPedometer(step_count, a_lambda_func);
	this->state =BACK;
	m1->back();
	m2->back();
	if (mode == FOUR_WHEEL_DRIVER) {
		m3->back();
		m4->back();
	}
	setSpeed(this->speed);

}

void MotorControllerClass::forward(int distance)
{
	if (this->state == FORWARD) {
		return;
	}
	this->velometer.removePedometer();

}

void MotorControllerClass::forward(int distance, void(*f)(int x))
{
	if (this->state == FORWARD) {
		return;
	}
	this->velometer.removePedometer();
	int step_count = distance;
	this->velometer.addRightPedometer(step_count, f);
	this->state = FORWARD;
	m1->forward();
	m2->forward();
	if (mode == FOUR_WHEEL_DRIVER) {
		m3->forward();
		m4->forward();
	}
	setSpeed(this->speed);
}

void MotorControllerClass::forward_back()
{
	is_forward_back = true;
	while (is_forward_back)
	{
		auto a_lambda_func = [](int x) {
			auto f = [](int x) {

				instance->forward_back();
			};
			instance->back(200, f);
		};
		forward(400, a_lambda_func);
	}
	
}


 
 
 
VehicleSpeed MotorControllerClass::getSpeed()
{
	return velometer.getSpeed();
}

void MotorControllerClass::openLeftMotorMaxSpeed()
{
	m2->openMaxSpeed();
}

void MotorControllerClass::printSpeed(MyMotorClass* m)
{
	if (Constant::isDebug==true) {
		/*MyUtils.print("curSpeed");
		MyUtils.print("->");
		MyUtils.println(m->currentSpeed);*/
	}
	
}

void MotorControllerClass::continueGo()
{
	switch (state)
	{
	case FORWARD:forward(); break;
	case BACK:back(); break;
	case RIGHT:right(); break;
	case LEFT:left(); break;
	default:
		break;
	}
}




void MotorControllerClass::on_back_finished(int x)
{
	instance->turnLeft(90);
}

 

void MotorControllerClass::onSpeedDetect(VehicleSpeed*speed)
{
	instance->adjustSpeed(speed);
}

MotorControllerClass::MotorControllerClass(MyMotorClass* motor1, MyMotorClass* motor2, MyMotorClass* motor3, MyMotorClass* motor4)
{
	this->init(motor1, motor2, motor3, motor4);
}

MotorControllerClass::MotorControllerClass(MyMotorClass* motor1, MyMotorClass* motor2)
{
	this->init(motor1, motor2);
}

void MotorControllerClass::init(MyMotorClass *motor1, MyMotorClass *motor2, MyMotorClass *motor3, MyMotorClass *motor4)
{
	this->m1 = motor1;
	this->m2 = motor2;
	this->m3 = motor3;
	this->m4 = motor4;
	instance = this;
	mode = FOUR_WHEEL_DRIVER;
	velometer.init(motor1,motor2);
	velometer.setSpeedListener(MotorControllerClass::onSpeedDetect);
}

void MotorControllerClass::init(MyMotorClass* motor1, MyMotorClass* motor2)
{
	this->m1 = motor1;
	this->m2 = motor2;
	instance = this;
	mode = TWO_WHEEL_DRIVER;
	velometer.init(motor1, motor2);
	velometer.setSpeedListener(MotorControllerClass::onSpeedDetect);
}



void MotorControllerClass::forward()
{
	if (this->state == FORWARD) {
		return;
	}
	this->velometer.removePedometer();
	m1->forward();
	m2->forward();
	if (mode == FOUR_WHEEL_DRIVER) {
		m3->forward();
		m4->forward();
	}
	setSpeed(this->speed);
	this->state = 1;
}

void MotorControllerClass::setSpeed(int speed)
{
	this->speed = speed;
	m1->setSpeed(speed);
	m2->setSpeed(speed);
	if (mode == FOUR_WHEEL_DRIVER) {
		m3->setSpeed(speed);
		m4->setSpeed(speed);
	}
}

void MotorControllerClass::back()
{

	if (state == BACK)
		return;
	this->velometer.removePedometer();
	m1->back();
	m2->back();
	if (mode == FOUR_WHEEL_DRIVER) {
		m3->back();
		m4->back();
	}
	setSpeed(this->speed);
	this->state = BACK;
}

void MotorControllerClass::left()
{
	if (state == LEFT)
		return;
	//this->velometer.removePedometer();
	m1->forward();
	m2->brake();

	if (mode == FOUR_WHEEL_DRIVER) {
		m3->stop();
		m4->forward();
	}
	setSpeed(this->speed);
	this->state = LEFT;
}

void MotorControllerClass::right()
{
	if (state == RIGHT)
		return;
	this->velometer.removePedometer();
	m1->brake();
	m2->forward();
	if (mode == FOUR_WHEEL_DRIVER) {
		m3->forward();
		m4->stop();
	}
	setSpeed(this->speed);
	this->state = RIGHT;
}

void MotorControllerClass::stop()
{
	if (state == STOP)
		return;
	this->velometer.removePedometer();
	m1->stop();
	m2->stop();
	if (mode == FOUR_WHEEL_DRIVER) {
		m3->stop();
		m4->stop();
	}
	this->state = STOP;
}

void MotorControllerClass::brake()
{
	if (state == BRAKE)
		return;
	this->velometer.removePedometer();
	if (state == FORWARD && (m1->getState() == FORWARD || m2->getState() == FORWARD)) {
 
		m1->brake();
		m2->brake();
		if (mode == FOUR_WHEEL_DRIVER) {
			m3->brake();
			m4->brake();
		}
		this->state = BRAKE;
	}
	
}
