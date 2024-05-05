export module io;

import font;
import types;
import integral;
import framebuffer;

static usize g_cursor_x;
static usize g_cursor_y;

export void put_char(const char c)
{
    if (c == '\n')
    {
        g_cursor_x = 0;
        g_cursor_y += g_font_height;
    }
    else if (c == '\t')
    {
        // TODO: What behaviour do we want on newline
        if (g_cursor_x != 0)
        {
            g_cursor_x += g_cursor_x % (4 * 8);
        }
        else
        {
            g_cursor_x += 4 * 8;
        }
    }
    else
    {
        framebuffer::draw_char(g_cursor_x, g_cursor_y, c, 0xFFFFFF, 0x000000);

        if (g_cursor_x > framebuffer::width())
        {
            g_cursor_x = 0;
            g_cursor_y += g_font_height;
        }
        else
        {
            g_cursor_x += g_font_width;
        }
    }
}

export void put_string(const char *s)
{
    for (usize i = 0; s[i] != '\0'; i++)
    {
        put_char(s[i]);
    }
}