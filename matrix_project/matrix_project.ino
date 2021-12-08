#include "LedControl.h"
#include <EEPROM.h>
#include <LiquidCrystal.h>

// matrix pins
const byte dinPin =12;
const byte clockPin =11;
const byte loadPin =10;
LedControl lc = LedControl(dinPin, clockPin, loadPin, 1);

// LCD pins
const int RS = 8;
const int enable = 3;
const int d4 = 4;
const int d5 = 1;  // backlight = 5, d5 = 1
const int d6 = 6;
const int d7 = 7;
const int V0 = 9;

LiquidCrystal lcd(RS, enable, d4, d5, d6, d7);

bool matrix[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

// initial lives, level and score
int lives = 3;
int level = 1;
int score = 0;

bool buttonState = 0;
int prevButtonValue = 1;
bool settingsButtonState = 0;
int selected = 1;


const int matrixSize = 8;

// joystick pins (A2 because a piece of cable is stuck in pin a1)
const int xPin = A0;
const int yPin = A2;
const int swPin = 2;
const int minThreshold = 400;
const int maxThreshold = 700;

int xValue;
int yValue;

bool yMoved = false;
bool xMoved = false;

int switchValue;

// if welcome message was displayed
bool welcome = false;

// each level has 10 seconds
int startLevelTime;
int startGame = 0;
int endGame = 0;

int highscoreValue = 0;

bool firstSettings = 1;
int settingsSelected = 1;

// helping for choose something in settings menu
int prevSettingsButtonValue = 0;

// first contrast value
int contrastValue = 90;

// first difficulty level
int difficulty = 1;

// variable for what page of about will be displayed on LCD
int pageabout = 0;


// first position of car
int col = 3;
int row = 6;

// if car is working
bool alive = 1;
// moment when car hit another car
// helps for reset level
int deathMoment;

// random column for generate cars
int randomCol;

// depending on dificulty, cars will be appear faster
const int fallIntervalEasy = 600;
const int fallIntervalMedium = 400;
const int fallIntervalHard = 200;

int currentTime;
// helping for appear the next car
int lastFall = 0;

// heart image on LCD
byte heartCustom[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000,
  0b00000
};

// prints for main menu
void mainMenu(int selected) {
  lcd.setCursor(0, 0);
  if (selected == 1) {
    lcd.print(">Play");
  }
  else {
    lcd.print(" Play");
  }
  lcd.setCursor(6, 0);
  if (selected == 2) {
    lcd.print(">HighScore");
  } else {
    lcd.print(" HighScore");
  }
  lcd.setCursor(0, 1);
  if (selected == 3) {
    lcd.print(">Settings");
  } else {
    lcd.print(" Settings");
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
    }
    prevButtonValue = switchValue;
  }
}

// when press play this will be displayed on LCD
void start() {
  lcd.setCursor(12, 0);
  lcd.print(lives);
  lcd.write((byte)0);
  lcd.setCursor(0, 0);
  lcd.print("Level:");
  lcd.setCursor(6, 0);
  lcd.print(level);
  lcd.setCursor(4, 1);
  lcd.print("Score:");
  lcd.setCursor(11, 1);
  lcd.print(score);
}

// when press high score this will be displayed on LCD
// high score will be load from EEPROM
void highscore() {
  lcd.setCursor(0, 0);
  lcd.print("Highscore:");
  lcd.setCursor(0, 1);
  int value = EEPROM.get(0, highscoreValue);
  lcd.print(value);
  if (prevButtonValue != switchValue) {
    if (switchValue == 0) {
      buttonState = !buttonState;
    }
    prevButtonValue = switchValue;
  }
}

// depending on what settings is selected 
// on LCD we will have this strings
void settingsMenu() {
  if (settingsSelected == 1) {
    lcd.setCursor(0, 0);
    lcd.print(">Difficulty");
    
    lcd.setCursor(0, 1);
    lcd.print(" Change contrast");
  }
  if (settingsSelected == 2) {
    lcd.setCursor(0, 0);
    lcd.print(" Difficulty");

    lcd.setCursor(0, 1);
    lcd.print(">Change contrast");
  }

  if (settingsSelected == 3) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(">Brightness");

    lcd.setCursor(0, 1);
    lcd.print(" Back");
  } 
  if (settingsSelected == 4) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" Brightness");

    lcd.setCursor(0, 1);
    lcd.print(">Back");
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
        if (settingsSelected > 4)
          settingsSelected = 1;
        yMoved = 1;
      }
      if (yValue < minThreshold && !yMoved) {
        settingsSelected--;
        if (settingsSelected < 1)
          settingsSelected = 4;
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
    }
    prevSettingsButtonValue = switchValue;
  }
}

// change contrast with joystick with xAxis
void contrast() {
  lcdClearLine(1);
  lcd.setCursor(0, 1);
  lcd.print("Contrast:< ");
  lcd.print(contrastValue);
  lcd.print(" >");
  xValue = analogRead(xPin);
  if (xValue > maxThreshold && !xMoved) {
    if (contrastValue < 150) {
      contrastValue += 10;
    }
    xMoved = 1;
  }
  if (xValue < minThreshold && !xMoved) {
    if (contrast > 0) {
      contrastValue -= 10;
    }
    xMoved = 1;
  }
  if (xValue > minThreshold && xValue < maxThreshold) {
    xMoved = 0;
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

const int brightnessPin = 5;
int brightnessValue = 128;

// TO DO: brightness like contrast
void brightness() {
  lcdClearLine(1);
  lcd.setCursor(0, 0);
  lcd.print("  Brightness: ");
  lcd.setCursor(0, 1);
  lcd.print("   < ");
  lcd.print(brightnessValue);
  lcd.print(" >");
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

// depending on what settings was selected will be do some actions
void settingsSelectedFunction() {
  switch (settingsSelected) {
    case 1: difficultySelect();
      break;
    case 2: contrast();
      break;
    case 3: brightness();
      break;
    case 4: back();
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
    lcd.print("   Credits:");
    lcd.setCursor(0, 1);
    lcd.print("  Iulian Gal");
  }
  else if (pageabout == 1) {
    lcd.setCursor(0, 0);
    lcd.print("    GitHub:     ");
    lcd.setCursor(0, 1);
    lcd.print("tinyurl.com/2fcr3ev6");
  }
  else if (pageabout == 2) {
    lcd.setCursor(0, 0);
    lcd.print("  Game Name: ");
    lcd.setCursor(0, 1);
    lcd.print("Overtaking cars ");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("  Powered by: ");
    lcd.setCursor(0, 1);
    lcd.print(" @UniBucRobotics");
  }
  if (prevButtonValue != switchValue) {
    if (switchValue == 0) {
      buttonState = !buttonState;
    }
    prevButtonValue = switchValue;
  }
}


// TODO: enter player name, for each game or in settings?
//String alphabet = "abcdefghijklmnopqrstuvwxyz";
//const int delayEnterName = 200;
//String playerName = "";
//int alphabetIterator = 0;
//
//void enterName() {
//  lcd.setCursor(0, 0);
//  lcd.print(" Enter name: ");
//  lcd.setCursor(12, 0);
//  
//  
//}

// choose options in main menu
void selectedFunction() {
  switch (selected) {
    case 1: startGame = true;
      endGame = 0;
      startLevelTime = millis();
      break;
    case 2: highscore();
      break;
    case 3:
      if (firstSettings) {
        settingsButtonState = 0;
        firstSettings = 0;
      }
      settings();
      if (settingsButtonState == 1) {
        lcdClearLine(0);
        lcdClearLine(1);
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

void back() {
  lcd.clear();
  buttonState = 0;
  settingsButtonState = 0;
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


// ------------ GAME PLAY --------------
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
    fall();
    loseLife();
    scoreFunction();
    yMoved = true;
  } //fast forward

  if (yValue >= minThreshold && yValue <= maxThreshold) {
    yMoved = false;
  }
}

// turn off initial position of car
void turnOffCar(int col, int row) {
  lc.setLed(0, row, col, false);
  lc.setLed(0, row + 1, col, false);
  lc.setLed(0, row + 1, col + 1, false);
  lc.setLed(0, row + 1, col - 1, false);
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

// when the car hits another car, the matrix will be deleted
void died() {
  clearMatrix();
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
    level = 1;
    lives = 3;
  }
}

// dependion on level, cars will be bigger
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
    EEPROM.put(0, highscore);
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

void setup() {
  pinMode(swPin, INPUT_PULLUP);
  lc.shutdown(0, false);
  lc.setIntensity(0, 2);
  lc.clearDisplay(0);
  randomSeed(analogRead(2));
  lcd.begin(16, 2);
  lcd.createChar(0, heartCustom);
}

int levelInterval = 10000;

void loop() {
  analogWrite(V0, contrastValue);
  analogWrite(brightnessPin, brightnessValue);
  switchValue = digitalRead(swPin);
  // display welcome message
  if (!startGame) {
    if (!welcome) {
      welcomeFunction();
    }
    // after diplayed welcome message on lcd we have main menu
    else {
      if (buttonState == 0) {
        menuSelect();
        lcdClearLine(0);
        lcdClearLine(1);
      }
      else {
        selectedFunction();
      }
    }
  } else { // start game
    if (!endGame) {
      start();
      if (level > 5) { // final level = 5
        endGame = 1;
        level = 0;
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
      if (alive) { // car doesn't hit another car
        moveJoystick();
        moveCar(col, row);
        chooseLevel(level);
        fallFrequency();
        currentTime = millis();
        if (currentTime - startLevelTime >= levelInterval) { // change level after 10s alive
          level++;
          clearMatrix();
          startLevelTime = millis();
          }
        }
      }
      else {
        currentTime = millis();
      }
    }
  }
