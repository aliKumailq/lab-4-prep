#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <type_traits>
#endif  // TIMER_H

//template <typename >
//bool IsValidTimeUnit = 

namespace {
    // an unnamed namespace automatically makes everything inside static.

    template <typename T, typename... Units>
    constexpr bool IsValidUnit = (std::is_same<T, Units>::value ||...); // for checking that the inserted type for click() and glance() are valid.
    // also folding expressions are crazy man. 
    
}

class Timer {

    using Nanos = std::chrono::nanoseconds;
    using Micros = std::chrono::microseconds;
    using Millis = std::chrono::milliseconds;
    using Seconds = std::chrono::seconds;
    using Minutes = std::chrono::minutes;
    using Hours = std::chrono::hours;

    template<typename T>
    inline constexpr bool IsValidTimeUnit() {return IsValidUnit<T,Nanos,Micros,Millis,Seconds,Minutes,Hours>;}



    std::chrono::time_point<std::chrono::steady_clock> TimeSinceCheck;

    Timer() {}

    inline void restart() {TimeSinceCheck= std::chrono::steady_clock::now();}

    template <typename T> 
    inline uint64_t click() {
        static_assert(IsValidTimeUnit<T>); // making sure T is one of the alias' above.
        const auto OldTimePoint = TimeSinceCheck;
        TimeSinceCheck = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<T>(TimeSinceCheck - OldTimePoint);
    }

    template <typename T>
    inline uint64_t glance() const {
        static_assert(IsValidTimeUnit<T>);
        const auto CurrentPoint = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<T>(CurrentPoint - TimeSinceCheck);
    }



};