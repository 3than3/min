import types;

// Do not modify the following, compiler will generate calls to them, and expects certain behavior
// TODO: Fast memcpy (rep movsb)
extern "C" {
    void *memcpy(void *dest, const void *src, usize n)
    {
        u8 *pdest = static_cast<u8 *>(dest);
        const u8 *psrc = static_cast<const u8 *>(src);

        for (usize i = 0; i < n; i++)
        {
            pdest[i] = psrc[i];
        }

        return dest;
    }

    void *memset(void *s, int c,usize n)
    {
        u8 *p = static_cast<u8 *>(s);

        for (usize i = 0; i < n; i++)
        {
            p[i] = static_cast<u8>(c);
        }

        return s;
    }

    void *memmove(void *dest, const void *src, usize n)
    {
        u8 *pdest = static_cast<u8 *>(dest);
        const u8 *psrc = static_cast<const u8 *>(src);

        if (src > dest)
        {
            for (usize i = 0; i < n; i++)
            {
                pdest[i] = psrc[i];
            }
        }
        else if (src < dest)
        {
            for (usize i = n; i > 0; i--)
            {
                pdest[i - 1] = psrc[i - 1];
            }
        }

        return dest;
    }

    int memcmp(const void *s1, const void *s2, usize n)
    {
        const u8 *p1 = static_cast<const u8 *>(s1);
        const u8 *p2 = static_cast<const u8 *>(s2);

        for (usize i = 0; i < n; i++)
        {
            if (p1[i] != p2[i])
            {
                return p1[i] < p2[i] ? -1 : 1;
            }
        }

        return 0;
    }
}