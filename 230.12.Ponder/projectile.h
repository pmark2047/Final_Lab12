/**********************************************************************
 * Header File:
 *    PROJECTILE
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a projectile
 ************************************************************************/

#pragma once

#include <list>
#include "projectile.h"
#include "velocity.h"
#include "position.h"
#include "physics.h"
#include "uiDraw.h"
#include "angle.h"
#include "acceleration.h"

#define DEFAULT_PROJECTILE_WEIGHT 46.7000    // kg
#define DEFAULT_PROJECTILE_RADIUS 0.077545   // m

// forward declaration for the unit test class
class TestProjectile; 

 /**********************************************************************
  * Projectile
  *    Everything we need to know about a projectile
  ************************************************************************/
class Projectile
{
public:
   // Friend the unit test class
   friend ::TestProjectile;

   // create a new projectile with the default settings
   Projectile() : mass(DEFAULT_PROJECTILE_WEIGHT),
      radius(DEFAULT_PROJECTILE_RADIUS) {}

   // advance the round forward until the next unit of time
   void advance(double simulationTime);
   
   // fire the round
   void fire(const Angle& a, const Position& pos, double s); // angle, position, speed
   
   // reset the projectile state
   void reset() {
      mass = DEFAULT_PROJECTILE_WEIGHT;
      radius = DEFAULT_PROJECTILE_RADIUS;
      flightPath.clear();
   }
   double currentTime() const { return !flightPath.empty() ? flightPath.back().t : 0.0; };

private:

   // keep track of one moment in the path of the projectile
   struct PositionVelocityTime
   {
      PositionVelocityTime() : pos(), v(), t(0.0000) {}
      Position pos;
      Velocity v;
      double t;
   };

   double mass;           // weight of the M795 projectile. Defaults to 46.7 kg
   double radius;         // radius of M795 projectile. Defaults to 0.077545 m
   std::list<PositionVelocityTime> flightPath;
};
