#include <util.hh>
#include <types.hh>
#include <limine.h>

namespace
{
    volatile LIMINE_BASE_REVISION(1);

    volatile limine_framebuffer_request framebuffer_request =
    {
            .id       = LIMINE_FRAMEBUFFER_REQUEST,
            .revision = 0,
            .response = nullptr
    };
}

// Global cnstructor arrays
extern void (*__init_array[])();
extern void (*__init_array_end[])();

extern "C" void _start()
{
    if (LIMINE_BASE_REVISION_SUPPORTED == false)
    {
        au::endless_hang();
    }

    // Call global constructors.
    for (au::usize i = 0; &__init_array[i] != __init_array_end; i++)
    {
        __init_array[i]();
    }

    if
    (
        framebuffer_request.response == nullptr
        || framebuffer_request.response->framebuffer_count < 1
    )
    {
        au::endless_hang();
    }

    limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];

    for (au::usize i = 0; i < 256; i++)
    {
        volatile au::u32 *fb_ptr = static_cast<volatile au::u32 *>(framebuffer->address);
        fb_ptr[i * (framebuffer->pitch / 4) + i] = 0xffffff;
    }

    au::endless_hang();
}
