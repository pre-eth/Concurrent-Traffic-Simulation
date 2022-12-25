#include <iostream>
#include <random>
#include <chrono>
#include <thread>

#include "TrafficLight.h"

namespace chrono = std::chrono;

void TrafficLight::waitForGreen() {
    auto phase = TrafficLight::RED; // aka 0
    while (!phase) {
        // enum where GREEN = 1
        phase = _phases.receive();
    }
} 

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases() {
    std::uniform_real_distribution<double> ufd(4.0, 6.0);
    std::default_random_engine rng;
    auto cycleDuration = ufd(rng);
    
    auto start = chrono::high_resolution_clock::now();
    auto elapsed = chrono::high_resolution_clock::now() - start;
    
    while (1) {
        std::this_thread::sleep_for(chrono::milliseconds(120));
        elapsed = chrono::high_resolution_clock::now() - start;
        if (elapsed.count() > cycleDuration) {
            start = chrono::high_resolution_clock::now();
            _currentPhase = _currentPhase ? GREEN : RED;
            _phases.send(std::move(_currentPhase));
        }
    }

}

