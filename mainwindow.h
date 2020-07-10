#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <opencv4/opencv2/core.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_open_clicked();

    void on_commonTolerance_valueChanged(int value);

    void on_redTolerance_valueChanged(int value);

    void on_greenTolerance_valueChanged(int value);

    void on_blueTolerance_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    cv::Mat m_image;
    void applyFloodFill(int r, int g, int b);
};
#endif // MAINWINDOW_H
