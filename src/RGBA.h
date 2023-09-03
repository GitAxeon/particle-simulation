#pragma once
#include <cstdint>
#include <iostream>

struct RGBA
{
    RGBA() : r(0), g(0), b(0), a(255) { }
    RGBA(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b), a(255) { }
    RGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) { }

    bool operator==(const RGBA& other)
    {
        return r == other.r && g == other.g && b == other.b && a == other.a;
    }

    bool operator!=(const RGBA& other)
    {
        return (r != other.r) || (g != other.g) || (b != other.b) || (a != other.a);
    }

    friend std::ostream& operator<<(std::ostream& os, const RGBA& rgba)
    {
        os << "(" << +rgba.r << ", " << +rgba.g << ", " << +rgba.b << ", " << +rgba.a << ")";
        return os;
    }

    // uint32_t MapSDL(SDL_PixelFormatEnum formatEnum)
    // {
    //     SDL_PixelFormat* format = SDL_CreatePixelFormat(formatEnum);
        
    //     uint32_t pixel = SDL_MapRGBA(format, this->r, this->g, this->b, this->a);

    //     SDL_DestroyPixelFormat(format);

    //     return pixel;
    // }

    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};