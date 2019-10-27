// Velometer.h
/*
	测速器类：测试小车左右前轮速度，只测前面两个轮子，它是一个辅助类，
	辅助MotorController控制小车
*/

#ifndef _VELOMETER_h1
#define _VELOMETER_h1

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include"MyMotor.h"
 


class  VehicleSpeed {
public:
	int leftSpeed = 0;//左前轮速度；
	int rightSpeed = 0;//右前轮速度;
};

class VelometerClass
{

public:
	static VelometerClass* curVelometer;
	static void onLeftCountStatic(void);//左轮计数回调函数 
	static void onRightCountStatic(void);//右轮计数回调函数 
	static void detectSpeed();

private:
	    const static int gridNum = 1;//一圈的栅格数
		 static  float  velometerPeriod;//测速周期，默认500ms

private:
	int leftCounter=0, rightCounter=0;
	unsigned long time=0, old_time=0; // 时间标记
	unsigned long time1=0; // 时间标记
	float leftSpeed=0, rightSpeed=0;//左、右轮速度
	int currentLeftGridCount=0;//当前左轮所经过的栅格数
	int leftAllGridCount;//左轮旋转指定转数需要经过的栅格数
	void (*onLeftPedometer)(int x);//转过指定转数回调
	bool hasLeftPedometer;//是否有左轮计数器
	int currentRightGridCount;//当前右轮所经过的栅格数
	int rightAllGridCount;//右轮旋转指定转数需要经过的栅格数
	void (*onRightPedometer)(int x);//右轮转过指定转数回调
	bool hasRightPedometer;//是否有右轮计数器
	void (*speedListener)(VehicleSpeed*);//速度监听函数回调指针
	MyMotorClass* rightMotor;
	MyMotorClass* leftMotor;

public:
	VehicleSpeed vs;
	int leftSum = 0;
	int rightSum = 0;

private:
	void onLeftCount();//左轮计数中断回调函数
	void onRightCount();//右轮计数中断回调函数

public:
	VelometerClass() {

	}

	~VelometerClass() {

	}
	void setCurMy()
	{//设置当前对象为回调函数调用的对象  
		curVelometer = this;
	}
	void init(MyMotorClass *rightMotor,MyMotorClass *leftMotor);
	void SpeedDetection();
	void addLeltPedometer(int step_count, void(*callback)(int));
	void addRightPedometer(int step_count, void(*callback)(int));
	void removeRightPedometer();
	void removeLeftPedometer();
	void removePedometer();
	void setSpeedListener(void(*callback)(VehicleSpeed*));
	VehicleSpeed getSpeed();
	 
	MyMotorClass* getLeftMotor();
	MyMotorClass* getRightMotor();

};

#endif

