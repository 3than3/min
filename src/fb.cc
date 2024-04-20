#include <fb.hh>

bool framebuffer::init(struct limine_framebuffer_request &request)
{
    if ( request.response == nullptr || request.response->framebuffer_count < 1)
    {
        return false;
    }

    auto *limine_fb = request.response->framebuffers [0];

    self() = framebuffer(limine_fb->width, limine_fb->height, limine_fb->pitch, static_cast<u32 *>(limine_fb->address));

    return true;
}

framebuffer &framebuffer::self()
{
    static framebuffer instance;
    return instance;
}

void framebuffer::draw_px(u64 x, u64 y, u32 color)
{
    m_address[m_pitch / 4 * y + x] = color;
}
