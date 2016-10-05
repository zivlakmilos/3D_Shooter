#ifndef _ENGINE_CORE_CONSTANTS_H_
#define _ENGINE_CORE_CONSTANTS_H_

#include <glm/glm.hpp>

namespace zi
{
    const double PI = 3.1415926535897932384;
    
    enum Axis {
        AxisX = 0,
        AxisY,
        AxisZ
    };
    
    const glm::vec3 right(1.0f, 0.0f, 0.0f);
    const glm::vec3 left(-1.0f, 0.0f, 0.0f);
    const glm::vec3 up(0.0f, 1.0f, 0.0f);
    const glm::vec3 down(0.0f, -1.0f, 0.0f);
    const glm::vec3 forward(0.0f, 0.0f, -1.0f);
    const glm::vec3 back(0.0f, 0.0f, 1.0f);
}

#endif // _ENGINE_CONSTANTS_H_
