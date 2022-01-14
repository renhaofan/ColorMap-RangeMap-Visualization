#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QMainWindow>
#include <QLabel>
#include <QScrollArea>
#include <QDockWidget>
#include <QButtonGroup>
#include <QSystemTrayIcon>
#ifndef QT_NO_PRINTER
#include <QPrinter>
#include <QMouseEvent>
#endif

namespace Ui {
class ImageViewer;
}

class ImageViewer : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImageViewer(QWidget *parent = nullptr);
    ~ImageViewer();

private slots:
    void dropEvent(QDropEvent *event) override;

    void dragEnterEvent(QDragEnterEvent *event) override;

    void wheelEvent(QWheelEvent *event) override;

    void closeEvent(QCloseEvent *event) override;

    void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);

    void on_actionOpen_triggered();

    void on_actionPrint_triggered();

    void on_actionExit_triggered();

    void on_actionZoomIn_triggered();

    void on_actionZoomOut_triggered();

    void on_actionNormalSize_triggered();

    void on_actionFitToWindow_triggered();

    void on_actionAboutQt_triggered();

    void on_actionSaveAs_triggered();

    void optionGroups_clicked();

    void on_actionAbout_triggered();

private:
    Ui::ImageViewer *ui;
    QIcon *icon;

    //! range-map visualization concerned
    QImage raw_image; // raw image
    QImage image; // pcolor
    QLabel *imageLabel;
    QScrollArea *scrollArea;
    QButtonGroup *optionGroups;
    QDockWidget *dock;

    //! system tray concerned
    QSystemTrayIcon *systemTray;
    QMenu *trayMenu;
    QAction *minimumAct;
    QAction *maximumAct;
    QAction *restoreAct;
    QAction *quitAct;



    //! menu bar concerned
    QAction *openAct;
    QAction *saveAsAct;
    QAction *printAct;
    QAction *exitAct;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *normalSizeAct;
    QAction *fitToWindowAct;
    QAction *aboutQtAct;

    double scaleFactor;

    bool loadFile(const QString &fileName);
    void updateActions();
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);
    void setImage(const QImage &newImage);
    bool saveFile(const QString &fileName);
    void createDockWindows();
    void idPcolor();

//    void resizeEvent(QResizeEvent*);

   #ifndef QT_NO_PRINTER
       QPrinter printer;
   #endif
};

#endif // IMAGEVIEWER_H
