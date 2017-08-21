#include <Adafruit_VS1053.h>
#include <Wire.h>
#include <Adafruit_Si4713.h>
#include <SPI.h>
#include <SD.h>
#include <Servo.h>

Servo myServo;

#define NOT_SET -1
#define RADIO_MODE 0
#define SPEAKER_MODE 1
#define LEAFLET_MODE 2

#define SHIELD_RESET  -1      // VS1053 reset pin (unused!)

#define FMSTATION 9130    // 10230 == 102.30 MHz

int current_mode = NOT_SET;
int previous_mode = NOT_SET;
int mode_switch = false;

int leftState = LOW;
int rightState = LOW;
const int leftSwitchPin = 9;
const int rightSwitchPin = 10;

int photoState = LOW;
int previousState = LOW;
int switchState = false;

int audioStarted = false;

//pin settings here
//these might change due to shield pin settings
// These are the pins used for the music maker shield
#define SHIELD_RESET  -1      // VS1053 reset pin (unused!)
#define SHIELD_CS     7      // VS1053 chip select pin (output)
#define SHIELD_DCS    6      // VS1053 Data/command select pin (output)
#define CARDCS 4     // Card chip select pin
#define DREQ 3       // VS1053 Data request, ideally an Interrupt pin
// the music maker is a total pig about the pins
// it also hogs 11, 12, and 13!

const int servoPin = 5;
const int photoPin = 2;
#define RESETPIN 8

Adafruit_VS1053_FilePlayer musicPlayer = 
  Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

Adafruit_Si4713 radio = Adafruit_Si4713(RESETPIN);

/*
void resetVariables(){
  
  mode_switch = false;
  current_mode = NOT_SET;
  previous_mode = NOT_SET;
  mode_switch = false;
  leftState = LOW;
  rightState = LOW;
  photoState = LOW;
  previousState = LOW;
  switchState = false;
  audioStarted = false;

}
*/

void setup() {

  Serial.begin(9600);
  Serial.println("Setting up....");

  pinMode(leftSwitchPin, INPUT);
  pinMode(rightSwitchPin, INPUT); 
  pinMode(photoPin, INPUT);

  checkPhotoState();
  Serial.print("Photo pin at: ");
  Serial.println(photoState);
  
  // Read mode setting
  //resetVariables();
  current_mode = checkMode(true);
  
  switch (current_mode) {
    case RADIO_MODE:
    // do radio set up
      setupRadio();
    case SPEAKER_MODE:
    // do audio setup
      setupAudio();
      break;
    case LEAFLET_MODE:
      myServo.attach(servoPin);
      toggleServo();
      break;
  }
  
}

void loop() {

/*
  current_mode = checkMode(false);
  if (mode_switch == true){
    setup();  
  }
*/
  
  delay(500);
  //sets photoState, switchState, previousState
  checkPhotoState();
  
  // if signal

  switch (current_mode) {
    case RADIO_MODE:
      playRadio();
    case SPEAKER_MODE:
      //call only when state changes
      toggleAudio();
      break;
    case LEAFLET_MODE:
      toggleServo();
      break;
  }
  
}


int checkMode(int init){

  int mode = NOT_SET;

  leftState = digitalRead(leftSwitchPin);
  rightState = digitalRead(rightSwitchPin);

  Serial.print("Left State: ");
  Serial.println(leftState);
  Serial.print("Right State: ");
  Serial.println(rightState);
    
  if(leftState == HIGH){
    mode = LEAFLET_MODE;  
  }
  else if (rightState == HIGH){
    mode = SPEAKER_MODE;    
  }
  else{
    mode = RADIO_MODE;  
  }

  Serial.print("Mode is ");
  Serial.println(mode);

  if(init == true){
    previous_mode = mode;
    mode_switch = false;
  }
  else{
    if(previous_mode != mode){
      Serial.println("Mode changed.");
      mode_switch = true;
    }
  }

  return mode;
}

//sets photoState, switchState, previousState
void checkPhotoState() {
  
  photoState = digitalRead(photoPin);

  if ((photoState == LOW && previousState == LOW)||
        (photoState == HIGH && previousState == HIGH)){
    switchState = false;
  }
  else if (photoState == HIGH && previousState == LOW){
    //low to high
    switchState = true;
  }
  else if (photoState == LOW && previousState == HIGH){
    //high to low
    switchState = true;  
  } 

  previousState = photoState;

  if(switchState){
    Serial.print("Photo state = ");
    if (photoState == 0){
      Serial.println("LOW");
    }
    else {
      Serial.println("HIGH");  
    }
  }

}

void setupAudio() {
  
  Serial.println("Adafruit VS1053 setup");


if (! musicPlayer.begin()) { // initialise the music player
     Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
     while (1);
  }
  Serial.println(F("VS1053 found"));
  
   if (!SD.begin(CARDCS)) {
    Serial.println(F("SD failed, or not present"));
    while (1);  // don't do anything more
   }

  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(20,20);

  // If DREQ is on an interrupt pin (on uno, #2 or #3) we can do background
  // audio playing
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int
  
}

void setupRadio() {
    
  Serial.println("Adafruit Radio - Si4713 Setup");

  if (! radio.begin()) {
    Serial.println("Couldn't find radio?");
    while (1);
  }

  Serial.print("\nSet TX power");
  radio.setTXpower(115);  // dBuV, 88-115 max

  Serial.print("\nTuning into "); 
  Serial.print(FMSTATION/100); 
  Serial.print('.'); 
  Serial.println(FMSTATION % 100);
  radio.tuneFM(FMSTATION);

  // This will tell you the status in case you want to read it from the chip
  radio.readTuneStatus();
  Serial.print("\tCurr freq: "); 
  Serial.println(radio.currFreq);
  Serial.print("\tCurr freqdBuV:"); 
  Serial.println(radio.currdBuV);
  Serial.print("\tCurr ANTcap:"); 
  Serial.println(radio.currAntCap);

  // begin the RDS/RDBS transmission
  radio.beginRDS();
  radio.setRDSstation("Inglourious Datanerds");
  radio.setRDSbuffer( "Inglourious Datanerds Radio!");

  Serial.println("RDS on!");  
  
}

void toggleServo() {
  if (photoState == HIGH){
    myServo.write(135);
  }
  else{
    myServo.write(0);
  }
}

void playRadio() {

  //these are just diagnostics and not really necessary to 'play' the radio
  radio.readASQ();
  Serial.print("\tCurr ASQ: 0x"); 
  Serial.println(radio.currASQ, HEX);
  Serial.print("\tCurr InLevel:"); 
  Serial.println(radio.currInLevel);

}

void toggleAudio() {

  if (switchState == false){
    return;
  }
  
  if (photoState == HIGH && !audioStarted){
    startAudio();  
  }
  else if (photoState == HIGH && audioStarted) {
    resumeAudio();
  }
  else {
    pauseAudio();
  }
  
}

void startAudio() {
  //eventually want to pass the current file to function
  Serial.println("Playing music");
  musicPlayer.startPlayingFile("track001.mp3");
  audioStarted = true;
}

void pauseAudio() {
  Serial.println("Paused");
  musicPlayer.pausePlaying(true);
}

void resumeAudio() {
  Serial.println("Resumed");
  musicPlayer.pausePlaying(false);
}


