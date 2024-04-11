// main.c

#include <obs-module.h>
#include "device_enumeration.h"
// LOCATION: /src/


#define SOURCE_NAME "rotate_capture_source"

struct rotate_capture_data {
    obs_source_t *source;
    // TODO: Add fields for managing timers and video device selection.
};

// Function prototypes for the source lifecycle
static const char *rotate_capture_get_name(void *unused);
static void *rotate_capture_create(obs_data_t *settings, obs_source_t *source);
static void rotate_capture_destroy(void *data);


// Called by OBS to load the plugin
bool obs_module_load(void) {
    obs_register_source(&rotate_capture_source_info);

    return true;
}

// Called by OBS to unload the plugin
void obs_module_unload(void) {
    
}

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("obs-rotate-capture", "en-US")