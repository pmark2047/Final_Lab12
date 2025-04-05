/**********************************************************************
 * Header File:
 *    HOWITZER
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a howitzer (aka the gun)
 ************************************************************************/

#pragma once

#include <list>
#include "angle.h"
#include "position.h"
#include "velocity.h"
#include "physics.h"
#include "uiDraw.h"


#pragma once

#define DEFAULT_MUZZLE_VELOCITY   827.000     // m/s


class TestHowitzer;

 /*********************************************
  * Howitzer
  * Everything we need to know about a howitzer (aka the gun)
  *********************************************/
class Howitzer
{
   public:
      // for unit tests
      friend ::TestHowitzer;

      // default constructor
      Howitzer() : muzzleVelocity(DEFAULT_MUZZLE_VELOCITY), elevation(45.0000) {}

      // draw
      void draw(ogstream& gout, double flightTime) const
      {
         gout.drawHowitzer(position,
            elevation.getRadians(),
            flightTime);
      }

      // where is the howitzer at right now?
      Position & getPosition() { return position; }

      // generate a new position for the howitzer
      void generatePosition(const Position& posUpperRight)
      {
         double xPixels = random(posUpperRight.getPixelsX() * 0.1,
            posUpperRight.getPixelsX() * 0.9);
         position.setPixelsX(xPixels);
         position.setPixelsY(0);
      }

      // get the muzzle velocity
      double getMuzzleVelocity() const { return muzzleVelocity; }

      // move the angle of the howitzer
      void rotate(double radian)
      {
         double newAngle = elevation.getRadians() + radian;

         // Normalize to [0, 2π)
         while (newAngle < 0)
            newAngle += 2 * M_PI;
         while (newAngle >= 2 * M_PI)
            newAngle -= 2 * M_PI;

         // Allow only if in the top half: [0, π/2] or [3π/2, 2π]
         if (newAngle <= M_PI / 2.0 || newAngle >= 3.0 * M_PI / 2.0)
            elevation.setRadians(newAngle);
      }

      // raise (or lower) the howitzer
      void raise(double radian)
      {
         double newAngle = elevation.getRadians() + (elevation.isRight() ? -radian : radian);

         // Normalize to [0, 2π)
         while (newAngle < 0)
            newAngle += 2 * M_PI;
         while (newAngle >= 2 * M_PI)
            newAngle -= 2 * M_PI;

         // Only allow if in top half
         if (newAngle <= M_PI / 2.0 || newAngle >= 3.0 * M_PI / 2.0)
            elevation.setRadians(newAngle);
      }

      // get the elevation
      const Angle & getElevation() const { return elevation; }

   private:
      Position position;      // initial position of the projectile
      double muzzleVelocity;  // muzzle velocity, defaults to 827.0 m/s
      Angle elevation;        // the elevation of the howitzer where 0 is up and positive is right.
};
