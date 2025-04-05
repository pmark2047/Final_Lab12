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
   // create variables and place in pvt
   PositionVelocityTime pvt;
   Velocity v;
   v.set(a, s);
   pvt.pos = pos;
   pvt.v = v;
   pvt.t = 1.0000; // start at 1
   
   flightPath.push_back(pvt);
}

void Projectile::advance(double simulationTime)
{
   // do nothing if empty
   if (flightPath.empty())
      return;
   
   // establish old pvt
   PositionVelocityTime initPVT = flightPath.back();
   
   // create new pvt
   PositionVelocityTime pvt;
   
   // Steps according to Bro. Helfrich demonstration video
   
   // Step 1: getSpeed
   double speed = initPVT.v.getSpeed();
   double altitude = initPVT.pos.getMetersY();
   double interval = simulationTime - currentTime();
   
   // Step 2: Find air density
   double density = densityFromAltitude(altitude);
   
   // Step 3: Find speed of sound
   double speedSound = speedSoundFromAltitude(altitude);
   
   // Step 4: Calculate mach
   double mach = speed / speedSound;
   
   // Step 5: Find drag coefficient
   double drag = dragFromMach(mach);
   
   // Step 6: Calculate force
   double force = forceFromDrag(density, drag, DEFAULT_PROJECTILE_RADIUS, speed);
   
   // Step 7: Calculate acceleration
   double accelerationMag = accelerationFromForce(force, DEFAULT_PROJECTILE_WEIGHT);
   
   // Step 8: Calculate ddx and ddy from total acceleration
   Acceleration a;
   Angle windAngle = Angle(initPVT.v.getAngle());
   windAngle.reverse();
   a.set(windAngle, accelerationMag);
   
   // Step 9: Account for gravity from ddy
   double gravity = gravityFromAltitude(altitude);
   Angle angleGravity;
   angleGravity.setDown();
   Acceleration aGravity;
   aGravity.set(angleGravity, gravity);
   
   // Step 9.5: add gravity and wind
   a.addDDX(aGravity.getDDX());
   a.addDDY(aGravity.getDDY());
   
   // Step 10: Find new Position
   Position newPOS;
   newPOS.setMetersX(initPVT.pos.getMetersX()
                     + initPVT.v.getDX() * interval
                     + 0.50000 * a.getDDX() * interval * interval);
   newPOS.setMetersY(initPVT.pos.getMetersY()
                     + initPVT.v.getDY() * interval
                     + 0.50000 * a.getDDY() * interval * interval);
   
   // Step 11: Find new Velocity
   Velocity newV;
   newV.setDX(initPVT.v.getDX() + a.getDDX() * interval);
   newV.setDY(initPVT.v.getDY() + a.getDDY() * interval);
   
   // Step 12: Put it all together
   pvt.pos = newPOS;
   pvt.v = newV;
   pvt.t = simulationTime;
   
   // Step 13: Push to flightPath
   flightPath.push_back(pvt);
}
