#include "engine/render/camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

zi::Camera::Camera(glm::vec3 position, glm::vec3 direction, float filedOfView)
    : m_position(position),
      m_direction(direction),
      m_filedOfView(filedOfView),
      m_up(0.0f, 1.0f, 0.0f)
{
    calculate();
}

zi::Camera::~Camera(void)
{
}

void zi::Camera::calculate(void)
{
    glm::mat4 projectionMatrix = glm::perspective(m_filedOfView,
                                                  4.0f / 3.0f,
                                                  0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(m_position,
                                 m_position + m_direction,
                                 m_up);
    
    m_transform = projectionMatrix * view;
}

void zi::Camera::rotate(float angle, glm::vec3 &axis)
{
    m_direction = glm::rotate(m_direction, angle, axis);
    calculate();
}

void zi::Camera::translate(glm::vec3 &direction)
{
    m_position += direction;
    calculate();
}

void zi::Camera::move(zi::Direction direction, float distance)
{
    if(direction & zi::DirectionForward)
        m_position += m_direction * distance;
    if(direction & zi::DirectionBack)
        m_position -= m_direction * distance;
    if(direction & zi::DirectionUp)
        m_position += m_up * distance;
    if(direction & zi::DirectionDown)
        m_position -= m_up * distance;
    if(direction & (zi::DirectionRight | zi::DirectionLeft))
    {
        glm::vec3 vecDirection = glm::normalize(glm::cross(m_direction, m_up));
        if(direction & zi::DirectionRight)
            m_position += vecDirection * distance;
        if(direction & zi::DirectionLeft)
            m_position -= vecDirection * distance;
    }
    
    calculate();
}
