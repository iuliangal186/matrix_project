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
  
}

void loop() {
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
