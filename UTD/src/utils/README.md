#Timer Utils

[steady_clock](https://en.cppreference.com/w/cpp/chrono/steady_clock)

*Reading*: Monotonic time source that does not jump back and forth due to Network Time Protocols / Daylight Savings
*Precision*: microseconds

_This is not the same as wall clock, it can be time since last reboot_


### To use 

```c++

// Helper Timer Class using std::chrono
utils::Timer clock_watch;
clock_watch.start();

test_code();

clock_watch.stop();
clock_watch.print_reading(utils::MICRO_SEC);


// Helper Time function
utils::time(test_code, utils::MICRO_SEC);


// Helper Timer Class RAII Style ( stops timer on exiting scope )
{
        utils::Timer_raii timer_raii("Testing set array", utils::MICRO_SEC);
        test_code();
}

/* Supported measurements
 * MICRO_SEC (default), MILLI_SEC, SEC
 */

```


## Standard Measurement Techniques apply

1. Take the average of multiple measurements
2. Measure with a sufficiently large workload to increase precision (e.g 1000 loops instead of 1 loop)
