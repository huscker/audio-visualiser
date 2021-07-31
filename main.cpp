#include "src/image_gen.h"
int main(){
    ImageGen ig(100,100,50);
    ig.setScale(4.0);
    ig.setFGB(250.0,1/40.0,5500.0);
    //ig.setFGB(100.0,1/100.0,500.0);
    //ig.setFGB2(100.0,1/200.0,500.0);
    ig.render_frames("kattest.wav",60);
    return 0;
}