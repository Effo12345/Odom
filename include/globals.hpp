#pragma once
#include "main.h"
//#include "xlib/grapher.hpp"
//#include "xlib/interface.hpp"

//Constants
const int MAX_VOLTAGE = 12000;

//Controller
extern Controller master;

extern MotorGroup driveL;
extern MotorGroup driveR;

extern pros::ADIEncoder leftEncoder;
extern pros::ADIEncoder rightEncoder;
extern pros::ADIEncoder backEncoder;