// render/capture_win.cpp
#include <obs-module.h>
#include <media-io/video-io.h>
#include <media-io/video-frame.h>
#include <thread>
#include <atomic>
#include <mutex>

class VideoCaptureWindows {
private:
    obs_source_t *videoSource;
    std::atomic<bool> active;
    std::mutex frameMutex;
    std::thread captureThread;

public:
    VideoCaptureWindows() : videoSource(nullptr), active(false) {
        videoSource = obs_source_create_private("video_capture_win", "Video Capture Windows", nullptr);
    }

    ~VideoCaptureWindows() {
        stop();
        if (videoSource)
            obs_source_release(videoSource);
    }

    void start() {
        if (!active) {
            active = true;
            captureThread = std::thread(&VideoCaptureWindows::captureLoop, this);
        }
    }

    void stop() {
        if (active) {
            active = false;
            if (captureThread.joinable())
                captureThread.join();
        }
    }

    void captureLoop() {
        while (active) {
            obs_source_frame frame = {};
            // Simulated fetching frame data
            std::this_thread::sleep_for(std::chrono::milliseconds(33)); // simulate ~30 FPS capture rate

            {
                std::lock_guard<std::mutex> lock(frameMutex);
                // Here you would typically fetch the frame data from the hardware
                frame.data[0] = nullptr; // Placeholder for actual frame data
                frame.width = 1920;
                frame.height = 1080;
                frame.format = VIDEO_FORMAT_RGBA;

                // Pass the frame to OBS
                if (videoSource) {
                    obs_source_output_video(videoSource, &frame);
                }
            }
        }
    }
};

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("video_capture_win", "en-US")

bool obs_module_load() {
    VideoCaptureWindows* capture = new VideoCaptureWindows();
    capture->start();
    return true;
}

void obs_module_unload() {
    delete capture;
}
