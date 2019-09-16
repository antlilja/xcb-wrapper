// Copyright(c) 2019-present, Anton Lilja.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include "xcb_wrapper/connection.hpp"

#include "xcb_helper.hpp"

namespace xcbw {
    connection_t::connection_t(const char* display_name, int* screen_p)
        : m_pointer(xcb_connect(display_name, screen_p)) {}

    connection_t::~connection_t() { xcb_disconnect(static_cast<xcb_connection_t*>(m_pointer)); }

    void connection_t::flush() { xcb_flush(static_cast<xcb_connection_t*>(m_pointer)); }

    generic_event_t connection_t::poll_for_events() {
        return generic_event_t(xcb_poll_for_event(static_cast<xcb_connection_t*>(m_pointer)));
    }
} // namespace xcbw