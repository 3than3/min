export module array;

import types;

export namespace au
{
    template<typename value_type, usize size>
    class array
    {
    public:
        // TODO: oob checking
        value_type& operator[](usize index)
        {
            return m_data[index];
        }

        const value_type& operator[](usize index) const
        {
            return m_data[index];
        }

    private:
        value_type m_data[size];
    };
}