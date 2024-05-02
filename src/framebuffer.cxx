export module framebuffer;

import font;
import types;
import limine;

export class framebuffer
{
public:
    // We need a default constructor for the singleton pattern, as otherwise
    // _cxa_guard_acquire is needed. I do not understand cpp well enough yet to come up
    // with something better
    framebuffer() = default;

    framebuffer(u64 width, u64 height, u64 pitch, u32 *address):
            m_width(width),
            m_height(height),
            m_pitch(pitch),
            m_buffer(address)
    {}

    static framebuffer &self()
    {
        static framebuffer instance;
        return instance;
    }

    static bool init(limine::framebuffer_request &request)
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

    void draw_px(u64 x, u64 y, u32 color)
    {
        m_buffer[m_pitch * y + x] = color;
    }

    // TODO: This is not efficient. At a minimun each line should be a memset,
    //       however memset basically does a for-loop. Rep movs* will be better
    void draw_rect(u64 x, u64 y, u64 width, u64 height, u32 color)
    {
        for (usize y1 = 0; y1 < height; y1++) {
            usize where = m_pitch * (y + y1) + x;

            for (usize x1 = 0; x1 < width; x1++)
            {
                m_buffer[where + x1] = color;
            }
        }
    }

    void draw_char(u64 x, u64 y, char c, u32 fg_color, u32 bg_color)
    {
        auto glyph = &g_font[c * 16];

        for (usize y1 = 0; y1 < g_font_height; y1++)
        {
            for (usize x1 = 0; x1 < g_font_width; x1++)
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

    u64 width() const
    {
        return m_width;
    }

    u64 height() const
    {
        return m_height;
    }

private:
    // All values are in pixels
    u64  m_pitch;
    u64  m_width;
    u64  m_height;
    u32 *m_buffer;
};