#ifndef TIMER_H
#define TIMER_H
#include <functional>
#include <thread>


class Timer {
public:
    Timer();

    ~Timer();

    /**
     * starts the timer
     * @param func anonymous function called in interval
     * @param interval interval defines in milliseconds
     */
    void start(const std::function<void()> &func, std::chrono::milliseconds interval);

    /**
     * stop the timer if it is running
     */
    void stop();

private:
    /// flag indicating whether timer is running
    std::atomic<bool> running;

    /// thread running the timer task
    std::thread worker;
};


#endif //TIMER_H
