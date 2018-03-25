#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    VkWindow* vkWin = new VkWindow();
    QWidget* vkWidget = QWidget::createWindowContainer(vkWin);
    vkWidget->setMinimumSize(800, 600);
    vkWidget->setMaximumSize(1920, 1080);
    ui->renderLayout->addWidget(vkWidget);
}

MainWindow::~MainWindow() {
    delete ui;
}
