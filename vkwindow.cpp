#include "vkwindow.h"

extern "C" {
void makeViewMetalCompatible(void* handle);
}

VkWindow::VkWindow() : QWindow() {
    makeViewMetalCompatible(reinterpret_cast<void*>(winId()));
    const void* viewId = reinterpret_cast<void*>(winId());
    render = new VkRender(viewId);

    renderTimer.setInterval(16);
    QObject::connect(&renderTimer, &QTimer::timeout, this, &VkWindow::drawFrame);
    renderTimer.start();
}

void VkWindow::drawFrame() {
    Q_ASSERT(render != nullptr);
    render->drawFrame();
}

VkWindow::~VkWindow() {
    delete render;
}

void VkWindow::resizeEvent(QResizeEvent* event) {
    QWindow::resizeEvent(event);
    if (windowWidth != event->size().width() || windowHeigh != event->size().height()) {
        windowWidth = event->size().width();
        windowHeigh = event->size().height();
        render->resize(windowWidth, windowHeigh);
    }
}
