// prints for main menu
void mainMenu(int selected) {
  lcd.setCursor(0, 0);
  if (selected == 1) {
    lcd.print(">Play ");
  }
  else {
    lcd.print(" Play ");
  }
  lcd.setCursor(6, 0);
  if (selected == 2) {
    lcd.print(">HighScore");
  } else {
    lcd.print(" HighScore");
  }
  lcd.setCursor(0, 1);
  if (selected == 3) {
    lcd.print(">Settings ");
  } else {
    lcd.print(" Settings ");
  }
  lcd.setCursor(10, 1);
  if (selected == 4) {
    lcd.print(">About");
  } else {
    lcd.print(" About");
  }
}

// xAxis to choose something from main menu
void menuSelect() {
  xValue = analogRead(xPin);
  if (buttonState == 0) {
    mainMenu(selected);
    if (buttonState == 0) {
      if (xValue > maxThreshold && !xMoved) {
        selected++;
        if (selected > 4)
          selected = 1;
        xMoved = 1;
      }
      if (xValue < minThreshold && !xMoved) {
        selected--;
        if (selected < 1)
          selected = 4;
        xMoved = 1;
      }
      if (xValue > minThreshold && xValue < maxThreshold) {
        xMoved = 0;
      }
    }
  }
  if (prevButtonValue != switchValue) {
    if (switchValue == 0) {
      buttonState = !buttonState;
      tone(buzzerPin, 100, 25);
    }
    prevButtonValue = switchValue;
  }
}

// when press play this will be displayed on LCD
void start() {
  lcd.setCursor(12, 0);
  lcd.print(lives);
  lcd.write((byte)0);
  lcd.print("  ");
  lcd.setCursor(0, 0);
  lcd.print("Level:");
  lcd.setCursor(6, 0);
  lcd.print(level);
  lcd.print("     ");
  lcd.setCursor(0, 1);
  lcd.print("    Score:");
  lcd.setCursor(11, 1);
  lcd.print(score);
  lcd.print("    ");
}

void highscoreSelectPage() {
  yValue = analogRead(yPin);
  if (yValue > maxThreshold && !yMoved) {
    highscoreSelected++;
    if (highscoreSelected > 1) {
      highscoreSelected = 0;
    }
    yMoved = 1;
  }
  if (yValue < maxThreshold) {
    yMoved = 0;
  }

}

// when press high score this will be displayed on LCD
// high score will be load from EEPROM
void highscore() {
  if ( highscoreSelected == 0) {
    lcd.setCursor(0, 0);
    lcd.print("Highscore:      ");
    lcd.setCursor(0, 1);
    lcd.print("1. ");
    int value = EEPROM.read(addressOneEEPROM);
    String playerName = "";
    int lenPlayerNameEEPROM = EEPROM.read(addressOneEEPROM + 1);
    for (int i = 0; i < lenPlayerNameEEPROM; i++){
       playerName += char(EEPROM.read(addressOneEEPROM + 2 + i));
    }
    
    lcd.print(playerName);
    lcd.print(": ");
    lcd.print(value);
    lcd.print(" ");
    lcd.print(lenPlayerNameEEPROM);
    lcd.print("             ");
  }

  if (highscoreSelected == 1) {
    lcd.setCursor(0, 0);
    lcd.print("2. ");
    int value = EEPROM.read(addressTwoEEPROM);
    String playerName = "";
    int lenPlayerNameEEPROM = EEPROM.read(addressTwoEEPROM + 1);
    for (int i = 0; i < lenPlayerNameEEPROM; i++){
       playerName += char(EEPROM.read(addressTwoEEPROM + 2 + i));
    }
    lcd.print(playerName);
    lcd.print(": ");
    lcd.print(value);
    lcd.print(" ");
    lcd.print(lenPlayerNameEEPROM);
    lcd.print("             ");

    lcd.setCursor(0, 1);
    lcd.print("3. ");
    value = EEPROM.read(addressThreeEEPROM);
    playerName = "";
    lenPlayerNameEEPROM = EEPROM.read(addressThreeEEPROM + 1);
    for (int i = 0; i < lenPlayerNameEEPROM; i++){
       playerName += char(EEPROM.read(addressThreeEEPROM + 2 + i));
    }
    lcd.print(playerName);
    lcd.print(": ");
    lcd.print(value);
    lcd.print(" ");
    lcd.print(lenPlayerNameEEPROM);
    lcd.print("             ");
  }

  
  if (prevButtonValue != switchValue) {
    if (switchValue == 0) {
      buttonState = !buttonState;
      tone(buzzerPin, 100, 25);
    }
    prevButtonValue = switchValue;
  }
}

// depending on what settings is selected 
// on LCD we will have this strings
void settingsMenu() {
  if (settingsSelected == 1) {
    lcd.setCursor(0, 0);
    lcd.print(">Difficulty     ");
    
    lcd.setCursor(0, 1);
    lcd.print(" Change contrast");
  }
  if (settingsSelected == 2) {
    lcd.setCursor(0, 0);
    lcd.print(" Difficulty     ");

    lcd.setCursor(0, 1);
    lcd.print(">Change contrast");
  }

  if (settingsSelected == 3) {
    lcd.setCursor(0, 0);
    lcd.print(">Brightness LCD ");

    lcd.setCursor(0, 1);
    lcd.print(" Brightness M   ");
  } 
  if (settingsSelected == 4) {
    lcd.setCursor(0, 0);
    lcd.print(" Brightness LCD ");

    lcd.setCursor(0, 1);
    lcd.print(">Brightness M   ");
  } 
  if (settingsSelected == 5) {
    lcd.setCursor(0, 0);
    lcd.print(">Enter Name     ");

    lcd.setCursor(0, 1);
    lcd.print(" Back           ");
  }

  if (settingsSelected == 6) {
    lcd.setCursor(0, 0);
    lcd.print(" Enter Name     ");

    lcd.setCursor(0, 1);
    lcd.print(">Back           ");
  }
}

// change settingsButtonState with joystick
// on yAxis
void settings() {
  yValue = analogRead(yPin);
  Serial.println(settingsButtonState);
  if (settingsButtonState == 0) {
    settingsMenu();
    if (settingsButtonState == 0) {
      if (yValue > maxThreshold && !yMoved) {
        settingsSelected++;
        if (settingsSelected > nrMaxOfSetiings)
          settingsSelected = 1;
        yMoved = 1;
      }
      if (yValue < minThreshold && !yMoved) {
        settingsSelected--;
        if (settingsSelected < 1)
          settingsSelected = 6;
        yMoved = 1;
      }
      if (yValue > minThreshold && yValue < maxThreshold) {
        yMoved = 0;
      }
    }
  }
  switchValue = digitalRead(swPin);
  if (prevSettingsButtonValue != switchValue) {
    if (switchValue == 0) {
      settingsButtonState = !settingsButtonState;
      lc.clearDisplay(0);
      tone(buzzerPin, 100, 25);
    }
    prevSettingsButtonValue = switchValue;
  }
}

// change contrast with joystick with xAxis
void contrast() {
//  lcdClearLine(1);
  lcd.setCursor(0, 1);
  lcd.print("Contrast:< ");
  lcd.print(contrastValue);
  lcd.print(" >");
  xValue = analogRead(xPin);
  if (xValue > maxThreshold && !xMoved) {
    if (contrastValue < maxContrastValue) {
      contrastValue += 10;
    }
    xMoved = 1;
  }
  if (xValue < minThreshold && !xMoved) {
    if (contrastValue > minContrastValue) {
      contrastValue -= 10;
    }
    xMoved = 1;
  }
  if (xValue > minThreshold && xValue < maxThreshold) {
    xMoved = 0;
  }
}

// depending on difficulty level will be displayed what we choose
void difficultyMenu() {
  lcd.setCursor(0, 0);
  if (difficulty == 1) {
    lcd.print(">easy");
  }
  else {
    lcd.print(" easy");
  }
  lcd.setCursor(0, 8);
  if (difficulty == 2) {
    lcd.print(">medium");
  } else {
    lcd.print(" medium");
  }
  lcd.setCursor(9, 1);
  if (difficulty == 3) {
    lcd.print(">hard");
  } else {
    lcd.print(" hard");
  }

}

// change difficluty (easy, medium, hard) with joystick on xAxis
void difficultySelect() {
  xValue = analogRead(xPin);
  if (settingsButtonState == 1) {
    difficultyMenu();
    if (settingsButtonState == 1) {
      if (xValue > maxThreshold && !xMoved) {
        difficulty++;
        if (difficulty > 3)
          difficulty = 1;
        xMoved = 1;
      }
      if (xValue < minThreshold && !xMoved) {
        difficulty--;
        if (difficulty < 1)
          difficulty = 3;
        xMoved = 1;
      }
      if (xValue > minThreshold && xValue < maxThreshold) {
        xMoved = 0;
      }
    }
  }
  if (prevSettingsButtonValue != switchValue) {
    if (switchValue == 0) {
      settingsButtonState = !settingsButtonState;
    }
    prevSettingsButtonValue = switchValue;
  }
}

// TO DO: brightness like contrast
void LCDbrightness() {
  //lcdClearLine(1);
  lcd.setCursor(0, 1);
  lcd.print("Brightness:<");
  lcd.print(brightnessValue);
  lcd.print(">");
  xValue = analogRead(xPin);
  if (xValue > maxThreshold && !xMoved) {
    if (brightnessValue < 200) {
      brightnessValue += 10;
    }
    xMoved = 1;
  }
  if (xValue < minThreshold && !xMoved) {
    if (brightnessValue > 0) {
      brightnessValue -= 10;
    }
    xMoved = 1;
  }
  if (xValue > minThreshold && xValue < maxThreshold) {
    xMoved = 0;
  }
  
}


void matrixBrightness() {
  //lcdClearLine(1);
  
  for (int row = 0; row < matrixSize; row++) {
    for (int col = 0; col < matrixSize; col++) {
      lc.setLed(0, col, row, true);
    }
  }
  
  lcd.setCursor(0, 1);
  lcd.print("Brightness:<");
  lcd.print(matrixBrightnessValue);
  lcd.print(">");

  xValue = analogRead(xPin);
  if (xValue > maxThreshold && !xMoved) {
    if (matrixBrightnessValue < maxMatrixBrightness) {
      matrixBrightnessValue += 1;
    }
    xMoved = 1;
  }
  if (xValue < minThreshold && !xMoved) {
    if (matrixBrightnessValue > minMatrixBrightness) {
      matrixBrightnessValue -= 1;
    }
    xMoved = 1;
  }
  if (xValue > minThreshold && xValue < maxThreshold) {
    xMoved = 0;
  }
  lc.setIntensity(0, matrixBrightnessValue);
}

void enterName() {
  lcd.setCursor(0, 0);
  lcd.print("Enter name:<");
  lcd.print(letter);
  lcd.print(">");
  lcd.setCursor(0, 1);
  lcd.print(playerName);
  lcd.print("_         ");
  xValue = analogRead(xPin);
  yValue = analogRead(yPin);

  if (yValue > maxThreshold && !yMoved) {
    if (iteratorAlphabet < nrOfLetter){
      iteratorAlphabet++;
      letter = alphabet.charAt(iteratorAlphabet);
      yMoved = 1;
    }
  }

  if (yValue < minThreshold && !yMoved) {
    if (iteratorAlphabet > 0){
      iteratorAlphabet--;
      letter = alphabet.charAt(iteratorAlphabet);
      yMoved = 1;
    }
  }

  if (xValue > maxThreshold && !xMoved) {
    if (playerName.length() < 10){
      playerName += letter;
      xMoved = 1;
    }
  }

  if (xValue < minThreshold && !xMoved) {
    if (playerName.length() > 0) {
      playerName.remove(playerName.length() - 1, 1);
      xMoved = 1;
    }
  }

  if (yValue > minThreshold && yValue < maxThreshold) {
    yMoved = 0;
  }
  if (xValue > minThreshold && xValue < maxThreshold) {
    xMoved = 0;
  }
}

void back() {
  lcd.clear();
  buttonState = 0;
  settingsButtonState = 0;
}

// depending on what settings was selected will be do some actions
void settingsSelectedFunction() {
  switch (settingsSelected) {
    case 1: difficultySelect();
      break;
    case 2: contrast();
      break;
    case 3: LCDbrightness();
      break;
    case 4: matrixBrightness();
      break;
    case 5: enterName();
      break;
    case 6: back();
      break;
    default: break;
  }
}

// BACK TO MAIN MENU
// about has 3 page 
// pageabout = 0 => page 1
// pageabout = 1 => page 2
// pageabout > 1 => page 3
void about() {
  xValue = analogRead(xPin);
  if (xValue < minThreshold) {
    if (xMoved == false) {
      if (pageabout > 2) {
        pageabout = 0;
        lcd.clear();
      }
      else {
        pageabout ++;
        
      }
      xMoved = true;
    }
  }
  else {
    xMoved = false;
  }
  if (pageabout == 0) {
    lcd.setCursor(0, 0);
    lcd.print("   Credits:     ");
    lcd.setCursor(0, 1);
    lcd.print("  Iulian Gal    ");
  }
  else if (pageabout == 1) {
    lcd.setCursor(0, 0);
    lcd.print("    GitHub:     ");
    lcd.setCursor(0, 1);
    lcd.print("tinyurl.com/2fcr3ev6");
  }
  else if (pageabout == 2) {
    lcd.setCursor(0, 0);
    lcd.print("  Game Name:    ");
    lcd.setCursor(0, 1);
    lcd.print("Overtaking cars ");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("  Powered by:   ");
    lcd.setCursor(0, 1);
    lcd.print(" @UniBucRobotics");
  }
  if (prevButtonValue != switchValue) {
    if (switchValue == 0) {
      buttonState = !buttonState;
      tone(buzzerPin, 100, 25);
    }
    prevButtonValue = switchValue;
  }
}


// choose options in main menu
void selectedFunction() {
  switch (selected) {
    case 1: startGame = true;
      endGame = 0;
      startLevelTime = millis();
      break;
    case 2: highscoreSelectPage();
      highscore();
      break;
    case 3:
      if (firstSettings) {
        settingsButtonState = 0;
        firstSettings = 0;
      }
      settings();
      if (settingsButtonState == 1) {
        lcd.clear();
        settingsSelectedFunction();
      }
      break;
    case 4: about();
      break;
    default: break;
  }
}

// funtion to clear just one line
void lcdClearLine(int line) {
  lcd.setCursor(0, line);
  for (int i = 0; i < 16; ++i) {
    lcd.write(' ');
  }
}

void welcomeFunction() { //used only once through the boolean "welcome" variable
  lcd.setCursor(0, 0);
  lcd.print("   Welcome to ");
  lcd.setCursor(0, 1);
  lcd.print("   Overtaking  ");
  delay(2000);
  lcd.setCursor(0, 0);
  lcd.print("  Overtaking  ");
  lcd.setCursor(0, 1);
  lcd.print("   Cars Game  ");
  delay(2000);
  
  lcd.clear();
  welcome = true;
}
