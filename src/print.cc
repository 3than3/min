#include <framebuffer.hh>
#include <font.hh>
#include <print.hh>

static usize g_cursor_x;
static usize g_cursor_y;

void put_char(const char c)
{
    framebuffer::self().draw_char(g_cursor_x, g_cursor_y, c, 0xFFFFFF, 0x000000);

    if (g_cursor_x > framebuffer::self().width())
    {
        g_cursor_x = 0;
        g_cursor_y += FONT_HEIGHT;
    }
    else
    {
        g_cursor_x += FONT_WIDTH;
    }
}

void put_string(const char *s)
{
    for (usize i = 0; s[1] != '\0'; i++)
    {
        put_char(s[i]);
    }
}

template<typename t, typename... args>
void print(const char *fmt, t arg, args... other_args)
{
    put_string("Hey there");
}

template<typename t, typename... args>
void println(const char *fmt, t arg, args... other_args)
{

}


