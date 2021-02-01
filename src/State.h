#include <LinkedList.h>

#ifndef _STATE_H
#define _STATE_H

/*
 * Transition is a structure that holds the address of 
 * a function that evaluates whether or not not transition
 * from the current state and the number of the state to transition to
 */
struct Transition{
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




#endif
