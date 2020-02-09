// Copyright(c) 2019-present, Anton Lilja.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include "xcb_wrapper/atom.hpp"

#include "xcb_helper.hpp"

#include <cstring>

#define getter(T, V) \
    T intern_atom_t::get_##V() const { return (T)((xcb_intern_atom_reply_t*)m_pointer)->V; }

namespace xcbw {
    intern_atom_t::intern_atom_t(const connection_t& c, bool only_if_exists, uint16_t name_len,
                                 const char* name)
        : intern_atom_t(c, intern_atom_cookie_t(
                               xcb_intern_atom(get(c), only_if_exists, name_len, name).sequence)) {}

    intern_atom_t::intern_atom_t(const connection_t& c, bool only_if_exists, const char* name)
        : intern_atom_t(c, only_if_exists, std::strlen(name), name) {}

    intern_atom_t::intern_atom_t(const connection_t& c, intern_atom_cookie_t cookie)
        : m_pointer(xcb_intern_atom_reply(get(c), {cookie}, nullptr)) {}

    intern_atom_t::~intern_atom_t() {
        if (m_pointer != nullptr) {
            free(m_pointer);
        }
    }

    getter(uint8_t, response_type);
    getter(uint16_t, sequence);
    getter(uint32_t, length);
    getter(atom_type_t, atom);
} // namespace xcbw
