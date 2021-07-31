#ifndef FRACTAL_GEN_H
#define FRACTAL_GEN_H
#include <complex>


int julia_set(float x,float y,float cx,float cy,const int max_iters);
int julia_set_complex(std::complex<float> z,std::complex<float> c,const int max_iters);
void julia_set_complex_rgb(std::complex<float> z,std::complex<float> c, const int max_iters,unsigned int &red,unsigned int &green,unsigned int &blue);

#endif // !FRACTAL_GEN_H