// rotate_capture_source.c
// LOCATION: /src/

#include <obs-module.h>
#include <pthread.h>
#include "rotate_capture_source.h"

// Forward declaration for helper functions if needed
static void rotate_to_next_device(struct rotate_capture_data *data);

// Example initialization function for your source
static void *rotate_capture_create(obs_data_t *settings, obs_source_t *source) {
    struct rotate_capture_data *data = bzalloc(sizeof(struct rotate_capture_data));
    enumerate_video_capture_devices(&data->device_names, &data->device_count);
    data->current_index = 0; // Start with the first device
    data->source = source;
    data->rotate_interval_ms = 5000; 
    pthread_mutex_init(&data->mutex, NULL); // Initialize mutex

    // TODO: Populate device_ids and device_count based on user settings or automatic enumeration
    // This is a placeholder for demonstration
    data->device_ids = NULL; // You would dynamically allocate and populate this based on actual devices
    data->device_count = 0;  // And set this accordingly
    data->current_device_index = 0;
    data->rotation_interval_ms = 5000; // Example: 5000 ms rotation interval
    data->last_switch_time_ms = obs_get_video_frame_time(); // Initialize with the current video frame time

    return data;
}

// Example cleanup function for your source
static void rotate_capture_destroy(void *ptr) {
    struct rotate_capture_data *data = ptr;

    pthread_mutex_destroy(&data->mutex); // Destroy mutex

    // Free device_ids array if allocated
    if (data->device_ids) {
        // Assume device_ids is an array of strings; free each string and then the array itself
        for (size_t i = 0; i < data->device_count; ++i) {
            bfree(data->device_ids[i]);
        }
        bfree(data->device_ids);
    }

    bfree(data); // Free the data structure itself
}

// Example function to switch to the next device
// This should be called periodically based on the rotation interval
static void rotate_to_next_device(struct rotate_capture_data *data) {
    pthread_mutex_lock(&data->mutex);
    // Increment current_device_index, wrap around if at the end of the list
    if (data->device_count > 0) {
        data->current_device_index = (data->current_device_index + 1) % data->device_count;
        // TODO: Implement logic to switch to the device indicated by current_device_index
    }
    pthread_mutex_unlock(&data->mutex);
}

// You may need a periodic update function or timing mechanism to call rotate_to_next_device
// Consider using OBS's timing mechanisms or a separate timing thread depending on your needs
