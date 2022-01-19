#include "imageviewer.h"
#include <QApplication>
#include <QSharedMemory>
#include <QSystemSemaphore>
#include <QDebug>
#include <QMessageBox>


//int main(int argc, char *argv[]) {
//    QApplication a(argc, argv);
//    ImageViewer w;
//    // reference: https://www.cxymm.net/article/qq_36170958/111300170
//    QSharedMemory shared("share"); //绑定共享内存
//    if (shared.attach()) {
////        QMessageBox::warning(NULL, "Warning", "One instance of application has already running in tray mode");
//        qWarning() << "Can't start more than one instance of the application.";
//        exit(0);
//    } else {
//        qDebug() << "Application started successfully.";
//    }
//    shared.create(1); // 1 byte
//    w.show();

//    return a.exec();
//}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImageViewer w;

    //确保只运行一次
    QSystemSemaphore sema("SystemSemaphore", 1, QSystemSemaphore::Open);
    sema.acquire();//在临界区操作共享内存  SharedMemory

    QSharedMemory mem("SharedObject"); //全局对象名
    bool bCreate = mem.create(1);
    qDebug() << "bCreate=============" << bCreate;

    if(bCreate)
    {
        qDebug() << "create shared memory success======";
        w.show();
    }
    else
    {
        QMessageBox::warning(NULL, "Warning", "One instance of application has already running in tray mode");
        qDebug() << "An instance has already been running======";
        sema.release(); //如果是 Unix 系统，会自动释放。
        exit(0);
    }

    sema.release();//临界区

    return a.exec();
}
