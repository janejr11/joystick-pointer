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
the sake of completeness, the download is below:
http://arduino.cc/en/main/software

This software has been developed under the direction of Dr. Victor Pauca in the Wake Forest University
Computer Science department and is free and open to any who wish to use it.

Contact info:
Jack Janes
janejr11@wfu.edu
(804) 484-4206
*/

// pin declarations
// directional controls
static const int ud = 20; // up and down movement of the joystick
static const int lr = 21; // left and right movement of the joystick

// button declarations
static const int right = 2;
static const int left = 3;
static const int ctrl = 4;
static const int shift = 5;

int xThresh; // threshold value (middle position) for the x axis
int yThresh; // threshold value (middle position) for the y axis

// function definitions
int calibrateX();
int calibrateY();

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
  delay(20);
  
  // button presses
  
  
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

