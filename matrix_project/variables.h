// matrix pins
const byte dinPin = 12;
const byte clockPin = 11;
const byte loadPin = 10;
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
int contrastValue = 50;

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

// 10 seconds per level
int levelInterval = 10000;

const int brightnessPin = 5;
int brightnessValue = 120;

byte matrixBrightnessValue = 2;

const int buzzerPin = 13;

int melody[] = {
  262, 196,196, 220, 196,0, 247, 262
};

int noteDurations[] = {
  4, 8, 8, 4,4,4,4,4 
};


const int addressOneEEPROM = 0;
const int addressTwoEEPROM = 50;
const int addressThreeEEPROM = 100;


const uint64_t loseLifeAnimation[] = {
  0x00183c7effff6600,
  0x000c1e3f7f7f3380,
  0x80460f1f3f3f5980,
  0x8043070f1f1f4c80,
  0x8043270f1f3f4c80,
  0x804123171f2f4680,
  0x8040211b1f274380,
  0x804024191b274180,
  0x8042241819254280,
  0x8142241818244281
};

const int loseLifeAnimationLen = sizeof(loseLifeAnimation)/8;

int highscoreAddressOne = 0;
int highscoreAddressTwo = 0;
int highscoreAddressThree = 0;

String varForCopyNames = "";
int varForCopyLens = 0;
int varForCopyHighscores = 0;


String defaultPlayerName = "Name1";
String alphabet = "abcdefghijklmnopqrstuvwxyz";
char letter = alphabet.charAt(0);
String playerName = "NoName";
int iteratorAlphabet = 0;
int nrOfLetter = 25;


int maxMatrixBrightness = 5;
int minMatrixBrightness = 0;


int maxContrastValue = 150;
int minContrastValue = 50;

int nrMaxOfSetiings = 6;

int highscoreSelected = 0;
