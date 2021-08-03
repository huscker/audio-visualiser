#include <unistd.h>
#include "src/parametric_location.h"
#include "src/image_gen.h"
int main(){
    ImageGen ig(100,100,50);
    ig.setScale(4.0);
    ig.setFGB(250.0,1/1.0,5500.0);
    //ig.setFGB(100.0,1/100.0,500.0);
    //ig.setFGB2(100.0,1/200.0,500.0);
    /*
    std::string output_dir = get_current_dir_name();
    output_dir = output_dir + "/result";
    std::printf("%s\n",output_dir.c_str());
    ig.render_frames("./input/kattest.wav",output_dir,60,8,3500);
    */
    ig.render_frames("./input/hop.wav","/home/huscker/work/cpp/fractal-audio-visualiser/build/result",60,modes::random_path_swapped,colors::purple);
    return 0;
}