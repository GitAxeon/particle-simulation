#pragma once

#include <SDL3/SDL_pixels.h>

#include <cstdint>
#include <iostream>

struct RGBA
{
    RGBA() : r(0), g(0), b(0), a(255) { }
    RGBA(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b), a(255) { }
    RGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) { }

    bool operator==(const RGBA& other)
    {
        return (r == other.r) && (g == other.g) && (b == other.b) && (a == other.a);
    }

    bool operator!=(const RGBA& other)
    {
        return (r != other.r) || (g != other.g) || (b != other.b) || (a != other.a);
    }

    uint32_t MapSDL(SDL_PixelFormatEnum formatEnum)
    {
        SDL_PixelFormat* format = SDL_CreatePixelFormat(formatEnum);
        
        uint32_t pixel = SDL_MapRGBA(format, this->r, this->g, this->b, this->a);

        SDL_DestroyPixelFormat(format);

        return pixel;
    }

    friend std::ostream& operator<<(std::ostream& os, const RGBA& rgba)
    {
        os << "(" << +rgba.r << ", " << +rgba.g << ", " << +rgba.b << ", " << +rgba.a << ")";
        return os;
    }


    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

class ColorMapper
{
public:
    ColorMapper(SDL_PixelFormatEnum format = SDL_PIXELFORMAT_RGBA32)
    {
        m_Format = SDL_CreatePixelFormat(format);
    }
    ~ColorMapper()
    {
        SDL_DestroyPixelFormat(m_Format);
    }

    uint32_t Map(const RGBA& color)
    {
        return SDL_MapRGBA(m_Format, color.r, color.g, color.b, color.a);
    }

private:
    SDL_PixelFormat* m_Format;
};