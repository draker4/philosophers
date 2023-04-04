# philosophers
8th 42 school's project.
This programs takes five arguments (in milliseconds) : number_of_philosophers, time_to_die, time_to_eat, time_to_sleep, number_of_times_each_philosopher_must_eat. All philosophers are sitting down in circle at the same table.
There is a fork for each philosopher. They have to take two forks, eat, put down the forks, sleep, and do this again. They can't eat with just one fork and so have to wait to have both to eat.
If there last meal is more than time_to_die milliseconds, they die and the program stops.
Each philospher has to be a thread and each fork is a mutex.
In the bonus part, each philosopher is a process and a semaphore is used for the forks.
