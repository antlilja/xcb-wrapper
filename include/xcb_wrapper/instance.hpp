#pragma once
#include "xcb_wrapper/connection.hpp"
#include "xcb_wrapper/screen.hpp"

namespace xcbw {
    class instance_t {
    public:
        instance_t(const char* display_name = nullptr, int* screen_pointer = nullptr)
            : m_connection(display_name, screen_pointer), m_screen(m_connection) {}

        instance_t(const instance_t& o) = delete;
        instance_t& operator=(const instance_t& o) = delete;

        instance_t(instance_t&& o) noexcept = default;
        instance_t& operator=(instance_t&& o) noexcept = default;

        const connection_t& get_connection() const { return m_connection; }
        const screen_t& get_screen() const { return m_screen; }

        inline operator const connection_t&() const { return m_connection; }

        // Connection
        void flush() { m_connection.flush(); }
        generic_event_t poll_for_events() { return m_connection.poll_for_events(); }

        // Screen
        window_t get_root() const { return m_screen.get_root(); }

        colormap_t get_default_colormap() const { return m_screen.get_default_colormap(); }

        uint32_t get_white_pixel() const { return m_screen.get_white_pixel(); }
        uint32_t get_black_pixel() const { return m_screen.get_black_pixel(); }

        uint32_t get_current_input_masks() const { return m_screen.get_current_input_masks(); }

        uint16_t get_width_in_pixels() const { return m_screen.get_width_in_pixels(); }
        uint16_t get_height_in_pixels() const { return m_screen.get_height_in_pixels(); }

        uint16_t get_width_in_millimeters() const { return m_screen.get_width_in_millimeters(); }
        uint16_t get_height_in_millimeters() const { return m_screen.get_height_in_millimeters(); }

        uint16_t get_min_installed_maps() const { return m_screen.get_min_installed_maps(); }
        uint16_t get_max_installed_maps() const { return m_screen.get_max_installed_maps(); }

        visualid_t get_root_visual() const { return m_screen.get_root_visual(); }

        uint8_t get_backing_stores() const { return m_screen.get_backing_stores(); }

        uint8_t get_save_unders() const { return m_screen.get_save_unders(); }

        uint8_t get_root_depth() const { return m_screen.get_root_depth(); }

        uint8_t get_allowed_depths_len() const { return m_screen.get_allowed_depths_len(); }

    private:
        connection_t m_connection;
        screen_t m_screen;
    };
} // namespace xcbw