# Overtaking cars Game
Overtaking Cars Game is a project made by me during the course Introduction to Robotics. The game mode is as follows: The player has at his disposal a car with which he has to overtake as many cars as possible in order to accumulate a highscore, but if during the overtaking, the car touches another car in traffic, the player will lose a life / heart of the 3 available. On the Ox axis of the joystick the player can move left and right and on the Oy axis he can accelerate when the road is clear. <br>
<br>
This game is structured on 5 levels that change automatically, in which depending on the level the cars to be overtaken will be bigger. To make everything more fun I also implemented the difficulty function which contains the easy, medium and hard levels, which depending on the level change the spawn interval of the cars (easy - 200ms, medium 400 - ms, hard - 600ms).
<br>
The game tests your dexterity and become so fun when you challenge a friend to beat your high score.  
<br>
Another similar game is the Traffic Rider available on Android and iOS.

How does the menu works? <br>
There are 4 buttons on the main page:
* PLAY button that starts a new game
* HIGHSCORE button where we can see what highscore we got in the past
* SETTINGS button where we can store the player's name, adjust the game difficulty / LCD brightness / LCD contrast and matrix brightness
* ABOUT button where you can find some data about the game and developer

There are 6 buttons on the settings menu:
* DIFFICULTY (easy, medium, hard) that changes the interval of spwan of the cars
* CHANGE CONTRAST (range 10 - 150, higher or lower values make the LCD blank)
* CHANGE LCD BRIGHTNESS 
* CHANGE MATRIX BRIGHTNESS (range 0 - 5) the matrix will be on for the user to see real-time matrix brightness
* ENTER NAME: with Oy axes user can choose the next letter from his name and with Ox axes he can remove or concatenate the selected letter
* BACK: returns to the main screen <br>
All settings and highscore are saved in EEPROM.

<br>

Materials Required:
* Arduino Uno - 1pcs
* Joystick - 1pcs
* 2x16 LCD Display - 1pcs
* MAX7219 Driver - 1pcs
* 8x8 led matrix - 1pcs
* buzzer - 1pcs
* capacitor - 3pcs
* 220Ohm resistor - 1pcs
* 100Ohm resistor - 1pcs
* breadboard - 3pcs
* a lot of cables ~ 40pcs

<br> 

Video Demo: https://youtu.be/B2VHj9GvN2s

<br>
The setup: <br>

<img src="https://user-images.githubusercontent.com/61587939/146786311-ec1cce17-2be8-47e1-97f9-11356423b31d.jpg" width=1200 height=700>





