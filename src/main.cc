#include <util.hh>
#include <framebuffer.hh>
#include <print.hh>

void kmain()
{
    //print("Hey there {} {}", 32, 32);
    put_string("Hey there");
    au::endless_hang();
}
