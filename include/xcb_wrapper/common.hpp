#pragma once
#include "xcb_wrapper/connection.hpp"

#include <array>
#include <iostream>
#include <cstdint>
#include <initializer_list>
#include <type_traits>

namespace xcbw {
    namespace detail {
        template <typename E>
        class enum_bit_field {
            static_assert(std::is_enum<E>::value, "Type E must be an enum");

            using bit_type = typename std::underlying_type<E>::type;

        public:
            inline constexpr enum_bit_field() = default;
            inline constexpr enum_bit_field(const E bit) : m_bits(static_cast<bit_type>(bit)) {}

            inline constexpr enum_bit_field(const std::initializer_list<E> bits) {
                for (const auto bit : bits) {
                    m_bits |= static_cast<bit_type>(bit);
                }
            }

            template <typename... Bits>
            inline constexpr enum_bit_field(const Bits... bits) : enum_bit_field({bits...}) {}

            inline constexpr bool operator&(const E o) const {
                return m_bits & static_cast<bit_type>(o);
            }

            inline constexpr void operator|=(const E o) { m_bits |= static_cast<bit_type>(o); }

            inline constexpr operator bit_type() const { return m_bits; }

        private:
            bit_type m_bits = 0;
        };

        template <typename T>
        struct xcb_value {
            inline constexpr explicit xcb_value(T v) : m_value(v) {}
            operator T() const { return m_value; }

        private:
            T m_value;
        };

        template <typename Mask, typename Value, typename... Values>
        class mask_and_values {
            inline constexpr Mask extract_mask(const Values... values) {
                // FIXME: Really ugly
                Mask mask;
                ([&mask](const auto v) { mask |= v.get_bit(); }(values), ...);
                return mask;
            }

        public:
            inline constexpr mask_and_values(const Values... values)
                : m_mask(extract_mask(values...)) {
                m_values = {values...};
            }

            inline constexpr const Mask get_mask() const { return m_mask; }
            inline constexpr const Value* get_values() const { return m_values.data(); }

        private:
            const Mask m_mask;
            std::array<Value, sizeof...(Values)> m_values;
        };

        template <typename MaskBits, MaskBits bit>
        class attribute {
        public:
            inline constexpr attribute(uint32_t value) : m_value(value) {}

            inline constexpr MaskBits get_bit() const { return bit; }
            inline constexpr operator uint32_t() const { return m_value; }

        private:
            const uint32_t m_value;
        };

        template <typename MaskBits, typename AttribMaskBits, AttribMaskBits Bit>
        class attribute_bit_field : public enum_bit_field<MaskBits> {
        public:
            inline constexpr attribute_bit_field() = default;
            inline constexpr attribute_bit_field(const MaskBits bit)
                : enum_bit_field<MaskBits>(bit) {}

            template <typename... Bits>
            inline constexpr attribute_bit_field(const Bits... bits)
                : enum_bit_field<MaskBits>(bits...) {}

            inline constexpr AttribMaskBits get_bit() const { return Bit; }
        };
    } // namespace detail

    template <typename T>
    struct point {
        static_assert(std::is_arithmetic<T>::value, "T is required to be an arithmetic type");

        point() = default;
        point(T x, T y) : x(x), y(y) {}

        T x = 0;
        T y = 0;
    };

    using colormap = detail::xcb_value<uint32_t>;
    using drawable = detail::xcb_value<uint32_t>;

    class pixmap {
    public:
        explicit pixmap(uint32_t id) : m_id(id) {}
        pixmap(connection& c, uint8_t depth, drawable _drawable, uint16_t width, uint16_t height);
        pixmap(connection& c, uint8_t depth, drawable _drawable, point<uint16_t> size)
            : pixmap(c, depth, _drawable, size.x, size.y) {}

        void free_pixmap(connection& c);

        inline operator uint32_t() const { return m_id; }

    private:
        uint32_t m_id = 0;
    };

} // namespace xcbw

#if defined(_WIN32)
#    define XCBW_BREAKPOINT __debugbreak();
#elif defined(__linux__)
#    define XCBW_BREAKPOINT asm("int $3");
#endif

#define XCBW_ASSERT(x)                                                                  \
    {                                                                                   \
        if (!(x)) {                                                                     \
            std::cerr << "Assertion: " << #x << " failed in function: " << __FUNCTION__ \
                      << " at line: " << __LINE__ << " in file: " << __FILE__ << '\n';  \
            XCBW_BREAKPOINT                                                             \
        }                                                                               \
    }