#include "SoftwareSerial.h"  //biblioteket som tillater seriell kommunikasjon på pinner 10 og 11
SoftwareSerial mySerial(10, 11);
# define Start_Byte 0x7E // commands for DFPlayer mini fra: https://wiki.dfrobot.com/DFPlayer_Mini_SKU_DFR0299 
# define Version_Byte 0xFF
# define Command_Length 0x06
# define End_Byte 0xEF 
# define Acknowledge 0x00 // 0x00: no info

# define ACTIVATED LOW

int buttonNext = 2;
int buttonPause = 3;
int buttonPrevious = 4;
int volumeUP = 5;
int volumeDOWN = 6;
int volume = 15;
boolean isPlaying = false;



void setup () {

pinMode(buttonPause, INPUT);
digitalWrite(buttonPause,HIGH);
pinMode(buttonNext, INPUT);
digitalWrite(buttonNext,HIGH);
pinMode(buttonPrevious, INPUT);
digitalWrite(buttonPrevious,HIGH);
pinMode(volumeUP, INPUT);
pinMode(volumeDOWN, INPUT);
digitalWrite(volumeUP, HIGH);
digitalWrite(volumeDOWN, HIGH);

mySerial.begin (9600);
delay(1000);
playFirst();
isPlaying = true;


}


void loop () { 

 if (digitalRead(buttonPause) == ACTIVATED)
  {
    if(isPlaying)
    {
      pause();
      isPlaying = false;
    }else
    {
      isPlaying = true;
      play();
    }
  }


 if (digitalRead(buttonNext) == ACTIVATED)
  {
    if(isPlaying)
    {
      playNext();
    }
  }

   if (digitalRead(buttonPrevious) == ACTIVATED)
  {
    if(isPlaying)
    {
      playPrevious();
    }
  }

  if(digitalRead(volumeUP) == ACTIVATED)
{
volumeINC();
}
if(digitalRead(volumeDOWN) == ACTIVATED)
{
volumeDEC();
}
}

void playFirst()
{
execute_CMD(0x3F, 0, 0);
delay(500);
execute_CMD(0x06, 0, volume);
delay(500);
execute_CMD(0x11,0,1);
delay(500);
}


void pause()
{
  execute_CMD(0x0E,0,0);
  delay(500);
}

void play()
{
  execute_CMD(0x0D,0,1); 
  delay(500);
}

void playNext()
{
  execute_CMD(0x01,0,1);
  delay(500);
}

void playPrevious()
{
  execute_CMD(0x02,0,1);
  delay(500);
}

void volumeINC()
{
volume = volume+1;
if(volume==31)
{
volume=30;
}
execute_CMD(0x06, 0, volume);
delay(500);
}
void volumeDEC()
{
volume = volume-1;
if(volume==-1)
{
volume=0;
}
execute_CMD(0x06, 0, volume);
delay(500);
}

//denne delene er inspirert av koden fra https://cahamo.delphidabbler.com/resources/dfplayer-mini
void execute_CMD(byte CMD, byte Par1, byte Par2) 
{

word checksum = -(Version_Byte + Command_Length + CMD + Acknowledge + Par1 + Par2);

byte Command_line[10] = { Start_Byte, Version_Byte, Command_Length, CMD, Acknowledge,
Par1, Par2, highByte(checksum), lowByte(checksum), End_Byte};

for (byte k=0; k<10; k++)
{
mySerial.write( Command_line[k]);
}
}
