#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QButtonGroup>

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <QFileDialog>
#include <QMessageBox>

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QUrl>
#include <QList>
#include <QMimeData>

// for Debug
#include <QDebug>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_LoadButton_clicked(); // load button
    void on_OptionGroups(); // Radio clicked slot function
    // draw image
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    // init ColorSale
    void initColoScale();
//    bool eventFilter(QObject *watched, QEvent *event);

//    void on_AutumnRadioButton_toggled(bool checked);

//    void on_BoneRadioButton_toggled(bool checked);

//    void on_AutumnRadioButton_clicked();





    void on_SaveButton_clicked();

private:
    Ui::Widget *ui;

    cv::Mat src;
    cv::Mat colormap;
    QButtonGroup *OptionGroups;

    void keyPressEvent(QKeyEvent *event);
};

#endif // WIDGET_H
