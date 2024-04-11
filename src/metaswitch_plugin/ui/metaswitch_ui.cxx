// ui/metaswitch_ui.cxx
#include <iostream>
#include <string>
#include <vector>
#include <obs-module.h>

class MetaSwitchUI {
private:
    std::vector<std::string> deviceNames;
    int currentDeviceIndex;
    int countdownDuration;
    std::string timerPosition;

public:
    MetaSwitchUI() : currentDeviceIndex(0), countdownDuration(10), timerPosition("bottom-right") {}

    void showUI() {
        std::cout << "Displaying MetaSwitch Plugin UI\n";
        configureDevices();
        configureTimer();
    }

    void configureDevices() {
        deviceNames.clear();
        obs_enum_video_devices([](void* data, const char* device_id, const char* device_name) {
            std::vector<std::string>* names = static_cast<std::vector<std::string>*>(data);
            names->push_back(device_name);
            return true;  // Continue enumeration
        }, &deviceNames);

        if (deviceNames.empty()) {
            std::cout << "No available devices found.\n";
        } else {
            std::cout << "Available Devices:\n";
            for (auto& name : deviceNames) {
                std::cout << " - " << name << std::endl;
            }
        }
    }

    void setTimerPosition(const std::string& position) {
        timerPosition = position;
        std::cout << "Countdown timer position set to: " << timerPosition << std::endl;
    }

    void setCountdownDuration(int duration) {
        countdownDuration = duration;
        std::cout << "Countdown duration set to: " << countdownDuration << " seconds\n";
    }

    void configureTimer() {
        std::cout << "Configuring timer...\n";
        std::cout << "Timer will be displayed at: " << timerPosition << "\n";
        std::cout << "Timer countdown set for: " << countdownDuration << " seconds until the next switch.\n";
    }
};


bool obs_module_load() {
    static MetaSwitchUI ui;
    ui.showUI();
    return true;
}

void obs_module_unload() {
    delete ui;
}
