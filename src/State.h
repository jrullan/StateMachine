#include <LinkedList.h>

#ifndef _STATE_H
#define _STATE_H

/*
 * Transition is a structure that holds the address of 
 * a function that evaluates whether or not not transition
 * from the current state and the number of the state to transition to
 */
typedef struct Transition{
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

	void addTransition(bool (*c)(), State* s);
    void addTransition(bool (*c)(), int stateNumber);
    int evalTransitions();
    int execute();
    int setTransition(int index, int stateNumber);	//Can now dynamically set the transition
	
    // stateLogic is the pointer to the function
    // that represents the state logic
    void (*stateLogic)();
    LinkedList<struct Transition*> *transitions;
	int index;
};

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
 * -1 if none evaluate to true
 */
int State::evalTransitions(){
  if(transitions->size() == 0) return -1;
  bool result = false;
  
  for(int i=0;i<transitions->size();i++){
    result = transitions->get(i)->conditionFunction();
    if(result == true){
      return transitions->get(i)->stateNumber;
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


#endif
