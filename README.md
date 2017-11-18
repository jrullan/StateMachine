# neotimer
Non blocking timer class for Arduino. 

When you use a delay() function in an Arduino sketch, the processor stops everything it is doing until this delay is completed. That is called a blocking delay, because it blocks the processor until it finishes. Many times we don't want this to happen. This timer provides a way to use time delays without blocking the processor, so it can do other things while the timer ends up. This is called a non-blocking delay timer.

The timer provides basic functionality to implement different ways of timing in a sketch. There are two main ways to use the timer, first as a Start-Stop-Reset timer.

### Start-Stop-Reset Mode
When you create an instance of the timer you must specify the preset value of the timer. Then you call start() whenever you want the timer to start. If you want to know if the timer has ended you check for done(). See the example below.

```c++
Neotimer mytimer = Neotimer(1000); // 1 second timer

void setup(){
  Serial.begin(9600);
  mytimer.start();
}

void loop(){
  if(mytimer.done()){
    Serial.println("Timer finished");
  }
  
  if(mytimer.waiting()){
    //...execute this code while the timer reaches done()
  }
}
```
You can use the waiting() function to check if the timer has been started but it's not done. 
The stop() command is used to stop the timer momentarily and it returns the elapsed time since the start() was given. 
In the start-stop mode reset() initializes the timer to start from the beginning. 

In this mode the timer will keep on counting past the done() event until you call the stop() and reset(). This allows the flexibility to use it to count the time required for some external condition to become true. For example,

```c++
void loop(){
  if(digitalRead(BTN1)==HIGH){
    mytimer.start();
  }
  
  if(digitalRead(BTN1)==LOW){
    Serial.print("BTN1 pressed for ");
    Serial.print(mytimer.stop());
    Serial.println(" milliseconds.");
    mytimer.reset();
  }
}
```

### Repeat mode
A convenient way to use the timer is to use the repeat(delay) mode. In this mode you specify the delay in the repeat() call and it will return true when done, and false if it isn't done. It automatically resets so it is a good way to repeat some task periodically. Remember, it is non-blocking so the program will skip the code when the timer is not done.

```c++
void loop(){
  if(mytimer.repeat(2000)){
    Serial.println("Calling this periodically each two seconds");
    digitalWrite(D13,!digitalRead(D13)); // Let's blink each two seconds
  }
}
```
