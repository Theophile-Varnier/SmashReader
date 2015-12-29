#include "smashvideo.h"
#include <make_shared.hpp>
#include <opencv2/videoio.hpp>
using namespace cv;

SmashVideo::SmashVideo()
    : _currentFrameNumber(0),
      _totalFrameNumber(0)
{

}

void SmashVideo::load(VideoCapture *videoCapture)
{
    _totalFrameNumber = videoCapture->get(CAP_PROP_FRAME_COUNT);
    Mat frame;
    while(videoCapture->read(frame)){
        _frames.push_back(boost::make_shared<SMat>(frame));
        emit loadedFrame(_currentFrameNumber++);
    }
}

boost::shared_ptr<SMat> SmashVideo::getCurrentFrame() const
{
    return _frames[_currentFrameNumber];
}

long SmashVideo::getCurrentFrameNumber() const{
    return _currentFrameNumber;
}

long SmashVideo::getTotalFrameNumber() const
{
    return _totalFrameNumber;
}

