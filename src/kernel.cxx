export module kernel;

import fmt;
import util;
import framebuffer;

export void main()
{
    print("Hello {b}", 0b100001);
    au::endless_hang();
}