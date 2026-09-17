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
    // folding expressions are crazy man. 
    
}

class Timer {

    public:

    using Nanos = std::chrono::nanoseconds;
    using Micros = std::chrono::microseconds;
    using Millis = std::chrono::milliseconds;
    using Seconds = std::chrono::seconds;
    using Minutes = std::chrono::minutes;
    using Hours = std::chrono::hours;

    private:
    template<typename T>
    static inline constexpr bool IsValidTimeUnit() {return IsValidUnit<T,Nanos,Micros,Millis,Seconds,Minutes,Hours>;}
    // after testing this out, it seems that it still returns true if T is something like std::chrono::seconds.. which I dont want.
    // will fix later if I have time.



    std::chrono::time_point<std::chrono::steady_clock> TimeSinceCheck;

    public:

    Timer() : TimeSinceCheck(std::chrono::steady_clock::now()) {}

    inline void restart() {TimeSinceCheck= std::chrono::steady_clock::now();}

    template <typename T> 
    inline uint64_t click() {
        static_assert(IsValidTimeUnit<T>()); // making sure T is one of the alias' above.
        const auto OldTimePoint = TimeSinceCheck;
        restart();
        return std::chrono::duration_cast<T>(TimeSinceCheck - OldTimePoint).count();
    }

    template <typename T>
    inline uint64_t glance() const {
        static_assert(IsValidTimeUnit<T>());
        const auto CurrentPoint = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<T>(CurrentPoint - TimeSinceCheck).count();
    }



};