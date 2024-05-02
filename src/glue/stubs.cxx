import util;

extern "C"
{
    int __cxa_atexit(void (*)(void *), void *, void *)
    {
        return 0;
    }

    void __cxa_pure_virtual()
    {
        au::endless_hang();
    }
}
