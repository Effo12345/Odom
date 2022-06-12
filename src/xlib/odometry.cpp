#include "odometry.hpp"
//To access odom data in other files/objects, use a const reference to a struct
//holding the odom data. Example:
namespace xlib {
    void Odometry::loop() {
        while(true) {
            float left = leftEncoder.get_value();
            float right = rightEncoder.get_value();
            float back = backEncoder.get_value();

            float L = (left -  leftLst) / 45.836     /*41.671*/; //The amount the left tracking wheel moved in inches
            float R = (right - rightLst) / 45.836; //The amount the right tracking wheel moved in inches
            float S = (back -  backLst) / 45.836; //The amount the back tracking wheel moved in inches

            //Update the last values
            leftLst = left;
            rightLst = right;
            backLst = back;

            float h; //The hypotenuse of the triangle formed by the middle of the robot on the starting position and ending position and the middle of the circle it travels around
            float i; //Half on the angle that I've traveled
            float h2; //The same as h but using the back instead of the side wheels
            float a = (L - R) / (L_DISTANCE_IN + R_DISTANCE_IN); // The angle that I've traveled


            if (a) {
                i = (a/2.0);
                float sinI = sin(i);
                h = (((R / a) + R_DISTANCE_IN) * sinI) * 2.0;
                h2 = (((S / a) + S_DISTANCE_IN) * sinI) * 2.0;
              }
              else {
                h = R; //Sets relative distance traveled to the right wheel as since their deltas are equal they traveled the same distance
                i = 0; //Half of angle traveled will always be zero if the angle traveled is sero
                h2 = S; //Back wheel movement is simply the difference in the back wheel if the angle didnt change
              }

            float p = i + position.theta; //The global ending angle of the robot
            float cosP = cos(p); //Cleans up final variable storage math
            float sinP = sin(p); //Cleans up final variable storage math

            //Update the global position
            position.y += h * cosP;
            position.x += h * sinP;

            //Update global position with back wheel data
            position.y += h2 * -sinP; //-sin(x) = sin(-x)
            position.x += h2 * cosP; //cos(x) = cos(-x)

            //Update the global rotation value according to relative value calculated earlier
            position.theta += a;

            //Output data to the LCD for debugging
            std::string output1 = "X: " + std::to_string(position.x);
            std::string output2 = "Y: " + std::to_string(position.y);
            std::string output3 = "A: " + std::to_string(position.theta);
            pros::lcd::set_text(1, output1);
            pros::lcd::set_text(2, output2);
            pros::lcd::set_text(3, output3);


            pros::delay(10);
        }
    }

    void Odometry::init() {
        startTask("Odometry");
    }

    Odometry odom;
}


//sPos position;
//public:
//const sPos& pos = position;



//Make pos public and take a mutex whenever writing to it. 

//Possibly make an object that holds all mutexes throughout the program and is 
//able to manage taking and releasing them.