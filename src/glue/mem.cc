#include <types.hh>

extern "C" {
    void *memcpy(void *dest, const void *src, au::usize n)
    {
        au::u8 *pdest = static_cast<au::u8 *>(dest);
        const au::u8 *psrc = static_cast<const au::u8 *>(src);

        for (au::usize i = 0; i < n; i++)
        {
            pdest[i] = psrc[i];
        }

        return dest;
    }

    void *memset(void *s, int c, au::usize n)
    {
        au::u8 *p = static_cast<au::u8 *>(s);

        for (au::usize i = 0; i < n; i++)
        {
            p[i] = static_cast<au::u8>(c);
        }

        return s;
    }

    void *memmove(void *dest, const void *src, au::usize n)
    {
        au::u8 *pdest = static_cast<au::u8 *>(dest);
        const au::u8 *psrc = static_cast<const au::u8 *>(src);

        if (src > dest)
        {
            for (au::usize i = 0; i < n; i++)
            {
                pdest[i] = psrc[i];
            }
        }
        else if (src < dest)
        {
            for (au::usize i = n; i > 0; i--)
            {
                pdest[i - 1] = psrc[i - 1];
            }
        }

        return dest;
    }

    int memcmp(const void *s1, const void *s2, au::usize n)
    {
        const au::u8 *p1 = static_cast<const au::u8 *>(s1);
        const au::u8 *p2 = static_cast<const au::u8 *>(s2);

        for (au::usize i = 0; i < n; i++)
        {
            if (p1[i] != p2[i])
            {
                return p1[i] < p2[i] ? -1 : 1;
            }
        }

        return 0;
    }
}