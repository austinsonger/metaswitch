// plugin-main.c

#include <obs-module.h>
#include "device_enumeration.h"
// LOCATION: /src/

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("obs-rotate-capture", "en-US")

#define SOURCE_NAME "rotate_capture_source"

struct rotate_capture_data {
    obs_source_t *source;
    // TODO: Add fields for managing timers and video device selection.
};

// Function prototypes for the source lifecycle
static const char *rotate_capture_get_name(void *unused);
static void *rotate_capture_create(obs_data_t *settings, obs_source_t *source);
static void rotate_capture_destroy(void *data);

// Get the name of the source, shown in the UI
static const char *rotate_capture_get_name(void *unused) {
    UNUSED_PARAMETER(unused);
    // This name will appear in the OBS source selection list
    return obs_module_text("Rotate Capture");
}

// Create a new instance of the source
static void *rotate_capture_create(obs_data_t *settings, obs_source_t *source) {
    struct rotate_capture_data *data = bzalloc(sizeof(struct rotate_capture_data));
    data->source = source;
    // TODO: Initialize additional fields here, set up device enumeration, etc.

    return data;
}

// Destroy an instance of the source
static void rotate_capture_destroy(void *data) {
    struct rotate_capture_data *rotate_data = data;
    // TODO: Clean up any allocated resources, stop timers, etc.

    bfree(rotate_data);
}

// Define the structure that OBS uses to register and interact with the source
static struct obs_source_info rotate_capture_source_info = {
    .id = SOURCE_NAME,
    .type = OBS_SOURCE_TYPE_INPUT,
    .output_flags = OBS_SOURCE_VIDEO,
    .get_name = rotate_capture_get_name,
    .create = rotate_capture_create,
    .destroy = rotate_capture_destroy,
    // TODO: Implement and reference additional callbacks as needed, e.g., video render, audio render, get width/height.
};

// Called by OBS to load the plugin
bool obs_module_load(void) {
    obs_register_source(&rotate_capture_source_info);
    EnumerateVideoCaptureDevices();
    return true;
}

// Called by OBS to unload the plugin
void obs_module_unload(void) {
    // TODO: Perform any necessary cleanup tasks
}
