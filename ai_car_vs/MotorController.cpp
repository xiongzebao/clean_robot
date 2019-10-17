#include "MotorController.h"
#include"Constant.h"
#include"MyUtils.h"

MotorControllerClass* MotorControllerClass::instance = nullptr;
//speed�ǵ�ǰʵʱ���٣��ɲ�����ʵʱ����speed��ֵ������Ƶ��Ĭ��1000ms
void MotorControllerClass::adjustSpeed(VehicleSpeed* speed)
{
 
	//����н�������ǰ������
 
	if (this->state == FORWARD || this->state == BACK) {
	 
		//У׼�ұ�
		if (m1->currentSpeed >m1->speed) {//��ǰ��ָ���ٶȴ��Ҵ����������
			m1->decreaseSpeed();//��ǰ����
			if (mode == FOUR_WHEEL_DRIVER) {
				m4->decreaseSpeed();//�Һ����
			}
	 
		}
		if ( m1->currentSpeed< m1->speed ) { //�Һ��ָ���ٶ�С���Ҵ����������
			m1->increaseSpeed();// ��ǰ����
			if (mode == FOUR_WHEEL_DRIVER) {
				m4->increaseSpeed();//�Һ����
			}
		}

		//У׼���
		if (m2->currentSpeed >m2->speed ) {//��ǰ��ָ���ٶȴ��Ҵ����������


			m2->decreaseSpeed();//��ǰ����
			if (mode == FOUR_WHEEL_DRIVER) {
				m3->decreaseSpeed();//������
			}
		}
		if (m2->speed > m2->currentSpeed  ) { //����ָ���ٶ�С���Ҵ����������
			m2->increaseSpeed();//��ǰ����
			if (mode == FOUR_WHEEL_DRIVER) {
				m3->increaseSpeed();//������
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


	//TODO:Ŀǰֻʵ��У׼ǰ���ͺ���У׼
}

void MotorControllerClass::turnLeft(int degree)
{
	
	auto a_lambda_func = [](int x) { 
		MyUtils.println("turnLeft finish");
		instance->stop();
	};
	this->velometer.addRightPedometer(degree, a_lambda_func);
	
	this->state = TURN_LEFT;
	m1->forward();
	m2->stop();
	if (mode == FOUR_WHEEL_DRIVER) {
		m3->stop();
		m4->forward();
	}
	setSpeed(this->speed);
}

void MotorControllerClass::turnRight(int degree)
{
	auto a_lambda_func = [](int x) {
		MyUtils.println("turnRight finish");
		instance->stop();
	};
	this->velometer.addLeltPedometer(degree, a_lambda_func);
	this->state = TURN_RIGHT;
	m1->stop();
	m2->forward();
	if (mode == FOUR_WHEEL_DRIVER) {
		m3->forward();
		m4->stop();
	}
	setSpeed(this->speed);
	MyUtils.println("turnRight");

}

void MotorControllerClass::startDetectSpeed()
{
	velometer.startVelometer();
}

void MotorControllerClass::stopDetectSpeed()
{
	velometer.stopVelometer();
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
