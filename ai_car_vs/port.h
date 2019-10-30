#pragma once
#ifndef _PORT_h
#define _PORT_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"

#else
#include "WProgram.h"
#endif

const int motorA1 = 30;
const int motorA2 = 32;
const int pwdA = 6;
const int motorB1 = 26;
const int motorB2 = 28;
const int pwdB = 7;

const int down_forward_gd = 34;
const int down_back_gd = 36;
const int down_right_gd = 38;
const int down_left_gd = 40;

const int back_left_gd = 42;
const int back_right_gd = 44;
const int left_back_gd = 46;
const int left_forward_gd = 48;
const int right_back_gd = 50;
const int right_forward_gd = 52;

const int forward_left_gd = 52;
const int forward_right_gd = 52;

const int back_left_crash = 21;
const int back_right_crash = 20;
const int forward_left_crash = 18;
const int forward_right_crash = 19;


//Board	int.0	int.1	int.2	int.3	int.4	int.5
//Uno, Ethernet	2	3
//Mega2560	2	3	21	20	19	18
//Leonardo	3	2	0	1	7
//Due(see below)

#endif