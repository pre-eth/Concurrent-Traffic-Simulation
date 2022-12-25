#include <iostream>
#include <random>
#include <chrono>
#include <thread>

#include "TrafficLight.h"

namespace chrono = std::chrono;

void TrafficLight::waitForGreen()
{
    auto phase = TrafficLight::RED; // aka 0
    while (!phase) {
        // enum where GREEN = 1
        phase = _phases.receive();
    }
} 

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases()
{
    std::uniform_real_distribution<double> ufd(4.0, 6.0);
    std::default_random_engine rng;
    auto cycleDuration = ufd(rng);
    
    auto start = chrono::high_resolution_clock::now();
    auto end = chrono::high_resolution_clock::now();
    auto elapsed = end - start;
    
    while (1) {
        std::this_thread::sleep_for(chrono::milliseconds(1));
        end = chrono::high_resolution_clock::now();
        if (elapsed.count() > cycleDuration) {
            start = chrono::high_resolution_clock::now();
            _currentPhase = _currentPhase ? GREEN : RED;
        }

        auto phase = _currentPhase;
        _phases.send(std::move(phase));
    }

}

