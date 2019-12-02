
#include "MyMotor.h"
int MyMotorClass::MAX_SPEED = 255;

MyMotorClass::MyMotorClass(int in1, int in2, int en)
{
	this->init(in1, in2, en);

}

void MyMotorClass::init(int in1, int in2, int en)
{
	this->in1 = in1;
	this->in2 = in2;
	this->en = en;
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(en, OUTPUT);
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);

}

void MyMotorClass::setSpeed(int speed)
{
	if (speed > MAX_SPEED) {
		speed = MAX_SPEED;
	}
	else if (speed < 0) {
		speed = 0;
	}
	this->speed = speed;
	this->currentDutyCycle= map(speed, 0, MAX_SPEED, 0, 255);
	analogWrite(en, this->currentDutyCycle);
}

void MyMotorClass::speedUp()
{
	this->speed++;
	//setSpeed(speed);
}

void MyMotorClass::speedDown()
{
	this->speed--;
	//setSpeed(speed);
}

void MyMotorClass::forward()
{
	digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
	//analogWrite(en, HIGH);
	this->state = 1;

}

void MyMotorClass::back()
{
	digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
	this->state = 2;
}

void MyMotorClass::stop()
{
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	this->state = 0;
	//analogWrite(en, LOW);
}

void MyMotorClass::brake()
{
	digitalWrite(in1, HIGH);
	digitalWrite(in2, HIGH);
	this->state = 3;
	//analogWrite(en, LOW);
}

int MyMotorClass::getState()
{
	return this->state;
}

void MyMotorClass::openMaxSpeed()
{
	analogWrite(en, 255);
}

void MyMotorClass::increaseSpeed()
{
	int speedabs = this->speed - this->currentSpeed;
	if (speedabs > 1000) {
		this->currentDutyCycle+=10;
	} else if(500<speedabs<=1000) {
		this->currentDutyCycle+=5;
	}
	else if (  300 <= speedabs <=500) {
		this->currentDutyCycle ++;
	}else {
		this->currentDutyCycle ++;
	}
	//Serial.println(this->currentDutyCycle);
	analogWrite(en, this->currentDutyCycle);
}

void MyMotorClass::decreaseSpeed()
{
	int speedabs =  this->currentSpeed- this->speed;
	if (speedabs > 1000) {
		this->currentDutyCycle -= 20;
	}
	else if (500 < speedabs <= 1000) {
		this->currentDutyCycle -= 10;
	}
	else if (300 <= speedabs <= 500) {
		this->currentDutyCycle --;
	}
	else {
		this->currentDutyCycle--;
	}
	analogWrite(en, this->currentDutyCycle);
}
