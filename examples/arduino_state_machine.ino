#include <StateMachine.h>

const int STATE_DELAY = 500;

StateMachine machine = StateMachine();
State S0;
State S1;
State S2;
State S3;
State S4;
State S5;

void setup() {
  Serial.begin(115200);
  S0 = machine.addState(&state0);
  S0.addTransition(&transitionS0S1,1);
  S0.addTransition(&transitionS0S3,3);
  
  S1 = machine.addState(&state1);
  S1.addTransition(&transitionS1S2,2);

  S2 = machine.addState(&state2);
  S2.addTransition(&transitionS2S3,3);
  
  S3 = machine.addState(&state3);
  S3.addTransition(&transitionS3S4,4);
  
  S4 = machine.addState(&state4);
  S4.addTransition(&transitionS4S5,5);
  
  S5 = machine.addState(&state5);
  S5.addTransition(&transitionS5S0,0);
  S5.addTransition(&transitionS5S2,2);
}

void loop() {
  machine.run();
  delay(STATE_DELAY);
}


//=======================================

void state0(){
  Serial.println("State 0");
}

bool transitionS0S1(){
  return random(0,2);
}

bool transitionS0S3(){
  return random(0,2);
}

//-------------------------
void state1(){
  Serial.println("State 1");
}

bool transitionS1S2(){
  return true;
}

//-------------------------
void state2(){
  Serial.println("State 2");
}

bool transitionS2S3(){
  return true;
}

//------------------------
void state3(){
  Serial.println("State 3");
}

bool transitionS3S4(){
  return true;
}

//-------------------------
void state4(){
  Serial.println("State 4");
}

bool transitionS4S5(){
  return true;
}

//-------------------------
void state5(){
  Serial.println("State 5");
}

bool transitionS5S0(){
  return random(0,2);
}

bool transitionS5S2(){
  return true;
}
