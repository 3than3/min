export module fmt;

import io;
import types;
import integral;

constexpr char base_2[] = "01";
constexpr char base_10[] = "0123456789";
constexpr char base_16[] = "0123456789abcdef";

void put_bin(usize value)
{
    put_string("0b");

    if (value == 0)
    {
        put_string("0");
        return;
    }

    char buffer[64] = {0};

    for (usize i = 63; value != 0; i--)
    {
        buffer[i] = base_2[value % 2];
        value /= 2;
    }

    for (char c : buffer)
    {
        if (c != '\0')
        {
            put_char(c);
        }
    }
}

void put_dec(usize value)
{
    if (value == 0)
    {
        put_string("0");
        return;
    }

    char buffer[32] = {0};

    for (usize i = 31; value != 0; i--)
    {
        buffer[i] = base_10[value % 10];
        value /= 10;
    }

    for (char c : buffer)
    {
        if (c != '\0')
        {
            put_char(c);
        }
    }
}

void put_hex(usize value)
{
    put_string("0h");

    if (value == 0)
    {
        put_string("0");
        return;
    }

    char buffer[16] = {0};

    for (usize i = 15; value != 0; i--)
    {
        buffer[i] = base_16[value % 16];
        value /= 16;
    }

    for (char c : buffer)
    {
        if (c != '\0')
        {
            put_char(c);
        }
    }
}

// Printing routines for all types
template<au::integral t>
void print_arg(t arg, const char specifier)
{
    // Only send absolute value to printing
    ssize absolute = 1;
    if (arg < 0)
    {
        put_char('-');
        absolute = -1;
    }

    if (specifier == 'd' || specifier == '\0')
    {
        put_dec(arg * absolute);
    }
    else if (specifier == 'h')
    {
        put_hex(arg * absolute);
    }
    else if (specifier == 'b')
    {
        put_bin(arg * absolute);
    }
    else
    {
        put_string("<Unknown format specifier>");
    }
}

void print_arg(bool arg, const char specifier)
{
    if (specifier != '\0')
    {
        put_string("<Cannot format boolean>");
        return;
    }

    if (arg)
    {
        put_string("true");
    }
    else
    {
        put_string("false");
    }
}

// Actual printng interface
export void print(const char *fmt)
{
    put_string(fmt);
}

export template<typename t, typename... args>
void print(const char *fmt, t arg, args... other_args)
{
    while (*fmt != '\0')
    {
        if (*fmt == '{')
        {
            // Check for format specifiers
            if (*(fmt + 1) != '}')
            {
                print_arg(arg, *(fmt + 1));
                fmt += 3;
                print(fmt, other_args...);
            }
            else
            {
                print_arg(arg, '\0');
                fmt += 2;
                print(fmt, other_args...);
            }
            return;
        }
        else
        {
            put_char(*fmt);
            fmt++;
        }
    }
}