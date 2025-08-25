#include <Servo.h>
#define num_of_values_recv 5
#define digits_per_value_recv 1

Servo thumb;
Servo index;
Servo middle;
Servo ring;
Servo pinky;

int values_recv[num_of_values_recv];
int string_length = num_of_values_recv * digits_per_value_recv + 1; //$00000
int counter = 0 ;
bool counter_start = false;
String recieved_string; 


void setup() {
  Serial.begin(9600);
  thumb.attach(3);
  index.attach(5);
  middle.attach(7);
  ring.attach(9);
  pinky.attach(11);



}



void receive_data(){
  while(Serial.available()){
    char c = Serial.read();
    if (c == '$'){
      counter_start = true;
    }

    if (counter_start){
      if(counter < string_length){
        recieved_string = String(recieved_string + c);
        counter ++;
      }

      if  (counter >= string_length){
        for(int i =0; i<num_of_values_recv; i++){
          int num = (i * digits_per_value_recv ) + 1;
          values_recv[i] = recieved_string.substring(num, num + digits_per_value_recv).toInt();
      }
      recieved_string = "";
      counter = 0;
      counter_start = false;
    }
  }
}
}

  int last_thumb = 1;
  int last_index = 1;
  int last_middle = 1;
  int last_ring = 1;
  int last_pinky = 1;
  

void loop() {

  for(int i=0 ; i<5; i++)
  {
    values_recv[i] = 2;
  }

    receive_data();

//thumb
    if(values_recv[0]==1)
    {
      if(last_thumb != 1){
      thumb.write(180);
      last_thumb = 1;
    }}
    else if (values_recv[0]==0) 
    {if(last_thumb != 0){
      thumb.write(0);
      last_thumb = 0;  
    }}

//index
    if(values_recv[1]==0)
    {
      if(last_index != 0){
      index.write(180);
      //delay(500);
      last_index = 0;
    }}
    else if (values_recv[1]==1) 
    {if(last_index != 1){
      index.write(0);
      //delay(500);
      last_index = 1;  
    }}

//middle
    if(values_recv[2]==0)
    {
      if(last_middle != 0){
      middle.write(0);
      last_middle = 0;
    }}
    else if (values_recv[2]==1) 
    {if(last_middle != 1){
      middle.write(180);
      last_middle = 1;  
    }}

//ring
if(values_recv[3]==0){
      if(last_ring != 0)
    {
      ring.write(180);
      delay(300);
      ring.write(90);
      last_ring = 0;
    }
    }
    else if(values_recv[3]==1){
      if(last_ring != 1)
      ring.write(0);
      delay(600);
      ring.write(90);
      last_ring = 1;
      }

//pinky
    if(values_recv[4]==1){
      if(last_pinky != 1)
    {
      pinky.write(180);
      delay(350);
      pinky.write(90);
      last_pinky = 1;
    }
    }
    else if(values_recv[4]==0){
      if(last_pinky != 0)
      pinky.write(0);
      delay(200);
      pinky.write(90);
      last_pinky = 0;
      }

    
}
