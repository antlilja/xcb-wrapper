// Copyright(c) 2019-present, Anton Lilja.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include "xcb_wrapper/drawable.hpp"

#include "xcb_helper.hpp"

namespace xcbw {
    pixmap_t::pixmap_t(connection_t& c, uint8_t depth, drawable_t drawable, uint16_t width,
                       uint16_t height)
        : m_id(xcb_generate_id(get(c))) {

        const auto cookie =
            xcb_create_pixmap_checked(get(c), depth, static_cast<xcb_pixmap_t>(m_id),
                                      static_cast<xcb_drawable_t>(drawable), width, height);

        if (auto* err = xcb_request_check(get(c), cookie)) {
            const auto code = err->error_code;
            free(err);
            throw std::runtime_error(
                (std::string("XCB: Cannot create pixmap_t : ") + std::to_string(code)));
        }
    }

    void pixmap_t::free_pixmap(connection_t& c) {
        xcb_free_pixmap(get(c), static_cast<xcb_pixmap_t>(m_id));
    }
} // namespace xcbw