// devices/enumerate.c
#include <stdio.h>
#include <obs-module.h>  // Include the OBS module header for OBS integration

void enumerate_devices() {
    // Initialize device enumeration logic
    printf("Enumerating video capture devices on Linux/macOS...\n");
    
    // Get the list of video capture devices
    obs_enum_video_devices([](void* data, const char* device_id, const char* device_name) {
        printf("Device ID: %s, Device Name: %s\n", device_id, device_name);
        return true;  // Continue enumeration
    }, NULL);
}