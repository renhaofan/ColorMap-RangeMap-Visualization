#include "imageviewer.h"
#include "ui_imageviewer.h"
#include "pcolor.h"

#include <QtWidgets>
#include <QFileDialog>
#include <QMessageBox>
#include <QPrintDialog>



bool channelsMormThan1(const QImage& img) {
    // based on Qt 5.14.2
    int format = img.format();
    if ((format >= 4 && format <= 22) || (format >= 25 && format <= 29 && format != QImage::Format_Grayscale16))
        return true;
    else
        return false;
}
static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode)
{
    static bool firstDialog = true;

    if (firstDialog) {
        firstDialog = false;
        const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    }

    QStringList mimeTypeFilters;
    const QByteArrayList supportedMimeTypes = acceptMode == QFileDialog::AcceptOpen
        ? QImageReader::supportedMimeTypes() : QImageWriter::supportedMimeTypes();
    foreach (const QByteArray &mimeTypeName, supportedMimeTypes)
        mimeTypeFilters.append(mimeTypeName);
    mimeTypeFilters.sort();
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/jpeg");
    if (acceptMode == QFileDialog::AcceptSave)
        dialog.setDefaultSuffix("jpg");
}



ImageViewer::ImageViewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageViewer)
{
    ui->setupUi(this);

    this->setAcceptDrops(true);

    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);
    QFont font("Microsoft YaHei", 10, 75);
    imageLabel->setFont(font);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setText("Start by dragging images here");
    imageLabel->resize(500, 400);

    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);

    setCentralWidget(scrollArea);


    createDockWindows();


    setWindowTitle(tr("Depthmap Visualization"));
    resize(1000, 400);


    openAct = ui->actionOpen;
    saveAsAct = ui->actionSaveAs;
    printAct = ui->actionPrint;
    exitAct = ui->actionExit;
    zoomInAct = ui->actionZoomIn;
    zoomOutAct = ui->actionZoomOut;
    normalSizeAct = ui->actionNormalSize;
    fitToWindowAct = ui->actionFitToWindow;
    aboutQtAct = ui->actionAboutQt;
//    connect(openAct,SIGNAL(triggered()),this,SLOT(open()));
//    connect(printAct, SIGNAL(triggered()), this, SLOT(print()));
//    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
//    connect(zoomInAct, SIGNAL(triggered()), this, SLOT(zoomIn()));
//    connect(zoomOutAct, SIGNAL(triggered()), this, SLOT(zoomOut()));
//    connect(normalSizeAct, SIGNAL(triggered()), this, SLOT(normalSize()));
//    connect(fitToWindowAct, SIGNAL(triggered()), this, SLOT(fitToWindow()));
//    connect(aboutQtAct, SIGNAL(triggered()), this, SLOT(about()));
}

ImageViewer::~ImageViewer()
{
    delete ui;
}

void ImageViewer::optionGroups_clicked() {
    if (raw_image.isNull()) return;
    if (channelsMormThan1(raw_image)) return;

    QImage copy_img = raw_image.copy();
//  bugs when load kitti.png
    if (copy_img.format() == QImage::Format_Grayscale16)
        copy_img = convertGray16ToGray8(copy_img);
    switch (optionGroups->checkedId()) {
        case 0:
            setImage(raw_image);
            break;
        case 1:
            setImage(image2autumn(copy_img));
            break;
        case 2:
            setImage(image2bone(copy_img));
            break;
        case 3:
            setImage(image2cool(copy_img));
            break;
        case 4:
            setImage(image2hot(copy_img));
            break;
        case 5:
            setImage(image2hsv(copy_img));
            break;
        case 6:
            setImage(image2jet(copy_img));
            break;
        case 7:
            setImage(image2ocean(copy_img));
            break;
        case 8:
            setImage(image2parula(copy_img));
            break;
        case 9:
            setImage(image2pink(copy_img));
            break;
        case 10:
            setImage(image2rainbow(copy_img));
            break;
        case 11:
            setImage(image2spring(copy_img));
            break;
        case 12:
            setImage(image2summer(copy_img));
            break;
        case 13:
            setImage(image2turbo(copy_img));
            break;
        case 14:
            setImage(image2winter(copy_img));
            break;
    }
}

void ImageViewer::createDockWindows() {
    dock = new QDockWidget(tr("Options"), this);
    dock->setFeatures(QDockWidget::DockWidgetMovable);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, dock);

    const int options = 15;
    // init QRadioButton
    QRadioButton * radioButton[options];
    for (int i = 0; i < options; ++i) {
        radioButton[i] = new QRadioButton(dock);
    }
    radioButton[0]->setText("Raw");
    radioButton[1]->setText("Autumn");
    radioButton[2]->setText("Bone");
    radioButton[3]->setText("Cool");
    radioButton[4]->setText("Hot");
    radioButton[5]->setText("Hsv");
    radioButton[6]->setText("Jet");
    radioButton[7]->setText("Ocean");
    radioButton[8]->setText("Parula");
    radioButton[9]->setText("Pink");
    radioButton[10]->setText("Rainbow");
    radioButton[11]->setText("Spring");
    radioButton[12]->setText("Summer");
    radioButton[13]->setText("Turbo");
    radioButton[14]->setText("Winter");
    radioButton[0]->setChecked(true);

    // init colorbar
    QImage grayscale = QImage(256, 10, QImage::Format_Indexed8);
    uchar* line;
    for(int y = 0; y < grayscale.height(); y++) {
        line = grayscale.scanLine(y);
        for(int x = 0; x < grayscale.width(); x++) {
              line[x] = x;
        }
    }
    QLabel* colorbar[options];
    for (int i = 0; i < options; ++i) {
        colorbar[i] = new QLabel(this);
    }
    colorbar[0]->setPixmap(QPixmap::fromImage(grayscale));
    colorbar[1]->setPixmap(QPixmap::fromImage(image2autumn(grayscale)));
    colorbar[2]->setPixmap(QPixmap::fromImage(image2bone(grayscale)));
    colorbar[3]->setPixmap(QPixmap::fromImage(image2cool(grayscale)));
    colorbar[4]->setPixmap(QPixmap::fromImage(image2hot(grayscale)));
    colorbar[5]->setPixmap(QPixmap::fromImage(image2hsv(grayscale)));
    colorbar[6]->setPixmap(QPixmap::fromImage(image2jet(grayscale)));
    colorbar[7]->setPixmap(QPixmap::fromImage(image2ocean(grayscale)));
    colorbar[8]->setPixmap(QPixmap::fromImage(image2parula(grayscale)));
    colorbar[9]->setPixmap(QPixmap::fromImage(image2pink(grayscale)));
    colorbar[10]->setPixmap(QPixmap::fromImage(image2rainbow(grayscale)));
    colorbar[11]->setPixmap(QPixmap::fromImage(image2spring(grayscale)));
    colorbar[12]->setPixmap(QPixmap::fromImage(image2summer(grayscale)));
    colorbar[13]->setPixmap(QPixmap::fromImage(image2turbo(grayscale)));
    colorbar[14]->setPixmap(QPixmap::fromImage(image2winter(grayscale)));


    // init widget
    QWidget * mywid = new QWidget(this);
    QVBoxLayout *vLayout = new QVBoxLayout;

    optionGroups = new QButtonGroup(this);
    for (int i = 0; i < options; ++i) {
        optionGroups->addButton(radioButton[i], i);
        connect(radioButton[i], SIGNAL(clicked()), this, SLOT(optionGroups_clicked()));
        QHBoxLayout *hLayout = new QHBoxLayout;
        hLayout->addWidget(radioButton[i]);
        hLayout->addWidget(colorbar[i]);
        vLayout->addLayout(hLayout);
    }
    mywid->setLayout(vLayout);
    dock->setWidget(mywid);

//    QWidget * mywid = new QWidget(this);
//    QGridLayout *gridLayout = new QGridLayout;

//    optionGroups = new QButtonGroup(this);
//    for (int i = 0; i < options; ++i) {
//        optionGroups->addButton(radioButton[i], i);
//        connect(radioButton[i], SIGNAL(clicked()), this, SLOT(optionGroups_clicked()));
//        gridLayout->addWidget(radioButton[i]);
//    }
//    mywid->setLayout(gridLayout);
//    dock->setWidget(mywid);
}

void ImageViewer::idPcolor() {
    if (raw_image.isNull()) return;
    if (channelsMormThan1(raw_image)) return;

    QImage copy_img = raw_image.copy();
//  bugs when load kitti.png
    if (copy_img.format() == QImage::Format_Grayscale16)
        copy_img = convertGray16ToGray8(copy_img);
    switch (optionGroups->checkedId()) {
        case 0:
            setImage(raw_image);
            break;
        case 1:
            setImage(image2autumn(copy_img));
            break;
        case 2:
            setImage(image2bone(copy_img));
            break;
        case 3:
            setImage(image2cool(copy_img));
            break;
        case 4:
            setImage(image2hot(copy_img));
            break;
        case 5:
            setImage(image2hsv(copy_img));
            break;
        case 6:
            setImage(image2jet(copy_img));
            break;
        case 7:
            setImage(image2ocean(copy_img));
            break;
        case 8:
            setImage(image2parula(copy_img));
            break;
        case 9:
            setImage(image2pink(copy_img));
            break;
        case 10:
            setImage(image2rainbow(copy_img));
            break;
        case 11:
            setImage(image2spring(copy_img));
            break;
        case 12:
            setImage(image2summer(copy_img));
            break;
        case 13:
            setImage(image2turbo(copy_img));
            break;
        case 14:
            setImage(image2winter(copy_img));
            break;
    }
}

void ImageViewer::setImage(const QImage &newImage)
{
    image = newImage;
    imageLabel->setPixmap(QPixmap::fromImage(image));

    scaleFactor = 1.0;

    scrollArea->setVisible(true);
    printAct->setEnabled(true);
    fitToWindowAct->setEnabled(true);
    updateActions();

    if (!fitToWindowAct->isChecked())
        imageLabel->adjustSize();
}

bool ImageViewer::loadFile(const QString &fileName)
{
    QImageReader reader(fileName);
    reader.setAutoTransform(true);
    const QImage newImage = reader.read();
    if (newImage.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1: %2")
                                 .arg(QDir::toNativeSeparators(fileName), reader.errorString()));
        return false;
    }

    raw_image = newImage;
    setImage(newImage);
    idPcolor();

    setWindowFilePath(fileName);

    const QString message = tr("Opened \"%1\", %2x%3, Depth: %4")
        .arg(QDir::toNativeSeparators(fileName)).arg(image.width()).arg(image.height()).arg(image.depth());
    statusBar()->showMessage(message);
    return true;
}

void ImageViewer::updateActions()
{
    saveAsAct->setEnabled(!image.isNull());
    zoomInAct->setEnabled(!fitToWindowAct->isChecked());
    zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
    normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
}

void ImageViewer::scaleImage(double factor)
{
    Q_ASSERT(imageLabel->pixmap());
    scaleFactor *= factor;
    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

    adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(scrollArea->verticalScrollBar(), factor);

    zoomInAct->setEnabled(scaleFactor < 3.0);
    zoomOutAct->setEnabled(scaleFactor > 0.333);
}

void ImageViewer::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}

bool ImageViewer::saveFile(const QString &fileName)
{
    QImageWriter writer(fileName);

    if (!writer.write(image)) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot write %1: %2")
                                 .arg(QDir::toNativeSeparators(fileName)), writer.errorString());
        return false;
    }
    const QString message = tr("Wrote \"%1\"").arg(QDir::toNativeSeparators(fileName));
    statusBar()->showMessage(message);
    return true;
}

void ImageViewer::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->type() != QEvent::DragEnter) return;
    // for linux:event->mimeData()->urls()[0].toLocalFile().right(3).compare("bmp")
    if (!event->mimeData()->urls()[0].toLocalFile().right(3).compare("bmp") ||
        !event->mimeData()->urls()[0].toLocalFile().right(3).compare("jpg") ||
        !event->mimeData()->urls()[0].toLocalFile().right(3).compare("pbm") ||
        !event->mimeData()->urls()[0].toLocalFile().right(3).compare("pgm") ||
        !event->mimeData()->urls()[0].toLocalFile().right(3).compare("png") ||
        !event->mimeData()->urls()[0].toLocalFile().right(3).compare("ppm") ||
        !event->mimeData()->urls()[0].toLocalFile().right(3).compare("xbm") ||
        !event->mimeData()->urls()[0].toLocalFile().right(3).compare("xpm"))
    {
        event->acceptProposedAction();
    }
    else
    {
        event->ignore();
    }
}

void ImageViewer::dropEvent(QDropEvent *event) {
    if (event->type() != QEvent::Drop) return;
    QList<QUrl> urls = event->mimeData()->urls();
    QString fileName = urls.first().toLocalFile();
    if (!loadFile(fileName)) {
        imageLabel->setPixmap(QPixmap::fromImage(image));


        scaleFactor = 1.0;

        printAct->setEnabled(true);
        fitToWindowAct->setEnabled(true);
        updateActions();

        if (!fitToWindowAct->isChecked())
            imageLabel->adjustSize();

    }
}


void ImageViewer::on_actionOpen_triggered()
{
    QFileDialog dialog(this, tr("Open File"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

    while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {

    }
}

void ImageViewer::on_actionPrint_triggered()
{
    Q_ASSERT(imageLabel->pixmap());
#ifndef QT_NO_PRINTER
    QPrintDialog dialog(&printer, this);
    if (dialog.exec()) {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = imageLabel->pixmap()->size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(imageLabel->pixmap()->rect());
        painter.drawPixmap(0, 0, *imageLabel->pixmap());
    }
#endif
}

void ImageViewer::on_actionExit_triggered()
{
    this->close();
}

void ImageViewer::on_actionZoomIn_triggered()
{
    scaleImage(1.25);
}

void ImageViewer::on_actionZoomOut_triggered()
{
    scaleImage(0.8);
}

void ImageViewer::on_actionNormalSize_triggered()
{
    imageLabel->adjustSize();
    scaleFactor = 1.0;
}

void ImageViewer::on_actionFitToWindow_triggered()
{
    bool fitToWindow = fitToWindowAct->isChecked();
    scrollArea->setWidgetResizable(fitToWindow);
    if (!fitToWindow) {
        on_actionNormalSize_triggered();
    }
    updateActions();
}

void ImageViewer::on_actionAboutQt_triggered()
{
    QApplication::aboutQt();
}

void ImageViewer::on_actionSaveAs_triggered()
{
    QFileDialog dialog(this, tr("Save File As"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptSave);

    while (dialog.exec() == QDialog::Accepted && !saveFile(dialog.selectedFiles().first())) {}
}

void ImageViewer::on_actionAbout_triggered() {
    // text with html, <br> instead of \n
    QString info;
    info += "Author: Steve Canvas<br>";
    info += "Emails: yqykrhf@163.com<br>";
    info += "<a href='https://github.com/renhaofan/colormap/'>Github Repo</a>";
    QMessageBox::about(this, tr("About"), info);

}
