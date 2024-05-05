export module kernel;

import fmt;
import util;
import framebuffer;

import amd64;

export void main()
{
    amd64::init();

    print("Initialisation complete...\n");
    au::endless_hang();
}