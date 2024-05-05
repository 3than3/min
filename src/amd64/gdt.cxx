export module amd64:gdt;

import types;

namespace amd64
{
    namespace gdt
    {
        struct __attribute__((packed))
        {
            u16   size;
            void *address;
        } m_pointer;

        struct __attribute__((packed))
        {
            // Only .high_flags and .low_flags matter, rest should be zero
            u16 limit;
            u16 low_base;
            u8  mid_base;
            u8  low_flags;
            u8  high_flags;
            u8  high_base;
        } m_entries[6];

        export constexpr usize kernel_code_segment = 0x08;
        export constexpr usize kernel_data_segment = 0x10;
        export constexpr usize user_data_segment   = 0x20;
        export constexpr usize user_code_segment   = 0x28;
        export constexpr usize tss_segment         = 0x30;

        export void init()
        {
            m_entries[0] = {0};                                                 // Null
            m_entries[1] = {.low_flags = 0b10011010, .high_flags = 0b00100000}; // Kernel code
            m_entries[2] = {.low_flags = 0b10010010, .high_flags = 0b00000000}; // Kernel data
            m_entries[3] = {.low_flags = 0b00000000, .high_flags = 0b00000000}; // Null (comp mode code)
            m_entries[4] = {.low_flags = 0b11110010, .high_flags = 0b00000000}; // User code
            m_entries[5] = {.low_flags = 0b11111010, .high_flags = 0b00100000}; // User data

            m_pointer =
            {
                .size = sizeof(m_entries) - 1,
                .address = &m_entries
            };

            // Point CPU to new GDT and reload segment registers
            asm volatile
            (
                // Load new GDT
                "lgdt %0\n"

                // Set cs register
                "push rbp\n"
                "mov rbp, rsp\n"
                "push %1\n"
                "push rbp\n"
                "pushfq\n"
                "push %2\n"
                "push OFFSET l1\n"
                "iretq\n"
                "l1:\n"
                "pop rbp\n"

                // Set other segment registers
                "mov ds, %1\n"
                "mov es, %1\n"
                "mov fs, %1\n"
                "mov gs, %1\n"
                "mov ss, %1\n"
                :
                : "m"(m_pointer), "r"(kernel_data_segment), "r"(kernel_code_segment)
                : "memory"
            );
        }
    };
}