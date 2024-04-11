// render/renderer.cpp
#include <obs-module.h>
#include <media-io/video-frame.h>
#include <atomic>
#include <mutex>

class Renderer {
private:
    obs_source_t *source;
    std::mutex mutex;

public:
    Renderer() : source(nullptr) {
        source = obs_source_create_private("custom_source", "MetaSwitch Renderer", nullptr);
    }

    ~Renderer() {
        if (source)
            obs_source_release(source);
    }

    // This method is called by OBS to render frames
    static void render(void *data, gs_effect_t *effect) {
        Renderer *renderer = static_cast<Renderer*>(data);
        renderer->draw(effect);
    }

    // Connect the render callback to OBS
    void start() {
        std::lock_guard<std::mutex> lock(mutex);
        obs_source_info si = {};
        si.id = "meta_switch_renderer";
        si.type = OBS_SOURCE_TYPE_INPUT;
        si.output_flags = OBS_SOURCE_VIDEO;
        si.get_name = [](void*) { return "MetaSwitch Renderer"; };
        si.create = [](obs_data_t *settings, obs_source_t *source) -> void* { return new Renderer(); };
        si.destroy = [](void* data) { delete static_cast<Renderer*>(data); };
        si.video_render = render;
        obs_register_source(&si);
    }

    // Method to draw using OBS' graphics system
    void draw(gs_effect_t *effect) {
        std::lock_guard<std::mutex> lock(mutex);
        if (!source) return;

        obs_source_frame frame = {};
        frame.data[0] = nullptr; // Typically, you'd fetch frame data from your video capture source
        frame.width = 1920;
        frame.height = 1080;
        frame.format = VIDEO_FORMAT_RGBA;

        obs_source_output_video(source, &frame);
    }
};

// Module load and unload functions
OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("meta_switch_renderer", "en-US")

bool obs_module_load() {
    Renderer* renderer = new Renderer();
    renderer->start();
    return true;
}

void obs_module_unload() {
    delete renderer;
}
