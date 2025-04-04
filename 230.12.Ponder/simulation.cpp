/**********************************************************************
 * Suurce File:
 *    SIMULATION
 * Author:
 *    <your name here>
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

#include "test.h"
#include "position.h"
#include "simulation.h"
#include "uiInteract.h"
#include "uiDraw.h"


Simulator::Simulator(const Position & posUpperRight)
    : ground(posUpperRight), posUpperRight(posUpperRight)
{
    howitzer.generatePosition(posUpperRight);
    Position & pos = howitzer.getPosition();
    ground.reset(pos);  // update Y to match ground height
}

double Position::metersFromPixels = 10.0;

void callBack(const Interface* pUI, void* p)
{
   Simulator * pSimulator = (Simulator*)p;
   
   ogstream gout;
   
   pSimulator->ground.draw(gout);
   
   pSimulator->howitzer.draw(gout, 0.0);
}


/*********************************
 * Main is pretty sparse.  Just initialize
 * my LM type and call the display engine.
 * That is all!
 *********************************/
#ifdef _WIN32
#include <windows.h>
int WINAPI WinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ LPSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   // Run the unit tests
   testRunner();
   
   // run the test code.
   testRunner();
   
   // Initialize open GL
   Position posUpperRight(6000, 6000);
   Interface ui("Howitzer Simulator", posUpperRight);
   
   // Initialize the game class
   Simulator simulator(posUpperRight);
   
   // set everything into one action
   ui.run(callBack, (void*)&simulator);


   return 0;
}
