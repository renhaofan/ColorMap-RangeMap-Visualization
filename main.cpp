#include "imageviewer.h"
#include <QApplication>
#include <QSharedMemory>
#include <QSystemSemaphore>
#include <QDebug>
#include <QMessageBox>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    ImageViewer w;

    // make sure one instance
    QSystemSemaphore sema("SystemSemaphore", 1, QSystemSemaphore::Open);
    sema.acquire(); // operate SharedMemory in temporary region

    QSharedMemory mem("SharedObject"); // global object name
    bool bCreate = mem.create(1);
    qDebug() << "bCreate=============" << bCreate;

    if (bCreate) {
        qDebug() << "create shared memory success======";
        w.show();
    } else {
        QMessageBox::warning(NULL, "Warning", "One instance of application has already running in tray mode");
        qDebug() << "An instance has already been running======";
        sema.release() ; // unix system, release automatically
        exit(0);
    }

    sema.release(); // temporary region
    return a.exec();
}
