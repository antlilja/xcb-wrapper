#pragma once
#include <cstdlib>
#include <cstdint>

namespace xcbw {
    enum class event_type {
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

    class generic_event {
    public:
        explicit generic_event(void* pointer);
        ~generic_event();

        generic_event(const generic_event& o) = delete;
        generic_event& operator=(const generic_event& o) = delete;

        generic_event(generic_event&& o) noexcept = default;
        generic_event& operator=(generic_event&& o) noexcept = default;

        bool is_null() const { return (m_pointer == nullptr); }

        uint8_t get_response_type() const;
        uint16_t get_sequence() const;
        uint32_t get_full_sequence() const;

        event_type get_event_type() const {
            return static_cast<event_type>(get_response_type() & ~0x80);
        }

        void* get_pointer() const { return m_pointer; }

    protected:
        mutable void* m_pointer = nullptr;
    };

    class key_press_event final : public generic_event {
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

    using key_release_event = key_press_event;

    using button_press_event = key_press_event;
    using button_release_event = button_press_event;

    using motion_notify_event = key_press_event;

    class enter_notify_event final : public generic_event {
    public:
        enter_notify_event(const generic_event event) : generic_event(event.get_pointer()) {}

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

    using leave_notify_event = enter_notify_event;

    class focus_in_event final : public generic_event {
    public:
        focus_in_event(const generic_event event) : generic_event(event.get_pointer()) {}

        uint8_t get_detail() const;
        // FIXME: add window

        uint8_t get_mode() const;
    };

    using focus_out_event = focus_in_event;

    class keymap_notify_event final : public generic_event {
    public:
        keymap_notify_event(const generic_event event) : generic_event(event.get_pointer()) {}

        uint8_t* get_keys() const;
    };

    class expose_event final : public generic_event {
    public:
        expose_event(const generic_event event) : generic_event(event.get_pointer()) {}

        // FIXME: add window

        uint16_t get_x() const;
        uint16_t get_y() const;

        uint16_t get_width() const;
        uint16_t get_height() const;

        uint16_t get_count() const;
    };

    union client_message_data {
        uint8_t data8[20];
        uint16_t data16[10];
        uint32_t data32[5];
    };

    class client_message_event final : public generic_event {
    public:
        client_message_event(const generic_event event) : generic_event(event.get_pointer()) {}

        uint8_t get_format() const;

        // FIXME: add window

        uint32_t get_type() const;
        const client_message_data& get_data() const;
    };

    class configure_notify_event final : public generic_event {
    public:
        configure_notify_event(const generic_event event) : generic_event(event.get_pointer()) {}

        // FIXME: add window

        int16_t get_x() const;
        int16_t get_y() const;

        uint16_t get_width() const;
        uint16_t get_height() const;

        uint16_t get_border_width() const;
        uint8_t get_override_redirect() const;
    };
} // namespace xcbw