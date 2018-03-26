#include "vkwindow.h"

#ifdef VK_USE_PLATFORM_MACOS_MVK
extern "C" {
void makeViewMetalCompatible(void* handle);
}
#endif

VkWindow::VkWindow() : QWindow() {
#ifdef VK_USE_PLATFORM_MACOS_MVK
    makeViewMetalCompatible(reinterpret_cast<void*>(winId()));
    const void* viewId = reinterpret_cast<void*>(winId());
    render = new VkRender(viewId);
#elif VK_USE_PLATFORM_WIN32_KHR
    render = new VkRender(reinterpret_cast<HWND>(winId()));
#endif

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
