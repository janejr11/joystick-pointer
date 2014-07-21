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
#define ud 0 // up and down movement of the joystick
#define lr 1 // left and right movement of the joystick

// button declarations
#define right 2
#define left 3
#define ctrl 4
#define shift 5

// status LED
#define led 11 // on when input is registered, blink for combined keypresses

void setup(){
  pinMode (ud, INPUT);
  pinMode (lr, INPUT); // might need pullup or analog reading setup
  
  pinMode(right, INPUT_PULLUP);
  pinMode(left, INPUT_PULLUP);
  pinMode(ctrl, INPUT_PULLUP);
  pinMode(shift, INPUT_PULLUP);
  
  pinMode(led, OUTPUT);
  
}

void loop(){
  
}


