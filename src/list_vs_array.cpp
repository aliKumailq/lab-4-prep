#include <cstddef>  // size_t

#include "timer.h"

#include <iostream>
#include <thread>
#include <random>
#include <list>

constexpr size_t SIZE = 16000000;
constexpr size_t SEED = 0;
using TIME_FORMAT = Timer::Micros;

template <typename T, typename ItemType>
inline void append_time(T& container, const ItemType& item);

template <typename U>
inline void append_time(std::vector<U>& container, const U& item) {
    container.push_back(item);

}

template <typename T>
inline void append_time(std::list<T>& container, const T& item) {
    container.push_back(item);

}


template <typename ContainerType, typename ItemType, typename TimeFormat, size_t Size>
inline uint64_t sum_container(ContainerType& container) {
    ItemType sum = 0;
    Timer sum_timer;
    for (const auto& item : container) sum += item;
    return sum_timer.click<TimeFormat>();
}




template <typename ContainerType, typename ItemType,typename TimeFormat ,size_t Size>
inline uint64_t fill_container(ContainerType& container) {
    std::mt19937_64 rng(SEED);
    Timer fill_timer;
    for (size_t i = 0; i < Size; ++i) append_time(container, rng()) ; 
    return fill_timer.click<TimeFormat>();
}

int main() {
    using vectorsizeT = std::vector<size_t>;
    using listsizeT = std::list<size_t>;

    uint64_t  time_to_fill_unreserved_vector, time_to_sum_unreserved_vector;
    uint64_t time_to_fill_reserved_vector,time_to_sum_reserved_vector;
    uint64_t time_to_fill_list,time_to_sum_list;

    {
    vectorsizeT v;
     time_to_fill_unreserved_vector = fill_container<vectorsizeT, size_t, TIME_FORMAT, SIZE>(v);
     time_to_sum_unreserved_vector = sum_container<vectorsizeT, size_t, TIME_FORMAT, SIZE>(v);
    }

    { // I know I could just v.clear() to remove all elements while keeping the reserved memory, but I want to be safe just to make sure its a fair comparison.
        vectorsizeT v;
        v.reserve(SIZE);
        time_to_fill_reserved_vector = fill_container<vectorsizeT, size_t, TIME_FORMAT, SIZE>(v);
        time_to_sum_reserved_vector = sum_container<vectorsizeT, size_t, TIME_FORMAT, SIZE>(v);
    }
    {
        listsizeT l;
        time_to_fill_list = fill_container<listsizeT, size_t, TIME_FORMAT, SIZE>(l);
        time_to_sum_list = sum_container<listsizeT, size_t, TIME_FORMAT, SIZE>(l);
    }

    auto print_stats = [](const char* type_name, uint64_t fill_time, uint64_t sum_time) -> void {
        std::cout << type_name << ": " <<  "fill=" << fill_time << "micro-s" << ", " << "sum=" << sum_time << "ms\n";
    };

    print_stats("unreserved vector", time_to_fill_unreserved_vector, time_to_sum_unreserved_vector);
    print_stats("reserved vector", time_to_fill_reserved_vector, time_to_sum_reserved_vector);
    print_stats("list", time_to_fill_list, time_to_sum_list);


}
