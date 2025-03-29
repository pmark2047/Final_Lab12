/***********************************************************************
 * Source File:
 *    PROJECTILE
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a projectile
 ************************************************************************/


 #include "projectile.h"
 using namespace std;

void Projectile::fire(Angle a, Position pos, double s)
{
   PositionVelocityTime pvt;
   Velocity v;
   v.set(a, s);
   pvt.pos = pos;
   pvt.v = v;
   pvt.t = 1.0;
   
   flightPath.push_back(pvt);
}
