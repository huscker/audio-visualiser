#include "parametric_location.h"
#include <random>

#define RAND_RESOLUTION 1000
#define RAND_STEP 1.0
#define FAIL_MAX 1000
#define RAND_BOUNDARIES 1.0
#define RAND_VELOCITY 0.2

struct LocationChoose::point
{
    float x;
    float y;
};

std::complex<float> LocationChoose::psychodelic(float high, float low)
{
    return std::polar<float>(
        high,
        low * 2);
}
std::complex<float> LocationChoose::standart(float high, float low)
{
    return std::polar<float>(
        high,
        low / 100);
}
std::complex<float> LocationChoose::swapped(float high)
{
    return std::polar<float>(
        0.5,
        high);
}
std::complex<float> LocationChoose::standart_both(float high, float low)
{
    return std::polar<float>(
        0.4 + high,
        low);
}
std::complex<float> LocationChoose::random_path(float high, int i)
{
    int a = LocationChoose::n_points * i / LocationChoose::max_frames;
    float t = float(i - a * LocationChoose::max_frames / LocationChoose::n_points) * LocationChoose::n_points / LocationChoose::max_frames;
    point p1 = LocationChoose::points[a];
    point p2 = LocationChoose::points[std::min(a+1,LocationChoose::n_points-1)];
    std::complex<float> temp(
        p1.x + (p2.x-p1.x)*t,
        p1.y + (p2.y-p1.y)*t
    );
    temp += std::polar<float>(
        high,
        std::arg(temp)
    );
    return temp;
}
std::complex<float> LocationChoose::random_path_different(float high,int i){
    int a = LocationChoose::n_points * i / LocationChoose::max_frames;
    float t = float(i - a * LocationChoose::max_frames / LocationChoose::n_points) * LocationChoose::n_points / LocationChoose::max_frames;
    point p1 = LocationChoose::points[a];
    point p2 = LocationChoose::points[std::min(a+1,LocationChoose::n_points-1)];
    std::complex<float> temp(
        p1.x + (p2.x-p1.x)*t,
        p1.y + (p2.y-p1.y)*t
    );
    temp += std::polar<float>(
        high-0.25,
        std::atan2(
            (p2.y-p1.y),
            (p2.x-p1.x)
        )
    );
    return temp;
}
std::complex<float> LocationChoose::random_path_swapped(float high){
    int a = std::min(int(high*RAND_VELOCITY),LocationChoose::n_points-2);
    float t = high*RAND_VELOCITY-a;
    point p1 = LocationChoose::points[a];
    point p2 = LocationChoose::points[std::min(a+1,LocationChoose::n_points-1)];
    return std::complex<float>(
        p1.x + (p2.x-p1.x)*t,
        p1.y + (p2.y-p1.y)*t
    );
}
LocationChoose::LocationChoose(int mode, int max_frames, int n_points)
{
    srand(time(NULL));
    LocationChoose::mode = mode;
    LocationChoose::max_frames = max_frames;
    LocationChoose::n_points = n_points;
    LocationChoose::points = new LocationChoose::point[n_points];
    LocationChoose::theta = 0.0;
    points[0].x = 0.0;
    points[0].y = 0.0;
    for (int i = 1; i < n_points; i++) // evenly spaced
    {
        bool isGenerated = false;
        int failCounter = 0;
        while(!isGenerated){
            float angle = (rand() % (2 * RAND_RESOLUTION + 1) - RAND_RESOLUTION) * 3.141592653589793238460 / RAND_RESOLUTION;
            points[i].x = points[i-1].x + std::cos(angle)*RAND_STEP;
            points[i].y = points[i-1].y + std::sin(angle)*RAND_STEP;
            if(-RAND_BOUNDARIES <= points[i].x && points[i].x <= RAND_BOUNDARIES){
                if(-RAND_BOUNDARIES <= points[i].y && points[i].y <= RAND_BOUNDARIES){
                    isGenerated = true;
                }
            }
            failCounter++;
            if(failCounter>=FAIL_MAX){
                isGenerated = true;
                i = std::max(1,i-2); // change previous point
            }
        }
    }
}
LocationChoose::~LocationChoose()
{
    delete[] LocationChoose::points;
}
std::complex<float> LocationChoose::get(float high, int i, float low)
{
    switch (LocationChoose::mode)
    {
    case 0: // standart
        return LocationChoose::standart(high, float(i));
    case 1: // standart both
        theta += low;
        return LocationChoose::standart_both(high, theta);
    case 2: // swapped
        return LocationChoose::swapped(high);
    case 3: // psychodelic
        return LocationChoose::psychodelic(high, float(i));
    case 4: // swapped remembering
        theta += high;
        return LocationChoose::swapped(theta);
    case 5: // random path
        return LocationChoose::random_path(high,i);
    case 6: // random path different
        return LocationChoose::random_path_different(high,i);
    case 7:
        theta += high;
        return LocationChoose::random_path_swapped(theta);
    default:
        return std::complex<float>(0, 0);
    }
}