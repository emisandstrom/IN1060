
int stjerne1 = 9;
int stjerne2 = 12; 
int stjerneHvitt = 13;


void setup () {
  pinMode(stjerne1, OUTPUT);
  pinMode(stjerne2, OUTPUT);
  pinMode(stjerneHvitt, OUTPUT);
}

void loop(){
   digitalWrite(stjerne1,HIGH);
   digitalWrite(stjerne2,HIGH);
   digitalWrite(stjerneHvitt,HIGH);
}
