export module framebuffer;

import font;
import types;
import limine;

namespace framebuffer
{
    u64   m_pitch;
    u64   m_width;
    u64   m_height;
    u32  *m_buffer;
    bool  m_initialized;

    export void init(volatile limine::framebuffer_request &request)
    {
        if (request.response == nullptr || request.response->framebuffer_count < 1)
        {
            m_initialized = false;
            return;
        }

        auto *limine_fb = request.response->framebuffers[0];

        m_width  = limine_fb->width;
        m_height = limine_fb->height;
        m_pitch  = limine_fb->pitch / 4;
        m_buffer = static_cast<u32 *>(limine_fb->address);

        m_initialized = true;
    }

    export void draw_px(u64 x, u64 y, u32 color)
    {
        m_buffer[m_pitch * y + x] = color;
    }

    // TODO: This is not efficient. At a minimun each line should be a memset,
    //       however memset basically does a for-loop. Rep movs* will be better
    export void draw_rect(u64 x, u64 y, u64 width, u64 height, u32 color)
    {
        for (usize y1 = 0; y1 < height; y1++) {
            usize where = m_pitch * (y + y1) + x;

            for (usize x1 = 0; x1 < width; x1++)
            {
                m_buffer[where + x1] = color;
            }
        }
    }

    export void draw_char(u64 x, u64 y, char c, u32 fg_color, u32 bg_color)
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

    export u64 width()
    {
        return m_width;
    }

    export u64 height()
    {
        return m_height;
    }

    export bool initialized()
    {
        return m_initialized;
    }
}