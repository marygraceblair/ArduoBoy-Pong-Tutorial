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
int paddlewidth = 4; 
int paddleheight = 9; 
int playerx = 0; 
int playery = 0;
int computery = 0; 
int computerx = 127 - paddlewidth; 
int playerscore = 0; 
int computerscore = 0; 


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
       
      drawItems(); 
      updateScore(); 
      
      //move ball to right
      ballx = moveBall(ballright, ballx); 
      bally = moveBall(balldown, bally); 

      //reflect off of edge of screen
      reflectOnContactWithEdge(); 

      //move player paddle
      movePlayerPaddle();

      //move computer paddle
      moveComputerPaddle(); 
      
      reflectAfterContactToPaddle();
     
      if (arduboy.justPressed(A_BUTTON) )
      {
        gamestate = 2; 
      }

      checkEndGame();
      break; 
    case 2: 
      //Win Screen
      arduboy.setCursor(0,0); 
      arduboy.print("Win Screen");
      if (arduboy.justPressed(A_BUTTON)) 
      {
        resetGame(); 
        gamestate = 0; 
      }
      break; 
    case 3:
      //Game over screen
      arduboy.setCursor(0,0); 
      arduboy.print("Game Over Screen");
      if (arduboy.justPressed(A_BUTTON)) 
      {
        resetGame(); 
        gamestate = 0; 
      }
      break;
      
  }
  
  arduboy.display(); 

}

void updateScore()
{
  if(ballx < -10)
      {
        ballx = 63; 
        computerscore += 1; 
      }
      if (ballx > 130)
      {
        ballx= 63;
        playerscore += 1; 
      }
}

void resetGame()
{
  ballx = 63; 
  playerscore = 0;
  computerscore = 0; 
}

void checkEndGame()
{
  if (playerscore == 5)
      {
        gamestate = 2; 
      }
      if (computerscore == 5)
      {
        gamestate = 3; 
      }

}

void movePlayerPaddle()
{
  if (arduboy.pressed(UP_BUTTON) && playery  > 0 )
      {
        playery -= 1; 
      }
      if (arduboy.pressed(DOWN_BUTTON) && playery + paddleheight < 63)
      {
        playery += 1; 
      }
}

void moveComputerPaddle()
{
  if (ballx > 115 || random(0,20) == 1)
      {
        if(bally< computery)
        {
          computery -= 1; 
        }

        if(bally + ballsize > computery +paddleheight)
        {
          computery += 1; 
        }
      }
}
void reflectAfterContactToPaddle()
{
  //if ball contacts players paddle
      if (ballx == playerx + paddlewidth && playery < bally + ballsize && playery + paddleheight > bally)
      {
        ballright = 1; 
      }
      //ball makes contact with the computer paddle 
      if (ballx + ballsize == computerx && computery < bally + ballsize && computery+ paddleheight > bally)
      {
        ballright = -1; 
      }
}

void reflectOnContactWithEdge()
{
  //reflect ball of the top of the screen
      if(bally == 0)
      {
        balldown = 1; 
      }

      //reflect ball off of the bottom of the screen
      if(bally + ballsize == 63)
      {
        balldown = -1; 
      }
}

int moveBall(int directionOfMovement, int axis)
{
  if (directionOfMovement > 0)
    {
      axis += 1; 
    }
    else //move to left
    {
      axis -= 1; 
    }
    return axis; 
}

void drawItems()
{
      arduboy.setCursor(20,0); 
      arduboy.print(playerscore);
      arduboy.setCursor(101, 0); 
      arduboy.print(computerscore);
      arduboy.fillRect(ballx, bally, ballsize, ballsize, WHITE); 
      arduboy.fillRect(playerx, playery, paddlewidth, paddleheight, WHITE);
      arduboy.fillRect(computerx, computery, paddlewidth, paddleheight, WHITE); 
}
