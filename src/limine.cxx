export module limine;

import array;
import types;

export namespace limine
{
    // Base revision
    template<u64 rev>
    constexpr u64 base_revision[3] = {0xf9562b2d5c95a6c8, 0x6a7b384944536bdc, rev};

    // Framebuffers
    using video_mode = struct
    {
        u64 pitch;
        u64 width;
        u64 height;
        u16 bpp;
        u8  memory_model;
        u8  red_mask_size;
        u8  red_mask_shift;
        u8  green_mask_size;
        u8  green_mask_shift;
        u8  blue_mask_size;
        u8  blue_mask_shift;
    };

    using framebuffer = struct
    {
        void *address;
        u64   width;
        u64   height;
        u64   pitch;
        u16   bpp;
        u8    memory_model;
        u8    red_mask_size;
        u8    red_mask_shift;
        u8    green_mask_size;
        u8    green_mask_shift;
        u8    blue_mask_size;
        u8    blue_mask_shift;
        u8    unused[7];
        u64   edid_size;
        void *edid;

        // Response revision 1
        u64          mode_count;
        video_mode **modes;
    };

    using framebuffer_response = struct
    {
        u64           revision;
        u64           framebuffer_count;
        framebuffer **framebuffers;
    };

    using framebuffer_request = struct
    {
        u64                   id[4];
        u64                   revision;
        framebuffer_response *response;
    };
}