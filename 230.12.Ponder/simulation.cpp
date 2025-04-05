/**********************************************************************
 * Suurce File:
 *    SIMULATION
 * Author:
 *    <your name here>
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

 #include "simulation.h"  // for SIMULATION

void Simulator::display(const Interface* pUI){
   ogstream gout;

   // Draw the ground
   ground.draw(gout);

   // Draw the howitzer
   howitzer.draw(gout, 0.0);
}
