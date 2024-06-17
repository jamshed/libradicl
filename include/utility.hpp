
#ifndef UTILITY_HPP
#define UTILITY_HPP



#include <atomic>


// A lightweight lock-free mutex class.
// It is based on `std::atomic_flag`, which is guaranteed to be a lock-free atomic construct .
// Reference: https://en.cppreference.com/w/cpp/atomic/atomic_flag
class Spin_Lock
{
private:

    std::atomic_flag lock_ = ATOMIC_FLAG_INIT;


public:

    // Acquires the lock for mutually-exlcusive access to it.
    void lock();

    // Releases the lock, giving up the exclusive access to it.
    void unlock();
};


// Wrapper class for a data-element of type `T_` to ensure that in a linear
// collection of `T_`'s, each element is aligned to a cache-line boundary.
template <typename T_>
class alignas(2 * L1_CACHE_LINE_SIZE)
    Padded_Data
{
private:

    T_ data_;


public:

    Padded_Data()
    {}

    Padded_Data(const T_& data):
      data_(data)
    {}

    Padded_Data(T_&& data):
        data_(std::move(data))
    {}

    T_& data() { return data_; }

    const T_& data() const { return data_; }
};


inline void Spin_Lock::lock()
{
    // Due to the memory access order `memory_order_acquire`, no reads or writes in the current thread can be
    // reordered before this load of the variable `lock_` (enforced by the compiler and the processor) —
    // ensuring that memory-access instructions after a `lock` invokation stays after it.

    while(lock_.test_and_set(std::memory_order_acquire))
        ;// while(lock_.test(std::memory_order_relaxed));   // C++20 optimization to avoid the redundant stores from the spinning `test_and_set`.
}


inline void Spin_Lock::unlock()
{
    // Due to the memory access order `memory_order_release`, no reads or writes in the current thread can be
    // reordered after this store of the variable `lock_` (enforced by the compiler and the processor) —
    // ensuring that memory-access instructions before an `unlock` invokation stays before it.

    lock_.clear(std::memory_order_release);
}



#endif
