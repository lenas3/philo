*This project has been created as part of the 42 curriculum by asay.*

## Description
Philosophers project is about the classic "Dining Philosophers Problem" and it basically aims to teach about threads, mutexes and deadlock.

In dining philosophers problem, there are n philosophers sitting on a round table and each philosopher has one fork next to them. In total there are n forks on the table. A philosopher needs two forks to eat. This means each philosopher also needs the fork that belongs to the philosopher next to them. But when a philosopher takes one fork, that fork gets locked using a mutex. This way two philosophers sitting side by side, can't eat at the same time. In this project, the goal is to synchronize the threads,which represent the philosophers, without a data race. As a result philosophers, won't die and continue their life cycle (eat->sleep->think).

## Instructions
To run philosophers project:
1. Clone the repository.
2. Go to the root of the repo and run 'make' command.
3. Run this format: ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
   * <number_of_philosophers>: Number of philosophers also number of forks.
   * <time_to_die>: If a philosopher has not eaten for <time_to_die> ms since the start of their last meal or the start of the simulation, the philosopher dies and the simulation ends.
   *  <time_to_eat>: The time in ms it takes a philosopher to eat.
   *  <time_to_sleep>: The time in ms a philosopher sleeps.
   *  [number_of_times_each_philosopher_must_eat] _(optional argument)_: If this argument is given   simulation stops if all philosophers have eaten at least [number_of_times_each_philosopher_must_eat] times. If argument is not given simulation stops when a philosopher dies.
   
## Resources
- A video that explains the philosophers problem and the functions we're allowed to use:  
  https://youtu.be/UGQsvVKwe90?si=0D7FDIQm0ugyilVi
- An article about mutexes and semaphores:  
  https://www.geeksforgeeks.org/operating-systems/mutex-vs-semaphore/
- A guide to the Dining Philosophers problem for 42 students:
  https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2
- A video about Dining Problem and explains how life cycle works:
  https://www.youtube.com/watch?v=FYUi-u7UWgw

----------------------------------------------------------
- Using AI
    
Before starting the project, I usually draw a blueprint to understand the overall structure. During this phase, I use AI to help me understand the project requirements and concepts, alongside searching YouTube and Google for resources. I also use AI to look up the allowed functions and understand what they do. After writing the code, I try to debug it on my own first.
During this project, I encountered timing issues caused by incorrect millisecond values in sleep functions, which led to philosophers sleeping too long or too short. Since the root cause was technical rather than architectural, these bugs were difficult to identify on my own and AI helped me spot them. Additionally, since this was my first time dealing with deadlock, I used AI to help me interpret the flag outputs during debugging.
  
