#include "src/image_gen.h"
#include <vector>
int main(){
    ImageGen ig(200,200,100);
    ig.setScale(4.0);
    ig.render_frames("test2.wav",60);
    return 0;
}