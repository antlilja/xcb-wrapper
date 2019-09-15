// Copyright(c) 2019-present, Anton Lilja.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once
#include "xcb_wrapper/common.hpp"
#include "xcb_wrapper/connection.hpp"

#include "xcb_wrapper/window_params.hpp"

#include <tuple>
#include <cstring>

namespace xcbw {

    using visual_id = detail::xcb_value<uint32_t>;

    class window {
    public:
        explicit window(uint32_t id) : m_id(id) {}

        window(const connection& c, window_class w_class, window parent, int16_t x, int16_t y,
               uint16_t width, uint16_t height, uint16_t border_width, visual_id visual,
               const wa_mask mask, const uint32_t* values);

        template <typename... Values>
        window(const connection& c, window_class w_class, window parent, int16_t x, int16_t y,
               uint16_t width, uint16_t height, uint16_t border_width, visual_id visual,
               const window_attributes<Values...> attributes)
            : window(c, w_class, parent, x, y, width, height, border_width, visual,
                     attributes.get_mask(), attributes.get_values()) {}

        template <typename... Values>
        window(const connection& c, window_class w_class, window parent, point<int16_t> pos,
               point<uint16_t> size, uint16_t border_width, visual_id visual,
               const window_attributes<Values...> attributes)
            : window(c, w_class, parent, pos.x, pos.y, size.x, size.y, border_width, visual,
                     attributes.get_mask(), attributes.get_values()) {}

        inline operator uint32_t() const { return m_id; }

        void destroy(const connection& c);

        void map(const connection& c);
        void unmap(const connection& c);

        // change_attributes
        void change_attributes(const connection& c, const wa_mask mask, const uint32_t* values);

        template <typename... Values>
        void change_attributes(const connection& c, const window_attributes<Values...> attributes) {
            change_attributes(c, attributes.get_mask(), attributes.get_values());
        }

        // configure
        void configure(const connection& c, const wc_mask mask, const uint32_t* values);

        template <typename... Values>
        void configure(const connection& c, const window_config<Values...> config) {
            configure(c, config.get_mask(), config.get_values());
        }

        // change_property
        void change_property(const connection& c, prop_mode mode, atom_type atom, atom_type type,
                             uint8_t format, uint32_t data_len, const void* data);

        void change_property(const connection& c, prop_mode mode, atom_type atom, atom_type type,
                             const char* data) {
            change_property(c, mode, atom, type, 8, std::strlen(data), data);
        }

        template <typename T, typename = std::enable_if_t<!std::is_pointer<T>::value>>
        void change_property(const connection& c, prop_mode mode, atom_type atom, atom_type type,
                             const T data) {

            constexpr auto format = static_cast<uint8_t>(sizeof(T) * 8);
            change_property(c, mode, atom, type, format, 1, &data);
        }

        template <typename... Values>
        void change_property(const connection& c, prop_mode mode, atom_type atom, atom_type type,
                             property_data<Values...> data) {
            change_property(c, mode, atom, type, data.get_format(), data.get_len(), data.data());
        }

        // get_property
        std::pair<void*, int32_t> get_property(const connection& c, atom_type property,
                                               atom_type type, bool _delete = false,
                                               uint32_t long_offset = 0, uint32_t long_length = 0);

    private:
        uint32_t m_id = 0;
    };
} // namespace xcbw