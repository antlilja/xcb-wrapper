// Copyright(c) 2019-present, Anton Lilja.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once
#include "xcb_wrapper/connection.hpp"
#include "xcb_wrapper/screen.hpp"

#include <xcb/xcb.h>

namespace xcbw {
    inline xcb_connection_t* get(const connection& c) { return (xcb_connection_t*)c.get_ptr(); }
    inline xcb_screen_t* get(screen s) { return (xcb_screen_t*)s.get_ptr(); }
} // namespace xcbw