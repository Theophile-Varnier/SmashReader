#ifndef CQLABEL_H
#define CQLABEL_H

#include <QLabel>
#include <QMouseEvent>

class CQLabel : public QLabel
{
    Q_OBJECT
public:
    explicit CQLabel(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

signals:
    void Mouse_Press(QMouseEvent *e);
    void Mouse_Move(QMouseEvent *e);

public slots:

};

#endif // CQLABEL_H
