#include <util.hh>

// Halt and catch fire function.
namespace au
{
    void endless_hang()
    {
        asm ("cli");

        while (true)
        {
            asm ("hlt");
        }
    }
}