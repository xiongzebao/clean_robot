// MotorController.h
//控制器类：控制小车的速度和方向以及各种动作
//小车轴径130mm，轮子直径65mm
#ifndef _MOTORCONTROLLER_h
#define _MOTORCONTROLLER_h

#include "arduino.h"
#include"MyMotor.h"
#include"Velometer.h"

class MotorControllerClass
{
public:
	static const int SPEED_ALLOW_MAX_DIFF = 20;//速度误差允许最大值
	static const int STOP = 0;
	static const int FORWARD = 1;
	static const int BACK = 2;
	static const int BRAKE = 3;//制动
	static const int LEFT = 4;//左转
	static const int RIGHT = 5;//右转
	static const int ROUND = 6;//原地转圈
	static const int TURN_RIGHT = 7;//右转
	static const int TURN_LEFT = 8;//右转

	static void onSpeedDetect(VehicleSpeed*);
	static MotorControllerClass* instance;

	static const int FOUR_WHEEL_DRIVER = 1;
	static const int TWO_WHEEL_DRIVER = 2;




public:
	//四个电机
	MyMotorClass *m1;
	MyMotorClass *m2;
	MyMotorClass *m3;
	MyMotorClass *m4;
	int state = 0;//记录当前小车行进状态，0，停止，1，前进，2，后退，3，制动,4,
	int speed = 0;//记录当前小车速度
	VelometerClass velometer;//测速器
	int mode = FOUR_WHEEL_DRIVER;
	static bool left_finished  ;
	static bool right_finished  ;
	static void (*on_turn_left)(int);
	static void (*on_turn_right)(int);



public:
	MotorControllerClass(MyMotorClass* motor1, MyMotorClass* motor2, MyMotorClass* motor3, MyMotorClass* motor4);

	MotorControllerClass(MyMotorClass* motor1, MyMotorClass* motor2);

	//控制四个电机
	void init(MyMotorClass *motor1, MyMotorClass *motor2, MyMotorClass *motor3, MyMotorClass *motor4);
	//控制个两个电机
	void init(MyMotorClass* motor1, MyMotorClass* motor2);
	

	
	void forward();
	void setSpeed(int speed);
	void back();
	void left();
	void right();
	void stop();
	void brake();//制动
	void adjustSpeed(struct VehicleSpeed* speed);//定时矫正速度，因为电机受摩擦和电池电压影响运转速度不稳定，要定时加减速以微调矫正到指定速度
	void turnLeft(int degree);//左转度数，0~360
	void turnLeft(int degree, void(*f)(int));
	void turnRight(int degree);//右转度数，0~360
	void turnRight(int degree, void(*f)(int));
	void back(int distance,void(*f)(int));//向前移动指定距离（单位厘米）
	void back(int distance);
	void forward(int distance);//向后移动指定距离（单位厘米）
	void forward(int distance,void(*f)(int x));//向后移动指定距离（单位厘米）

	void startDetectSpeed();
	void stopDetectSpeed();
	VehicleSpeed  getSpeed();
	void openLeftMotorMaxSpeed();//开启左边电机最大速度
	int getLeftAllGridNum() {
		return velometer.leftSum;
	}
	void continueGo();

	
private:
	void printSpeed(MyMotorClass *m);
	
	static void left_callback(int x);
	static void right_callback(int x);
	static void on_back_finished(int x);
	

};



#endif

