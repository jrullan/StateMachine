#include "State.h"

State::State(){
  transitions = new LinkedList<struct Transition*>();
};

State::~State(){};

/*
 * Adds a transition structure to the list of transitions
 * for this state.
 * Params:
 * conditionFunction is the address of a function that will be evaluated
 * to determine if the transition occurs
 * state is the state to transition to
 */
void State::addTransition(bool (*conditionFunction)(), State* s){
  struct Transition* t = new Transition{conditionFunction,s->index};
  transitions->add(t);
}

/*
 * Adds a transition structure to the list of transitions
 * for this state.
 * Params:
 * conditionFunction is the address of a function that will be evaluated
 * to determine if the transition occurs
 * stateNumber is the number of the state to transition to
 */
void State::addTransition(bool (*conditionFunction)(), int stateNumber){
  struct Transition* t = new Transition{conditionFunction,stateNumber};
  transitions->add(t);
}

/*
 * Evals all transitions sequentially until one of them is true.
 * Returns:
 * The stateNumber of the transition that evaluates to true
 * -1 if none evaluate to true ===> Returning index now instead to avoid confusion between first run and no transitions
 */
int State::evalTransitions(){
  if(transitions->size() == 0) return index;
  bool result = false;
  
  for(int i=0;i<transitions->size();i++){
    result = transitions->get(i)->conditionFunction();
    if(result == true){
      return transitions->get(i)->stateNumber;
    }
  }
  return index;
}

/*
 * Execute runs the stateLogic and then evaluates
 * all available transitions. The transition that
 * returns true is returned.
 */
int State::execute(){
  stateLogic();
  return evalTransitions();
}

/*
 * Method to dynamically set a transition
 */
int State::setTransition(int index, int stateNo){
	if(transitions->size() == 0) return -1;
	transitions->get(index)->stateNumber = stateNo;
	return stateNo;
}