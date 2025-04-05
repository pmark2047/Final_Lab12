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

void Projectile::fire(const Angle& a, const Position& pos, double s, double simulationTime)
{
   reset();
   
   // create variables and place in pvt
   PositionVelocityTime pvt;
   pvt.pos = pos;
   pvt.t = simulationTime;
   pvt.v.set(a, s);
   
   flightPath.push_back(pvt);
}

void Projectile::advance(double simulationTime)
{
   if (!flying())
      return;
   
   PositionVelocityTime pvt = flightPath.back();
   double speed = pvt.v.getSpeed();
   double altitude = pvt.pos.getMetersY();
   double interval = simulationTime - currentTime();
   assert(interval > 0.0);
   
   // compute acceleration as it pertains to wind resistance
   double density             = densityFromAltitude(altitude);
   double speedSound          = speedSoundFromAltitude(altitude);
   double mach                = speed / speedSound;
   double dragCoefficient     = dragFromMach(mach);
   double windResistance      = forceFromDrag(density, dragCoefficient, radius, speed);
   double magnitudeWind       = accelerationFromForce(windResistance, mass);
   Acceleration aWind(-pvt.v.getAngle(), magnitudeWind);
   
   // compute acceleration as it pertains to gravity
   double magnitudeGravity = gravityFromAltitude(altitude);
   Angle angleGravity;
   angleGravity.setDown();
   Acceleration aGravity(angleGravity, magnitudeGravity);
   
   // compute total acceleration
   Acceleration aTotal = aGravity + aWind;
   
   // update position, velocity, and time
   pvt.pos.add(aTotal, pvt.v, interval);
   pvt.v.add(aTotal, interval);
   pvt.t = simulationTime;
   
   // add to the back of the flightPath
   flightPath.push_back(pvt);
}
