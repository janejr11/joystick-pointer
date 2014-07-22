/*

 Git repository:
 
 https://github.com/janejr11/joystick-pointer
 
 This software is designed to drive a Teensy (version) board attached to a joystick and a number of buttons
 in order to improve computer accessability for users with unique needs. The "Teensy Loader" and 
 "Teensyduino" downloads are necessary to properly upload software to the Teensy board. These can be found
 at the following websites:
 http://www.pjrc.com/teensy/td_download.html
 http://www.pjrc.com/teensy/loader_vista.html
 The Arduino IDE is being used and is necessary to view this file so I assume you have it already but for
 the sake of completeness, the link is below:
 http://arduino.cc/en/main/software
 
 This software has been developed under the direction of Dr. Victor Pauca in the Wake Forest University
 Computer Science department and is free and open to any who wish to use it.
 
 Contact info:
 Jack Janes
 janejr11@wfu.edu
 (804) 484-4206
 */

// mouse sensitivity, higher numbers -> less reactive mouse
static const int mouseDelay = 20;

// pin declarations
// directional controls
static const int ud = 20; // up and down movement of the joystick
static const int lr = 21; // left and right movement of the joystick

// button declarations
static const int right = 0;
static const int left = 1;
static const int ctrl = 2;
static const int shift = 3;

static const int led = 11; // led pin to report stickyKeys
static const int leftLED = 4;
static const int ctrlLED = 5;
static const int shiftLED = 6;

int xThresh; // threshold value (middle position) for the x axis
int yThresh; // threshold value (middle position) for the y axis

// function definitions
int calibrateX();
int calibrateY();

// toggle status of buttons
boolean ctrlPressed;
boolean shiftPressed;

void setup(){
  pinMode (ud, INPUT);
  pinMode (lr, INPUT); // might need pullup or analog reading setup

  pinMode(right, INPUT_PULLUP);
  pinMode(left, INPUT_PULLUP); 
  pinMode(ctrl, INPUT_PULLUP);
  pinMode(shift, INPUT_PULLUP);

  //pinMode(led, OUTPUT);

  xThresh = calibrateX();
  yThresh = calibrateY();

  ctrlPressed = false;
  shiftPressed = false;
}



void loop(){
  // mouse movement
  // read and threshold values
  int x = analogRead(lr) - xThresh;
  int y = analogRead(ud) - yThresh;

  // --X--
  int xShift;
  if (x >= 300) // fast R
    xShift = 10;
  else if (x >= 150) // medium R
    xShift = x/20-5;
  else if (x >= 10) // slow R
    xShift = x/60;
  else if (x >= -10) // nothing
    xShift = 0;
  else if (x >= -150) // slow L
    xShift = x/60;
  else if (x >= -300) // medium L
    xShift = x/20+5;
  else                // fast L
  xShift = -10;



  // --Y--
  int yShift;
  if (y >= 300) // fast U
    yShift = 10;
  else if (y >= 150) // medium U
    yShift = y/20-5;
  else if (y >= 10) // slow U
    yShift = y/60;
  else if (y >= -10) // no movement
    yShift = 0;
  else if (y >= -150) // slow D
    yShift = y/60;
  else if (y >= -300) // medium D
    yShift = y/20+5;
  else
    yShift = -10;

  Mouse.move(xShift,yShift);
  Serial.print("X Shift: ");
  Serial.println(xShift);
  delay(mouseDelay); // affects sensitivity


    // left mouse

  // in order to click and drag, the button can be pressed for a half second,
  // then pressed again to release the key, short presses result in only one click
  // The circuit is sampled five times in order to assertain if the button has been
  // held down constantly
  if (digitalRead(left) == LOW){ // the left mouse button has been pressed
    boolean clicked = false;
    if (Mouse.isPressed()){ // if the mouse was previously toggled, release it
      Mouse.release();
      digitalWrite(leftLED,LOW); // dim toggle led
      clicked = true;
    }
    delay(100);
    if (digitalRead(left) == HIGH){ // if the button has been released, click once
      if (clicked == false)
        Mouse.click();
      clicked = true;
    }
    delay (100);
    if (digitalRead(left) == HIGH){ // if the button has been released, click once
      if (clicked == false)
        Mouse.click();
      clicked = true;
    }
    delay (100);
    if (digitalRead(left) == HIGH){ // if the button has been released, click once
      if (clicked == false)
        Mouse.click();
      clicked = true;
    }
    delay (100);
    if (digitalRead(left) == HIGH){ // if the button has been released, click once
      if (clicked == false)
        Mouse.click();
      clicked = true;
    }
    delay (100);
    if (digitalRead(left) == HIGH){ // if the button has been released, click once
      if (clicked == false)
        Mouse.click();
      clicked = true;
    }
    if (digitalRead(left) == LOW){ // if the button was held down for a half second, enable click-and-drag mode
      Mouse.press();
      digitalWrite(leftLED,HIGH); // light toggle led
      delay(500); // delay for a half second to prevent immediate relase of key
    }
  }


  // right mouse
  if (digitalRead(right) == LOW)
    Mouse.click(MOUSE_RIGHT);



  // ctrl
  if (digitalRead(ctrl) == LOW){ // ctrl has been pressed
    if (ctrlPressed == true){ // if ctrl was previously toggled, release it
      Keyboard.release(KEY_LEFT_CTRL);
      
      
      
      ctrlPressed = false;
      digitalWrite(ctrlLED,LOW);
      // digitalWrite(ctrlLED, HIGH); // dim the ctrl LED
      delay(500); // give time to release the button before resampling
    }
    else { // toggle the key so that the next action will be 'ctrl+action'
      Keyboard.press(KEY_LEFT_CTRL);
      ctrlPressed = true;
      digitalWrite(ctrlLED,HIGH);
      // digitalWrite(ctrlLED,LOW); // light ctrl LED
      delay(500); // give time to release the button before resampling
    }
  }
  
  
  // shift
   if (digitalRead(shift) == LOW){ // shift has been pressed
     if (shiftPressed == true){ // if shift was previously toggled, release it
       Keyboard.release(KEY_LEFT_SHIFT);
       shiftPressed = false;
       digitalWrite(shiftLED,LOW);
       // digitalWrite(shiftLED,HIGH); // dim the shift LED
       delay(500); // give time to release the button before resampling
     }
     else { // toggle the key so that the next action will be 'shift+action'
       Keyboard.press(KEY_LEFT_SHIFT);
       digitalWrite(shiftLED,HIGH);
       shiftPressed = true;
       // digitalWrite(shiftLED,LOW); // light the shift LED
       delay(500); // give time to release the button before resampling
     }
   }
   
}

// read 10 values to calculate the threshold x sensor values
int calibrateX(){
  int xSum;
  xSum = 0;

  for (int i=0; i<10; i++){
    xSum = xSum + analogRead(lr);
  }

  Serial.print("X Threshold: ");
  Serial.println(xSum/10);

  return xSum/10;
}

// read 10 values to calculate the threshold y sensor values
int calibrateY(){
  int ySum;
  ySum = 0;

  for (int i=0; i<10; i++){
    ySum = ySum + analogRead(ud);
  }

  Serial.print("Y Threshold: ");
  Serial.println(ySum/10);

  return ySum/10;
}


