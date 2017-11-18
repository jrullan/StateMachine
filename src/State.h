#include <LinkedList.h>

#ifndef _STATE_H
#define _STATE_H

const bool DEBUG = false;

/*
 * Transition is a structure that holds the address of 
 * a function that evaluates whether or not not transition
 * from the current state and the number of the state to transition to
 */
typedef struct transition{
  bool (*conditionFunction)();
  int stateNumber;
};

/*
 * State represents a state in the statemachine. 
 * It consists mainly of the address of the function
 * that contains the state logic and a collection of transitions 
 * to other states.
 */
class State{
  public:
    State();
    ~State();

    void addTransition(bool (*c)(), int stateNumber);
    int evalTransitions();
    int execute();
    
    // stateLogic is the pointer to the function
    // that represents the state logic
    void (*stateLogic)();
    LinkedList<struct transition> *transitions;
};

State::State(){
  transitions = new LinkedList<struct transition>();
};

State::~State(){};

/*
 * Adds a transition structure to the list of transitions
 * for this state.
 * Params:
 * conditionFunction is the address of a function that will be evaluated
 * to determine if the transition occurs
 * stateNumber is the number of the state to transition to
 */
void State::addTransition(bool (*conditionFunction)(), int stateNumber){
  if(DEBUG) Serial.println("Adding a transition");
  struct transition t = {conditionFunction,stateNumber};
  transitions->add(t);
}

/*
 * Evals all transitions sequentially until one of them is true.
 * Returns:
 * The stateNumber of the transition that evaluates to true
 * -1 if none evaluate to true
 */
int State::evalTransitions(){
  if(transitions->size() == 0) return -1;
  bool result = false;
  
  if(DEBUG) Serial.print("Evaluating ");
  if(DEBUG) Serial.print(transitions->size());
  if(DEBUG) Serial.println(" transitions.");
  
  for(int i=0;i<transitions->size();i++){
    if(DEBUG) Serial.print("Transition ");
    if(DEBUG) Serial.print(i);
    if(DEBUG) Serial.print(" result = ");
    result = transitions->get(i).conditionFunction();
    if(result == true){
      if(DEBUG) Serial.println("true");
      return transitions->get(i).stateNumber;
    }else{
      if(DEBUG) Serial.println("false");
    }
  }
  return -1;
}

/*
 * Execute runs the stateLogic and then evaluates
 * all available transitions. The transition that
 * returns true is returned.
 */
int State::execute(){
  if(DEBUG) Serial.println("Executing stateLogic()");
  stateLogic();
  if(DEBUG) Serial.println("Executing evalTransitions()");
  return evalTransitions();
}

#endif
