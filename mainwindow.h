#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QProgressDialog>
#include <player.h>
#include <QTime>
#include <QRubberBand>
#include <QPoint>

namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //Display video frame in player UI
    void updatePlayerUI(QImage img);
    //Slot for the load video push button.
    void on_pushButton_clicked();
    // Slot for the play push button.
    void on_pushButton_2_clicked();
    QString getFormattedTime(int timeInSeconds);

    void on_horizontalSlider_sliderPressed();

    void on_horizontalSlider_sliderReleased();

    void on_horizontalSlider_sliderMoved(int position);
    void drawRubberBand(QMouseEvent *event);
    void startDrawRubberBand(QMouseEvent *event);
    void update_progress_bar(long value);

private:
    Ui::MainWindow *ui;
    Player* myPlayer;
    QProgressDialog *progressBar;
    QRubberBand *rubberBand;
    QPoint origin;
};
#endif // MAINWINDOW_H

