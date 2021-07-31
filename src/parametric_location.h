#ifndef LOCATION_CHOOSE_H
#define LOCATION_CHOOSE_H
#include <complex>

class LocationChoose{
    struct point;
    private:
        point *points;
        int mode;
        int max_frames;
        int n_points;
        float theta;

        std::complex<float> psychodelic(float high,float low);
        std::complex<float> standart(float high, float low);
        std::complex<float> swapped(float high);
        std::complex<float> standart_both(float high,float low);
        std::complex<float> random_path(float high,int i);
        std::complex<float> random_path_different(float high,int i);
        std::complex<float> random_path_swapped(float high);
    public:
        LocationChoose(int mode,int max_frames,int n_points = 1);
        ~LocationChoose();
        std::complex<float> get(float high,int i,float low = 0.0);
};
#endif