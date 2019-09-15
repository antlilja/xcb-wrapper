// Copyright(c) 2019-present, Anton Lilja.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once
#include "xcb_wrapper/common.hpp"
#include "xcb_wrapper/connection.hpp"
#include "xcb_wrapper/screen.hpp"
#include "xcb_wrapper/window.hpp"

#include <optional>

namespace xcbw {
    void warp_pointer(const connection& c, std::optional<window> src_window,
                      std::optional<window> dst_window, point<int16_t> src_pos,
                      point<int16_t> src_size, point<int16_t> dst_pos);

    class cursor_context {
    public:
        cursor_context(connection& c, screen s);
        ~cursor_context();

        inline operator void*() const { return m_pointer; }

    private:
        void* m_pointer;
    };

    class cursor {
    public:
        explicit cursor(uint32_t id) : m_id(id) {}
        cursor(connection& c, pixmap source, pixmap mask, uint16_t fore_red, uint16_t fore_green,
               uint16_t fore_blue, uint16_t back_red, uint16_t back_green, uint16_t back_blue,
               uint16_t x, uint16_t y);

        cursor(connection& c, pixmap source, pixmap mask, uint16_t fore_red, uint16_t fore_green,
               uint16_t fore_blue, uint16_t back_red, uint16_t back_green, uint16_t back_blue,
               point<uint16_t> pos)
            : cursor(c, source, mask, fore_red, fore_blue, fore_green, back_red, back_green,
                     back_blue, pos.x, pos.y) {}

        cursor(connection& c, cursor_context context, const char* name);

        void free_cursor(connection& c);

    private:
        uint32_t m_id = 0;
    };
} // namespace xcbw