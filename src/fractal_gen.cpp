#include "fractal_gen.h"

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