#include <iostream>
#include <random>
#include <chrono>
#include <thread>

#include "TrafficLight.h"

namespace chrono = std::chrono;

/* Implementation of class "MessageQueue" */

/* 
template <typename T>
T MessageQueue<T>::receive()
{
    // FP.5a : The method receive should use std::unique_lock<std::mutex> and _condition.wait() 
    // to wait for and receive new messages and pull them from the queue using move semantics. 
    // The received object should then be returned by the receive function. 
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // FP.4a : The method send should use the mechanisms std::lock_guard<std::mutex> 
    // as well as _condition.notify_one() to add a new message to the queue and afterwards send a notification.
}
*/

/* Implementation of class "TrafficLight" */

/* 
void TrafficLight::waitForGreen()
{
    // FP.5b : add the implementation of the method waitForGreen, in which an infinite while-loop 
    // runs and repeatedly calls the receive function on the message queue. 
    // Once it receives TrafficLightPhase::green, the method returns.
} */

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases()
{
    std::uniform_real_distribution<double> ufd(4.0, 6.0);
    std::default_random_engine rng;
    auto cycleDuration = ufd(rng);
    
    auto start = chrono::high_resolution_clock::now();
    auto end = chrono::high_resolution_clock::now();
    auto elapsed = end - start;
    
    while (true) {
        std::this_thread::sleep_for(chrono::milliseconds(1));
        end = chrono::high_resolution_clock::now();
        if (elapsed.count() > cycleDuration) {
            start = chrono::high_resolution_clock::now();
            _currentPhase = _currentPhase ? GREEN : RED;
        }
    }

}

