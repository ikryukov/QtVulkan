#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qtimer.h>
#include <QMainWindow>
#include <QResizeEvent>

#include <vkrender.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

    void resize(int w, int h);

    void drawFrame();

   protected:
    void resizeEvent(QResizeEvent* event);

   private:
    Ui::MainWindow* ui;

    VkRender* render = nullptr;
    QTimer renderTimer;

    uint32_t windowWidth = 800;
    uint32_t windowHeigh = 600;
};

#endif  // MAINWINDOW_H
