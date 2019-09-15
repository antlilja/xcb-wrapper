// Copyright(c) 2019-present, Anton Lilja.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include "xcb_wrapper/window.hpp"

#include "xcb_helper.hpp"

namespace xcbw {
    window::window(const connection& c, window_class w_class, window parent, int16_t x, int16_t y,
                   uint16_t width, uint16_t height, uint16_t border_width, visual_id visual,
                   const wa_mask mask, const uint32_t* values)
        : m_id(static_cast<uint32_t>(xcb_generate_id((xcb_connection_t*)c.get_ptr()))) {
        xcb_create_window((xcb_connection_t*)c.get_ptr(), XCB_COPY_FROM_PARENT,
                          static_cast<xcb_window_t>(m_id), static_cast<xcb_window_t>(parent), x, y,
                          width, height, border_width, static_cast<uint16_t>(w_class),
                          static_cast<xcb_visualid_t>(visual), static_cast<uint32_t>(mask), values);
    }

    void window::destroy(const connection& c) {
        xcb_destroy_window(get(c), static_cast<xcb_window_t>(m_id));
    }

    void window::map(const connection& c) {
        xcb_map_window(get(c), static_cast<xcb_window_t>(m_id));
    }
    void window::unmap(const connection& c) {
        xcb_unmap_window(get(c), static_cast<xcb_window_t>(m_id));
    }

    void window::configure(const connection& c, const wc_mask mask, const uint32_t* values) {
        xcb_configure_window(get(c), static_cast<xcb_window_t>(m_id), mask, values);
    }

    void window::change_attributes(const connection& c, const wa_mask mask,
                                   const uint32_t* values) {
        xcb_change_window_attributes(get(c), static_cast<xcb_window_t>(m_id),
                                     static_cast<uint32_t>(mask), values);
    }

    void window::change_property(const connection& c, prop_mode mode, atom_type atom,
                                 atom_type type, uint8_t format, uint32_t data_len,
                                 const void* data) {
        xcb_change_property(get(c), static_cast<uint8_t>(mode), static_cast<xcb_window_t>(m_id),
                            static_cast<xcb_atom_t>(atom), static_cast<xcb_atom_t>(type), format,
                            data_len, data);
    }

    std::pair<void*, int32_t> window::get_property(const connection& c, atom_type property,
                                                   atom_type type, bool _delete,
                                                   uint32_t long_offset, uint32_t long_length) {
        const auto cookie = xcb_get_property(
            get(c), _delete, static_cast<xcb_window_t>(m_id), static_cast<xcb_atom_t>(property),
            static_cast<xcb_atom_t>(type), long_offset, long_length);

        xcb_generic_error_t* err;
        const auto reply = xcb_get_property_reply(get(c), cookie, &err);

        if (err->error_code) {
            const auto code = err->error_code;
            free(err);
            throw std::runtime_error(
                (std::string("XCB: Failed to get window property: ") + std::to_string(code)));
        }

        const auto value = xcb_get_property_value(reply);
        const auto length = xcb_get_property_value_length(reply);
        free(reply);
        return {value, length};
    }
} // namespace xcbw