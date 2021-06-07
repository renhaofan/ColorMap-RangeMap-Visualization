#ifndef PCOLOR_H
#define PCOLOR_H
#include <QImage>

/*
 *  This is implementation for pesudo color
 *  Make sure Qt version more than Qt 5.13
 *  Need Qt 5.13 for QImage::Format_Grayscale16 support. See QTBUG-41176
*/

QImage convertGray16ToGray8(const QImage& img);
bool channelsMormThan1(const QImage& img);

QImage image2autumn(const QImage& img);
QImage image2bone(const QImage& img);
QImage image2cool(const QImage& img);
QImage image2hot(const QImage& img);
QImage image2hsv(const QImage& img);
QImage image2jet(const QImage& img);
QImage image2ocean(const QImage& img);
QImage image2parula(const QImage& img);
QImage image2pink(const QImage& img);
QImage image2rainbow(const QImage& img);
QImage image2spring(const QImage& img);
QImage image2summer(const QImage& img);
QImage image2turbo(const QImage& img);
QImage image2winter(const QImage& img);


#endif // PCOLOR_H
