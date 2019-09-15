#include "xcb_wrapper/connection.hpp"

#include "xcb_helper.hpp"

namespace xcbw {
    connection::connection(const char* display_name, int* screen_p)
        : m_pointer(xcb_connect(display_name, screen_p)) {}

    connection::~connection() { xcb_disconnect((xcb_connection_t*)m_pointer); }

    void connection::flush() { xcb_flush((xcb_connection_t*)m_pointer); }

    generic_event connection::poll_for_events() {
        return generic_event(xcb_poll_for_event((xcb_connection_t*)m_pointer));
    }
} // namespace xcbw