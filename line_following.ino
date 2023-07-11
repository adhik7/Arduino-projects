#include "motor_lib.h"
  //  motor(4,"forward",s);
    // _delay_ms(165);
void setup(){
  
  volatile int *ddrc=0x27,*inc=0x26;
  *ddrc==0x00;
  
  while(1){
    
    if(*inc==0){
     motor(1,"forward",165);
     motor(2,"forward",165);
    motor(3,"forward",165);
    motor(4,"forward",165);
  }
  else if(*inc==0x01){
    motor(1,"backward",165);
     motor(2,"backward",165);
     motor(3,"forward",165);
     motor(4,"forward",165);
  }
  else if(*inc==0x02){
    motor(1,"forward",165);
     motor(2,"forward",165);
     motor(3,"backward",165);
     motor(4,"backward",165);
  }
  else if(*inc==0x03){
    motor(1,"stops",165);
     motor(2,"stops",165);
     motor(3,"stops",165);
     motor(4,"stops",165);
  }
}
}

void loop() {
  // put your main code here, to run repeatedly:

}
