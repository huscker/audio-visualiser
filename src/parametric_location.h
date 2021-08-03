#ifndef LOCATION_CHOOSE_H
#define LOCATION_CHOOSE_H
#include <complex>

enum modes {
    standart,
    standart_both,
    swapped,
    swapped_remembering,
    psychodelic,
    random_path,
    random_path_different,
    random_path_swapped,
    random_path_swapped_both
};

class LocationChoose{
    struct point;
    private:
        point *points;
        modes mode;
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
        std::complex<float> random_path_swapped_both(float high,float low);
    public:
        LocationChoose(modes mode,int max_frames,int n_points = 1);
        ~LocationChoose();
        std::complex<float> get(float high,int i,float low = 0.0);
};
#endif