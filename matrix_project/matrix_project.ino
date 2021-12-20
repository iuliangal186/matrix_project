//In addition to the code comments in this block I will explain every important function in the code:
//Let's start with gameplay.h:
//* turfOffCar()- and moveCar() will move the car left and right
//* loseLife() - check if the car touches another car, decreases number of lives and make a specific sound
//* chooseLevel() - depending on level cars will be bigger
//              - here I used random function to spawn cars in different location 
//              - random function is specific for each level because cars have different sizes
//* scoreFunction() - calculate score (level + 1 for each car) and check if the score is highscore
//* fall() - the generated cars approach the player's car at a speed set with the help of difficulty - fallFrequency() (different intervals)
//* moveJoystick() - use all the functions listed above (the player can move his car and the other cars move)
//                 - through a succesion of 2 function calls I implemented the acceleration function which sometime is a little buggish but in generally works
//* displayScore() - congratulations and "your score is: " message
//* gameOver - game over message
//
//menu.h:
//* mainMenu() - display on LCD button from Main Menu
//* menuSelect() - with joystick change selected to know where we are with the cursor
//*start() - what is displayed during the game
//*highscore() - what is diplayed when acces highscore (data from EEPROM)
//*settings() - analog mainMenu() but for settings
//*contrast(), LCDBrightness(), matrixBrightness(), enterName() - functions in settings, nothing complicated
//*welcomeFunction() - message displayed when turn on the Arduino for a game session
//
//loop.h:
//*gameNotStarted() - check if need to display welcome message or main menu
//*loseLifeAndReset() - animation when we lost a life in game or reset the game when is game over
//*carMoves() - when player car dosen't touch another car he can move left and right for overtaking
//*checkFinalGame() - checks if the player reach the final game (level 5) and the game will be reset form level 1

#include "LedControl.h"
#include <EEPROM.h>
#include <LiquidCrystal.h>
#include "variables.h"
#include "menu.h"
#include "gameplay.h"
#include "loop.h"

void setup() {
  pinMode(swPin, INPUT_PULLUP);
  lc.shutdown(0, false);
  lc.setIntensity(0, 2);
  lc.clearDisplay(0);
  randomSeed(analogRead(2));
  lcd.begin(16, 2);
  lcd.createChar(0, heartCustom);
  getDataFormEEPROM();
}

void loop() {
  saveDataToEEPROM();
  analogWrite(V0, contrastValue);
  analogWrite(brightnessPin, brightnessValue);
  switchValue = digitalRead(swPin);
  // display welcome message
  if (!startGame) {
    gameNotStarted();
  } else { // start game
    if (!endGame) {
      checkFinalGame();
      if (alive) { // car doesn't hit another car
        carMoves();
      } else {
        loseLifeAndReset();
      }
    }
  }
}
