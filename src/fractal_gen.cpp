#include "fractal_gen.h"
#include <complex>
#include <math.h>

int julia_set(float x, float y, float cx, float cy, const int max_iters)
{
    float tempx;
    for (int i = 0; i < max_iters; i++)
    {
        tempx = x;
        x = x * x - y * y + cx;
        y = 2.0 * tempx * y + cy;
        if (x * x + y * y >= 4.0)
        {
            return i;
        }
    }
    return max_iters;
}
int julia_set_complex(std::complex<float> z, std::complex<float> c, const int max_iters)
{
    for (int i = 0; i < max_iters; i++)
    {
        z = z * z + c;
        if (std::abs(z) >= 2.0)
        {
            return i;
        }
    }
    return 0;
}
float julia_set_complex_rgb(std::complex<float> z, std::complex<float> c, const int max_iters)
{
    float sc = 0.0;
    for (int i = 0; i < max_iters; i++)
    {
        z = z * z + c;
        sc += std::exp2f(-std::abs(z));
        if (std::abs(z) >= 2.0)
        {
            break;
        }
    }
    return sc;
}
void colorise_smooth(colors color,float sc, int &red, int &green, int &blue)
{
    switch (color)
    {
    case colors::red:
        red = std::min(255, int((0.1+0.25 * sc) * 255));
        green = std::min(255, int(0.09 * sc * 255));
        blue = std::min(255, int(0.09 * sc * 255));
        break;
    case colors::green:
        red = std::min(255, int(0.15 * sc * 255));
        green = std::min(255, int((0.1+0.25 * sc) * 255));
        blue = std::min(255, int(0.1 * sc * 255));
        break;
    case colors::blue:
        red = std::min(255, int((0.05+0.13 * sc) * 255));
        green = std::min(255, int((0.05+0.16 * sc) * 255));
        blue = std::min(255, int((0.1+0.3 * sc) * 255));
        break;
    case colors::purple:
        red = std::min(255, int((0.1+0.2 * sc) * 255));
        green = std::min(255, int(0.1 * sc * 255));
        blue = std::min(255, int(0.2 * sc * 255));
        break;
    case colors::white:
        red = std::min(255, int((0.1+0.13 * sc) * 255));
        green = std::min(255, int((0.1+0.13 * sc) * 255));
        blue = std::min(255, int((0.1+0.13 * sc) * 255));
        break;
    case colors::orange:
        red = std::min(255, int((0.1+0.32 * sc) * 255));
        green = std::min(255, int((0.1+0.2 * sc) * 255));
        blue = std::min(255, int((0.1+0.1 * sc) * 255));
        break;
    case colors::wavy:
        red = std::min(255, int(std::sin(std::pow(sc,2.0)*0.02) * 255));
        green = std::min(255, int(std::sin(std::pow(sc,2.0)*0.03)* 255));
        blue = std::min(255, int(std::sin(std::pow(sc,2.0)*0.035) * 255));
        break;
    }
            
}