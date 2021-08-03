#ifndef AUDIO_HANDLER_H
#define AUDIO_HANDLER_H

#include <string>
#include <vector>
#include <complex>
#include <valarray>
#include "parametric_location.h"

class AudioHandler{
    private:
        std::string fname;
        int bitrate;
        int framerate;
        float bias;
        float fallout;
        float gain;
        std::vector<float> data;
        std::vector<std::complex<float>> frames;
    public:
        void set_framerate(int framerate);
        void load_data(std::string fname);
        void update_frames(modes mode,float fallout, float gain,float bias,float fallout2,float gain2,float bias2);
        std::vector<std::complex<float>> get_frames();
        float filter_smooth(float x,float gain,float fallout,float bias);
        void fft(std::valarray<std::complex<double>>& x);
};

#endif 