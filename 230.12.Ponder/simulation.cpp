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
#include <iomanip>


using namespace std;


Simulator::Simulator(const Position & posUpperRight) : ground(posUpperRight), posUpperRight(posUpperRight)
{
    howitzer.generatePosition(posUpperRight);
    Position & pos = howitzer.getPosition();
    ground.reset(pos);  // update Y to match ground height
}

double Position::metersFromPixels = 10.0;

/*********************************
 * DISPLAY
 * displays the stuff
 *********************************/
void Simulator::display(const Interface* pUI)
{
   ogstream gout;
   
   // Draw the ground
   ground.draw(gout);
   
   // Draw the howitzer
   howitzer.draw(gout, time);
   
   // Draw the projectile
   projectile.draw(gout);
   
   // Draw the angle readout
   double angle = howitzer.getElevation().getDegrees();
   
   // Convert to formatted string
   std::ostringstream angleStream;
   angleStream << std::fixed << std::setprecision(1) << angle;
   std::string angleText = "Angle: " + angleStream.str() + "°";
   
   // Set position near top-right corner (10px padding)
   Position textPos = posUpperRight;
   textPos.addPixelsX(-120);  // Move left from right edge
   textPos.addPixelsY(-20);   // Move down from top edge
   
   gout.drawText(textPos, angleText.c_str());
   
   if (targetHit == true)
   {
      gout.drawWinMessage();
   }

}

/*********************************
 * INPUT
 * handles the key input
 *********************************/
void Simulator::input(const Interface* pUI)
{
   double increment = 0.1;

   if (pUI->isUp())    { howitzer.raise(increment/15);   }
   if (pUI->isDown())  { howitzer.raise(-increment/15);  }
   if (pUI->isRight()) { howitzer.rotate(increment);  }
   if (pUI->isLeft())  { howitzer.rotate(-increment); }
   
   if (pUI -> isSpace())
   {
      if (!inFlight)
      {
         inFlight = true;
         projectile.fire(howitzer.getElevation(),   // current angle
                         howitzer.getPosition(),   // current position
                         howitzer.getMuzzleVelocity(),
                         time// initial speed
                        );
      }
   }
   
   if (pUI->isQ())  // assume 'Q' is being used for 'R'
   {
      reset();
   }
}

/*********************************
 * RESET
 * resets the program
 *********************************/
void Simulator::reset()
{
   // Reset internal time
   time = 0.0;

   // Reset in-flight flag
   inFlight = false;

   // Reset projectile
   projectile.reset();

   // Regenerate howitzer position
   howitzer.generatePosition(posUpperRight);

   // Reset the ground to match new howitzer position
   ground.reset(howitzer.getPosition());
}



/*********************************
 * CALLBACK
 * holla back at ya cpu
 * handles redrawing the screen
 *********************************/
void callBack(const Interface* pUI, void* p)
{
   Simulator * pSimulator = (Simulator*)p;
   
   // handle input
   pSimulator->input(pUI);
   
   // advance the projectile
   if (pSimulator->inFlight == true)
   {
      pSimulator->time += 0.1;
      pSimulator->projectile.advance(pSimulator->time);
      
      // Get current projectile position
      Position shellPos = pSimulator->projectile.getPosition();
      
      // Check for collision with ground
      double groundElevation = pSimulator->ground.getElevationMeters(shellPos);
      if (shellPos.getMetersY() <= groundElevation)
      {
         pSimulator->inFlight = false;
      }
      
      // Check for collision with target
      Position targetPos = pSimulator->ground.getTarget();
      double dx = shellPos.getMetersX() - targetPos.getMetersX();
      double dy = shellPos.getMetersY() - targetPos.getMetersY();
      double distanceSquared = dx * dx + dy * dy;
      
      if (distanceSquared <= (500.0 * 500.0))
      {
         pSimulator->inFlight = false;
         pSimulator->targetHit = true;
      }
   }
   
   // display the screen again
   pSimulator->display(pUI);
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
