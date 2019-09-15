// Copyright(c) 2019-present, Anton Lilja.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once
#include "xcb_wrapper/common.hpp"
#include "xcb_wrapper/connection.hpp"

#include <utility>

namespace xcbw {
    enum class atom_type : uint32_t {
        e_none = 0,
        e_any = 0,
        e_primary = 1,
        e_secondary = 2,
        e_arc = 3,
        e_atom = 4,
        e_bitmap = 5,
        e_cardinal = 6,
        e_colormap = 7,
        e_cursor = 8,
        e_cut_buffer0 = 9,
        e_cut_buffer1 = 10,
        e_cut_buffer2 = 11,
        e_cut_buffer3 = 12,
        e_cut_buffer4 = 13,
        e_cut_buffer5 = 14,
        e_cut_buffer6 = 15,
        e_cut_buffer7 = 16,
        e_drawable = 17,
        e_font = 18,
        e_integer = 19,
        e_pixmap = 20,
        e_point = 21,
        e_rectangle = 22,
        e_resource_manager = 23,
        e_rgb_color_map = 24,
        e_rgb_best_map = 25,
        e_rgb_blue_map = 26,
        e_rgb_default_map = 27,
        e_rgb_gray_map = 28,
        e_rgb_green_map = 29,
        e_rgb_red_map = 30,
        e_string = 31,
        e_visualid = 32,
        e_window = 33,
        e_wm_command = 34,
        e_wm_hints = 35,
        e_wm_client_machine = 36,
        e_wm_icon_name = 37,
        e_wm_icon_size = 38,
        e_wm_name = 39,
        e_wm_normal_hints = 40,
        e_wm_size_hints = 41,
        e_wm_zoom_hints = 42,
        e_min_space = 43,
        e_norm_space = 44,
        e_max_space = 45,
        e_end_space = 46,
        e_superscript_x = 47,
        e_superscript_y = 48,
        e_subscript_x = 49,
        e_subscript_y = 50,
        e_underline_position = 51,
        e_underline_thickness = 52,
        e_strikeout_ascent = 53,
        e_strikeout_descent = 54,
        e_italic_angle = 55,
        e_x_height = 56,
        e_quad_width = 57,
        e_weight = 58,
        e_point_size = 59,
        e_resolution = 60,
        e_copyright = 61,
        e_notice = 62,
        e_font_name = 63,
        e_family_name = 64,
        e_full_name = 65,
        e_cap_height = 66,
        e_wm_class = 67,
        e_wm_transient_for = 68
    };

    using intern_atom_cookie = detail::xcb_value<uint32_t>;

    class intern_atom {
    public:
        explicit intern_atom(void* pointer) : m_pointer(pointer) {}

        intern_atom(connection& c, bool only_if_exists, uint16_t name_len, const char* name);
        intern_atom(connection& c, bool only_if_exists, const char* name);
        intern_atom(connection& c, intern_atom_cookie cookie);
        ~intern_atom();

        intern_atom(const intern_atom& o) = delete;
        intern_atom& operator=(const intern_atom& o) = delete;

        intern_atom(intern_atom&& o) noexcept = default;
        intern_atom& operator=(intern_atom&& o) noexcept = default;

        bool is_null() const { return (m_pointer == nullptr); }

        uint8_t get_response_type() const;
        uint16_t get_sequence() const;
        uint32_t get_length() const;
        atom_type get_atom() const;

    protected:
        mutable void* m_pointer = nullptr;
    };
} // namespace xcbw