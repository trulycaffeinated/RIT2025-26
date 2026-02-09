# Lab 3 Important Points
Every **Hardware Device** is  accessed only within one task - a single task to output/input

All **Local Variables** for tasks are *similar* to static variables
**Static** - variable retains value from previous function run
- These variables are allocated on the stack for the task
- Remember, each task has its own stack
- One characteristic of a static variable we must always do is give it an initial value
- Local variables that aren't initialized get whatever happens to be on the stack