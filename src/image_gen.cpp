#include "image_gen.h"
#include "fractal_gen.h"
#include <complex>
#include <exception>
#define cimg_display 0
//#define DEBUG

#include "CImg.h"
using namespace cimg_library;

void ImageGen::render_frames(std::string output_dir,AudioHandler &ah,colors color,int startframe)
{
    std::vector<std::complex<float>> frames = ah.get_frames();
    if (1 > startframe && startframe > frames.size()){
        throw std::invalid_argument("startframe should be in [1;frames.size()]");
    }
#if defined(_WIN32)
    _mkdir(output_dir.c_str());
#else
    mkdir(output_dir.c_str(), 0777);
#endif
    for (int i = startframe; i <= frames.size(); i++)
    {

        char buf[100];
        std::string output_file = std::string(output_dir) + "/%d.jpg";
        std::sprintf(buf, output_file.c_str(), i);
        ImageGen::save_frame_at(frames[i - 1],color, buf);
        std::printf("%d %d\n", i, frames.size());
    }
}

void ImageGen::save_frame_at(std::complex<float> c,colors color, char fname[])
{

    CImg<unsigned int> img(ImageGen::width, ImageGen::height, 1, 3, 0);
    for (int x = 0; x < ImageGen::width; x++)
    {
        for (int y = 0; y < ImageGen::height; y++)
        {
#ifdef DEBUG
            if (std::abs(ImageGen::scale * (float(x) / ImageGen::width - 0.5) - std::real(c)) + std::abs(ImageGen::scale * (float(y) / ImageGen::width - 0.5) - std::imag(c)) <= 0.1)
            {
                img(x, y, 0) = 255;
                img(x, y, 1) = 0;
                img(x, y, 2) = 0;
            }
#endif // DEBUG
#ifndef DEBUG
            int red = 0;
            int blue = 0;
            int green = 0;
            std::complex<float> z(ImageGen::scale * (float(x) / ImageGen::width - 0.5), ImageGen::scale * (float(y) / ImageGen::width - 0.5));
            float sc = julia_set_complex_rgb(z, c, ImageGen::max_iters);
            colorise_smooth(color,sc,red,green,blue);
            img(x, y, 0) = red;
            img(x, y, 1) = green;
            img(x, y, 2) = blue;
#endif // !DEBUG
        }
    }
    img.save(fname);
}

void ImageGen::setScale(float scale)
{
    ImageGen::scale = scale;
}
ImageGen::ImageGen(int width, int height, int max_iters)
{
    ImageGen::width = width;
    ImageGen::height = height;
    ImageGen::max_iters = max_iters;
    ImageGen::scale = 2.0;
}