#ifndef AUDIO_HANDLER_H
#define AUDIO_HANDLER_H

#include <string>
#include <vector>
#include <complex>
#include <valarray>

class AudioHandler{
    private:
        std::string fname;
        int bitrate;
        int framerate;
        std::vector<float> data;
        std::vector<float> frames;
    public:
        void set_framerate(int framerate);
        void load_data(std::string fname);
        void update_frames();
        std::vector<float> get_frames();
        float filter_smooth(float x,float gain,float fallout,float bias);
        void fft(std::valarray<std::complex<double>>& x);
};

#endif 