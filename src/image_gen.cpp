#include "image_gen.h"
#include "fractal_gen.h"

#define cimg_display 0
#include "CImg.h"
using namespace cimg_library;

void ImageGen::render_frames(std::string fname, int framerate)
{
    ImageGen::ah.load_data(fname);
    ImageGen::ah.set_framerate(framerate);
    ImageGen::ah.update_frames();
    std::vector<float> frames = ImageGen::ah.get_frames();
#if defined(_WIN32)
    _mkdir("../result");
#else
    mkdir("../result", 0777);
#endif
    for (int i = 1; i <= frames.size(); i++)
    {
        char buf[50];
        std::sprintf(buf, "../result/%d.jpg", i);
        ImageGen::save_frame_at(frames[i - 1], 0.0, buf);
        std::printf("%.1f%%\n", i*100.0/frames.size());
    }
}

void ImageGen::save_frame_at(float cx, float cy, char fname[])
{

    CImg<unsigned int> img(ImageGen::width, ImageGen::height, 1, 3, 0);
    for (int x = 0; x < ImageGen::width; x++)
    {
        for (int y = 0; y < ImageGen::height; y++)
        {
            int it = julia_set(
                ImageGen::scale * (float(x) / ImageGen::width - 0.5),
                ImageGen::scale * (float(y) / ImageGen::width - 0.5),
                cx, cy, ImageGen::max_iters);
            img(x, y, 0) = 255 * it / ImageGen::max_iters;
            img(x, y, 1) = 255 * it / ImageGen::max_iters;
            img(x, y, 2) = 255 * it / ImageGen::max_iters;
        }
    }
    img.save(fname);
}

void ImageGen::setScale(float scale)
{
    ImageGen::scale = scale;
}
void ImageGen::setGain(float gain){
    ImageGen::gain = gain;
}
ImageGen::ImageGen(int width, int height, int max_iters)
{
    ImageGen::width = width;
    ImageGen::height = height;
    ImageGen::max_iters = max_iters;
    ImageGen::scale = 2.0;
    ImageGen::ah = AudioHandler();
    ImageGen::gain = 1.0;
}