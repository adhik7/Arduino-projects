* In this project, the car will follow a line.
* In this, 4 dc motors, Arduino uno,2 ir sensors, and a motor driver are used.
* Motor function is imported from a user-defined library motor_lib.h.
* In the main program "line_following.ino" the code constantly reads the inputs from ir sensor, according to that motor wheels rotate to follow the line(where the line will be black).
* If the right ir sensor gives input if it crosses the line.
* To bring back to its normal position left side wheels rotate forward and the right side wheels rotate backward.
* If the left sensor crosses the line right side wheels rotate forward and the left side wheels rotate backward.
