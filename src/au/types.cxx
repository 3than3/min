export module types;

// Unsigned integers
export using u8  = unsigned char;
export using u16 = unsigned short;
export using u32 = unsigned int;
export using u64 = unsigned long long;

// Signed integers
export using s8  = signed char;
export using s16 = signed short;
export using s32 = signed int;
export using s64 = signed long long;

template<bool is_64_bit>
struct pointer_sized;

// Pointer sized integers
template<>
struct pointer_sized<true>
{
    using usize = unsigned long long;
    using ssize = long long;
};

template<>
struct pointer_sized<false>
{
    using usize = unsigned int;
    using ssize = int;
};

export using usize = typename pointer_sized<sizeof(void*) == 8>::usize;
export using ssize = typename pointer_sized<sizeof(void*) == 8>::ssize;
