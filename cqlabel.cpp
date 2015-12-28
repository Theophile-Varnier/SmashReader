#include "cqlabel.h"

CQLabel::CQLabel(QWidget *parent) :
    QLabel(parent)
{
}

void CQLabel::mousePressEvent(QMouseEvent *e)
{
    emit Mouse_Press(e);
}

void CQLabel::mouseMoveEvent(QMouseEvent *e)
{
    emit Mouse_Move(e);
}
