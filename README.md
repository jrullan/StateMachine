# StateMachine
This library implements a basic State Machine. The state logic and its transition's conditions are implemented as functions in your sketch for flexibility. The machine is intended to be deterministic, meaning that you can only be in one state at the time and transitions should occur only when your transition condition functions return true. Please note that if multiple transitions are defined for a state the first one to evaluate to true is the one that modifies the current state. The 

This implementation relies on LinkedList (https://github.com/ivanseidel/LinkedList) to implement the collection of states and the collection of transitions for a state.
