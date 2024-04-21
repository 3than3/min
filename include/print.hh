#pragma once

void put_string(const char *s);

template<typename t, typename... args>
void print(const char *fmt, t arg, args... other_args);

template<typename t, typename... args>
void println(const char *fmt, t arg, args... other_args);