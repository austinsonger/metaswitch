# Project Plan

### plugin-main.c


### rotate_capture_source.c


2. Include Logic for Handling Source Rotation and Timers

    Objective: Implement the core functionality for rotating between video capture sources based on timers.
    Steps:
        Define a function or mechanism to switch the active video capture device.
        Implement timer logic that triggers the switch function at defined intervals.
        Ensure synchronization and thread safety, as OBS sources may be interacted with from multiple threads.

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
