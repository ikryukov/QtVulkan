#include "vkwindow.h"

#include <vector>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

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

    {
        std::vector<glm::vec3> vertices;
        std::vector<uint32_t> indices;

        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string err;

        if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &err, "/Users/ilyakryukov/Documents/workspace/QtVulkan/Porsche_911_GT2.obj")) {
            throw std::runtime_error(err);
        }
        for (const auto& shape : shapes) {
            for (const auto& index : shape.mesh.indices) {
                //                Vertex vertex = {};
                glm::vec3 pos = {attrib.vertices[3 * index.vertex_index + 0], attrib.vertices[3 * index.vertex_index + 1],
                                 attrib.vertices[3 * index.vertex_index + 2]};
                vertices.push_back(pos);
                indices.push_back(indices.size());
            }
        }
        render->addGeometry(vertices, indices, 1);
        render->recreateVertexBuffer();
        render->recreateIndexBuffer();

        std::vector<InstanceData> instData;
        InstanceData a;
        a.transform = glm::mat4(1.0f);
        a.color = glm::vec4(1.0f);
        instData.push_back(a);
        render->updateInstanceBuffer(instData);

        std::vector<DrawItem> drawItems;
        DrawItem b;
        b.meshId = 1;
        b.instanceBase = 0;
        b.instanceCount = 1;
        drawItems.push_back(b);
        render->buildCommandBuffers(drawItems);
    }

    {
        glm::vec3 camPos(2, 2, 3);
        glm::vec3 worldUp(0.0f, 1.0f, 0.0f);

        glm::mat4x4 view = glm::lookAt(camPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        glm::mat4x4 proj = glm::perspective(glm::radians(45.0f), windowWidth / (float)windowHeigh, 0.1f, 1000.0f);
        proj[1][1] *= -1;

        render->updateCamera(view, proj, camPos, worldUp);
    }
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
