// Copyright(c) 2019-present, Anton Lilja.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include "xcb_wrapper/window.hpp"

#include "xcb_helper.hpp"

#include <cstring>

namespace xcbw {
    window_t::window_t(const connection_t& c, window_class_t window_class, window_t parent,
                       int16_t x, int16_t y, uint16_t width, uint16_t height, uint16_t border_width,
                       visualid_t visual, const wa_mask_t mask, const uint32_t* values)
        : m_id(static_cast<uint32_t>(xcb_generate_id(get(c)))) {
        xcb_create_window(get(c), XCB_COPY_FROM_PARENT, static_cast<xcb_window_t>(m_id),
                          static_cast<xcb_window_t>(parent), x, y, width, height, border_width,
                          static_cast<uint16_t>(window_class), static_cast<xcb_visualid_t>(visual),
                          static_cast<uint32_t>(mask), values);
    }

    void window_t::destroy(const connection_t& c) {
        xcb_destroy_window(get(c), static_cast<xcb_window_t>(m_id));
    }

    void window_t::map(const connection_t& c) {
        xcb_map_window(get(c), static_cast<xcb_window_t>(m_id));
    }
    void window_t::unmap(const connection_t& c) {
        xcb_unmap_window(get(c), static_cast<xcb_window_t>(m_id));
    }

    void window_t::configure(const connection_t& c, const wc_mask_t mask, const uint32_t* values) {
        xcb_configure_window(get(c), static_cast<xcb_window_t>(m_id), mask, values);
    }

    void window_t::change_attributes(const connection_t& c, const wa_mask_t mask,
                                     const uint32_t* values) {
        xcb_change_window_attributes(get(c), static_cast<xcb_window_t>(m_id),
                                     static_cast<uint32_t>(mask), values);
    }

    void window_t::change_property(const connection_t& c, property_mode_t mode, atom_type_t atom,
                                   atom_type_t type, uint8_t format, uint32_t data_len,
                                   const void* data) {
        xcb_change_property(get(c), static_cast<uint8_t>(mode), static_cast<xcb_window_t>(m_id),
                            static_cast<xcb_atom_t>(atom), static_cast<xcb_atom_t>(type), format,
                            data_len, data);
    }

    void window_t::change_property(const connection_t& c, property_mode_t mode, atom_type_t atom,
                                   atom_type_t type, const char* data) {
        change_property(c, mode, atom, type, 8, std::strlen(data), data);
    }

    std::pair<void*, int32_t> window_t::get_property(const connection_t& c, atom_type_t property,
                                                     atom_type_t type, bool _delete,
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
                (std::string("XCB: Failed to get window_t property: ") + std::to_string(code)));
        }

        const auto value = xcb_get_property_value(reply);
        const auto length = xcb_get_property_value_length(reply);
        free(reply);
        return {value, length};
    }
} // namespace xcbw