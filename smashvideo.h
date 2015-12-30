#ifndef SMASHVIDEO_H
#define SMASHVIDEO_H

#include "smat.h"
#include <shared_ptr.hpp>
#include <vector>
#include <opencv2/videoio.hpp>
#include <QObject>

class SmashVideo : public QObject
{
    Q_OBJECT

signals:
    void loadedFrame(long frameNumber);
public:
    SmashVideo();
    void load(cv::VideoCapture *videoCapture);
    boost::shared_ptr<SMat> getCurrentFrame();
    long getCurrentFrameNumber() const;
    long getTotalFrameNumber() const;
    bool finished() const;
    void setCurrentFrameNumber(long newNumber);

private:
    std::vector<boost::shared_ptr<SMat> > _frames;
    long _currentFrameNumber;
    long _totalFrameNumber;
};

#endif // SMASHVIDEO_H
