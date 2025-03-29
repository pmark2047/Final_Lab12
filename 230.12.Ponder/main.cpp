/***********************************************************************
 * Source File:
 *    MAIN
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Launches the unit tests - that is all!
 ************************************************************************/

#include "test.h"
#include "position.h"
#include "simulation.h"
#include "uiInteract.h"
#include "uiDraw.h"

double Position::metersFromPixels = 10.0;

void callBack(const Interface* pUI, void* p)
{
   Simulator * pSimulator = (Simulator*)p;
   Position posUpperRight;
   posUpperRight.setPixelsX(1000);
   posUpperRight.setPixelsY(1000);
   
   ogstream gout;
   
   pSimulator->ground.draw(gout);
   
   pSimulator->howitzer.draw(gout, 0.0);
}

 /************************************
  * MAIN
  * There can be only one!
  ************************************/
int main()
{
   // run the test code.
   testRunner();
   
   // Initialize open GL
   Position posUpperRight(4000, 4000);
   Interface ui("Howitzer Simulator", posUpperRight);
   
   // Initialize the game class
   Simulator simulator(posUpperRight);
   
   // set everything into one action
   ui.run(callBack, (void*)&simulator);

   // return success
   return 0;
}
