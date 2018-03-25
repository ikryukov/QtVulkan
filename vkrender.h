#ifndef VKRENDER_H
#define VKRENDER_H

#include <array>
#include <chrono>
#include <unordered_map>
#include <vector>

#define NOMINMAX
#include <vulkan/vulkan.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct QueueFamilyIndices {
    int graphicsFamily = -1;
    int presentFamily = -1;

    bool isComplete() { return graphicsFamily >= 0 && presentFamily >= 0; }
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

struct UniformBufferObject {
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
};

struct InstanceData {
    glm::vec3 color;
};

struct Vertex {
    glm::vec3 pos;
};

const int VERTEX_BUFFER_BIND_ID = 0;
const int INSTANCE_BUFFER_BIND_ID = 1;

class VkRender {
   public:
    VkRender(const void* viewId);
    virtual ~VkRender();

    void drawFrame();
    void updateUniformBuffer();

    void addMesh(const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indices, int id);
    void createBuffersFromMeshes();

    void resize(int w, int h);

   private:
    uint32_t height = 0;
    uint32_t width = 0;

    const std::vector<const char*> validationLayers = {"VK_LAYER_LUNARG_standard_validation"};

    const std::vector<const char*> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

    const std::vector<Vertex> vertices = {{{-0.5f, -0.5f, 1.0f}}, {{0.5f, -0.5f, 1.0f}}, {{0.5f, 0.5f, 1.0f}}, {{-0.5f, 0.5f, 1.0f}}};
    const std::vector<uint16_t> indices = {0, 1, 2, 2, 3, 0};
    const std::vector<InstanceData> instances = {{{1.0f, 0.0f, 1.0f}}};

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = false;
#endif

    void initVulkan();
    void setupDebugCallback();
    void pickPhysicalDevice();
    void createLogicalDevice();
    void createSurface();
    void createSwapChain();
    void createImageViews();
    void createRenderPass();
    void createGraphicsPipeline();
    void createFramebuffers();
    void createCommandPool();
    void createCommandBuffers();
    void createSemaphores();
    void createFences();
    void recreateSwapChain();
    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    void createVertexBuffer();
    void createIndexBuffer();
    void createInstanceBuffer();
    void createUniformBuffer();
    void createDescriptorPool();
    void createDescriptorSet();
    void createDescriptorSetLayout();

    void cleanup();
    void cleanupSwapChain();

    void createInstance();
    void checkExtensions();
    bool checkValidationLayerSupport();
    std::vector<const char*> getRequiredExtensions();
    bool isDeviceSuitable(VkPhysicalDevice device);
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
    VkShaderModule createShaderModule(const std::vector<char>& code);
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

    std::vector<InstanceData> mInstances;
    std::vector<Vertex> mVertices;
    std::vector<uint16_t> mIndices;

    struct RenderItem {
        glm::mat4x4 transform;
        glm::vec3 color;
        int meshId;
        int instanceBase;
        int instanceCount;
    };

    struct Mesh {
        int vertexBase;
        int indexBase;
        int indexCount;
        int instanceBase;
    };
    std::vector<Mesh> mMeshes;

    VkInstance instance;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;

    VkSurfaceKHR surface;

    VkQueue graphicsQueue;
    VkQueue presentQueue;

    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;

    std::vector<VkImageView> swapChainImageViews;
    std::vector<VkFramebuffer> swapChainFramebuffers;

    VkRenderPass renderPass;
    VkDescriptorSetLayout descriptorSetLayout;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;

    VkSemaphore imageAvailableSemaphore;
    VkSemaphore renderFinishedSemaphore;

    VkCommandPool commandPool;
    std::vector<VkCommandBuffer> commandBuffers;
    std::vector<VkFence> waitFences;

    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;
    VkBuffer uniformBuffer;
    VkDeviceMemory uniformBufferMemory;
    VkBuffer instanceBuffer;
    VkDeviceMemory instanceBufferMemory;

    VkDescriptorPool descriptorPool;
    VkDescriptorSet descriptorSet;

    VkDebugReportCallbackEXT callback;

    const void* viewId;
};

#endif  // VKRENDER_H
