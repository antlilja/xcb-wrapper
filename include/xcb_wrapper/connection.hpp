#pragma once
#include "xcb_wrapper/event.hpp"

namespace xcbw {
    class connection {
    public:
        connection(const char* display_name, int* screen_p);
        ~connection();

        connection(const connection& o) = delete;
        connection& operator=(const connection& o) = delete;

        connection(connection&& o) noexcept = default;
        connection& operator=(connection&& o) noexcept = default;

        void* get_ptr() const { return m_pointer; }

        void flush();

        generic_event poll_for_events();

    private:
        void* m_pointer = nullptr;
    };
} // namespace xcbw