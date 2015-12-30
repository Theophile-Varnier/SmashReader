#ifndef PLAYER_H
#define PLAYER_H
#include <QMutex>
#include <QThread>
#include <QImage>
#include <QWaitCondition>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <shared_ptr.hpp>

#include "smashvideo.h"

using namespace cv;

class Player : public QThread
{    Q_OBJECT

 private:

    bool stop;
    QMutex mutex;
    QWaitCondition condition;
    Mat frame;
    int frameRate;
    VideoCapture *capture;
    Mat RGBframe;
    QImage img;
     boost::shared_ptr<SmashVideo> _video;

 signals:
 //Signal to output frame to be displayed
      void processedImage(const QImage &image);
 protected:
     void run();
 public:
    //Constructor
    Player(QObject *parent = 0);
    //Destructor
    ~Player();
    //Load a video from memory
    bool loadVideo(std::string filename);
    //Play the video
    void Play();
    //Stop the video
    void Stop();
    //check if the player has been stopped
    bool isStopped() const;
    //set video properties
    void setCurrentFrame( int frameNumber);
    //Get video properties
    double getFrameRate();
    long getCurrentFrame();
    long getNumberOfFrames();
     boost::shared_ptr<SmashVideo> video() const;
};
#endif // VIDEOPLAYER_H
