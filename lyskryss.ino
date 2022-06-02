int carRed = 2; //car lights assigned
int carYellow = 3;
int carGreen = 4;
int pedRed = 6; //ped lights assigned
int pedGreen = 7; 
int button = 10; 
int crossTime = 5000;  //crossing time 5 s given to pedestrians
unsigned long changeTime ; // collects the time since the button was last pressed

void setup () {
  pinMode(carRed, OUTPUT);
  pinMode(carYellow, OUTPUT);
  pinMode(carGreen, OUTPUT);
  pinMode(pedRed, OUTPUT);
  pinMode(pedGreen, OUTPUT);
  pinMode(button, INPUT);
 
  digitalWrite(carGreen,HIGH); //starts with green car light on
  digitalWrite(pedRed, HIGH); //starts with red pedestrian light on
}

void loop(){
  int state = digitalRead(button);
  if(state==HIGH && (millis() - changeTime) > 10000) {
    delay(1000);
    changeLights();  //function to change lights
  }
}

void changeLights() {
  digitalWrite(carGreen,LOW);  //green car light off
  digitalWrite(carYellow,HIGH); //yellow car light on
  digitalWrite(pedRed,HIGH); //red pedestrian light on
  delay(2000); //wait 2 seconds

  digitalWrite(carYellow,LOW); // yellow car light off
  digitalWrite(carRed,HIGH); //red car light on
  delay(2000); //wait 2 seconds

  digitalWrite(pedRed,LOW); //red ped light off
  digitalWrite(pedGreen,HIGH); //green ped light on
  delay(crossTime); //delay 5 seconds

  //flashing green pedestrian light
  for (int x=0; x<5; x++){
    digitalWrite(pedGreen,HIGH);
    delay(250);
    digitalWrite(pedGreen,LOW);
    delay(250);
  }
 
  digitalWrite(pedRed, HIGH); //turn red ped light on
  delay(4000);
 
  digitalWrite(carGreen,HIGH); //car green light on
  digitalWrite(carRed,LOW); //car red light off
 
  changeTime = millis(); //recording time
 
}
