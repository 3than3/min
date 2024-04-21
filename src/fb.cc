#include <fb.hh>
#include <font.hh>

bool framebuffer::init(struct limine_framebuffer_request &request)
{
    if ( request.response == nullptr || request.response->framebuffer_count < 1)
    {
        return false;
    }

    auto *limine_fb = request.response->framebuffers[0];

    self() = framebuffer
    (
            limine_fb->width,
            limine_fb->height,
            limine_fb->pitch / 4,
            static_cast<u32 *>(limine_fb->address)
    );

    return true;
}

framebuffer &framebuffer::self()
{
    static framebuffer instance;
    return instance;
}

void framebuffer::draw_px(u64 x, u64 y, u32 color)
{
    m_buffer[m_pitch * y + x] = color;
}

// TODO: This is not efficient. At a minimun each line should be a memset,
//       however memset basically does a for-loop. Rep movs* will be better
void framebuffer::draw_rect(u64 x, u64 y, u64 width, u64 height, u32 color)
{
    for (usize y1 = 0; y1 < height; y1++) {
        usize where = m_pitch * (y + y1) + x;

        for (usize x1 = 0; x1 < width; x1++)
        {
            m_buffer[where + x1] = color;
        }
    }
}

void framebuffer::draw_char(u64 x, u64 y, char c, u32 fg_color, u32 bg_color)
{
    auto glyph = &FONT[c * 16];

    for (usize y1 = 0; y1 < 16; y1++)
    {
        for (usize x1 = 0; x1 < 8; x1++)
        {
            if ((glyph[y1] >> x1 & 1) == 1)
            {
                draw_px(x + 7 - x1, y + y1, fg_color);
            }
            else
            {
                draw_px(x + 7 - x1, y + y1, bg_color);
            }
        }
    }
}
