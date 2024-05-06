export module debug_info;

import types;

export namespace au
{
    // Design sourced from:
    //      https://github.com/paweldac/source_location/blob/master/include/source_location/source_location.hpp
    //
    // Usage:
    // function(au::debug_info dbg = au::debug_info::current())
    //      - dbg will contain the location of the call site for function
    struct debug_info
    {
    public:
        static constexpr debug_info current
        (
            const char* file_name = __builtin_FILE(),
            const char* func_name = __builtin_FUNCTION(),
            const usize line      = __builtin_LINE(),
            const usize column    = __builtin_COLUMN()
        )
        {
            return {file_name, func_name, line, column};
        }

        const char *file_name() const
        {
            return m_file_name;
        }

        const char *func_name() const
        {
            return m_func_name;
        }

        const usize line() const
        {
            return m_line;
        }

        const usize column() const
        {
            return m_column;
        }

    private:
        constexpr debug_info(const char *file_name, const char *func_name, const usize line, const usize column):
            m_file_name(file_name),
            m_func_name(func_name),
            m_line(line),
            m_column(column)
        {}

        const char  *m_file_name;
        const char  *m_func_name;
        const usize  m_line;

        // NOTE: Column-offset is only provided by clang, expect issues on gcc
        const usize m_column;
    };
}