/******************************************
 * 
 * This is a test combining the StateMachine
 * and neotimer in dynamically generated states
 * and timer objects. 
 * 
 * Because these are dynamically generated
 * the compiler can't really determine the 
 * correct memory usage and the microcontroller
 * will crash after a given quantity of states.
 * 
 * Currently more than 25 states crashes the micro
 * 
 ******************************************/
#include <neotimer.h>
#include <StateMachine.h>

#define STATES 25

StateMachine machine = StateMachine();
State* states[STATES];
Neotimer timers[STATES];

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  
  for(int i=0; i<STATES; i++){
    int randomDuration = random(500,3000);
    Serial.print("Duration ");
    Serial.print(i);
    Serial.print(" ");
    Serial.println(randomDuration);
    timers[i]= Neotimer(randomDuration);

    // Add a state to the machine with code to display currentState
    states[i] = machine.addState(&stateLogic);
    
    /*  LAMBDA STATE
      states[i] = machine.addState([](){
      if(machine.executeOnce){
        Serial.print("State ");
        Serial.print(machine.currentState);
        Serial.println(" Execute Once");
        timers[machine.currentState].stop();
        timers[machine.currentState].start();
      }
    });*/
    

    // Add a transition to the state, for the next state
    states[i]->addTransition(&stateTransition, (i==(STATES-1)) ? 0 : i+1);
    
    /*  LAMBDA TRANSITION
    states[i]->addTransition([](){
      return (timers[machine.currentState].done())?true:false;
    },(i==(STATES-1)) ? 0 : i+1);
    */
  }
 
}

void loop(){
  machine.run();  
}


/******************************************
 * Functions to be used as State logic 
 * and transitions logic
 * if not using lambda functions.
 ******************************************/

void stateLogic(){
  if(machine.executeOnce){
    Serial.print("State ");
    Serial.print(machine.currentState);
    Serial.println(" Execute Once");
    timers[machine.currentState].stop();
    timers[machine.currentState].start();
  }
}

bool stateTransition(){
  return (timers[machine.currentState].done())?true:false;
}
