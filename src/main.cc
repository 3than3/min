#include <util.hh>
#include <types.hh>
#include <limine.h>
#include <fb.hh>

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

// Global constructor arrays
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

    framebuffer::init(const_cast<limine_framebuffer_request &>(framebuffer_request));

    framebuffer::self().draw_px(10, 10, 0xFFFFFF);

    au::endless_hang();
}
