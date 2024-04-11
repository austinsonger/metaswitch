// rotate_capture_source.h

#pragma once
// LOCATION: /src/
#include <obs-module.h>
#include <pthread.h> // Ensure this include is here for pthread_mutex_t

typedef struct rotate_capture_data {
    obs_source_t *source;  // Reference to the OBS source itself, useful for API calls.
    char **device_names;   // Array of device names to rotate through.
    size_t num_devices;    // Number of devices in the rotation.
    size_t current_index;  // Index of the currently active device.
    uint64_t rotate_interval_ms; // Rotation interval in milliseconds.
    pthread_mutex_t mutex; // Mutex for thread-safe access to the structure.
    uint64_t last_switch_time_ms; // Last time the device was switched, to manage rotation timing.
    // Optional: fields for device-specific settings, like resolution or framerate.
} rotate_capture_data_t;

// Function declarations for source lifecycle management
const char *rotate_capture_get_name(void *unused);
void *rotate_capture_create(obs_data_t *settings, obs_source_t *source);
void rotate_capture_destroy(void *data);

// Additional function declarations for OBS source functionality
uint32_t rotate_capture_getwidth(void *data);
uint32_t rotate_capture_getheight(void *data);
void rotate_capture_video_render(void *data, gs_effect_t *effect);

// If handling audio, declare the audio render callback
// void rotate_capture_audio_render(void *data, uint32_t samples_per_sec, struct obs_audio_data *audio_data);

// Declaration for any helper functions, such as device rotation logic
void rotate_to_next_device(rotate_capture_data_t *data);
