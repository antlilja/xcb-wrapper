#include "xcb_wrapper/screen.hpp"

#include "xcb_helper.hpp"

#define getter(T, V) \
    T screen::get_##V() const { return (T)((xcb_screen_t*)m_pointer)->V; }

namespace xcbw {
    screen::screen(const connection& c)
        : m_pointer(xcb_setup_roots_iterator(xcb_get_setup(get(c))).data) {}

    getter(window, root);

    getter(colormap, default_colormap);

    getter(uint32_t, white_pixel);
    getter(uint32_t, black_pixel);

    getter(uint32_t, current_input_masks);

    getter(uint16_t, width_in_pixels);
    getter(uint16_t, height_in_pixels);

    getter(uint16_t, width_in_millimeters);
    getter(uint16_t, height_in_millimeters);

    getter(uint16_t, min_installed_maps);
    getter(uint16_t, max_installed_maps);

    getter(visual_id, root_visual);

    getter(uint8_t, backing_stores);
    getter(uint8_t, save_unders);
    getter(uint8_t, root_depth);
    getter(uint8_t, allowed_depths_len);
} // namespace xcbw
