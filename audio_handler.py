import audio2numpy

class AudioHandler:
    def __init__(self):
        self.fname = None
        self.bitrate = None
        self.data = None
        self.frames = None
        self.framerate = None
    def load_data(self,fname,force=False):
        if self.fname != fname or force: # update only if changed
            self.fname = fname
            self.data,self.bitrate = audio2numpy.open_audio(self.fname)
    def set_framerate(self,framerate):
        self.framerate = framerate
    def update_frames(self):
        self.frames = list()  # [x,y]
        for i in range(len(self.data) * self.framerate // self.bitrate):
            t = self.data[i * self.bitrate // self.framerate:(i + 1) * self.bitrate // self.framerate]
            self.frames.append([sum(t) / len(t), 0])
    def get_frames(self):
        return self.frames
