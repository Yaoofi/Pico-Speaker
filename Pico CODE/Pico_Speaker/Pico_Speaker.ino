#include <DFRobotDFPlayerMini.h>
#include <SoftwareSerial.h>



/*
Play/Pause = GP14
Vol+ = GP12
Vol- = GP11

DFPlayer TX = GP0
DFPlayer RX = GP1
*/


/*
---------[PINS]---------
*///                   |
int PlayPause = 19;//  |
int VolM = 20;//       |
int VolP = 21;//       |
//----------------------

int Files;
bool isPlaying = false;

SoftwareSerial softSerial(/*rx =*/1, /*tx =*/0);
//#define FPSerial softSerial
#define FPSerial Serial1

DFRobotDFPlayerMini myDFPlayer;

void setup()
{
  pinMode(PlayPause, INPUT_PULLUP);
  pinMode(VolP, INPUT_PULLUP);
  pinMode(VolM, INPUT_PULLUP);


  FPSerial.begin(9600);
  Serial.begin(115200);

  Serial.println();
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

   if (!myDFPlayer.begin(FPSerial, /*isACK = */true, /*doReset = */true)) 
   {
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true)
    {
      
    }
  }
  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.pause();
  myDFPlayer.volume(20);
}

void loop()
{
 if(digitalRead(VolP) == LOW && myDFPlayer.readVolume() < 31)
  {
    myDFPlayer.volumeUp();
    Serial.println("Actual volume is:");
    Serial.println(myDFPlayer.readVolume());
    delay(100);
  }

   if(digitalRead(VolM) == LOW && myDFPlayer.readVolume() > 1)
  {
   myDFPlayer.volumeDown();
   Serial.println("Actual volume is:");
   Serial.println(myDFPlayer.readVolume());
   delay(100);
  }


  if(digitalRead(PlayPause) == LOW)
  {
    Files = myDFPlayer.readFileCounts();
    if(isPlaying == false)
    {
      Serial.println("Started!");
      isPlaying = true;
      myDFPlayer.play(random(0, Files + 1));
      delay(300);
    }
    else
    {
      Serial.println("Stoped!");
      isPlaying = false;
      myDFPlayer.pause();
      delay(300);
    }
    delay(500);
  }
}