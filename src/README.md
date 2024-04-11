# Project Plan

### plugin-main.c
### rotate_capture_source.c
### rotate_capture_source.h
1. Add Fields for Managing Timers, Sources

    Objective: Extend the source data structure to manage necessary state for device rotation and timing.
    Steps:
        Add to the rotate_capture_data structure fields for device list, current device index, and timer management.

2. Declare Additional Functions

    Objective: Declare prototypes for any new functions required for source management beyond the standard OBS source lifecycle functions.
    Steps:
        Declare functions for device enumeration, source switching logic, and timer callbacks.
        Ensure these declarations match the implementations in rotate_capture_source.c.
