# Rangemap Visualization 
![demo](https://github.com/renhaofan/colormap/blob/master/images/demo/demoV2.gif)


Some test images are located in folder `/images/test`

visualize 16bit and 8bit images, 16bit images will be converted to 8bit images by scale `(values - vmin) * 255 / (vmax - vmin)`

Requirements
============
* Qt version above 5.13 (just gray16lib will likely compile with 5.13)
  * [`QImage::Format_Grayscale16`](https://doc.qt.io/qt-5/qimage.html#Format-enum) was added in Qt 5.13 (released [June 19th, 2019](https://blog.qt.io/blog/2019/06/19/qt-5-13-released/)). References: [QTBUG-41176](http://bugreports.qt.io/browse/QTBUG-41176), [Gerrit patch](https://codereview.qt-project.org/#/c/239203/)

# Log
Version: 2.1
* add tray mode
![tray](https://github.com/renhaofan/colormap/blob/master/images/demo/tray.png)



