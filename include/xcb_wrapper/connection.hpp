// Copyright(c) 2019-present, Anton Lilja.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once
#include "xcb_wrapper/event.hpp"

namespace xcbw {
    class connection_t {
    public:
        connection_t(const char* display_name = nullptr, int* screen_p = nullptr);
        ~connection_t();

        connection_t(const connection_t& o) = delete;
        connection_t& operator=(const connection_t& o) = delete;

        connection_t(connection_t&& o) noexcept = default;
        connection_t& operator=(connection_t&& o) noexcept = default;

        void* get_ptr() const { return m_pointer; }

        void flush();

        generic_event_t poll_for_events();

    private:
        void* m_pointer = nullptr;
    };
} // namespace xcbw