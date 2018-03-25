#ifndef VKWINDOW_H
#define VKWINDOW_H
#include <qtimer.h>
#include <vkrender.h>
#include <QResizeEvent>
#include <QWindow>

class VkWindow : public QWindow {
   public:
    VkWindow();
    virtual ~VkWindow();

    void resize(int w, int h);
    void drawFrame();

   protected:
    void resizeEvent(QResizeEvent* event);

    VkRender* render = nullptr;
    QTimer renderTimer;

    uint32_t windowWidth = 800;
    uint32_t windowHeigh = 600;
};

#endif  // VKWINDOW_H
