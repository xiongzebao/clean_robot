#include "Velometer.h"

#include "MyUtils.h"
#include "FlexiTimer2.h"



VelometerClass* VelometerClass::curVelometer = nullptr;
float  VelometerClass::velometerPeriod = 0.4;

void VelometerClass::onLeftCountStatic(void)
{
	curVelometer->onLeftCount();
}

void VelometerClass::onRightCountStatic(void)
{
	 
	curVelometer->onRightCount();
}

void VelometerClass::detectSpeed()
{
	
	curVelometer->SpeedDetection();
}

//����դ������ж���Ӧ
void   VelometerClass::onLeftCount(){

	/*if (this->leftSum % 50 == 0) {
		MyUtils.print("l:");
		MyUtils.println(leftSum);
		MyUtils.println(this->hasLeftPedometer);
	}*/
	if(this->hasLeftPedometer) {//�Ʋ���
		this->currentLeftGridCount++;
		if (this->currentLeftGridCount % 50 == 0) {
			MyUtils.println("currentLeftGridCount:");
			MyUtils.println(currentLeftGridCount);
		}

		if (this->currentLeftGridCount == this->leftAllGridCount&& this->onLeftPedometer != nullptr) {
			MyUtils.println("onLeftPedometer: call back");
			
			(*onLeftPedometer)(0);//�ﵽ�ǲ����ص�
			this->onLeftPedometer = nullptr;
			this->hasLeftPedometer = false;
			this->currentLeftGridCount = 0;
		}
	}
	this->leftCounter++;
	this->leftSum++;
}

//����դ������ж���Ӧ
void   VelometerClass::onRightCount()
{
	//if (this->rightSum % 50 == 0) {
	//	MyUtils.print("r:");
	//	MyUtils.println(rightSum);
	//	MyUtils.println(this->hasLeftPedometer);

	//}
	if (this->hasRightPedometer) {
		this->currentRightGridCount++;
		 
		if (this->currentRightGridCount % 50 == 0) {
			MyUtils.println("currentRightGridCount:");
			MyUtils.println(currentRightGridCount);
		}
 
		if (this->currentRightGridCount == this->rightAllGridCount) {

			(*onRightPedometer)(0);
			Serial.println(currentRightGridCount);
			this->onRightPedometer = nullptr;
			this->hasRightPedometer = false;
			this->currentRightGridCount = 0;
		}
	}
	this->rightCounter++;
	this->rightSum++;
}

//https://blog.csdn.net/coolwriter/article/details/80598134
void   VelometerClass::init(MyMotorClass *rightMotor, MyMotorClass *leftMotor)
{
	setCurMy();
	this->leftMotor = leftMotor;
	this->rightMotor = rightMotor;
	attachInterrupt(digitalPinToInterrupt(2), VelometerClass::onLeftCountStatic, FALLING);
	attachInterrupt(digitalPinToInterrupt(3), VelometerClass::onRightCountStatic, FALLING);//wending

}




//��ʱ�������Իص��������ٶ�
void   VelometerClass::SpeedDetection()
{

	//ת�ٵ�λ��ÿ���Ӷ���ת����r/min���������������Ϊ20���ն���
	float leftSpeed = (float)(this->leftCounter)/Constant::velometerPeriod;//С�����ֵ��ת��
	float rightSpeed =(float)(this->rightCounter)/ Constant::velometerPeriod;//С�����ֵ��ת��

	//	Serial.println(leftSpeed);
												   //�ָ������������ٵĳ�ʼ״̬
	this->leftCounter = 0;   //���������ֵ���㣬�Ա������һ����������
	this->rightCounter = 0;

	leftMotor->currentSpeed = leftSpeed;
	rightMotor->currentSpeed = rightSpeed;

	if (speedListener!= nullptr) {
		(*speedListener)(&vs);
	}

	
}

//���ּƲ���
void   VelometerClass::addLeltPedometer(int step_count, void(*callback)(int))
{
	this->leftAllGridCount = step_count * this->gridNum;
	this->onLeftPedometer = callback;
	this->hasLeftPedometer = true;
	MyUtils.println("addLeltPedometer");
}

void   VelometerClass::addRightPedometer(int zhuanshu, void(*callback)(int))
{
	this->rightAllGridCount = zhuanshu * this->gridNum;
	this->onRightPedometer = callback;
	this->hasRightPedometer = true;
	
	MyUtils.println("addRightPedometer");
}

void VelometerClass::removeRightPedometer()
{
	this->rightAllGridCount = 0;
	this->onRightPedometer = nullptr;
	this->hasRightPedometer = false;
	this->currentRightGridCount = 0;
	MyUtils.println("removeRightPedometer");
}

void VelometerClass::removeLeftPedometer()
{
	this->leftAllGridCount = 0;
	this->onLeftPedometer = nullptr;
	this->hasLeftPedometer = false;
	this->currentLeftGridCount = 0;
	MyUtils.println("removeLeftPedometer");
}

void VelometerClass::removePedometer()
{
	removeLeftPedometer();
	removeRightPedometer();
}



//�����ٶȼ����ߣ������Իص�
void   VelometerClass::setSpeedListener(void(*callback)(VehicleSpeed*))
{
	this->speedListener = callback;
}

VehicleSpeed VelometerClass::getSpeed()
{
	return this->vs;
}
 

MyMotorClass* VelometerClass::getLeftMotor()
{
	return this->leftMotor;
}

MyMotorClass* VelometerClass::getRightMotor()
{
	return this->rightMotor;
}

