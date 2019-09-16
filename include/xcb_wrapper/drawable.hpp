#pragma once
#include "xcb_wrapper/common.hpp"
#include "xcb_wrapper/connection.hpp"

namespace xcbw {
    using colormap_t = detail::xcb_value<uint32_t>;
    using drawable_t = detail::xcb_value<uint32_t>;

    class pixmap_t {
    public:
        explicit pixmap_t(uint32_t id) : m_id(id) {}
        pixmap_t(connection_t& c, uint8_t depth, drawable_t drawable, uint16_t width,
                 uint16_t height);
        pixmap_t(connection_t& c, uint8_t depth, drawable_t drawable, point_t<uint16_t> size)
            : pixmap_t(c, depth, drawable, size.x, size.y) {}

        void free_pixmap(connection_t& c);

        inline operator uint32_t() const { return m_id; }

    private:
        uint32_t m_id = 0;
    };
} // namespace xcbw