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
   pvt.t = 1.0; // start at 1
   
   flightPath.push_back(pvt);
}

void Projectile::advance(double simulationTime)
{
   // do nothing if empty
   if (flightPath.empty())
      return;
   
   // establish old pvt
   PositionVelocityTime initPVT = flightPath.front();
   
   // create new pvt
   PositionVelocityTime pvt;
   
   // Steps according to Bro. Helfrich demonstration video
   
   // Step 1: getSpeed
   double speed = initPVT.v.getSpeed();
   
   // Step 2: Find air density
   double density = densityFromAltitude(initPVT.pos.getMetersY());
   
   // Step 3: Find speed of sound
   double speedSound = speedSoundFromAltitude(initPVT.pos.getMetersY());
   
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
   a.set(initPVT.v.getAngle(), accelerationMag);
   
   // Step 9: Account for gravity from ddy
   double gravity = gravityFromAltitude(initPVT.pos.getMetersY());
   a.addDDY(-gravity);
   
   // Step 10: Find new Position
   Position newPOS;
   newPOS.setMetersX(initPVT.pos.getMetersX() + initPVT.v.getDX() + 0.5 * a.getDDX());
   newPOS.setMetersY(initPVT.pos.getMetersY() + initPVT.v.getDX() + 0.5 * a.getDDY());
   
   // Step 11: Find new Velocity
   Velocity newV;
   newV.setDX(initPVT.v.getDX() + a.getDDX());
   newV.setDY(initPVT.v.getDY() + a.getDDY());
   
   // Step 12: Define new time
   double newT = initPVT.t + 1.0;
   
   // Step 13: Put it all together
   pvt.pos = newPOS;
   pvt.v = newV;
   pvt.t = newT;
   
   // Step 14: Push to flightPath
   flightPath.push_back(pvt);
   
}
