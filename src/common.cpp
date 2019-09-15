#include "xcb_wrapper/common.hpp"

#include "xcb_helper.hpp"

namespace xcbw {
    pixmap::pixmap(connection& c, uint8_t depth, drawable _drawable, uint16_t width,
                   uint16_t height)
        : m_id(xcb_generate_id(get(c))) {

        xcb_create_pixmap(get(c), depth, static_cast<xcb_pixmap_t>(m_id),
                          static_cast<xcb_drawable_t>(_drawable), width, height);
    }

    void pixmap::free_pixmap(connection& c) {
        xcb_free_pixmap(get(c), static_cast<xcb_pixmap_t>(m_id));
    }
} // namespace xcbw