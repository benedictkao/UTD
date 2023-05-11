# Timer Utils

[steady_clock](https://en.cppreference.com/w/cpp/chrono/steady_clock)

*Reading*: Monotonic time source that does not jump back and forth due to Network Time Protocols / Daylight Savings
*Precision*: microseconds

_This is not the same as wall clock, it can be time since last reboot_


### To use 

```c++
utils::timer clock_watch;

clock_watch.start();

// Do operations

clock_watch.stop();

clock_watch.print_reading(); // {number} microseconds

```


## Standard Measurement Techniques apply

1. Take the average of multiple measurements
2. Measure with a sufficiently large workload to increase precision (e.g 1000 loops instead of 1 loop)
