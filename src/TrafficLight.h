#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <mutex>
#include <deque>
#include <condition_variable>
#include "TrafficObject.h"

// forward declarations to avoid include cycle
class Vehicle;

template <class T>
class MessageQueue {
    public:
        void send(T &&message) {
            std::lock_guard<std::mutex> guard(_mutex);
            _queue.push_back(std::move(message));

            cond.notify_one();
        };

        T receive() {
            std::unique_lock<std::mutex> lock(_mutex);
            cond.wait(lock, [this] { return !_queue.empty(); });

            T green = std::move(_queue.back());
            _queue.clear();

            return green;
        };

    private:
        std::deque<T> _queue;
        std::condition_variable cond;
        std::mutex _mutex;
};


class TrafficLight : TrafficObject
{
    public:

    enum TrafficLightPhase { RED, GREEN };
    // getters / setters

    void waitForGreen();
    void simulate() { threads.emplace_back(std::thread(&TrafficLight::cycleThroughPhases, this)); };
    TrafficLightPhase getCurrentPhase() { return _currentPhase; };

    private:
        void cycleThroughPhases();


        MessageQueue<TrafficLightPhase> _phases;
        std::condition_variable _condition;
        std::mutex _mutex;
        TrafficLightPhase _currentPhase{TrafficLightPhase::RED};
};

#endif