/**********************************************************************
 * Suurce File:
 *    SIMULATION
 * Author:
 *    <your name here>
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

 #include "simulation.h"  // for SIMULATION

// Constructor implementation
Simulator::Simulator(const Position & posUpperRight)
    : ground(posUpperRight), posUpperRight(posUpperRight)
{
    howitzer.generatePosition(posUpperRight);
    Position & pos = howitzer.getPosition();
    ground.reset(pos);  // update Y to match ground height
}

// Display function implementation
void Simulator::display(const Interface* pUI)
{
    ogstream gout;

    // Draw the ground
    ground.draw(gout);

    // Draw the howitzer
    howitzer.draw(gout, 0.0);
}
