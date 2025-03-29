/**********************************************************************
 * Header File:
 *    SIMULATION
 * Author:
 *    <your name here>
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

#pragma once
#include "position.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include "howitzer.h"
#include "ground.h"


 /*********************************************
  * Simulation
  * Execute one simulation of a projectile being fired.
  *********************************************/
class Simulator
{
public:
   Ground ground;
   Howitzer howitzer;
   Position posUpperRight;
   
   Simulator(const Position & posUpperRight)
         : ground(posUpperRight), posUpperRight(posUpperRight)
      {
         howitzer.generatePosition(posUpperRight);
         Position & pos = howitzer.getPosition();
         ground.reset(pos);  // update Y to match ground height
      }

      void display(const Interface* pUI)
      {
         ogstream gout;

         // Draw the ground
         ground.draw(gout);

         // Draw the howitzer
         howitzer.draw(gout, 0.0);
      }
};
