#pragma once

#include <chrono>
#include <iostream>

// Utility classes
namespace utils
{
        // Helper Timer Class using std::chrono
        class timer
        {
        private:
                std::chrono::time_point<std::chrono::steady_clock> start_time;
                std::chrono::time_point<std::chrono::steady_clock> end_time;

                void reset()
                {
                        start_time = std::chrono::steady_clock::now();
                        end_time = std::chrono::steady_clock::now();
                }

        public:
                timer() { reset(); }

                void start() { reset(); }

                void stop() { end_time = std::chrono::steady_clock::now(); }

                void print_reading()
                {
                        const auto interval =
                            std::chrono::duration_cast<std::chrono::microseconds>(
                                end_time - start_time);

                        std::cout << "Time Reading: " << interval.count()
                                  << "microseconds"
                                  << "\n";
                }
        };

} // namespace utils
