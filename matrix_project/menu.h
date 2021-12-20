//functions for save and get data from eeprom (difficulty, contrast, brightness, highscore)
void saveDataToEEPROM() {
  address = 0;
  EEPROM.put(address, difficulty);
  address += sizeof(int);
  EEPROM.put(address, contrastValue);
  address += sizeof(int);
  EEPROM.put(address, brightnessValue);
  address += sizeof(int);
  EEPROM.put(address, matrixBrightnessValue);
  address += sizeof(int);
  EEPROM.put(address, highscoreValue);
  address += sizeof(int);
}

void getDataFormEEPROM() {
  address = 0;
  EEPROM.get(address, difficulty);
  address += sizeof(int);
  EEPROM.get(address, contrastValue);
  address += sizeof(int);
  EEPROM.get(address, brightnessValue);
  address += sizeof(int);
  EEPROM.get(address, matrixBrightnessValue);
  address += sizeof(int);
  EEPROM.get(address, highscoreValue);
  address += sizeof(int);
}

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
  if (nameQuestion == 0) {
    lcd.setCursor(0, 0);
    lcd.print("Your name is:   ");
    lcd.setCursor(0, 1);
    lcd.print(playerName);
    lcd.print("                ");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Change your name");
    lcd.setCursor(0, 1);
    lcd.print(" from settings  ");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" if that is not ");
    lcd.setCursor(0, 1);
    lcd.print("   your name    ");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("   Let's gooo!  ");
    delay(2000);
    lcd.clear();
    nameQuestion = 1;
    startLevelTime = millis(); //reinitialize because level 1 duration = 2 sec due to the dealy
  }
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
  lcd.print("    Score: ");
  lcd.setCursor(11, 1);
  lcd.print(score);
  lcd.print("    ");
}

// top in highscore: page 1 with top 1 and page 2 with top 2 and 3
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
    getDataFormEEPROM();
    String playerName = "";
    int lenPlayerNameEEPROM;
    EEPROM.get(address, lenPlayerNameEEPROM);
    char chr;
    for (int i = 0; i < lenPlayerNameEEPROM; i++){
       EEPROM.get(address + i + sizeof(int), chr);
       playerName += char(chr);
    }
    
    lcd.print(playerName);
    lcd.print(": ");
    lcd.print(highscoreValue);
    lcd.print("             ");
  }

  if (highscoreSelected == 1) {
    lcd.setCursor(0, 0);
    lcd.print("2. !Implemented ");
//    int value = EEPROM.read(addressTwoEEPROM);
//    String playerName = "";
//    int lenPlayerNameEEPROM = EEPROM.read(addressTwoEEPROM + 1);
//    for (int i = 0; i < lenPlayerNameEEPROM; i++){
//       playerName += char(EEPROM.read(addressTwoEEPROM + 2 + i));
//    }
//    lcd.print(playerName);
//    lcd.print(": ");
//    lcd.print(value);
//    lcd.print(" ");
//    lcd.print(lenPlayerNameEEPROM);
//    lcd.print("             ");

    lcd.setCursor(0, 1);
    lcd.print("3. !Implemented ");
//    value = EEPROM.read(addressThreeEEPROM);
//    playerName = "";
//    lenPlayerNameEEPROM = EEPROM.read(addressThreeEEPROM + 1);
//    for (int i = 0; i < lenPlayerNameEEPROM; i++){
//       playerName += char(EEPROM.read(addressThreeEEPROM + 2 + i));
//    }
//    lcd.print(playerName);
//    lcd.print(": ");
//    lcd.print(value);
//    lcd.print(" ");
//    lcd.print(lenPlayerNameEEPROM);
//    lcd.print("             ");
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
          settingsSelected = nrMaxOfSetiings;
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
      contrastValue += intervalChangeContrast;
    }
    xMoved = 1;
  }
  if (xValue < minThreshold && !xMoved) {
    if (contrastValue > minContrastValue) {
      contrastValue -= intervalChangeContrast;
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
        if (difficulty > maxDifficulty)
          difficulty = minDifficulty;
        xMoved = 1;
      }
      if (xValue < minThreshold && !xMoved) {
        difficulty--;
        if (difficulty < minDifficulty)
          difficulty = maxDifficulty;
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
    if (brightnessValue < maxBrighntessValue) {
      brightnessValue += intervalChangeBrightness;
    }
    xMoved = 1;
  }
  if (xValue < minThreshold && !xMoved) {
    if (brightnessValue > minBrighntessValue) {
      brightnessValue -= intervalChangeBrightness;
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
    if (playerName.length() < maxLenPlayerName){
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
// pageAbout = 0 => page 1
// pageAbout = 1 => page 2
// pageAbout > 1 => page 3
void about() {
  xValue = analogRead(xPin);
  if (xValue < minThreshold) {
    if (xMoved == false) {
      if (pageAbout > maxPageAbout) {
        pageAbout = 0;
        lcd.clear();
      }
      else {
        pageAbout ++;
        
      }
      xMoved = true;
    }
  }
  else {
    xMoved = false;
  }
  if (pageAbout == 0) {
    lcd.setCursor(0, 0);
    lcd.print("   Credits:     ");
    lcd.setCursor(0, 1);
    lcd.print("  Iulian Gal    ");
  }
  else if (pageAbout == 1) {
    lcd.setCursor(0, 0);
    lcd.print("    GitHub:     ");
    lcd.setCursor(0, 1);
    lcd.print("tinyurl.com/2fcr3ev6");
  }
  else if (pageAbout == 2) {
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
