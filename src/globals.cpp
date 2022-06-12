#include "globals.hpp"
using namespace xlib;

//Controllers
Controller master(ControllerId::master);

//Motors
Motor driveFL(1, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor driveBL(2, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor driveFR(3, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor driveBR(4, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);

MotorGroup driveL({driveFL, driveBL});
MotorGroup driveR({driveFR, driveBR});

pros::ADIEncoder leftEncoder(1, 2, false);
pros::ADIEncoder rightEncoder(3, 4, false);
pros::ADIEncoder backEncoder(5, 6, false);