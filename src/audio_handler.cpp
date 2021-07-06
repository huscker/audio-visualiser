#include "audio_handler.h"
#include <string>
#include <vector>
#include <numeric>
#include <complex>
#include <valarray>
#include "AudioFile.h"

void AudioHandler::update_frames()
{
    AudioHandler::frames.clear();
    int max_frames = AudioHandler::data.size() * AudioHandler::framerate / AudioHandler::bitrate - 1;
    int margin = 2;
    for (int i = margin; i < max_frames - margin; i++)
    {
        std::vector<float> f;
        std::valarray<std::complex<double>> temp;
        temp.resize(2 * margin * AudioHandler::bitrate / AudioHandler::framerate + 1);
        std::copy(AudioHandler::data.begin() + (i - margin) * AudioHandler::bitrate / AudioHandler::framerate,
                  AudioHandler::data.begin() + (i + margin) * AudioHandler::bitrate / AudioHandler::framerate,
                  std::begin(temp));
        fft(temp);
        for (int i = 0; i < temp.size(); i++)
        {
            if ((AudioHandler::framerate * i) / (2 * margin + 1) > 16000)
            {
                break;
            }
            f.push_back(std::abs(temp[i]) * filter_smooth((AudioHandler::framerate * i) / (2 * margin + 1), 1.0 / 25.0, 750.0, 4000.0));
        }
        AudioHandler::frames.push_back(std::accumulate(f.begin(), f.end(), 0.0));
    }
}

void AudioHandler::load_data(std::string fname)
{
    fname = "../" + fname;
    if (AudioHandler::fname != fname)
    { // update only if changed
        AudioHandler::fname = fname;
        AudioFile<float> a;
        bool loadedOK = a.load(AudioHandler::fname);
        assert(loadedOK);
        AudioHandler::data = a.samples[0];
        AudioHandler::bitrate = a.getSampleRate();
    }
}

void AudioHandler::set_framerate(int framerate)
{
    AudioHandler::framerate = framerate;
}

std::vector<float> AudioHandler::get_frames()
{
    return AudioHandler::frames;
}

float AudioHandler::filter_smooth(float x, float gain, float fallout, float bias)
{
    return gain / (1 + (x - bias) * (x - bias) / fallout);
}

void AudioHandler::fft(std::valarray<std::complex<double>> &x)
{
    const size_t N = x.size();
    if (N <= 1)
        return;
    std::valarray<std::complex<double>> even = x[std::slice(0, N / 2, 2)];
    std::valarray<std::complex<double>> odd = x[std::slice(1, N / 2, 2)];
    fft(even);
    fft(odd);
    for (size_t k = 0; k < N / 2; ++k)
    {
        std::complex<double> t = std::polar(1.0, -2 * 3.141592653589793238460 * k / N) * odd[k];
        x[k] = even[k] + t;
        x[k + N / 2] = even[k] - t;
    }
}