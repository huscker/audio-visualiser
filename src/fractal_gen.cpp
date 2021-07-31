#include "fractal_gen.h"
#include <complex>
#include <math.h>

int julia_set(float x,float y,float cx,float cy,const int max_iters){
    float tempx;
    for (int i = 0;i<max_iters;i++){
        tempx = x;
        x = x*x-y*y+cx;
        y=2.0*tempx*y+cy;
        if(x*x+y*y>=4.0){
            return i;
        }
    }
    return max_iters;
}
int julia_set_complex(std::complex<float> z,std::complex<float> c,const int max_iters){
    for(int i = 0;i<max_iters;i++){
        z = z*z+c;
        if(std::abs(z) >= 2.0){
            return i;
        }
    }
    return 0;
}
void julia_set_complex_rgb(std::complex<float> z,std::complex<float> c, const int max_iters,unsigned int &red,unsigned int &green,unsigned int &blue){
    float sc = 0.0;
    for(int i = 0;i<max_iters;i++){
        z = z*z+c;
        sc += std::exp2f(-std::abs(z));
        if(std::abs(z) >= 2.0){
            break;
        }
    }
    red = std::min(255,int(0.05*sc*255));
    green = std::min(255,int(0.03*sc*255));
    blue = std::min(255,int(0.07*sc*255));
}