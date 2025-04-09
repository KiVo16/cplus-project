//
// Created by Jakub Kurek on 08/04/2025.
//

#ifndef TIMER_H
#define TIMER_H
#include <functional>
#include <thread>


class Timer {
public:
    Timer();
    ~Timer();

    // Start the timer by supplying a callable and the time interval between calls
    void start(const std::function<void()>& func, std::chrono::milliseconds interval);

    // Stop the timer if it is running
    void stop();

private:
    std::atomic<bool> running;  // Flag to indicate whether the timer is running
    std::thread worker;         // The thread that runs the timer task
};


#endif //TIMER_H
