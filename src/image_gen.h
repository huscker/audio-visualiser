#ifndef IMAGE_GEN_H
#define IMAGE_GEN_H

#include "audio_handler.h"
#include <string>

class ImageGen{
    private:
        int width;
        int height;
        float scale;
        float gain;
        int max_iters;
        AudioHandler ah;
    public:
        ImageGen(int width,int height,int max_iters);
        void setScale(float scale);
        void setGain(float gain);
        void save_frame_at(float cx,float cy,char fname[]);
        void render_frames(std::string fname,int framerate);

};

#endif // !IMAGE_GEN_H