#ifndef FRACTAL_GEN_H
#define FRACTAL_GEN_H
#include <complex>

enum colors{red,green,blue,purple,white,orange};

int julia_set(float x,float y,float cx,float cy,const int max_iters);
int julia_set_complex(std::complex<float> z,std::complex<float> c,const int max_iters);
float julia_set_complex_rgb(std::complex<float> z,std::complex<float> c, const int max_iters,int &red,int &green,int &blue);
void colorise_smooth(colors color,float sc,int &red,int &green,int &blue);

#endif // !FRACTAL_GEN_H