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

    Simulator(const Position & posUpperRight);
    void display(const Interface* pUI);
    void input(const Interface* pUI);
};
