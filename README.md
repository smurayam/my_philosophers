*This project has been created as part of the 42 curriculum by smurayam.*

## Description
This project is a simulation of the classic Dining Philosophers problem, designed to introduce the basics of multi-threading and process synchronization. The core objective is to learn how to create threads, implement mutexes, and effectively manage shared resources to avoid concurrent programming pitfalls such as deadlocks and data races.

In this simulation, a number of philosophers sit at a round table with a large bowl of spaghetti in the middle. They cycle through three states: eating, sleeping, and thinking. Since a philosopher requires two forks to eat, they must pick up both the fork to their left and the fork to their right. The simulation stops immediately if a philosopher dies of starvation, or voluntarily if an optional meal count condition is reached for all philosophers.

## Instructions

### Compilation
To compile the mandatory program, navigate to the directory containing the `Makefile` and execute the following command:
```bash
make

```

This compiles the source files with the required `-Wall -Wextra -Werror` flags and generates the executable named `philo`.

### Execution

The program accepts the following command-line arguments:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

```

* **number_of_philosophers**: The number of philosophers and also the number of forks.
* **time_to_die** (in milliseconds): If a philosopher hasn't started eating within this time since their last meal or the start of the simulation, they die.
* **time_to_eat** (in milliseconds): The time it takes for a philosopher to eat (during which they hold two forks).
* **time_to_sleep** (in milliseconds): The time a philosopher spends sleeping.
* **number_of_times_each_philosopher_must_eat** (optional): If all philosophers have eaten at least this many times, the simulation stops.

#### Example Usage

To run a simulation with 4 philosophers, where a philosopher dies if they do not eat within 410ms, takes 200ms to eat, and 200ms to sleep:

```bash
./philo 4 410 200 200

```

## Resources

### References

* [Peer's Explanation Slide for Philosophers](https://docs.google.com/presentation/d/1pvkJ_ZJ0KfrttQftwaeoXVyUBjTm4TT5rleXLlbbArQ/edit?usp=drivesdk)
* [42 Discord Server - Philosophers Channel](https://discord.com/channels/691903146909237289/749128558902771722)
* [Qiita Article: 42 Philosophers Project Reference](https://qiita.com/42yliu/items/86d16cdbc584c250ca6e)

### AI Usage Disclosure

In accordance with the 42 curriculum guidelines, AI tools were utilized during the development of this project for the following specific tasks:

* **Project Comprehension**: Assisted in breaking down and understanding the complex subject requirements and multi-threading concepts.
* **Naming Conventions**: Provided suggestions and brainstorming support for function and variable naming to ensure clarity, readability, and compliance with the 42 Norm.
* **Code Review**: Used to review the codebase to confirm logical structure, identify potential issues, and ensure proper implementation of synchronization mechanisms.

```
