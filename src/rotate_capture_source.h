// rotate_capture_source.h
#pragma once
// LOCATION: /src/
#include <obs-module.h>

struct rotate_capture_data {
    obs_source_t *source;
    // Add additional fields needed for managing timers, sources, etc.
};

// Function declarations for source lifecycle management
const char *rotate_capture_get_name(void *unused);
void *rotate_capture_create(obs_data_t *settings, obs_source_t *source);
void rotate_capture_destroy(void *data);
// Declare any additional functions needed for your source
