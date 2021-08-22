#ifndef IMAGE_GEN_H
#define IMAGE_GEN_H

#include "audio_handler.h"
#include "fractal_gen.h"
#include "parametric_location.h"
#include <string>
#include <complex>

class ImageGen{
    private:
        int width;
        int height;
        float scale;
        int max_iters;
    public:
        ImageGen(int width,int height,int max_iters);
        void setScale(float scale);
        void save_frame_at(std::complex<float> c,colors color,char fname[]);
        void render_frames(std::string output_dir,AudioHandler &ah,colors color,int startframe = 1); // startframe doesnt work on all modes

};

#endif // !IMAGE_GEN_H