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
    void on_LoadButton_clicked();
    void on_OptionGroups();


//    void on_AutumnRadioButton_toggled(bool checked);

//    void on_BoneRadioButton_toggled(bool checked);

//    void on_AutumnRadioButton_clicked();

private:
    Ui::Widget *ui;

    cv::Mat src;
    cv::Mat colormap;
    QButtonGroup *OptionGroups;
};

#endif // WIDGET_H
