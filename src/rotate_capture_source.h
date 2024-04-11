// rotate_capture_source.h

#pragma once
// LOCATION: /src/
#include <obs-module.h>
#include <pthread.h> // Ensure this include is here for pthread_mutex_t

typedef struct rotate_capture_data {
    obs_source_t *source;           // Reference to the OBS source itself, useful for API calls.
    char **device_names;            // Array of device names to rotate through.
    size_t num_devices;             // Number of devices in the rotation.
    size_t current_index;           // Index of the currently active device.
    uint64_t rotate_interval_ms;    // Rotation interval in milliseconds.
    pthread_mutex_t mutex;          // Mutex for thread-safe access to the structure.
    uint64_t last_switch_time_ms;   // Last time the device was switched, to manage rotation timing.
} rotate_capture_data_t;

// Standard OBS source lifecycle functions
const char *rotate_capture_get_name(void *unused);
void *rotate_capture_create(obs_data_t *settings, obs_source_t *source);
void rotate_capture_destroy(void *data);
uint32_t rotate_capture_getwidth(void *data);
uint32_t rotate_capture_getheight(void *data);
void rotate_capture_video_render(void *data, gs_effect_t *effect);

// Additional function prototypes
void rotate_to_next_device(rotate_capture_data_t *data); // Logic to rotate to the next device
void enumerate_video_capture_devices(char ***device_names, size_t *num_devices); // Device enumeration logic
void initialize_rotation_timer(rotate_capture_data_t *data); // Initializes and manages rotation timing
void cleanup_rotation_timer(rotate_capture_data_t *data); // Cleanup for any timer resources

// You may also need additional functions depending on your implementation, such as:
void update_device_list_from_settings(obs_data_t *settings, rotate_capture_data_t *data); // Update device list based on OBS settings
