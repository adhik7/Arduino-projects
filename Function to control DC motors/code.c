//example
//motor(3,"forward",255);
//motor(3,"backward",255);
//motor(3,"stops",255);
#define pulse 0x10 //data clk in port d
#define en 0x80   //data enable in port d
#define pwm  0x08  //latch port d
#define latch 0x10 //latch in port b
#define data 0x01  //data in  port b
#define times 12
#include <stdio.h>
//motor(motorno,dir,speeds);//
void delt(volatile int t){
  for(volatile int i=0;i<t;i++);
}
int global,updated;
void motor(char motorno , char dir[20] , int speeds){
         char *dport=0x2a,*dout=0x2b;//port d address
        char *bport=0x24,*bout=0x25;//port b address
        //int a;
        int i,z;
        int a,b[8];//={0,0,0,0,0,0,0,0};
        
         *dport |=0xff;
        *bport |=0xff;
        
        *bout &= ~(data) ;
         /******<<------------------------------->>******/      
       //TO CONTROL THE DIRECTION OF MOTORS//
 //<<MOTOR 1>>//       
      if(motorno==1){
        if(dir=="forward"){
                 a=0b00000100;//forward
              
        }
        if(dir=="backward"){
               a=0b00001000;//backward
               
        }
      }
//<<MOTOR 2>>//      
      if(motorno==2){
        if(dir=="forward"){
                 a=0b00000010;//forward
               
        }
        if(dir=="backward"){
                 a=0b00010000;//backward
               
        }
      }
      
//<<MOTOR 3>>//        
      if(motorno==3){
        if(dir=="forward"){
                a=0b00100000;//forward
               
        }
        if(dir=="backward"){
                a=0b10000000;//backward
               
        }
      }
//<<MOTOR 4>>//        
      if(motorno==4){
        if(dir=="forward"){
                a=0b00000001;//forward
               
        }
        if(dir=="backward"){
                a=0b01000000;//backward
               
        }
      } 
   
      updated |= a;
   if(global != updated || dir=="stops"){
        global = updated;
      int c,i=updated,d[8]={0,0,0,0,0,0,0,0};
           
           if(i>=128  ){
             d[0]=1;
             i=i-128;
           }
             if(i<=127 && i>=64){
                 d[1]=1;
               i=i-64;
             }
            // 64
             if(i<=63 && i>=32){
                 d[2]=1;
               i=i-32;
             }
             //32
             if(i<=31 && i>=16){
                 d[3]=1;
                i=i-16;
             }
             //16
             if(i<=15 && i>=8)
             {
                  d[4]=1;
                i=i-8;
             }
             //8
             if(i<=7 && i>=4){
                  d[5]=1;
                i=i-4;
             }
             //4
             if(i<=3 && i>=2){
                  d[6]=1;
                i=i-2;
             }
             //2
             if(i==1){
                  d[7]=1;
                i=i-1;
             }
             //1
          if(d[4]==d[5] && motorno==1 && (d[4]!=0 || d[5]!=0)){
            if(dir=="forward"){
              d[4]=0;   
              updated &= ~(0b00001000);  
            }
             if(dir=="backward"){
              d[5]=0;   
               updated &= ~(0b00000100);    
            }
             if(dir=="stops"){
              d[4]=0;
              d[5]=0;    
               updated &= ~(0b00001100);    
            }
        }    
          if(d[3]==d[6] && motorno==2 && (d[3]!=0 || d[6]!=0)){
            if(dir=="forward"){
              d[3]=0;   
              updated &= ~(0b00010000);  
            }
             if(dir=="backward"){
              d[6]=0;   
               updated &= ~(0b00000010);    
            }
             if(dir=="stops"){
              d[3]=0;
              d[6]=0;    
               updated &= ~(0b00010010);    
            }
        }    
        if(d[2]==d[0] && motorno==3 && (d[2]!=0 || d[0]!=0)){
          if(dir=="forward"){
            d[0]=0;   
            updated &= ~(0b10000000);  
          }
           if(dir=="backward"){
            d[2]=0;   
             updated &= ~(0b00100000);    
          }
           if(dir=="stops"){
            d[2]=0;
            d[0]=0;    
             updated &= ~(0b10100000);    
          }
        }
         if(d[7]==d[1] && motorno==4 && (d[1]!=0 || d[7]!=0)){
          if(dir=="forward"){
            d[1]=0;  
             updated &= ~(0b01000000);     
          }
           if(dir=="backward"){
            d[7]=0;  
             updated &= ~(0b00000001);     
          }
          if(dir=="stops"){
            d[1]=0;
            d[7]=0;    
             updated &= ~(0b01000001);    
          }
        }
             
              
    //  <<GIVING PULSES TO SHIFT REGISTER>>//
          for(i=0;i<8;i++){
               if(d[i]==0){
                  *bout &= ~(data);   //Data into shift register
                // _delay_ms(1);
                delt(times);
               }
            
               if(d[i]==1){
                  *bout |= data ;        //Data into shift register
                  //_delay_ms(1);
                  delt(times);
               }
            
            //SHIFTING DATA WITH EACH PULSE
              *dout &= ~(pulse);
             // _delay_ms(1);  
             delt(times);   
              *dout |= pulse;
             // _delay_ms(1);
             delt(times);
              *dout &= ~(pulse);
             // _delay_ms(1);
             delt(times);
          }
      }
        
      
  /******<<---------------------------->>******/          
      //STORING DATA FROM REGISTER TO LATCH
         { *bout &= ~(latch);
         // _delay_ms(1);
           delt(times);
          *bout |= latch;
         // _delay_ms(1);
           delt(times);
          *bout &= ~(latch);
         }
   
   /******<<------------------------------->>******/     
      //<<PWM TO CONTROL MOTOR SPEED>>//
 
               *dport=0xff;
            *bport=0xff;
            
            char *m_one=0xb3,*tccr0a1=0xb0,*tccr0b1=0xb1;
             char *m_two=0xb4;
              *tccr0a1=0xa3;
        
              *tccr0b1=0x01;
               if(motorno==1){
                 if(dir!="stops"){
                 *m_one=speeds;
                 }
                  if(dir=="stops"){
                 *m_one=0;
                 }
               }
               if(motorno==2){
                 if(dir!="stops"){   
                  *m_two=speeds;
                 }
                 if(dir=="stops"){   
                  *m_two=0;
                 }
               } 
           
           
            //<<REGISTERS IN TIMER>>
            
            char *ocr0a=0x47,*tccr0a=0x44,*tccr0b=0x45;
            char *ocr0b=0x48;//*tccr0a=0x44,**tccr0b=0x45;
             *tccr0a=0xa3;
             *tccr0b=0x01;
         if(motorno==3){
            if(dir!="stops"){
             *ocr0a=speeds;
            }
            if(dir=="stops"){
             *ocr0a=0;
            }
            
         }
         if(motorno==4){   
            if(dir!="stops"){
              *ocr0b=speeds;
            }
            if(dir=="stops"){
             *ocr0b=0;
            }
         }     
              
}
