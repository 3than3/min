export module integral;

import types;

export namespace au
{
    template<typename t>
    constexpr bool is_integral = false;

    template<>
    constexpr bool is_integral<u8> = true;

    template<>
    constexpr bool is_integral<u16> = true;

    template<>
    constexpr bool is_integral<u32> = true;

    template<>
    constexpr bool is_integral<u64> = true;

    template<>
    constexpr bool is_integral<s8> = true;

    template<>
    constexpr bool is_integral<s16> = true;

    template<>
    constexpr bool is_integral<s32> = true;

    template<>
    constexpr bool is_integral<s64> = true;

    template <typename t>
    concept integral = is_integral<t>;
}