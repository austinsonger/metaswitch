// ui/countdown_ui.cpp
#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>

class CountdownUI {
private:
    std::atomic<int> countdownTime; // Countdown time in seconds
    std::atomic<bool> running; // Is the countdown running
    std::string position; // Position on the screen

public:
    CountdownUI(int initialTime, std::string pos)
        : countdownTime(initialTime), position(pos), running(false) {}

    void start() {
        running = true;
        while (countdownTime > 0 && running) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            countdownTime--;
            render();
        }
        if (running) {
            std::cout << "Countdown completed. Switching devices..." << std::endl;
            // Trigger device switch functionality or notify observers
        }
    }

    void stop() {
        running = false;
    }

    void updatePosition(const std::string& newPosition) {
        position = newPosition;
    }

    void render() {
        std::cout << "Countdown at " << position << ": " << countdownTime.load() << " seconds remaining\n";
    }

    void setCountdownTime(int time) {
        countdownTime = time;
    }
};

int main() {
    CountdownUI countdown(10, "bottom-right");
    countdown.start();
    return 0;
}
