// MyMotor.h
// 电机类：控制一个电机速度和方向
#ifndef _MYMOTOR_h
#define _MYMOTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class MyMotorClass
{//一分钟转的转数，由于不能计算出达到此转速所需要的pwd值，需要电机控制类进行不断调速
public:
	static int MAX_SPEED;//定义电机能达到的最大转速
	static const int ALLOW_ARROE_RANGE = 10;//定义允许速度误差为10
  	static const int STOP = 0;
	static const int FORWARD = 1; 
	static const int BACK = 2;
	static const int BRAKE = 3;
	int currentSpeed = 0;//当前速度；

private:
	int in1;//端口1
	int in2;//端口2
	int en;//使能端
	int state = 0;//记录当前电机行进状态，STOP，停止，FORWARD，前进，BACK，后退，BRAKE，制动
	int currentDutyCycle=0;//当前占空比,电机通过调整占空比来调整速度

 protected:

 public:
	 MyMotorClass(int   in1, int   in2, int   en);
	void init( int   in1,  int   in2,   int   en);
	void setSpeed(int speed);
	void speedUp();
	void speedDown();
	void forward();
	void back();
	void stop();//停止
	void brake();//制动
	int getState();//获取运行状态
	void openMaxSpeed();//开启最大速度

public:
	int speed = 0;//目标速度，当设置了电机速度时，
		//电机不能立刻设置到目标速度，必须通过不断调整达到,
	//当currentSpeed与speed的差值在运行误差范围内,即认为达到目标速度
	void increaseSpeed();//调用此函数来增加实际速度
	void decreaseSpeed();
	 

};
 

#endif

