/***********************************************************************
 * Source File:
 *    ACCELERATION 
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about changing speed
 ************************************************************************/

#include "acceleration.h"
#include "angle.h"

#include <cmath>



/*********************************************
 * ACCELERATION : SET
 *  set from angle and direction
 *********************************************/
void Acceleration::set(const Angle & a, double magnitude)
{
   ddx = sin(a.getRadians()) * magnitude;
   ddy = cos(a.getRadians()) * magnitude;
}

void Acceleration::add(const Acceleration& acceleration)
{
   ddx += acceleration.ddx;
   ddy += acceleration.ddy;
}
