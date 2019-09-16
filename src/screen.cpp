// Copyright(c) 2019-present, Anton Lilja.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include "xcb_wrapper/screen.hpp"

#include "xcb_helper.hpp"

#define getter(T, V) \
    T screen_t::get_##V() const { return static_cast<T>(static_cast<xcb_screen_t*>(m_pointer)->V); }

namespace xcbw {
    screen_t::screen_t(const connection_t& c)
        : m_pointer(xcb_setup_roots_iterator(xcb_get_setup(get(c))).data) {}

    getter(window_t, root);

    getter(colormap_t, default_colormap);

    getter(uint32_t, white_pixel);
    getter(uint32_t, black_pixel);

    getter(uint32_t, current_input_masks);

    getter(uint16_t, width_in_pixels);
    getter(uint16_t, height_in_pixels);

    getter(uint16_t, width_in_millimeters);
    getter(uint16_t, height_in_millimeters);

    getter(uint16_t, min_installed_maps);
    getter(uint16_t, max_installed_maps);

    getter(visualid_t, root_visual);

    getter(uint8_t, backing_stores);
    getter(uint8_t, save_unders);
    getter(uint8_t, root_depth);
    getter(uint8_t, allowed_depths_len);
} // namespace xcbw
