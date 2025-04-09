//
// Created by Jakub Kurek on 08/04/2025.
//

#include "Timer.h"

// Constructor: initialize the running flag to false
Timer::Timer() : running(false) {}

// Destructor: stop the timer if it's still running
Timer::~Timer() {
    stop();
}

// Start the timer with a function and time interval
void Timer::start(const std::function<void()>& func, std::chrono::milliseconds interval) {
    // Stop any existing timer before starting a new one
    stop();

    running = true;
    // Capture this pointer, the function, and interval by value in the lambda.
    worker = std::thread([this, func, interval]() {
        while (running.load()) {
            // Record the next scheduled time
            auto next_call = std::chrono::steady_clock::now() + interval;
            // Execute the provided function
            func();

            // Sleep until the next scheduled execution time
            std::this_thread::sleep_until(next_call);
        }
    });
}

// Stop the timer and join the thread if it is joinable
void Timer::stop() {
    running = false;
    if (worker.joinable()) {
        // Prevent deadlock by checking if we're not in the worker thread.
        if (worker.get_id() != std::this_thread::get_id()) {
            worker.join();
        } else {
            // If for some reason stop() is called from within the worker thread,
            // detach the thread instead.
            worker.detach();
        }
    }
}