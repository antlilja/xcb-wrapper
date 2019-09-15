// Copyright(c) 2019-present, Anton Lilja.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include "xcb_wrapper/common.hpp"

#include "xcb_helper.hpp"

namespace xcbw {
    pixmap_t::pixmap_t(connection_t& c, uint8_t depth, drawable_t drawable, uint16_t width,
                   uint16_t height)
        : m_id(xcb_generate_id(get(c))) {

        xcb_create_pixmap(get(c), depth, static_cast<xcb_pixmap_t>(m_id),
                          static_cast<xcb_drawable_t>(drawable), width, height);
    }

    void pixmap_t::free_pixmap(connection_t& c) {
        xcb_free_pixmap(get(c), static_cast<xcb_pixmap_t>(m_id));
    }
} // namespace xcbw