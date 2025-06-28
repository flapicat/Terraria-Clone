#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Entity
{
public:
	Entity() {};

	void UpdateModel();

	glm::mat4 GetModel() const { return m_model; };
	
	glm::vec3 GetPosition() const { return m_position; };
	void setPosition(const glm::vec3& pos) { m_position = pos; };

	glm::vec3 GetScale() const { return m_scale; };
	void setScale(const glm::vec3& scale) { m_scale = scale; };

	float GetRotation() const { return m_rotation; };
	void setRotation(const float rotation) { m_rotation = rotation; };
private:
	//MODEL
	glm::mat4 m_model = glm::mat4(1.0f);
	glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
	float m_rotation = 0.0f;
};

