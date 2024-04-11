// rotate_capture_source.c
// LOCATION: /src/

#include <obs-module.h>
#include <pthread.h>
#include "rotate_capture_source.h"
#include <util/platform.h> // For os_gettime_ns()

// Forward declaration for helper functions if needed
static void rotate_to_next_device(struct rotate_capture_data *data);

static const char *rotate_capture_get_name(void *unused) {
    UNUSED_PARAMETER(unused);
    return "Rotate Capture Source";
}

// Initialization function for your source
static void *rotate_capture_create(obs_data_t *settings, obs_source_t *source) {
    rotate_capture_data_t *data = bzalloc(sizeof(rotate_capture_data_t));
    data->source = source;
    pthread_mutex_init(&data->mutex, NULL);

    enumerate_video_capture_devices(&data->device_names, &data->num_devices);
  
    data->current_index = 0;
    data->rotate_interval_ms = 5000;  
    data->last_switch_time_ms = obs_get_video_frame_time();

    return data;
}

// Cleanup function for your source
static void rotate_capture_destroy(void *ptr) {
    rotate_capture_data_t *data = ptr;

    for (size_t i = 0; i < data->num_devices; ++i) {
        bfree(data->device_names[i]);
    }
    bfree(data->device_names);

    pthread_mutex_destroy(&data->mutex);
    bfree(data);
}

static uint32_t rotate_capture_getwidth(void *data) {
    return 1920; //  width
}

static uint32_t rotate_capture_getheight(void *data) {
    return 1080; //  height
}

static void rotate_capture_audio_render(void *data, uint32_t samples_per_sec, struct obs_audio_data *audio_data) {
    // Your audio processing here

static void rotate_capture_video_render(void *data, gs_effect_t *effect) {
    rotate_capture_data_t *rotate_data = data;

    uint64_t now = os_gettime_ns();
    if (now - rotate_data->last_switch_time_ms >= rotate_data->rotate_interval_ms * 1000000) {
        rotate_to_next_device(rotate_data);
        rotate_data->last_switch_time_ms = now;
    }

    // Placeholder render logic
    UNUSED_PARAMETER(effect);
    gs_clear(GS_CLEAR_COLOR, &(vec4){0.0f, 0.0f, 0.0f, 0.0f}, 0.0f, 0);
}

// Function to switch to the next device
// This should be called periodically based on the rotation interval
static void rotate_to_next_device(rotate_capture_data_t *data) {
    pthread_mutex_lock(&data->mutex);
    if (data->num_devices > 0) {
        data->current_index = (data->current_index + 1) % data->num_devices;
        blog(LOG_INFO, "Switched to device: %s", data->device_names[data->current_index]);
        // Here you would add logic to switch the visible source in OBS
    }
    pthread_mutex_unlock(&data->mutex);
}


static struct obs_source_info rotate_capture_source_info = {
    .id = "rotate_capture_source",
    .type = OBS_SOURCE_TYPE_INPUT,
    .output_flags = OBS_SOURCE_VIDEO | OBS_SOURCE_AUDIO, // Add OBS_SOURCE_AUDIO if you implement audio processing
    .get_name = rotate_capture_get_name,
    .create = rotate_capture_create,
    .destroy = rotate_capture_destroy,
    .get_width = rotate_capture_getwidth,
    .get_height = rotate_capture_getheight,
    .video_render = rotate_capture_video_render,
    // .audio_render = rotate_capture_audio_render, // Uncomment if implementing audio processing
    // Other fields...
};


OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("rotate_capture", "en-US")

bool obs_module_load(void) {
    obs_register_source(&rotate_capture_source_info);
    return true;
}
