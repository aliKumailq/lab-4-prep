#include <cstddef>  // size_t

#include "timer.h"

#include <iostream>
#include <thread>
constexpr size_t SIZE = 16000000;

int main() {
    Timer myTimer;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << myTimer.glance<std::chrono::seconds>() << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << myTimer.glance<Timer::Seconds>() << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << myTimer.glance<Timer::Seconds>() << "\n";

    myTimer.restart();

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << myTimer.glance<Timer::Seconds>() << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << myTimer.glance<Timer::Seconds>() << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << myTimer.click<Timer::Seconds>() << "\n";
    return 0;
}
