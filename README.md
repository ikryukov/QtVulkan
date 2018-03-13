# QtVulkan
Example of usage Vulkan (MoltenVK) with Qt on OS X

# Dependencies
Install Lunar SDK from: https://vulkan.lunarg.com/sdk/home#mac

Qt 5.10.0

# Preparations
Set env variables:

VK_LAYER_PATH = <sdk>/macOS/etc/vulkan/explicit_layers.d

VK_ICD_FILENAMES = <sdk>/macOS/etc/vulkan/icd.d/MoltenVK_icd.json

In QtVulkan change VULKAN_SDK_PATH to sdk path on your mac
