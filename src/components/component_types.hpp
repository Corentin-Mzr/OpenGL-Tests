#pragma once

enum class ComponentType : unsigned int {
    TRANSFORM = 1 << 0, 
    PHYSICS = 1 << 1,
    RENDER = 1 << 2,
    CAMERA = 1 << 3,
};