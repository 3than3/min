export module kernel;

import fmt;
import util;
import require;
import framebuffer;

import types;
import optional;

import amd64;

export void main()
{
    amd64::init();

    print("Initialisation complete...\n");

    auto option = au::optional<u32>();

    if (option.valid())
    {
        print("{}", option.unwrap());
    }
    else
    {
        option = 5;
        print("{}", option.unwrap());
    }


    au::endless_hang();
}