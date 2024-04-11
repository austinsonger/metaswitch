// ui/countdown_ui.cpp
#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>

class CountdownUI {
private:
    std::atomic<int> countdownTime; // Countdown time in seconds
    std::string position; // Position on the screen
    bool running; // Is the countdown running

public:
    CountdownUI(int initialTime, std::string pos)
        : countdownTime(initialTime), position(pos), running(false) {}

    // Start the countdown timer
    void start() {
        running = true;
        while (countdownTime > 0 && running) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            countdownTime--;
            render();
        }
        if (running) {
            std::cout << "Countdown completed. Switching devices..." << std::endl;
            // Here you would trigger the device switch functionality
        }
    }

    // Stop the countdown timer
    void stop() {
        running = false;
    }

    // Update the countdown timer's position
    void updatePosition(const std::string& newPosition) {
        position = newPosition;
    }

    // Render the countdown timer on the screen
    void render() {
        std::cout << "Countdown at " << position << ": " << countdownTime << " seconds remaining\n";
    }

    // Set the countdown time
    void setCountdownTime(int time) {
        countdownTime = time;
    }
};

// Example usage
int main() {
    CountdownUI countdown(10, "bottom-right"); // 10-second countdown at the bottom-right of the screen
    countdown.start(); // Start the countdown
    return 0;
}
