#pragma once

#include <WString.h>
using namespace std;

class Constant
{
public:
	static  const bool  isDebug = true;
	static  const String  SPEED_UP;
	static  const String  SPEED_DOWN;
	static  const String  SPEED_AT;

	static  const String  TURN_LEFT;
	static  const String  TURN_LEFT_AT;

	static  const String  TURN_RIGHT;
	static  const String  TURN_RIGHT_AT;

	static  const String  FORWARD;
	static  const String  BACK;
	static  const String  STOP;

	static const float velometerPeriod;



};

