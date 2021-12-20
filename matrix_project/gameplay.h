// ------------ GAME PLAY --------------

// turn off initial position of car
void turnOffCar(int col, int row) {
  lc.setLed(0, row, col, false);
  lc.setLed(0, row + 1, col, false);
  lc.setLed(0, row + 1, col + 1, false);
  lc.setLed(0, row, col + 1, false);
}

// turn on the next position of car
void moveCar(int col, int row) {

  lc.setLed(0, row, col, true);
  lc.setLed(0, row + 1, col, true);
  lc.setLed(0, row + 1, col + 1, true);
  lc.setLed(0, row, col + 1, true);
}

void clearMatrix() {
  for (int i = 0; i < matrixSize; i++)
    for (int j = 0; j < matrixSize; j++) {
      matrix[i][j] = 0;
    }
}

// lives-- when car hits another car
// if we have 0 lives the game will be reset (level = 1, lives = 3);
void loseLife() {

  if ((matrix[row][col] == 1) || (matrix[row + 1][col + 1] == 1) || (matrix[row + 1][col] == 1) || (matrix[row][col + 1] == 1)) {
    lives--;
    alive = 0;
    deathMoment = millis();
  }
  if (lives == 0) {
   for (int thisNote = 0; thisNote < 8; thisNote++) {
      noteDuration = 1000 / noteDurations[thisNote];
      tone(13, melody[thisNote], noteDuration);
      pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      noTone(12);    
    }
    level = 1;
    lives = 3;
    resetLives = 1;
  }
}

// depending on level, cars will be bigger
void chooseLevel(int level) {
  // check if the first 3 lines are empty to have car enough space
  bool checkSpace = true; 
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < matrixSize; j++) {
      if (matrix[i][j] != 0)
        checkSpace = false;
    }
  if (checkSpace) {
    switch (level) {
      case 1: randomCol = random(0, 7);
        if (randomCol % 2) {
          lc.setLed(0, 0, randomCol, true);
          matrix[0][randomCol] = 1;
          lc.setLed(0, 1, randomCol + 1, true);
          matrix[1][randomCol + 1] = 1;
        }
        else {
          lc.setLed(0, 0, randomCol, true);
          matrix[0][randomCol] = 1;
          lc.setLed(0, 1, randomCol + 1, true);
          matrix[0][randomCol + 1] = 1;
        }
        break;
      case 2: randomCol = random(0, 6);
        if (randomCol % 2) {
          lc.setLed(0, 0, randomCol, true);
          matrix[0][randomCol] = 1;
          lc.setLed(0, 0, randomCol + 1, true);
          matrix[0][randomCol + 1] = 1;
          lc.setLed(0, 1, randomCol - 1, true);
          matrix[1][randomCol - 1] = 1;
        }
        else {
          lc.setLed(0, 0, randomCol, true);
          matrix[0][randomCol] = 1;
          lc.setLed(0, 0, randomCol + 1, true);
          matrix[0][randomCol + 1] = 1;
        }
        break; 
      case 3: randomCol = random(0, 5);
        if (randomCol % 2) {
          lc.setLed(0, 0, randomCol, true);
          matrix[0][randomCol] = 1;
          lc.setLed(0, 0, randomCol + 1, true);
          matrix[0][randomCol + 1] = 1;
          lc.setLed(0, 1, randomCol + 1, true);
          matrix[1][randomCol + 1] = 1;
        }
        else {
          if (randomCol == 3) {
            lc.setLed(0, 0, randomCol, true);
            matrix[0][randomCol] = 1;
            lc.setLed(0, 0, randomCol + 1, true);
            matrix[0][randomCol + 1] = 1;
            lc.setLed(0, 0, randomCol + 2, true);
            matrix[0][randomCol + 2] = 1;
          }
          else {
            lc.setLed(0, 0, randomCol, true);
            matrix[0][randomCol] = 1;
            lc.setLed(0, 0, randomCol + 1, true);
            matrix[0][randomCol + 1] = 1;
            lc.setLed(0, 1, randomCol + 2, true);
            matrix[1][randomCol] = 1;
          }
        }
        break;
      case 4: randomCol = random(0, 4);
        if (randomCol == 2) {
          lc.setLed(0, 0, randomCol, true);
          matrix[0][randomCol] = 1;
          lc.setLed(0, 0, randomCol + 1, true);
          matrix[0][randomCol + 1] = 1;
          lc.setLed(0, 0, randomCol + 2, true);
          matrix[0][randomCol + 2] = 1;
          lc.setLed(0, 0, randomCol + 3, true);
          matrix[0][randomCol + 3] = 1;
        }
        else if (randomCol == 3) {
          lc.setLed(0, 0, randomCol, true);
          matrix[0][randomCol] = 1;
          lc.setLed(0, 0, randomCol + 1, true);
          matrix[0][randomCol + 1] = 1;
          lc.setLed(0, 0, randomCol + 2, true);
          matrix[0][randomCol + 2] = 1;
          lc.setLed(0, 1, randomCol + 2, true);
          matrix[1][randomCol + 2] = 1;
        }
        else {
          lc.setLed(0, 0, randomCol, true);
          matrix[0][randomCol] = 1;
          lc.setLed(0, 0, randomCol + 1, true);
          matrix[0][randomCol + 1] = 1;
          lc.setLed(0, 0, randomCol + 2, true);
          matrix[0][randomCol + 2] = 1;
          lc.setLed(0, 1, randomCol, true);
          matrix[1][randomCol] = 1;
        }
        break;
      case 5: randomCol = random(0, 4);
        if (randomCol == 2) {
          lc.setLed(0, 0, randomCol, true);
          matrix[0][randomCol] = 1;
          lc.setLed(0, 0, randomCol + 1, true);
          matrix[0][randomCol + 1] = 1;
          lc.setLed(0, 0, randomCol + 2, true);
          matrix[0][randomCol + 2] = 1;
          lc.setLed(0, 0, randomCol + 3, true);
          matrix[0][randomCol + 3] = 1;
          lc.setLed(0, 1, randomCol + 3, true);
          matrix[1][randomCol + 3] = 1;
        }
        else if (randomCol == 3) {
          lc.setLed(0, 0, randomCol, true);
          matrix[0][randomCol] = 1;
          lc.setLed(0, 0, randomCol + 1, true);
          matrix[0][randomCol + 1] = 1;
          lc.setLed(0, 0, randomCol + 2, true);
          matrix[0][randomCol + 2] = 1;
          lc.setLed(0, 0, randomCol + 3, true);
          matrix[0][randomCol + 3] = 1;
          lc.setLed(0, 1, randomCol, true);
          matrix[1][randomCol] = 1;
        }
        else if (randomCol == 4) {
          lc.setLed(0, 0, randomCol, true);
          matrix[0][randomCol] = 1;
          lc.setLed(0, 0, randomCol + 1, true);
          matrix[0][randomCol + 1] = 1;
          lc.setLed(0, 0, randomCol + 2, true);
          matrix[0][randomCol + 2] = 1;
          lc.setLed(0, 0, randomCol + 3, true);
          matrix[0][randomCol + 3] = 1;
          lc.setLed(0, 1, randomCol + 2, true);
          matrix[1][randomCol + 2] = 1;
        }
        else if (randomCol == 1) {
          lc.setLed(0, 0, randomCol, true);
          matrix[0][randomCol] = 1;
          lc.setLed(0, 0, randomCol + 1, true);
          matrix[0][randomCol + 1] = 1;
          lc.setLed(0, 0, randomCol + 2, true);
          matrix[0][randomCol + 2] = 1;
          lc.setLed(0, 1, randomCol + 1, true);
          matrix[1][randomCol + 1] = 1;
          lc.setLed(0, 1, randomCol + 2, true);
          matrix[1][randomCol + 2] = 1;
        }
        else {
          lc.setLed(0, 0, randomCol, true);
          matrix[0][randomCol] = 1;
          lc.setLed(0, 0, randomCol + 1, true);
          matrix[0][randomCol + 1] = 1;
          lc.setLed(0, 0, randomCol + 2, true);
          matrix[0][randomCol + 2] = 1;
          lc.setLed(0, 1, randomCol + 1, true);
          matrix[1][randomCol + 1] = 1;
          lc.setLed(0, 1, randomCol, true);
          matrix[1][randomCol] = 1;
        }
        break;
    default: break;
    }
  }
}  


// score calculator depending on level
void scoreFunction() {
  int scoreLevel = level + 1;
  bool passedObstacle = 0;
  for (int j = 0; j < matrixSize && !passedObstacle; j++) {
    if (matrix[matrixSize - 1][j] == 1 && matrix[matrixSize - 2][j] != 1 && matrix[matrixSize - 2][j - 1] != 1) {
      if (j != col && j != col + 1) {
        score += scoreLevel;
        passedObstacle = 1;
      }
    }
  }

  if (score > highscoreValue) {
    highscoreValue = score;
    saveDataToEEPROM();
    EEPROM.put(address, playerName.length());
    for (int i = 0; i < playerName.length(); i++) {
      EEPROM.put(address + i + sizeof(int), playerName[i]);
    }
  }
}


// cars generated fall to our car
void fall() {
  for (int i = matrixSize - 1; i > 0; i--) {
    for (int j = 0; j < matrixSize; j++) {
      matrix[i][j] = matrix[i - 1][j];
      lc.setLed(0, i - 1, j, false);
      lc.setLed(0, i, j, matrix[i][j]);
    }
  }
  for (int j = 0; j < matrixSize; j++) {
    matrix[0][j] = 0;
    lc.setLed(0, 0, j, false);
  }
}

// depending on difficulty choosen in settings
// cars will fall faster or slower
void fallFrequency() {
  currentTime = millis();
  switch (difficulty) {
    case 1:  if (currentTime - lastFall >= fallIntervalEasy) {
        fall();
        loseLife();
        scoreFunction();
        lastFall = currentTime;
      }
      break;
    case 2:  if (currentTime - lastFall >= fallIntervalMedium) {
        fall();
        loseLife();
        scoreFunction();
        lastFall = currentTime;
      }
      break;
    case 3:  if (currentTime - lastFall >= fallIntervalHard) {
        fall();
        loseLife();
        scoreFunction();
        lastFall = currentTime;
      }
      break;
    default: break;
  }
}

// depending on joystick this function calls funtions wrote before
// and make the game logic
void moveJoystick() {
  xValue = analogRead(xPin);
  yValue = analogRead(yPin);
  if (xValue > maxThreshold && !xMoved) {
    turnOffCar(col, row);
    if (col < 6) {
      col++;
    }
    xMoved = true;
  }

  if (xValue < minThreshold && !xMoved) {
    turnOffCar(col, row);
    if (col > 0) {
      col--;
    }
    xMoved = true;
  }

  if (xValue >= minThreshold && xValue <= maxThreshold) {
    xMoved = false;
  }

  if (yValue < minThreshold && !yMoved) {
    turnOffCar(col, row);
    fall();
    loseLife();
    scoreFunction();
    if (resetLives == 0) { // if block that solved the bug with 1 live remaining => 2 lives if car hit another car in fast forward mode
      fall();
      loseLife();
      scoreFunction();
    }
    yMoved = true;
  } //fast forward with some bugs: 
    //if hit one car in fast forward mode lives decrease with 2 or 0
    //depending on phase in which is fastforward (start or final)

  if (yValue >= minThreshold && yValue <= maxThreshold) {
    yMoved = false;
  }
}

// messages from final game
void displayScore() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Congratulations!");
    for (int i = 0; i < 5; i++) {
    lcd.display();
    delay(500);
    lcd.noDisplay();
    delay(500);
  }
  lcd.display();
  lcd.setCursor(0, 0);
  lcd.print(" Your score is: ");
  lcd.setCursor(6, 1);
  lcd.print(score);
  delay(5000);

  getDataFormEEPROM();
  if (score == highscoreValue) { //highscore was changed in scoreFunction
    lcd.setCursor(1, 0);
    lcd.print("New Highscore!!");
    for (int i = 0; i < 5; i++) {
      lcd.display();
      delay(500);
      lcd.noDisplay();
      delay(500);
    }
    lcd.display();
  }    
  score = 0;
  resetLives = 0;
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
  nameQuestion = 0;
}

void gameOver() {
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Game over!");
    for (int i = 0; i < 5; i++) {
    lcd.display();
    delay(500);
    lcd.noDisplay();
    delay(500);
  }
  lcd.display();

  displayScore();
}


void animation(uint64_t image) {
  for (int i = 0; i < 8; i++) {
    byte r = (image >> i * 8) & 0xFF;
    for (int j = 0; j < 8; j++) {
      lc.setLed(0, i, j, bitRead(r, j));
    }
  }
}
