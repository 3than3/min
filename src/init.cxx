import util;
import types;
import kernel;
import limine;
import framebuffer;

namespace
{
    volatile auto limine_revision = limine::base_revision<1>;

    volatile limine::framebuffer_request framebuffer_request =
    {
        // TODO: Find a less atrocious way of doing this
        .id =
        {
                0xc7b1dd30df4c8b88,
                0x0a82e883a194f07b,
                0x9d5827dcd881dd75,
                0xa3148604f6fab11b
        },
        .revision = 0,
        .response = nullptr
    };
}

// Global constructor arrays
extern void (*__init_array[])();
extern void (*__init_array_end[])();

// Role of _init
//   1. Call global constructors.
//   2. Set up a way for the kernel to output information (usually framebuffer).
extern "C" void _init()
{
    // Call global constructors
    for (usize i = 0; &__init_array[i] != __init_array_end; i++)
    {
        __init_array[i]();
    }

    // Initialize framebuffer, or hang, there isn't anything better to do
    if (!framebuffer::init(const_cast<limine::framebuffer_request &>(framebuffer_request)))
    {
        au::endless_hang();
    }

    main();
}