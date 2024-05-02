export module verify;

[[noreturn]]
void verify(bool expression, const char* file = __FILE__, int = __LINE__)
{
    while (true);
}
