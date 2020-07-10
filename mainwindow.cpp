#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>

#include "hoverablepicture.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(new QGraphicsScene(ui->graphicsView));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::applyFloodFill(int r, int g, int b)
{
    cv::Mat mask = cv::Mat::zeros (m_image.rows + 2, m_image.cols + 2, CV_8UC1);
    int res = cv::floodFill(m_image,
                            mask,
                            cv::Point(0, 0),
                            cv::Scalar(0, 0, 0, 0),
                            nullptr,
                            cv::Scalar(b, g, r),
                            cv::Scalar(255, 255, 255),
                            4 | cv::FLOODFILL_MASK_ONLY | (255<<8));
    mask = cv::Mat(mask, cv::Rect(1, 1, m_image.cols, m_image.rows));
    auto output = m_image;
    cv::cvtColor(output, output, CV_BGR2RGBA);
    output.setTo(cv::Scalar{}, mask);
    ui->graphicsView->scene()->clear();
    //ui->graphicsView->scene()->addPixmap(QPixmap::fromImage(QImage(output.data, output.cols, output.rows, output.step, QImage::Format_RGBA8888)));
    ui->graphicsView->scene()->addItem(new HoverablePicture(QPixmap::fromImage(QImage(output.data, output.cols, output.rows, output.step, QImage::Format_RGBA8888))));
}

void MainWindow::on_open_clicked()
{
    auto filename = QFileDialog::getOpenFileName(this, "Открыть изображение",
                                                 {}, "*.jpg *.jpeg;;*.png;;*.bmp").toStdString();
    if (filename.length())
    {
        try
        {
            m_image = cv::imread(filename, -1);
            applyFloodFill(0, 0, 0);
        }
        catch (const std::exception &e)
        {
            qDebug() << e.what();
        }
    }

}

void MainWindow::on_commonTolerance_valueChanged(int value)
{
    applyFloodFill(value, value, value);
}

void MainWindow::on_redTolerance_valueChanged(int value)
{
    applyFloodFill(value, ui->greenTolerance->value(), ui->blueTolerance->value());
}

void MainWindow::on_greenTolerance_valueChanged(int value)
{
    applyFloodFill(ui->redTolerance->value(), value, ui->blueTolerance->value());
}

void MainWindow::on_blueTolerance_valueChanged(int value)
{
    applyFloodFill(ui->redTolerance->value(), ui->greenTolerance->value(), value);
}
