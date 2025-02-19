// Copyright(c) 2019-present, Anton Lilja.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include "xcb_wrapper/cursor.hpp"
#include "xcb_helper.hpp"

#include <xcb/xcb_cursor.h>

#include <cstring>

namespace xcbw {
    void warp_pointer(const connection_t& c, std::optional<window_t> src_window,
                      std::optional<window_t> dst_window, point_t<int16_t> src_pos,
                      point_t<int16_t> src_size, point_t<int16_t> dst_pos) {

        uint32_t src = src_window.has_value() ? src_window.value() : 0;
        uint32_t dst = dst_window.has_value() ? dst_window.value() : 0;

        xcb_warp_pointer(get(c), (xcb_window_t)src, (xcb_window_t)dst, src_pos.x, src_pos.y,
                         src_size.x, src_pos.y, dst_pos.x, dst_pos.y);
    }

    cursor_context_t::cursor_context_t(const connection_t& c, screen_t s) {
        if (const auto err = xcb_cursor_context_new(
                get(c), get(s), reinterpret_cast<xcb_cursor_context_t**>(&m_pointer));
            err < 0) {
            throw std::runtime_error(
                (std::string("XCB: Failed to create cursor_context_t: ") + std::to_string(err)));
        }
    }

    cursor_context_t::~cursor_context_t() {
        xcb_cursor_context_free(static_cast<xcb_cursor_context_t*>(m_pointer));
    }

    cursor_t::cursor_t(const connection_t& c, pixmap_t source, pixmap_t mask, uint16_t fore_red,
                       uint16_t fore_green, uint16_t fore_blue, uint16_t back_red,
                       uint16_t back_green, uint16_t back_blue, uint16_t x, uint16_t y)
        : m_id(xcb_generate_id(get(c))) {
        const auto cookie = xcb_create_cursor_checked(
            get(c), static_cast<xcb_cursor_t>(m_id), static_cast<xcb_pixmap_t>(source),
            static_cast<xcb_pixmap_t>(mask), fore_red, fore_blue, fore_green, back_red, back_green,
            back_blue, x, y);

        if (auto* err = xcb_request_check(get(c), cookie)) {
            const auto code = err->error_code;
            free(err);
            throw std::runtime_error(
                (std::string("XCB: Cannot create cursor_t : ") + std::to_string(code)));
        }
    }

    cursor_t::cursor_t(const connection_t& c, const cursor_context_t& context, const char* name)
        : m_id(xcb_cursor_load_cursor(
              static_cast<xcb_cursor_context_t*>(static_cast<void*>(context)), name)) {}

    void cursor_t::free_cursor(const connection_t& c) {
        xcb_free_cursor(get(c), static_cast<xcb_cursor_t>(m_id));
    }

} // namespace xcbw
