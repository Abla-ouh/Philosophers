<h1 align="center">
	📖 Philosophers
</h1>

<p align="center">
	<b><i>Basics of process threading, and how work on the same memory space.</i></b><br>
</p>
<p align="center">
<img alt="ph" src="https://www.en-attendant-nadeau.fr/wp-content/uploads/2019/05/voltaire_categorie.jpg" />
</p>

Philosophers is a project at [42](https://www.42.fr/42-network/) which covers the basics of process threading, and how to work on the same memory space. And learn about mutexes, semaphores, and shared memory. It is also a problem solving project of the fameous "The dinning philosophers". 

## the dining philosophers problem :
In computer science, the dining philosophers problem is an example problem often used in concurrent algorithm design to illustrate synchronization issues and techniques for resolving them.

It was originally formulated in  _1965 by Edsger Dijkstra_  as a student exam exercise, presented in terms of computers competing for access to tape drive peripherals. Soon after, Tony Hoare gave the problem its present formulation

### The scene :

There are N philosphers sitting around a circular table eating spaghetti and discussing philosophy. The problem is that **each philosopher needs 2 forks to eat, and there are only N forks, one between each 2 philosophers**. Design an algorithm that the philosophers can follow that insures that none starves as long as each philosopher eventually stops eating, and such that the maximum number of philosophers can eat at once.

<p align="center">
<img alt="ph" src="https://static.javatpoint.com/operating-system/images/os-dining-philosophers-problem2.png" />
</p>

## Installation🖥️

 1. choose a folder, the mandatory or the bonus part.
 2. Execute `make`
 3. Test the project using an executable.
 #### Usage :
 `./philo number_philosopher time_to_die time_to_eat time_to_sleep [number_of_time_each_philosophers_must_eat]` arguments in square brackets are not required (number_of_time_each_philosophers_must_eat)
 **exemple :**

`./philo_zero -v 4 500 200 200`

---

# Ressouces :
- https://www.codequoi.com/en/threads-mutexes-and-concurrent-programming-in-c/
- https://medium.com/swlh/the-dining-philosophers-problem-solution-in-c-90e2593f64e8
- [UNIX Threads in C](https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2)
---
> ⚠️  Warning: Don't copy/paste code you don't understand: it's bad for you, and for the school.
