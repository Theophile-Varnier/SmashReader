#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    rubberBand(NULL)
{
    myPlayer = new Player();
    progressBar = new QProgressDialog(tr("Chargement de la vidéo..."), tr("Annuler"), 0, 100, this);
    progressBar->setWindowModality(Qt::WindowModal);
    progressBar->setCancelButton(0);
    QObject::connect(myPlayer, SIGNAL(processedImage(QImage)),
                     this, SLOT(updatePlayerUI(QImage)));
    QObject::connect(myPlayer->video().get(), SIGNAL(loadedFrame(long)), this, SLOT(update_progress_bar(long)));
    ui->setupUi(this);
    QObject::connect(ui->label, SIGNAL(Mouse_Press(QMouseEvent*)), this, SLOT(startDrawRubberBand(QMouseEvent*)));
    QObject::connect(ui->label, SIGNAL(Mouse_Move(QMouseEvent*)), this, SLOT(drawRubberBand(QMouseEvent*)));
    ui->pushButton_2->setEnabled(false);
    ui->horizontalSlider->setEnabled(false);
}

void MainWindow::updatePlayerUI(QImage img)
{
    if (!img.isNull())
    {
        ui->label->setAlignment(Qt::AlignCenter);
        ui->label->setPixmap(QPixmap::fromImage(img).scaled(ui->label->size(),
                                                            Qt::KeepAspectRatio, Qt::FastTransformation));
        ui->horizontalSlider->setValue(myPlayer->getCurrentFrame());
        ui->label_2->setText( getFormattedTime( (int)myPlayer->getCurrentFrame()/(int)myPlayer->getFrameRate()));
    }
}

MainWindow::~MainWindow()
{
    delete myPlayer;
    delete ui;
    delete rubberBand;
    delete progressBar;
}

void MainWindow::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Open Video"), ".",
                                                    tr("Video Files (*.avi *.mpg *.mp4)"));
    QFileInfo name = filename;

    if (!filename.isEmpty()){
        progressBar->show();
        if (!myPlayer->loadVideo(filename.toStdString().data()))
        {
            QMessageBox msgBox;
            msgBox.setText("The selected video could not be opened!");
            msgBox.exec();
        }
        else{
            this->setWindowTitle(name.fileName());
            ui->pushButton_2->setEnabled(true);
            ui->horizontalSlider->setEnabled(true);
            ui->horizontalSlider->setMaximum(myPlayer->getNumberOfFrames());
            ui->label_3->setText( getFormattedTime( (int)myPlayer->getNumberOfFrames()/(int)myPlayer->getFrameRate()) );
        }
        progressBar->hide();
    }
}
void MainWindow::on_pushButton_2_clicked()
{
    if (myPlayer->isStopped())
    {
        myPlayer->Play();
        ui->pushButton_2->setText(tr("Stop"));
    }else
    {
        myPlayer->Stop();
        ui->pushButton_2->setText(tr("Play"));
    }
}


QString MainWindow::getFormattedTime(int timeInSeconds){

    int seconds = (int) (timeInSeconds) % 60 ;
    int minutes = (int) ((timeInSeconds / 60) % 60);
    int hours   = (int) ((timeInSeconds / (60*60)) % 24);

    QTime t(hours, minutes, seconds);
    if (hours == 0 )
        return t.toString("mm:ss");
    else
        return t.toString("h:mm:ss");
}

void MainWindow::startDrawRubberBand(QMouseEvent *event)
{
    origin = event->pos();
    if (!rubberBand){
        rubberBand = new QRubberBand(QRubberBand::Rectangle, ui->label);
    } else {
        rubberBand->hide();
    }
    rubberBand->setGeometry(QRect(origin, QSize()));
    rubberBand->show();
}

void MainWindow::drawRubberBand(QMouseEvent *event)
{
    rubberBand->setGeometry(QRect(origin, event->pos()).normalized());
}

void MainWindow::on_horizontalSlider_sliderPressed()
{
    myPlayer->Stop();
}

void MainWindow::on_horizontalSlider_sliderReleased()
{
    myPlayer->Play();
}

void MainWindow::update_progress_bar(long value)
{
    int newValue = (100*value)/myPlayer->video()->getTotalFrameNumber();
    progressBar->setValue(newValue);
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    myPlayer->setCurrentFrame(position);
    ui->label_2->setText( getFormattedTime( position/(int)myPlayer->getFrameRate()) );
}
