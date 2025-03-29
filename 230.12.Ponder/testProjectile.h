/***********************************************************************
 * Header File:
 *    TEST PROJECTILE
 * Author:
 *    <your name here>
 * Summary:
 *    All the unit tests for Projectile
 ************************************************************************/


#pragma once

#include "projectile.h"
#include "unitTest.h"


using namespace std;

/*******************************
 * TEST PROJECTILE
 * A friend class for Projectile which contains the Projectile unit tests
 ********************************/
class TestProjectile : public UnitTest
{
public:
   void run()
   {
      // Ticket 3: Setup
      defaultConstructor();
      reset_empty();
      reset_full();
      fire_right();
      fire_left();
      fire_up();

      // Ticket 4: Advance
      advance_nothing();
      advance_fall();
      advance_horizontal();
      advance_up();
      advance_diagonalUp();
      advance_diagonalDown();

      report("Projectile");
   }

private:
   double metersFromPixels = -1.0;


   /*****************************************************************
    *****************************************************************
    * CONSTRUCTOR
    *****************************************************************
    *****************************************************************/

   /*********************************************
    * name:    DEFAULT CONSTRUCTOR
    * input:   nothing
    * output:  mass=46.7, radius=0.077545 flightPath={}
    *********************************************/
   void defaultConstructor()
   {
      // SETUP
      Projectile p;
      
      // EXERCISE
      // VERIFY
      assertEquals(p.mass, 46.7);
      assertEquals(p.radius, 0.077545);
   }

   /*********************************************
    * name:    RESET from empty
    * input:   mass=-99, radius=-99, flightPath={}
    * output:  mass=46.7, radius=0.077545 flightPath={}
    *********************************************/
   void reset_empty()
   {
      // SETUP
      Projectile p;
      p.mass = -99;
      p.radius = -99;
      p.flightPath = {};
      Projectile::PositionVelocityTime emptyPath;
      
      // EXERCISE
      p.reset();
      
      // VERIFY
      assertEquals(p.mass, 46.7);
      assertEquals(p.radius, 0.077545);
      assertUnit(p.flightPath.empty());
   }

   /*********************************************
    * name:    RESET with a non-zero flight path
    * input:   mass=-99, radius=-99, flightPath={0,1,2}
    * output:  mass=46.7, radius=0.077545 flightPath={}
    *********************************************/
   void reset_full()
   {
      // SETUP
      Projectile p;
      p.mass = -99;
      p.radius = -99;
      Projectile::PositionVelocityTime one;
      Projectile::PositionVelocityTime two;
      Projectile::PositionVelocityTime three;
      
      p.flightPath.push_back(one);
      p.flightPath.push_back(two);
      p.flightPath.push_back(three);
      
      Projectile::PositionVelocityTime emptyPath;
      
      // EXERCISE
      p.reset();
      
      // VERIFY
      assertEquals(p.mass, 46.7);
      assertEquals(p.radius, 0.077545);
      assertUnit(p.flightPath.empty());
   }


   /*****************************************************************
    *****************************************************************
    * FIRE
    *****************************************************************
    *****************************************************************/  

   /*********************************************
    * name:    FIRE horizontally right
    * input:   angle=90  pos=(111,222) muzzleVelocity=100
    * output:  flightPath={pos=111,222 v=100,0 t=1}
    *********************************************/
   void fire_right()
   {
      // SETUP
      Projectile p;
      Angle a = Angle(90);
      Position pos = Position(111, 222);
      double muzzleVelocity = 100;
      
      Projectile::PositionVelocityTime expectedPVT;
      expectedPVT.pos = Position(111.0, 222.0);
      expectedPVT.v = Velocity(100.0, 0.0);
      expectedPVT.t = 1.0;
      
      // EXERCISE
      p.fire(a, pos, muzzleVelocity);
      
      // VERIFY
      assertEquals(p.flightPath.size(), 1); // flightPath should only have one PVt
      assertEquals(p.flightPath.front().pos.x, expectedPVT.pos.x); // verify x position
      assertEquals(p.flightPath.front().pos.y, expectedPVT.pos.y); // verify y postion
      assertEquals(p.flightPath.front().v.dx, expectedPVT.v.dx); // verify velocity dx
      assertEquals(p.flightPath.front().v.dy, expectedPVT.v.dy); // verify velocity dy
      assertEquals(p.flightPath.front().t, expectedPVT.t); // verify time
      
   }

   /*********************************************
    * name:    FIRE horizontally left
    * input:   angle=-90  pos=(111,222) muzzleVelocity=100
    * output:  flightPath={pos=111,222 v=-100,0 t=1}
    *********************************************/
   void fire_left()
   {
      // SETUP
      Projectile p;
      Angle a = Angle(-90);
      Position pos;
      pos.x = 111;
      pos.y = 222;
      double muzzleVelocity = 100;
      
      Projectile::PositionVelocityTime expectedPVT;
      expectedPVT.pos = Position(111.0, 222.0);
      expectedPVT.v = Velocity(-100.0, 0.0);
      expectedPVT.t = 1.0;
      
      // EXERCISE
      p.fire(a, pos, muzzleVelocity);
      
      // VERIFY
      assertEquals(p.flightPath.size(), 1); // flightPath should only have one PVt
      assertEquals(p.flightPath.front().pos.x, expectedPVT.pos.x); // verify x position
      assertEquals(p.flightPath.front().pos.y, expectedPVT.pos.y); // verify y postion
      assertEquals(p.flightPath.front().v.dx, expectedPVT.v.dx); // verify velocity dx
      assertEquals(p.flightPath.front().v.dy, expectedPVT.v.dy); // verify velocity dy
      assertEquals(p.flightPath.front().t, expectedPVT.t); // verify time
   }

   /*********************************************
    * name:    FIRE straight up
    * input:   angle=0  pos=(111,222) muzzleVelocity=100
    * output:  flightPath={pos=111,222 v=0,100 t=1}
    *********************************************/
   void fire_up()
   {
      // SETUP
      Projectile p;
      Angle a = Angle(0);
      Position pos;
      pos.x = 111;
      pos.y = 222;
      double muzzleVelocity = 100;
      
      Projectile::PositionVelocityTime expectedPVT;
      expectedPVT.pos = Position(111.0, 222.0);
      expectedPVT.v = Velocity(0.0, 100.0);
      expectedPVT.t = 1.0;
      
      // EXERCISE
      p.fire(a, pos, muzzleVelocity);
      
      // VERIFY
      assertEquals(p.flightPath.size(), 1); // flightPath should only have one PVt
      assertEquals(p.flightPath.front().pos.x, expectedPVT.pos.x); // verify x position
      assertEquals(p.flightPath.front().pos.y, expectedPVT.pos.y); // verify y postion
      assertEquals(p.flightPath.front().v.dx, expectedPVT.v.dx); // verify velocity dx
      assertEquals(p.flightPath.front().v.dy, expectedPVT.v.dy); // verify velocity dy
      assertEquals(p.flightPath.front().t, expectedPVT.t); // verify time
   }

   /*****************************************************************
    *****************************************************************
    * ADVANCE
    *****************************************************************
    *****************************************************************/ 

   /*********************************************
    * name:    ADVANCE : the projectile is not fired. Nothing will happen
    * input:   flightPath={}
    * output:  flightPath={}
    *********************************************/
   void advance_nothing()
   {
      // SETUP
      Projectile p;
      
      // EXERCISE
      p.advance(1.0);
      
      // VERIFY
      assertUnit(p.flightPath.empty());
   }

   /*********************************************
    * name:    ADVANCE : the projectile is stationary and falls down
    * input:   flightPath={pos=100,200 v=0,0 t=100}
    * output:  flightPath={}{pos.x=100      = 100 + 0*1
    *                        pos.y=195.0968 = 200 + 0*1 + .5(-9.806)*1*1
    *                        v.dx =0        = 0 + 0*1
    *                        v.dy =-9.8     = 0 + (-9.8064)*1
    *                        t=101}
    *********************************************/
   void advance_fall()
   {
      // setup
         setupStandardFixture();
         Position pos;
         Projectile p;
         Projectile::PositionVelocityTime pvt;
         pvt.pos.x = 100.0;
         pvt.pos.y = 200.0;
         pvt.v.dx = 0.0;
         pvt.v.dy = 0.0;
         pvt.t = 100.0;
         p.flightPath.push_back(pvt);
         // exercise
         p.advance(101.0);
         // verify
         assertUnit(p.flightPath.size() == 2);
         assertEquals(p.mass, 46.7);
         assertEquals(p.radius, 0.077545);
         assertUnit(!p.flightPath.empty());
         if (!p.flightPath.empty())
         {
            assertEquals(p.flightPath.back().pos.x, 100); // 100 + 50*1 + .5(-0.0799)*1*1
            assertEquals(p.flightPath.back().pos.y, 195.0968); // 200 + 40*1 + .5(-9.8064+0.0638)*1*1
            assertEquals(p.flightPath.back().v.dx, 0);   // 50 + (-0.0799)*1
            assertEquals(p.flightPath.back().v.dy, -9.8);  //-40 + (-9.8064+0.0638)*1*1
            assertEquals(p.flightPath.back().t, 101.0);
         }
         // teardown
         teardownStandardFixture();
   }

   /*********************************************
    * name:    ADVANCE : the projectile is traveling horizontally
    * input:   flightPath={pos=100,200 v=50,0 t=100}
    * output:  flightPath={}{pos.x=149.9756 = 100 + 50*1 + .5(-0.0487)*1*1
    *                        pos.y=195.0968 = 200 + 0*1  + .5(-9.8064)*1*1
    *                        v.dx =49.9513  = 50 + (-0.0487)*1
    *                        v.dy =-9.8064  = 0  + (-9.8064)*1
    *                        t=101}
    *********************************************/
   void advance_horizontal()
   {
      // setup
         setupStandardFixture();
         Position pos;
         Projectile p;
         Projectile::PositionVelocityTime pvt;
         pvt.pos.x = 100.0;
         pvt.pos.y = 200.0;
         pvt.v.dx = 50.0;
         pvt.v.dy = 0.0;
         pvt.t = 100.0;
         p.flightPath.push_back(pvt);
         // exercise
         p.advance(101.0);
         // verify
         assertUnit(p.flightPath.size() == 2);
         assertEquals(p.mass, 46.7);
         assertEquals(p.radius, 0.077545);
         assertUnit(!p.flightPath.empty());
         if (!p.flightPath.empty())
         {
            assertEquals(p.flightPath.back().pos.x, 149.9756);
            assertEquals(p.flightPath.back().pos.y, 195.0968);
            assertEquals(p.flightPath.back().v.dx, 49.9513);
            assertEquals(p.flightPath.back().v.dy, -9.8064);
            assertEquals(p.flightPath.back().t, 101.0);
         }
         // teardown
         teardownStandardFixture();
   }

   /*********************************************
    * name:    ADVANCE : the projectile is traveling up, no horizontal position change
    * input:   flightPath={pos=100,200 v=0,100 t=100}
    * output:  flightPath={}{pos.x=100      = 0   + 0*1   + .5(0)*1*1
    *                        pos.y=294.9021 = 200 + 100*1 + .5(-9.8064-.3893)*1*1
    *                        v.dx =0        = 0   + 0*1
    *                        v.dy =89.8042  = 100 + (-9.8064-.3893)
    *                        t=101}
    *********************************************/
   void advance_up()
   {
      // setup
         setupStandardFixture();
         Position pos;
         Projectile p;
         Projectile::PositionVelocityTime pvt;
         pvt.pos.x = 100.0;
         pvt.pos.y = 200.0;
         pvt.v.dx = 0.0;
         pvt.v.dy = 100.0;
         pvt.t = 100.0;
         p.flightPath.push_back(pvt);
         // exercise
         p.advance(101.0);
         // verify
         assertUnit(p.flightPath.size() == 2);
         assertEquals(p.mass, 46.7);
         assertEquals(p.radius, 0.077545);
         assertUnit(!p.flightPath.empty());
         if (!p.flightPath.empty())
         {
            assertEquals(p.flightPath.back().pos.x, 100.0);
            assertEquals(p.flightPath.back().pos.y, 294.9021);
            assertEquals(p.flightPath.back().v.dx, 0.0);
            assertEquals(p.flightPath.back().v.dy, 89.8042);
            assertEquals(p.flightPath.back().t, 101.0);
         }
         // teardown
         teardownStandardFixture();
   }

   /*********************************************
    * name:    ADVANCE : the projectile is traveling up and across
    * input:   flightPath={pos=100,200 v=50,40 t=100}
    * output:  flightPath={}{pos.x=149.9600 = 100 + 50*1 + .5(-0.0799)*1*1
    *                        pos.y=235.0648 = 200 + 40*1 + .5(-9.8064-0.0638)*1*1
    *                        v.dx =49.9201  = 50 + (-.0799)*1
    *                        v.dy =30.1297  = 40 + (-9.8064-0.0638)*1
    *                        t=101}
    *********************************************/
   void advance_diagonalUp()
   {
      // setup
         setupStandardFixture();
         Position pos;
         Projectile p;
         Projectile::PositionVelocityTime pvt;
         pvt.pos.x = 100.0;
         pvt.pos.y = 200.0;
         pvt.v.dx = 50.0;
         pvt.v.dy = 40.0;
         pvt.t = 100.0;
         p.flightPath.push_back(pvt);
         // exercise
         p.advance(101.0);
         // verify
         assertUnit(p.flightPath.size() == 2);
         assertEquals(p.mass, 46.7);
         assertEquals(p.radius, 0.077545);
         assertUnit(!p.flightPath.empty());
         if (!p.flightPath.empty())
         {
            assertEquals(p.flightPath.back().pos.x, 149.9600);
            assertEquals(p.flightPath.back().pos.y, 235.0648);
            assertEquals(p.flightPath.back().v.dx, 49.9201);
            assertEquals(p.flightPath.back().v.dy, 30.1297);
            assertEquals(p.flightPath.back().t, 101.0);
         }
         // teardown
         teardownStandardFixture();
   }

   /*********************************************
    * name:    ADVANCE : the projectile is traveling down and across
    * input:   flightPath={}{}{pos=100,200 v=50,-40 t=100}
    * output:  flightPath={}{}{}{pos.x=149.9201 = 100 + 50*1 + .5(-0.0799)*1*1
    *                            pos.y=155.1287 = 200 +-40*1 + .5(-9.8064+0.0638)*1*1
    *                            v.dx = 49.9201 =  50 + (-0.0799)*1
    *                            v.dy =-49.7425 = -40 + (-9.8064+0.0638)*1*1
    *                            t=101}
    *********************************************/
   void advance_diagonalDown()
   {  // setup
      setupStandardFixture();
      Position pos;
      Projectile p;
      Projectile::PositionVelocityTime pvt;
      p.flightPath.push_back(pvt);
      p.flightPath.push_back(pvt);
      pvt.pos.x = 100.0;
      pvt.pos.y = 200.0;
      pvt.v.dx = 50.0;
      pvt.v.dy = -40.0;
      pvt.t = 100.0;
      p.flightPath.push_back(pvt);
      // exercise
      p.advance(101.0);
      // verify
      assertUnit(p.flightPath.size() == 4);
      assertEquals(p.mass, 46.7);
      assertEquals(p.radius, 0.077545);
      assertUnit(!p.flightPath.empty());
      if (!p.flightPath.empty())
      {
         assertEquals(p.flightPath.back().pos.x, 149.9601);
         assertEquals(p.flightPath.back().pos.y, 155.1287);
         assertEquals(p.flightPath.back().v.dx, 49.9201);
         assertEquals(p.flightPath.back().v.dy, -49.7425);
         assertEquals(p.flightPath.back().t, 101.0);
      }
      // teardown
      teardownStandardFixture();
   }

   /*****************************************************************
    *****************************************************************
    * STANDARD FIXTURE
    *****************************************************************
    *****************************************************************/

   // setup standard fixture - set the zoom to 1100m per pixel
   void setupStandardFixture()
   {
      Position p;
      metersFromPixels = p.metersFromPixels;
      p.metersFromPixels = 1.0;
   }

   // teardown the standard fixture - reset the zoom to what it was previously
   void teardownStandardFixture()
   {
      assert(metersFromPixels != -1.0);
      Position p;
      p.metersFromPixels = metersFromPixels;
   }

};

