#ifndef SMAT_H
#define SMAT_H

#include <opencv2/core/core.hpp>
#include <QRect>

class SMat
{
public:
    SMat(const cv::Mat& source);
    const QRect& getBlobZone() const;
    void setBlobZone(const QRect& rect);
    const cv::Mat& source() const;

private:
    cv::Mat _source;
    QRect _blobZone;
};

#endif // SMAT_H
