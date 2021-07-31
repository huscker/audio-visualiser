#include "image_gen.h"
#include "fractal_gen.h"
#include <complex>

#define cimg_display 0
//#define DEBUG
#include "CImg.h"
using namespace cimg_library;

void ImageGen::render_frames(std::string fname, int framerate, int startframe)
{
    ImageGen::ah.load_data(fname);
    ImageGen::ah.set_framerate(framerate);
    ImageGen::ah.update_frames(ImageGen::fallout, ImageGen::gain, ImageGen::bias, ImageGen::fallout2, ImageGen::gain2, ImageGen::bias2);
    std::vector<std::complex<float>> frames = ImageGen::ah.get_frames();
#if defined(_WIN32)
    _mkdir("../result");
#else
    mkdir("../result", 0777);
#endif
    for (int i = startframe; i <= frames.size(); i++)
    {
        char buf[50];
        std::sprintf(buf, "../result/%d.jpg", i);
        ImageGen::save_frame_at(frames[i - 1], buf);
        std::printf("%d %d\n", i, frames.size());
    }
}

void ImageGen::save_frame_at(std::complex<float> c, char fname[])
{

    CImg<unsigned int> img(ImageGen::width, ImageGen::height, 1, 3, 0);
    for (int x = 0; x < ImageGen::width; x++)
    {
        for (int y = 0; y < ImageGen::height; y++)
        {
#ifdef DEBUG
            if (std::abs(ImageGen::scale * (float(x) / ImageGen::width - 0.5) - std::real(c)) + std::abs(ImageGen::scale * (float(y) / ImageGen::width - 0.5) - std::imag(c)) <= 0.1)
            {
                img(x, y, 0) = 255 ;
                img(x, y, 1) = 0 ;
                img(x, y, 2) = 0 ;
            }else{
                img(x, y, 0) = 0 ;
                img(x, y, 1) = 0 ;
                img(x, y, 2) = 0 ;
            }
#endif // DEBUG
#ifndef DEBUG
            if (std::abs(ImageGen::scale * (float(x) / ImageGen::width - 0.5) - std::real(c)) + std::abs(ImageGen::scale * (float(y) / ImageGen::width - 0.5) - std::imag(c)) <= 0.1)
            {
                img(x, y, 0) = 255 ;
                img(x, y, 1) = 0 ;
                img(x, y, 2) = 0 ;
            }else{
                // fast method
                std::complex<float> z(ImageGen::scale * (float(x) / ImageGen::width - 0.5), ImageGen::scale * (float(y) / ImageGen::width - 0.5));
                int it = julia_set_complex(z, c, ImageGen::max_iters);
                img(x, y, 0) = 255 * it / ImageGen::max_iters;
                img(x, y, 1) = 255 * it / ImageGen::max_iters;
                img(x, y, 2) = 255 * it / ImageGen::max_iters;
            }
#endif // !DEBUG
        }
    }
    img.save(fname);
}

void ImageGen::setScale(float scale)
{
    ImageGen::scale = scale;
}
void ImageGen::setFGB(float fallout, float gain, float bias)
{
    ImageGen::gain = gain;
    ImageGen::fallout = fallout;
    ImageGen::bias = bias;
}
void ImageGen::setFGB2(float fallout2, float gain2, float bias2)
{
    ImageGen::gain2 = gain2;
    ImageGen::fallout2 = fallout2;
    ImageGen::bias2 = bias2;
}
ImageGen::ImageGen(int width, int height, int max_iters)
{
    ImageGen::width = width;
    ImageGen::height = height;
    ImageGen::max_iters = max_iters;
    ImageGen::scale = 2.0;
    ImageGen::ah = AudioHandler();
    ImageGen::gain = 1.0 / 40.0;
    ImageGen::fallout = 1000.0;
    ImageGen::bias = 4000.0;
    ImageGen::gain2 = 0.0;
}