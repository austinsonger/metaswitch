/*
Plugin Name
Copyright (C) 2024 Austin Songer avsonger@protonmail.com

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program. If not, see <https://www.gnu.org/licenses/>
*/

#include <obs-module.h>

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("obs-rotate-capture", "en-US")

#define SOURCE_NAME "rotate_capture_source"

struct rotate_capture_data {
    obs_source_t *source;
    // Add more fields as needed for managing your sources and timing
};

// Forward declarations
static const char *rotate_capture_get_name(void *unused);
static void *rotate_capture_create(obs_data_t *settings, obs_source_t *source);
static void rotate_capture_destroy(void *data);

// This function is called to get the name of the source
static const char *rotate_capture_get_name(void *unused) {
    UNUSED_PARAMETER(unused);
    return obs_module_text("Rotate Capture");
}

// This function is called when a new source of this type is created
static void *rotate_capture_create(obs_data_t *settings, obs_source_t *source) {
    struct rotate_capture_data *data = bzalloc(sizeof(struct rotate_capture_data));
    data->source = source;
    // Initialize your source data here

    return data;
}

// This function is called when the source is destroyed
static void rotate_capture_destroy(void *data) {
    struct rotate_capture_data *rotate_data = data;
    // Clean up your source data here

    bfree(rotate_data);
}

// Define the source info structure
static struct obs_source_info rotate_capture_source_info = {
    .id = SOURCE_NAME,
    .type = OBS_SOURCE_TYPE_INPUT,
    .output_flags = OBS_SOURCE_VIDEO,
    .get_name = rotate_capture_get_name,
    .create = rotate_capture_create,
    .destroy = rotate_capture_destroy,
    // Add more function pointers and settings as needed
};

// Module load function, OBS calls this to load the plugin
bool obs_module_load(void) {
    obs_register_source(&rotate_capture_source_info);
    return true;
}

// Module unload function, OBS calls this to unload the plugin
void obs_module_unload(void) {
    // Clean up tasks as necessary
}

