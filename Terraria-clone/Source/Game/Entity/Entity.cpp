#include "trpch.h"
#include "Entity.h"

void Entity::UpdateModel()
{
    m_model = glm::mat4(1.0f);
    m_model = glm::translate(m_model, m_position);
    m_model = glm::rotate(m_model, glm::radians(m_rotation), glm::vec3(0, 0, 1));
    m_model = glm::scale(m_model, m_scale);
}
