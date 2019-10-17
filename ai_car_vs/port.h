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

const int down_forward = 34;
const int down_back = 36;
const int down_right = 38;
const int down_left = 40;

const int back_left = 42;
const int back_right = 44;
const int left_back = 46;
const int left_forward = 48;
const int right_back = 50;
const int right_forward = 52;



#endif