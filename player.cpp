#include "player.h"
#include <make_shared.hpp>

Player::Player(QObject *parent)
 : QThread(parent)
{
    stop = true;
    _video = boost::make_shared<SmashVideo>();
}

bool Player::loadVideo(std::string filename) {

    capture  =  new cv::VideoCapture(filename);

    if (capture->isOpened())
    {
        frameRate = (int) capture->get(CV_CAP_PROP_FPS);
        _video->load(capture);
        return true;
    }
    else
        return false;
}

void Player::Play()
{
    if (!isRunning()) {
        if (isStopped()){
            stop = false;
        }
        start(LowPriority);
    }
}

void Player::run()
{
    while(!stop){
        if(_video->finished()){
            stop = true;
        } else{
            frame = _video->getCurrentFrame()->source();
            if (frame.channels()== 3){
                cv::cvtColor(frame, RGBframe, CV_BGR2RGB);
                img = QImage((const unsigned char*)(RGBframe.data),
                                  RGBframe.cols,RGBframe.rows,QImage::Format_RGB888);
            }
            else
            {
                img = QImage((const unsigned char*)(frame.data),
                                     frame.cols,frame.rows,QImage::Format_Indexed8);
            }
            emit processedImage(img);
        }
//        if (!capture->read(frame))
//        {
//            stop = true;
//        }
//        if (frame.channels()== 3){
//            cv::cvtColor(frame, RGBframe, CV_BGR2RGB);
//            img = QImage((const unsigned char*)(RGBframe.data),
//                              RGBframe.cols,RGBframe.rows,QImage::Format_RGB888);
//        }
//        else
//        {
//            img = QImage((const unsigned char*)(frame.data),
//                                 frame.cols,frame.rows,QImage::Format_Indexed8);
//        }
    }
}

Player::~Player()
{
    mutex.lock();
    stop = true;
    capture->release();
    delete capture;
    condition.wakeOne();
    mutex.unlock();
    wait();
}
void Player::Stop()
{
    stop = true;
}

bool Player::isStopped() const{
    return this->stop;
}

long Player::getCurrentFrame(){

    return _video->getCurrentFrameNumber();
}

long Player::getNumberOfFrames(){

    return _video->getTotalFrameNumber();
}

boost::shared_ptr<SmashVideo> Player::video() const
{
    return _video;
}

double Player::getFrameRate(){
    return frameRate;
}

void Player::setCurrentFrame( int frameNumber )
{
    _video->setCurrentFrameNumber(frameNumber);
}
