// Copyright(c) 2019-present, Anton Lilja.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once
#include "xcb_wrapper/connection.hpp"
#include "xcb_wrapper/window.hpp"
#include "xcb_wrapper/drawable.hpp"

namespace xcbw {
    class screen_t {
    public:
        screen_t(const connection_t& c);

        window_t get_root() const;

        colormap_t get_default_colormap() const;

        uint32_t get_white_pixel() const;
        uint32_t get_black_pixel() const;

        uint32_t get_current_input_masks() const;

        uint16_t get_width_in_pixels() const;
        uint16_t get_height_in_pixels() const;

        uint16_t get_width_in_millimeters() const;
        uint16_t get_height_in_millimeters() const;

        uint16_t get_min_installed_maps() const;
        uint16_t get_max_installed_maps() const;

        visualid_t get_root_visual() const;

        uint8_t get_backing_stores() const;

        uint8_t get_save_unders() const;

        uint8_t get_root_depth() const;

        uint8_t get_allowed_depths_len() const;

        void* get_ptr() const { return m_pointer; }

    private:
        void* m_pointer = nullptr;
    };
} // namespace xcbw