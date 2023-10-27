#include "Timer.h"


Timer::Timer() {
    clock.restart();
    isRunning = false;
    totalTime = 0.0f;
}

void Timer::Start() {
    if (!isRunning) {
        isRunning = true;
        clock.restart();
    }
}

void Timer::Stop() {
    if (isRunning) {
        isRunning = false;
        totalTime += clock.getElapsedTime().asSeconds();
    }
}

void Timer::Reset() {
    totalTime = 0.0f;
    if (isRunning) {
        clock.restart();
    }
}

float Timer::GetTotalTime() {
    return totalTime + (isRunning ? clock.getElapsedTime().asSeconds() : 0.0f);
}

