// Copyright(c) 2019-present, Anton Lilja.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once
#include <cstdlib>
#include <cstdint>

namespace xcbw {
    enum class event_type_t {
        e_key_press = 2,
        e_key_release = 3,
        e_button_press = 4,
        e_button_release = 5,
        e_motion_notify = 6,
        e_enter_notify = 7,
        e_leave_notify = 8,
        e_focus_in = 9,
        e_focus_out = 10,
        e_keymap_notify = 11,
        e_expose = 12,
        e_configure_notify = 22,
        e_client_message = 33
    };

    class generic_event_t {
    public:
        explicit generic_event_t(void* pointer);
        ~generic_event_t();

        generic_event_t(const generic_event_t& o) = delete;
        generic_event_t& operator=(const generic_event_t& o) = delete;

        generic_event_t(generic_event_t&& o) noexcept = default;
        generic_event_t& operator=(generic_event_t&& o) noexcept = default;

        bool is_null() const { return (m_pointer == nullptr); }

        uint8_t get_response_type() const;
        uint16_t get_sequence() const;
        uint32_t get_full_sequence() const;

        event_type_t get_event_type() const {
            return static_cast<event_type_t>(get_response_type() & ~0x80);
        }

        void* get_pointer() const { return m_pointer; }

    protected:
        mutable void* m_pointer = nullptr;
    };

    class key_press_event_t final : public generic_event_t {
    public:
        uint8_t get_detail() const;
        uint32_t get_time() const;

        // FIXME: add window

        int16_t get_root_x() const;
        int16_t get_root_y() const;

        int16_t get_event_x() const;
        int16_t get_event_y() const;

        uint16_t get_state() const;
        uint8_t get_same_screen() const;
    };

    using key_release_event_t = key_press_event_t;

    using button_press_event_t = key_press_event_t;
    using button_release_event_t = button_press_event_t;

    using motion_notify_event_t = key_press_event_t;

    class enter_notify_event_t final : public generic_event_t {
    public:
        enter_notify_event_t(const generic_event_t event) : generic_event_t(event.get_pointer()) {}

        uint8_t get_detail() const;
        uint32_t get_time() const;

        // FIXME: add window

        int16_t get_root_x() const;
        int16_t get_root_y() const;

        int16_t get_event_x() const;
        int16_t get_event_y() const;

        uint16_t get_state() const;
        uint8_t get_mode() const;
        uint8_t get_same_screen_focus() const;
    };

    using leave_notify_event_t = enter_notify_event_t;

    class focus_in_event_t final : public generic_event_t {
    public:
        focus_in_event_t(const generic_event_t event) : generic_event_t(event.get_pointer()) {}

        uint8_t get_detail() const;
        // FIXME: add window

        uint8_t get_mode() const;
    };

    using focus_out_event_t = focus_in_event_t;

    class keymap_notify_event_t final : public generic_event_t {
    public:
        keymap_notify_event_t(const generic_event_t event) : generic_event_t(event.get_pointer()) {}

        uint8_t* get_keys() const;
    };

    class expose_event_t final : public generic_event_t {
    public:
        expose_event_t(const generic_event_t event) : generic_event_t(event.get_pointer()) {}

        // FIXME: add window

        uint16_t get_x() const;
        uint16_t get_y() const;

        uint16_t get_width() const;
        uint16_t get_height() const;

        uint16_t get_count() const;
    };

    union client_message_data_t {
        uint8_t data8[20];
        uint16_t data16[10];
        uint32_t data32[5];
    };

    class client_message_event_t final : public generic_event_t {
    public:
        client_message_event_t(const generic_event_t event)
            : generic_event_t(event.get_pointer()) {}

        uint8_t get_format() const;

        // FIXME: add window

        uint32_t get_type() const;
        const client_message_data_t& get_data() const;
    };

    class configure_notify_event_t final : public generic_event_t {
    public:
        configure_notify_event_t(const generic_event_t event)
            : generic_event_t(event.get_pointer()) {}

        // FIXME: add window

        int16_t get_x() const;
        int16_t get_y() const;

        uint16_t get_width() const;
        uint16_t get_height() const;

        uint16_t get_border_width() const;
        uint8_t get_override_redirect() const;
    };
} // namespace xcbw