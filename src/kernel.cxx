export module kernel;

import util;
import framebuffer;

export void main()
{
    framebuffer::self().draw_char(0, 0, 'H', 0xFFFFFF, 0x000000);
    au::endless_hang();
}