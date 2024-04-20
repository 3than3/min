#pragma once

#include <types.hh>
#include <limine.h>

using namespace au;

class framebuffer
{
public:
    // We need a default constructor for the singleton pattern, as otherwise
    // _cxa_guard_acquire is needed. I do not understand cpp well enough yet to come up
    // with something better
    framebuffer() = default;

    framebuffer(u64 width, u64 height, u64 pitch, u32* address):
        m_width(width),
        m_height(height),
        m_pitch(pitch),
        m_address(address)
    {}

    static framebuffer &self();

    static bool init(struct limine_framebuffer_request &request);

    void draw_px(u64 x, u64 y, u32 color);
    void draw_rect();
    void draw_char();

    u64 width() const
    {
        return m_width;
    }

    u64 height() const
    {
        return m_height;
    }

private:
    u64  m_pitch;
    u64  m_width;
    u64  m_height;
    u32 *m_address;
};