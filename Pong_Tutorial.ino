//MaryGrace Blair 
//following Arduboy Tutorial for Pong 
//Tutorial found at https://community.arduboy.com/t/make-your-own-arduboy-game-part-7-make-pong-from-scratch/7930

#include <Arduboy2.h>
Arduboy2 arduboy;
int gamestate; 

void setup() {
  arduboy.begin(); 
  arduboy.initRandomSeed(); 
  arduboy.setFrameRate(60); 
  
  arduboy.clear(); 

}

void loop() {
  
  if (!arduboy.nextFrame())
  {
    return; 
  }
  //the tutorial is missing this function
  //justPressed requires it at the start of each frame
  arduboy.pollButtons();
 
  arduboy.clear(); 
  
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
