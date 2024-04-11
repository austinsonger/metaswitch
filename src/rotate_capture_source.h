// rotate_capture_source.h
#pragma once
// LOCATION: /src/
#include <obs-module.h>

struct rotate_capture_data {
    obs_source_t *source;  // Reference to the OBS source itself, useful for API calls.
    char **device_ids;     // Array of device IDs or names to rotate through.
    size_t device_count;   // Number of devices in the rotation.
    size_t current_device_index; // Index of the currently active device.
    uint64_t rotation_interval_ms; // Rotation interval in milliseconds.
    pthread_mutex_t mutex; // Mutex for thread-safe access to the structure.
    uint64_t last_switch_time_ms; // Last time the device was switched, to manage rotation timing.
    // Optional: fields for device-specific settings, like resolution or framerate.
} rotate_capture_data_t;


// Function declarations for source lifecycle management
const char *rotate_capture_get_name(void *unused);
void *rotate_capture_create(obs_data_t *settings, obs_source_t *source);
void rotate_capture_destroy(void *data);
// Declare any additional functions needed for your source
