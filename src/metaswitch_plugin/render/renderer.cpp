// render/renderer.cpp
#include <obs-module.h>
#include <media-io/video-frame.h>
#include <util/threading.h>

static std::unique_ptr<Renderer> global_renderer;
static const char* get_name(void*);
static void* create(obs_data_t*, obs_source_t*);
static void destroy(void*);
static void render(void*, gs_effect_t*);

class Renderer {
private:
    obs_source_t *source;
    os_event_t *mutex;

public:
    Renderer() {
        os_event_init(&mutex, OS_EVENT_TYPE_MANUAL);
        source = obs_source_create_private("custom_source", "MetaSwitch Renderer", nullptr);
    }

    ~Renderer() {
        if (source)
            obs_source_release(source);
        os_event_destroy(mutex);
    }

    static const char* get_name(void*) {
        return "MetaSwitch Renderer";
    }

    static void* create(obs_data_t*, obs_source_t*) {
        return new Renderer();
    }

    static void destroy(void* data) {
        delete static_cast<Renderer*>(data);
    }

    static void render(void *data, gs_effect_t *effect) {
        Renderer *renderer = static_cast<Renderer*>(data);
        renderer->draw(effect);
    }

    void start() {
        os_event_wait(mutex);
        obs_source_info si = {};
        si.id = "meta_switch_renderer";
        si.type = OBS_SOURCE_TYPE_INPUT;
        si.output_flags = OBS_SOURCE_VIDEO;
        si.get_name = get_name;
        si.create = create;
        si.destroy = destroy;
        si.video_render = render;
        obs_register_source(&si);
    }

    void draw(gs_effect_t *effect) {
        os_event_wait(mutex);
        if (!source) return;

        obs_source_frame frame = {};
        frame.data[0] = nullptr;  // Consider filling this with valid data if necessary.
        frame.width = 1920;
        frame.height = 1080;
        frame.format = VIDEO_FORMAT_RGBA;

        obs_source_output_video(source, &frame);
    }
};

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("meta_switch_renderer", "en-US")

bool obs_module_load() {
    global_renderer = std::make_unique<Renderer>();
    global_renderer->start();
    return true;
}

void obs_module_unload() {
    global_renderer.reset();
}
