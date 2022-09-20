#include "StateMachine.h"

StateMachine::StateMachine(){
  stateList = new LinkedList<State*>();
};

StateMachine::~StateMachine(){};

/*
 * Main execution of the machine occurs here in run
 * The current state is executed and it's transitions are evaluated
 * to determine the next state. 
 * 
 * By design, only one state is executed in one loop() cycle.
 */
void StateMachine::run(){
  //Serial.println("StateMachine::run()");
  // Early exit, no states are defined
  if(stateList->size() == 0) return;

  // Initial condition
  if(currentState == -1){
    currentState = 0;
  }
  
  // Execute state logic and return transitioned
  // to state number. Remember the current state then check
  // if it wasnt't changed in state logic. If it was, we 
  // should ignore predefined transitions.
  int initialState = currentState;
  int next = stateList->get(currentState)->execute();
  if(initialState == currentState){
    executeOnce = (currentState == next)?false:true;
    currentState = next;
  }
}

/*
 * Adds a state to the machine
 * It adds the state in sequential order.
 */
State* StateMachine::addState(void(*functionPointer)()){
  State* s = new State();
  s->stateLogic = functionPointer;
  stateList->add(s);
  s->index = stateList->size()-1;
  return s;
}

/*
 * Jump to a state
 * given by a pointer to that state.
 */
State* StateMachine::transitionTo(State* s){
  this->currentState = s->index;
  this->executeOnce = true;
  return s;
}

/*
 * Jump to a state
 * given by a state index number.
 */
int StateMachine::transitionTo(int i){
  if(i < stateList->size()){
	this->currentState = i;
	this->executeOnce = true;
	return i;
  }
  return currentState;
}

bool StateMachine::isInState(State* s){
  return this->stateList->get(this->currentState) == s;
}
