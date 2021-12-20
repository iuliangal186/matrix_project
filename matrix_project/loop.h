void gameNotStarted() {
  if (!welcome) {
    welcomeFunction();
  }
  // after diplayed welcome message on lcd we have main menu
  else {
    if (buttonState == 0) {
      menuSelect();
    } else {
        selectedFunction();
    }
  }
}

void loseLifeAndReset() {
  if (lives >= 1 && lives != 3) { // helps for some bugs (ex: tone after game over)
    tone(buzzerPin, 600, 500);
    for (int i = 0; i < loseLifeAnimationLen; i++) {
      animation(loseLifeAnimation[i]);
      delay(200);
    }
  }
  clearMatrix();
  currentTime = millis();
  alive = 1;
  if (lives == 3) { //lives was reset
    startGame = 0;
    buttonState = 0;
    gameOver();
    clearMatrix();
  }
  startLevelTime = millis();
}

void carMoves() {
  moveJoystick();
  moveCar(col, row);
  chooseLevel(level);
  fallFrequency();
  currentTime = millis();
  if (currentTime - startLevelTime >= levelInterval) { // change level after 10s alive
    level++;
    if (level == 2) {
      tone(buzzerPin, 200, 300);
      for (int i = 0; i < level2AnimationLen; i++) {
        animation(level2Animation[i]);
        delay(300);
      }
    }

    if (level == 3) {
      tone(buzzerPin, 200, 300);
      for (int i = 0; i < level3AnimationLen; i++) {
        animation(level3Animation[i]);
        delay(300);
      }
    }

    if (level == 4) {
      tone(buzzerPin, 200, 300);
      for (int i = 0; i < level4AnimationLen; i++) {
        animation(level4Animation[i]);
        delay(300);
      }
    }

    if (level == 5) {
      tone(buzzerPin, 200, 300);
      for (int i = 0; i < level5AnimationLen; i++) {
        animation(level5Animation[i]);
        delay(300);
      }
    }
    clearMatrix();
    if (level <= 5) {
      startLevelTime = millis();
    }
  }
}

void checkFinalGame() {
  start();
  if (level > 5) { // final level = 5
    endGame = 1;
    level = 1;
    startGame = 0;
    buttonState = 0;

    // animation final game
    // fill and clear matrix
    for (int row = 0; row < 8; row++) {
      for (int col = 0; col < 8; col++) {
        lc.setLed(0, row, col, true);
         delay(25);
       }
    }
    for (int row = 0; row < 8; row++) {
      for (int col = 0; col < 8; col++) {
        lc.setLed(0, row, col, false);
        delay(25);
       }
    }
    clearMatrix();
  }
}
