#include "globals.hpp"
#include "okapi/api/chassis/controller/odomChassisController.hpp"
#include "okapi/api/util/mathUtil.hpp"

//Controllers
Controller master(ControllerId::master);

//Motors
Motor driveFL(1, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor driveBL(2, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor driveFR(3, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor driveBR(4, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);

MotorGroup driveL({driveFL, driveBL});
MotorGroup driveR({driveFR, driveBR});

ADIEncoder leftEncoder('A', 'B', false);
ADIEncoder rightEncoder('C', 'D', false);
ADIEncoder middleEncoder('E', 'F', false);

std::shared_ptr<OdomChassisController> chassis = ChassisControllerBuilder()
    .withMotors(driveL, driveR)
    .withMaxVelocity(200)
    .withSensors(leftEncoder, rightEncoder, middleEncoder)
    .withGains(
        {0.1, 0, 0.1, 0}, // Distance controller gains
        {0.1, 0, 0.1, 0}, // Turn controller gains
        {0.1, 0, 0.1, 0}  // Angle controller gains (helps drive straight)
    )
    // green gearset, tracking wheel diameter (2.75 in), track width (7 in), and TPR (360)
    // 1 inch middle encoder distance, and 2.75 inch middle wheel diameter
    .withDimensions(AbstractMotor::gearset::green, {{2.75_in, 7_in, 1_in, 2.75_in}, quadEncoderTPR})
    .withOdometry()
    .buildOdometry();