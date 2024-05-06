export module require;

import fmt;
import util;
import debug_info;

export namespace au
{
    void require(bool expression, debug_info dbg = debug_info::current())
    {
        if (!expression)
        {
            print("\nFatal: requirement not met in {}::{} at {}:{}\n", dbg.file_name(), dbg.func_name(), dbg.line(), dbg.column());
            endless_hang();
        }
    }
}