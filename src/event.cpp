// Copyright(c) 2019-present, Anton Lilja.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include "xcb_wrapper/event.hpp"

#include <xcb/xcb.h>

#define getter(C, T, V) \
    T C::get_##V() const { return static_cast<T>(static_cast<xcb_##C*>(m_pointer)->V); }

namespace xcbw {
    generic_event_t::generic_event_t(void* pointer) : m_pointer(pointer) {}

    generic_event_t::~generic_event_t() {
        if (m_pointer != nullptr) {
            free(m_pointer);
        }
    }

    getter(generic_event_t, uint8_t, response_type);
    getter(generic_event_t, uint16_t, sequence);
    getter(generic_event_t, uint32_t, full_sequence);

    // key press
    getter(key_press_event_t, uint8_t, detail);
    getter(key_press_event_t, uint32_t, time);

    getter(key_press_event_t, int16_t, root_x);
    getter(key_press_event_t, int16_t, root_y);

    getter(key_press_event_t, int16_t, event_x);
    getter(key_press_event_t, int16_t, event_y);

    getter(key_press_event_t, uint16_t, state);
    getter(key_press_event_t, uint8_t, same_screen);

    // enter notify
    getter(enter_notify_event_t, uint8_t, detail);
    getter(enter_notify_event_t, uint32_t, time);

    getter(enter_notify_event_t, int16_t, root_x);
    getter(enter_notify_event_t, int16_t, root_y);

    getter(enter_notify_event_t, int16_t, event_x);
    getter(enter_notify_event_t, int16_t, event_y);

    getter(enter_notify_event_t, uint8_t, mode);
    getter(enter_notify_event_t, uint8_t, same_screen_focus);

    // focus in
    getter(focus_in_event_t, uint8_t, detail);
    getter(focus_in_event_t, uint8_t, mode);

    // keymap notify
    getter(keymap_notify_event_t, uint8_t*, keys);

    // expose
    getter(expose_event_t, uint16_t, x);
    getter(expose_event_t, uint16_t, y);

    getter(expose_event_t, uint16_t, width);
    getter(expose_event_t, uint16_t, height);

    getter(expose_event_t, uint16_t, count);

    // client message data
    getter(client_message_event_t, uint32_t, type);
    const client_message_data_t& client_message_event_t::get_data() const {
        return reinterpret_cast<const client_message_data_t&>(
            static_cast<xcb_client_message_event_t*>(m_pointer)->data);
    }

    // configure_notify
    getter(configure_notify_event_t, int16_t, x);
    getter(configure_notify_event_t, int16_t, y);

    getter(configure_notify_event_t, uint16_t, width);
    getter(configure_notify_event_t, uint16_t, height);

    getter(configure_notify_event_t, uint16_t, border_width);
    getter(configure_notify_event_t, uint8_t, override_redirect);
} // namespace xcbw