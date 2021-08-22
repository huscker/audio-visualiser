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
        std::vector<float> data;
        std::vector<std::complex<float>> frames;
        
        void fft(std::valarray<std::complex<double>>& x);
        float filter_smooth(float x,float gain,float fallout,float bias);
    public:
        AudioHandler();
        AudioHandler(std::string fname, int framerate);
        void set_framerate(int framerate);
        void load_data(std::string fname);
        void update_frames(modes mode,float fallout, float gain,float bias,float fallout2=0.0,float gain2=0.0,float bias2=0.0);
        std::vector<std::complex<float>> get_frames();
};

#endif 