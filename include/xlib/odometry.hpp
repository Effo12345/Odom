#pragma once
#include "globals.hpp"

namespace xlib {
    struct Pos {
        double x;
        double y;
        double theta;
    };


    class Odometry : TaskWrapper {
        const float L_DISTANCE_IN = 7.25; //Placeholder values
        const float R_DISTANCE_IN = 7.25; //
        const float S_DISTANCE_IN = 7.25; //

        float leftLst = 0;
        float rightLst = 0;
        float backLst = 0;
        
        Pos position;

        void loop();

        public:
        void init();
    };

    extern Odometry odom;
}

