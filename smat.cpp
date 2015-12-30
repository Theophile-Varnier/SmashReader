#include "smat.h"

using cv::Mat;

SMat::SMat(const Mat& source): _source(source)
{
}

const QRect &SMat::getBlobZone() const
{
    return _blobZone;
}

void SMat::setBlobZone(const QRect &rect)
{
    _blobZone = rect;
}

const cv::Mat &SMat::source() const
{
    return _source;
}
