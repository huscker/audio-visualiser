# audio-visualiser
https://github.com/adamstark/AudioFile
https://github.com/dtschump/CImg
apt install libpng-dev
gcc version 7.5.0 (thats why experimental/filesystem)

features:
load wav data
generate sequence of png images

make && ./AudioVisualiser && ffmpeg -y -framerate 60 -i ./result/%d.jpg -i ./input/hop.wav -map 0:v -map 1:a -shortest -c:v libx264 -profile:v high -crf 20 -pix_fmt yuv420p ../output.mp4

darude 200.0,1/10.0,500.0
hotncold 250.0,1/40.0,5500.0
