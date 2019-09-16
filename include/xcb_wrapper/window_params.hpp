// Copyright(c) 2019-present, Anton Lilja.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once
#include "xcb_wrapper/common.hpp"
#include "xcb_wrapper/atom.hpp"

#include <cstdint>

namespace xcbw {
    enum class window_class_t : uint8_t {
        e_copy_from_parent = 0,
        e_input_output = 1,
        e_input_only = 2
    };

    // Attribute mask
    enum class wa_mask_bits : uint16_t {
        e_back_pixmap = 1,
        e_back_pixel = 2,
        e_border_pixmap = 4,
        e_border_pixel = 8,
        e_bit_gravity = 16,
        e_win_gravity = 32,
        e_backing_store = 64,
        e_backing_planes = 128,
        e_backing_pixel = 256,
        e_override_redirect = 512,
        e_save_under = 1024,
        e_event_mask = 2048,
        e_dont_propagate = 4096,
        e_colormap = 8192,
        e_cursor = 16384
    };

    using wa_mask_t = detail::enum_bit_field<wa_mask_bits>;

    template <typename... Values>
    using window_attributes_t = detail::mask_and_values<wa_mask_t, uint32_t, Values...>;

    template <typename... Values>
    inline static constexpr window_attributes_t<Values...>
    make_window_attributes(const Values... values) {
        return window_attributes_t<Values...>(values...);
    }

    // Attributes
    using back_pixmap_attrib = detail::attribute<wa_mask_bits, wa_mask_bits::e_back_pixmap>;
    using back_pixel_attrib = detail::attribute<wa_mask_bits, wa_mask_bits::e_back_pixel>;
    using border_pixmap_attrib = detail::attribute<wa_mask_bits, wa_mask_bits::e_border_pixmap>;
    using border_pixel_attrib = detail::attribute<wa_mask_bits, wa_mask_bits::e_border_pixel>;
    using bit_gravity_attrib = detail::attribute<wa_mask_bits, wa_mask_bits::e_bit_gravity>;
    using win_gravity_attrib = detail::attribute<wa_mask_bits, wa_mask_bits::e_win_gravity>;
    using backing_store_attrib = detail::attribute<wa_mask_bits, wa_mask_bits::e_backing_store>;
    using backing_planes_attrib = detail::attribute<wa_mask_bits, wa_mask_bits::e_backing_planes>;
    using backing_pixel_attrib = detail::attribute<wa_mask_bits, wa_mask_bits::e_backing_pixel>;
    using override_redirect_attrib =
        detail::attribute<wa_mask_bits, wa_mask_bits::e_override_redirect>;
    using save_under_attrib = detail::attribute<wa_mask_bits, wa_mask_bits::e_save_under>;
    using dont_propagate_attrib = detail::attribute<wa_mask_bits, wa_mask_bits::e_dont_propagate>;
    using colormap_attrib = detail::attribute<wa_mask_bits, wa_mask_bits::e_colormap>;
    using cursor_attrib = detail::attribute<wa_mask_bits, wa_mask_bits::e_cursor>;

    enum class event_mask_bits : uint32_t {
        e_no_event = 0,
        e_key_press = 1,
        e_key_release = 2,
        e_button_press = 4,
        e_button_release = 8,
        e_enter_window = 16,
        e_leave_window = 32,
        e_pointer_motion = 64,
        e_pointer_motion_hint = 128,
        e_button_1_motion = 256,
        e_button_2_motion = 512,
        e_button_3_motion = 1024,
        e_button_4_motion = 2048,
        e_button_5_motion = 4096,
        e_button_motion = 8192,
        e_keymap_state = 16384,
        e_exposure = 32768,
        e_visibility_change = 65536,
        e_structure_notify = 131072,
        e_resize_redirect = 262144,
        e_substructure_notify = 524288,
        e_substructure_redirect = 1048576,
        e_focus_change = 2097152,
        e_property_change = 4194304,
        e_color_map_change = 8388608,
        e_owner_grab_button = 16777216
    };

    using event_mask_attrib =
        detail::attribute_bit_field<event_mask_bits, wa_mask_bits, wa_mask_bits::e_event_mask>;

    // Config mask
    enum class wc_mask_bits : uint8_t {
        e_x = 1,
        e_y = 2,
        e_width = 4,
        e_height = 8,
        e_border_width = 16,
        e_sibling = 32,
        e_stack_mode = 64
    };
    using wc_mask_t = detail::enum_bit_field<wc_mask_bits>;

    template <typename... Values>
    using window_config_t = detail::mask_and_values<wc_mask_t, uint32_t, Values...>;

    template <typename... Values>
    inline static constexpr window_config_t<Values...> make_window_config(const Values... values) {
        return window_config_t<Values...>(values...);
    }

    // Configs
    using window_x_config = detail::attribute<wc_mask_bits, wc_mask_bits::e_x>;
    using window_y_config = detail::attribute<wc_mask_bits, wc_mask_bits::e_y>;
    using window_width_config = detail::attribute<wc_mask_bits, wc_mask_bits::e_width>;
    using window_height_config = detail::attribute<wc_mask_bits, wc_mask_bits::e_height>;
    using window_border_width_config =
        detail::attribute<wc_mask_bits, wc_mask_bits::e_border_width>;
    using sibling_config = detail::attribute<wc_mask_bits, wc_mask_bits::e_sibling>;
    using stack_mode_config = detail::attribute<wc_mask_bits, wc_mask_bits::e_stack_mode>;

    // Property
    enum class property_mode_t : uint8_t { e_replace = 0, e_prepend = 1, e_append = 2 };
} // namespace xcbw