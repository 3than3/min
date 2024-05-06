export module kernel;

import fmt;
import util;
import require;
import framebuffer;

import amd64;

export void main()
{
    amd64::init();

    print("Initialisation complete...\n");

    //au::require(false);

    panic("Boogabooga\n");

    au::endless_hang();
}