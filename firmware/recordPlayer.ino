
/*
 *	Copyright:	Makezone
 *	name:		record player 
 *	Author:		hayeon
 *	Date:		2015-02-25
 */
 
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

SoftwareSerial mySerial(10, 11); // RX, TX

const int potentiometer = A6;
const int motorPin = 6;


boolean isPlaying = false; 

int needleState = 0;   
int volume = 3; 
int currentVolume;  

void setup () {
	Serial.begin (9600);
	mySerial.begin (9600);
	mp3_set_serial (mySerial);	//set softwareSerial for DFPlayer-mini mp3 module 
	mp3_set_volume (volume);
        mp3_stop();

   pinMode(potentiometer, INPUT); 
   pinMode(motorPin, OUTPUT);

}


void loop () {        

  // Needle (potentionmeter)
   needleState = analogRead(potentiometer); 

   if(needleState < 20) { 
     play();
     analogWrite(motorPin,150);
   }
   else if(needleState < 30) {
   }
   else {
     pause();
     analogWrite(motorPin,0);
   }


}

void play() {
  if(isPlaying) {
    return;
  }
  
  Serial.println("play"); 
  isPlaying = true;
  mp3_play (1);
  delay (1000);
  mp3_next ();
}

void pause() {
  if(!isPlaying) {
    return;
  }
  Serial.println("pause"); 
  isPlaying = false;
  mp3_pause();
  //mp3_stop();
  delay (500);
}

/*
   mp3_play ();		//start play
   mp3_play (5);	//play "mp3/0005.mp3"
   mp3_next ();		//play next 
   mp3_prev ();		//play previous
   mp3_set_volume (uint16_t volume);	//0~30
   mp3_set_EQ ();	//0~5
   mp3_pause ();
   mp3_stop ();
   void mp3_get_state (); 	//send get state command
   void mp3_get_volume (); 
   void mp3_get_u_sum (); 
   void mp3_get_tf_sum (); 
   void mp3_get_flash_sum (); 
   void mp3_get_tf_current (); 
   void mp3_get_u_current (); 
   void mp3_get_flash_current (); 
   void mp3_single_loop (boolean state);	//set single loop 
   void mp3_DAC (boolean state); 
   void mp3_random_play (); 
 */

