export module amd64:idt;

import fmt;
import types;

import :gdt;

namespace amd64
{
    namespace idt
    {
        // Affects how the CPU will handle the interrupt
        //      interrupt: disables interrupt flag
        //      trap: does not disable interrupt flag
        // For kernel, we mostly want to disable interrupts when one of these occur
        enum gate: u8
        {
            interrupt = 0b00001110,
            trap      = 0b00000111,
        };

        constexpr u8 present = 0b10000000;

        extern "C" using handler = void(*)();

        struct __attribute__((packed)) entry
        {
            u16 low_base;
            u16 cs_selector;
            u8  ist;
            u8  attributes;
            u16 mid_base;
            u32 high_base;
            u32 reserved;

            entry() = default;

            entry(handler h, u8 ist, u8 ring, gate g):
                ist(ist),
                cs_selector(gdt::kernel_code_segment),
                attributes(present | g | (ring & 0b00000011)),
                low_base(reinterpret_cast<u64>(h)),
                mid_base(reinterpret_cast<u64>(h) >> 16),
                high_base(reinterpret_cast<u64>(h) >> 32),
                reserved(0)
            {}
        } m_entries[256];

        struct __attribute__((packed))
        {
            u16   size;
            void *address;
        } m_pointer;

        extern "C" void div_zero_handler();
        extern "C" void debug_handler();
        extern "C" void nmi_handler();
        extern "C" void breakpoint_handler();
        extern "C" void overflow_handler();
        extern "C" void bound_range_handler();
        extern "C" void invalid_op_handler();
        extern "C" void no_device_handler();
        extern "C" void double_fault_handler();
        extern "C" void invalid_tss_handler();
        extern "C" void seg_absent_handler();
        extern "C" void ss_fault_handler();
        extern "C" void gpf_handler();
        extern "C" void page_fault_handler();
        extern "C" void fpu_fault_handler();
        extern "C" void align_check_handler();
        extern "C" void machine_check_handler();
        extern "C" void simd_fault_handler();
        extern "C" void virt_fault_handler();
        extern "C" void sec_fault_handler();

        void init()
        {
            m_pointer =
            {
                .size    = sizeof(m_entries) - 1,
                .address = &m_entries
            };

            m_entries[0]  = entry(&div_zero_handler,      0, 0, gate::interrupt);
            m_entries[1]  = entry(&debug_handler,         0, 0, gate::interrupt);
            m_entries[2]  = entry(&nmi_handler,           0, 0, gate::interrupt);
            m_entries[3]  = entry(&breakpoint_handler,    0, 0, gate::interrupt);
            m_entries[4]  = entry(&overflow_handler,      0, 0, gate::interrupt);
            m_entries[5]  = entry(&bound_range_handler,   0, 0, gate::interrupt);
            m_entries[6]  = entry(&invalid_op_handler,    0, 0, gate::interrupt);
            m_entries[7]  = entry(&no_device_handler,     0, 0, gate::interrupt);
            m_entries[8]  = entry(&double_fault_handler,  0, 0, gate::interrupt);
            m_entries[10] = entry(&invalid_tss_handler,   0, 0, gate::interrupt);
            m_entries[11] = entry(&seg_absent_handler,    0, 0, gate::interrupt);
            m_entries[12] = entry(&ss_fault_handler,      0, 0, gate::interrupt);
            m_entries[13] = entry(&gpf_handler,           0, 0, gate::interrupt);
            m_entries[14] = entry(&page_fault_handler,    0, 0, gate::interrupt);
            m_entries[16] = entry(&fpu_fault_handler,     0, 0, gate::interrupt);
            m_entries[17] = entry(&align_check_handler,   0, 0, gate::interrupt);
            m_entries[18] = entry(&machine_check_handler, 0, 0, gate::interrupt);
            m_entries[19] = entry(&simd_fault_handler,    0, 0, gate::interrupt);
            m_entries[20] = entry(&virt_fault_handler,    0, 0, gate::interrupt);
            m_entries[30] = entry(&sec_fault_handler,     0, 0, gate::interrupt);

            asm volatile
            (
                    "lidt %0"
                    :
                    : "m" (m_pointer)
            );
        }

        // Useful information for debugging
        using interrupt_frame = struct __attribute__((packed))
        {
            u64 r15;
            u64 r14;
            u64 r13;
            u64 r12;
            u64 r11;
            u64 r10;
            u64 r9;
            u64 r8;
            u64 rdi;
            u64 rsi;
            u64 rbp;
            u64 rdx;
            u64 rcx;
            u64 rbx;
            u64 rax;

            u64 ident;

            // Error code will always be present, even for exceptions without one, in which case it will be zero
            u64 error;

            u64 rip;
            u64 cs;
            u64 eflags;
            u64 rsp;
            u64 ss;
        };

        const char *exceptions[] =
        {
            "Divide by zero",
            "Debug",
            "Non-maskable interrupt",
            "Breakpoint",
            "Overflow",
            "Out of bounds",
            "Invalid Opcode",
            "Device not found",
            "Double fault",
            "Invalid",
            "Invalid TSS",
            "Segment not present",
            "Stack segment fault",
            "General protection",
            "Paging",
            "Invalid",
            "Floating point",
            "Alignment check",
            "Machine check",
            "SIMD",
            "Virtualization",
            "Invalid",
            "Invalid",
            "Invalid",
            "Invalid",
            "Invalid",
            "Invalid",
            "Invalid",
            "Invalid",
            "Invalid",
            "Invalid",
            "Security"
        };

        extern "C" void exception_handler(interrupt_frame *frame)
        {
            print("\nFatal: {} exception occurred\nInterrupt frame:\n", exceptions[frame->ident]);
            print
            (
                "\tR15: {h}\n\tR14: {h}\n\tR14: {h}\n\tR13: {h}\n\tR11: {h}\n\tR10: {h}\n\tR9: {h}\n\tR8: {h}\n\tRDI: {h}\n\tRSI: {h}\n\tRBP: {h}\n\tRDX: {h}\n\tRCX: {h}\n\tRBX: {h}\n\tRAX: {}\n\tError Code: {b}\n\tRIP: {h}\n\tCS: {h}\n\tRSP: {h}\n\tSS: {h}\nend\n\n",
                frame->r15,
                frame->r14,
                frame->r13,
                frame->r12,
                frame->r11,
                frame->r10,
                frame->r9,
                frame->r8,
                frame->rdi,
                frame->rsi,
                frame->rbp,
                frame->rdx,
                frame->rcx,
                frame->rbx,
                frame->rax,
                frame->error,
                frame->rip,
                frame->cs,
                frame->eflags,
                frame->rsp,
                frame->ss
            );
        }
    }
}