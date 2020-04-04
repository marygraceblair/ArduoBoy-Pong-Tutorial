//MaryGrace Blair 
//following Arduboy Tutorial for Pong 
//Tutorial found at https://community.arduboy.com/t/make-your-own-arduboy-game-part-7-make-pong-from-scratch/7930

#include <Arduboy2.h>
Arduboy2 arduboy;
int gamestate = 0; 
//location and size of ball
int ballx = 62; 
int bally = 0; 
int ballsize = 4; 
int ballright = 1; 
int balldown = 1; 

void setup() {
  arduboy.begin(); 
  arduboy.initRandomSeed(); 
  arduboy.setFrameRate(60);
  arduboy.clear(); 
}

void loop() {

  //prevent the arudboy from running too fast 
  if (!arduboy.nextFrame())
  {
    return; 
  }
  arduboy.clear(); 
  arduboy.pollButtons();
 
  switch (gamestate) {
    case 0:
      //Title
      arduboy.setCursor(0,0); 
      arduboy.print("Title Screen"); 
      if (arduboy.justPressed(A_BUTTON)) 
      {
        gamestate = 1; 
      }
      break; 
    case 1: 
      //Gameplay screen
      arduboy.setCursor(0,0); 
      arduboy.print("Gameplay");
      arduboy.fillRect(ballx, bally, ballsize, ballsize, WHITE); 
      if (ballright > 0)
      {
        ballx += 1; 
      }
      else
      {
        ballx -= 1; 
      }

      //change direction of the ball if it hits the edge of the screen
      //arduboy screen size is 128 pixels wide
      if (ballx == 0)
      {
        ballright = 1; 
      }
      if (ballx + ballsize == 127)
      {
        ballright = -1; 
      }



      if (balldown > 0)
      {
        bally += 1; 
      }
      else
      {
        bally -= 1; 
      }

      //flip the ball if it touches the bottom or top of the screen
      if(bally == 0)
      {
        balldown = 1; 
      }
      if(bally + ballsize == 63)
      {
        balldown = -1; 
      }
      
      if (arduboy.justPressed(A_BUTTON)) 
      {
        gamestate = 2; 
      }
      break; 
    case 2: 
      //Win Screen
      arduboy.setCursor(0,0); 
      arduboy.print("Win Screen");
      if (arduboy.justPressed(A_BUTTON)) 
      {
        gamestate = 3; 
      }
      break; 
    case 3:
      //Game over screen
      arduboy.setCursor(0,0); 
      arduboy.print("Game Over Screen");
      if (arduboy.justPressed(A_BUTTON)) 
      {
        gamestate = 0; 
      }
      break;
      
  }
  
  arduboy.display(); 

}
