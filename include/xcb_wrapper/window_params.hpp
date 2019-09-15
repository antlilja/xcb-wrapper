// Copyright(c) 2019-present, Anton Lilja.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once
#include "xcb_wrapper/common.hpp"
#include "xcb_wrapper/atom.hpp"

#include <array>
#include <cstdint>
#include <functional>

namespace xcbw {
    enum class window_class : uint8_t { copy_from_parent = 0, input_output = 1, input_only = 2 };

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

    using wa_mask = detail::enum_bit_field<wa_mask_bits>;

    template <typename... Values>
    using window_attributes = detail::mask_and_values<wa_mask, uint32_t, Values...>;

    template <typename... Values>
    inline static constexpr window_attributes<Values...>
    make_window_attributes(const Values... values) {
        return window_attributes<Values...>(values...);
    }

    // Attributes
    using back_pixel = detail::attribute<wa_mask_bits, wa_mask_bits::e_back_pixel>;
    using window_cursor = detail::attribute<wa_mask_bits, wa_mask_bits::e_cursor>;

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

    using event_mask =
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
    using wc_mask = detail::enum_bit_field<wc_mask_bits>;

    template <typename... Values>
    using window_config = detail::mask_and_values<wc_mask, uint32_t, Values...>;

    template <typename... Values>
    inline static constexpr window_config<Values...> make_window_config(const Values... values) {
        return window_config<Values...>(values...);
    }

    // Configs
    using window_x = detail::attribute<wc_mask_bits, wc_mask_bits::e_x>;
    using window_y = detail::attribute<wc_mask_bits, wc_mask_bits::e_y>;

    using window_width = detail::attribute<wc_mask_bits, wc_mask_bits::e_width>;
    using window_height = detail::attribute<wc_mask_bits, wc_mask_bits::e_height>;

    using window_border_width = detail::attribute<wc_mask_bits, wc_mask_bits::e_border_width>;

    // Property
    enum class prop_mode : uint8_t { replace = 0, prepend = 1, append = 2 };

    template <typename... Values>
    class property_data {
        using T = typename std::tuple_element<0, std::tuple<Values...>>::type;

    public:
        inline constexpr property_data(const Values... values) : m_data({values...}) {}

        inline constexpr uint8_t get_format() const {
            return static_cast<uint8_t>((sizeof...(Values) * 8));
        }

        inline constexpr uint32_t get_len() const { return static_cast<uint32_t>(m_data.size()); }

        inline constexpr T* get_data() const { return m_data.data(); }

    private:
        const std::array<T, sizeof...(Values)> m_data;
    };
} // namespace xcbw