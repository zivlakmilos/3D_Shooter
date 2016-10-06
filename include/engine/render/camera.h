#ifndef _ENGINE_RENDER_CAMERA_
#define _ENGINE_RENDER_CAMERA_

#include <glm/glm.hpp>

#include "engine/core/constants.h"

namespace zi
{
    class Camera
    {
    public:
        Camera(glm::vec3 position, glm::vec3 direction, float filedOfView = 45.0f);
        virtual ~Camera(void);
        
        void calculate(void);
        void rotate(float angle, glm::vec3 &axis);
        void translate(glm::vec3 &direction);
        void move(zi::Direction direction, float distance);
        
        inline glm::vec3 getPosition(void) { return m_position; };
        inline glm::vec3 getDirection(void) { return m_direction; };
        inline glm::mat4 getTransform(void) { return m_transform; };
        
        inline void setPosition(glm::vec3 position) { m_position = position; calculate(); };
        inline void setDirection(glm::vec3 direction) { m_direction = direction; calculate(); };
        inline void setUp(glm::vec3 up) { m_up = up; calculate(); };
        
    private:
        glm::vec3 m_position;
        glm::vec3 m_direction;
        glm::vec3 m_up;
        glm::mat4 m_transform;
        
        float m_filedOfView;
    };
}

#endif //_ENGINE_RENDER_CAMERA_
