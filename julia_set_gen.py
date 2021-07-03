from PIL import Image
from audio_handler import AudioHandler
import os

class JuliaGen:
    def __init__(self,width,height,scale,max_iters):
        self.width = width
        self.height = height
        self.scale = scale
        self.max_iters = max_iters
        self.audio_handler = AudioHandler()
    def calc_at(self,x,y,cx,cy):
        for i in range(self.max_iters):
            t = x
            x = x*x-y*y+cx
            y = 2*t*y+cy
            if x*x+y*y >= 4.0:
                return (i*255//self.max_iters,i*255//self.max_iters,i*255//self.max_iters)
        return (255,255,255)
    def save_at_frame(self,cx,cy,fname):
        img = Image.new('RGB',(self.width,self.height),(0,0,0))
        for x in range(self.width):
            for y in range(self.height):
                img.putpixel((x,y),self.calc_at(self.scale*(x/self.width-0.5),self.scale*(y/self.width - 0.5),cx,cy))
        img.save(fname)
    def render_frames(self,fname,framerate,outdir):
        self.audio_handler.load_data(fname)
        self.audio_handler.set_framerate(framerate)
        self.audio_handler.update_frames()
        frames = self.audio_handler.get_frames()
        print(frames)
        os.makedirs(outdir, exist_ok=True)
        for t,el in enumerate(frames):
            self.save_at_frame(el[0],el[1],f'{outdir}/{t+1}.png')