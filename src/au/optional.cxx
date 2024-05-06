export module optional;

import require;
import debug_info;

export namespace au
{
    template <typename type>
    class optional
    {
    public:
        explicit optional(const type &value):
                m_value(value),
                m_valid(true)
        {}

        explicit optional():
                m_valid(false)
        {}

        optional& operator=(const type &value)
        {
            m_value = value;
            m_valid = true;

            return *this;
        }

        bool valid()
        {
            return m_valid;
        }

        type& unwrap(debug_info dbg = debug_info::current())
        {
            require(m_valid, "optional has value", dbg);
            return m_value;
        }

    private:
        bool m_valid;
        type m_value;
    };
}
