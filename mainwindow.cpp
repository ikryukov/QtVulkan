#include "mainwindow.h"
#include "ui_mainwindow.h"

extern "C" {
void makeViewMetalCompatible(void* handle);
}

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    makeViewMetalCompatible(reinterpret_cast<void*>(winId()));
    const void* viewId = reinterpret_cast<void*>(winId());
    render = new VkRender(viewId);

    renderTimer.setInterval(16);
    QObject::connect(&renderTimer, &QTimer::timeout, this, &MainWindow::drawFrame);
    renderTimer.start();
}

MainWindow::~MainWindow() {
    delete render;
    delete ui;
}

void MainWindow::drawFrame() {
    Q_ASSERT(render != nullptr);
    render->drawFrame();
}

void MainWindow::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);
    if (windowWidth != event->size().width() || windowHeigh != event->size().height()) {
        windowWidth = event->size().width();
        windowHeigh = event->size().height();
        render->resize(windowWidth, windowHeigh);
    }
}
