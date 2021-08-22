#include <unistd.h>
#include "src/parametric_location.h"
#include "src/image_gen.h"
int main(){
    const int framerate = 60;
    std::string input("");
    std::string output_dir("");
    AudioHandler ah(input,60);
    ImageGen ig(100,100,50);
    ah.update_frames(modes::psychodelic,200.0,1/40.0,500.0);
    ig.setScale(4.0);
    /*
    std::string output_dir = get_current_dir_name();
    output_dir = output_dir + "/result";
    std::printf("%s\n",output_dir.c_str());
    */
    ig.render_frames(output_dir.c_str(),ah,colors::wavy);
    return 0;
}