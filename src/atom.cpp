// Copyright(c) 2019-present, Anton Lilja.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include "xcb_wrapper/atom.hpp"

#include "xcb_helper.hpp"

#include <cstring>

#define getter(T, V) \
    T intern_atom::get_##V() const { return (T)((xcb_intern_atom_reply_t*)m_pointer)->V; }

namespace xcbw {
    intern_atom::intern_atom(connection& c, bool only_if_exists, uint16_t name_len,
                             const char* name)
        : intern_atom(c, intern_atom_cookie(
                             xcb_intern_atom(get(c), only_if_exists, name_len, name).sequence)) {}

    intern_atom::intern_atom(connection& c, bool only_if_exists, const char* name)
        : intern_atom(c, only_if_exists, std::strlen(name), name) {}

    intern_atom::intern_atom(connection& c, intern_atom_cookie cookie)
        : m_pointer(xcb_intern_atom_reply(get(c), {cookie}, nullptr)) {}

    intern_atom::~intern_atom() {
        if (m_pointer != nullptr) {
            free(m_pointer);
        }
    }

    getter(uint8_t, response_type);
    getter(uint16_t, sequence);
    getter(uint32_t, length);
    getter(atom_type, atom);
} // namespace xcbw
