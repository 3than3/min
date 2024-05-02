export module util;

namespace au
{
    export [[noreturn]] void endless_hang()
    {
        asm ("cli");

        while (true)
        {
            asm ("hlt");
        }
    }
}