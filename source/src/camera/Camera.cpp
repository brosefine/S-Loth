#include <GL/freeglut.h>
#include "camera/Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>


Camera::Camera(int w, int h, glm::vec3 camPos)
	: m_old_x{0}
	, m_old_y{0}
	, m_speed{0.f}
	, m_motion_speed{0.05f}
    , m_width{w}
    , m_height{h}
	, m_position{camPos}
	, m_projection{glm::perspective(70.0f, (float)w / (float)h, m_near, m_far)}
{}

Camera::~Camera(){}


void Camera::mouseButton(int button, int state, int x, int y){
	// Left mouse button: turn camera
	if (button == GLUT_LEFT_BUTTON)	{
		if (state == GLUT_DOWN)		{
			m_old_x = x;
			m_old_y = y;
			m_move = true;
            m_old_dir = m_view_direction;
		} else if (state == GLUT_UP) {
            m_move = false;
        }
	}

}

void Camera::mouseRotate(int x, int y){
	if(!m_move) return;

	float deltaX = (x - m_old_x) / (float)m_width;
	float deltaY = (y - m_old_y) / (float)m_height;

	glm::vec3 center = glm::normalize(m_old_dir);
	center.x += deltaX;
	center.y -= deltaY;

	m_view_direction = glm::normalize(center);
}

void Camera::update(){
	m_position += m_speed * m_view_direction;
	m_view = glm::lookAt(m_position, m_position + m_view_direction, glm::vec3(0.0f, 0.75f, 0.0f));
}

const glm::mat4& Camera::getViewMatrix() const{
	return m_view;
}

const glm::mat4& Camera::getProjectionMatrix() const{
	return m_projection;
}

void Camera::updateProjection(int w, int h){
    m_height = h;
    m_width = w;
	m_projection = glm::perspective(70.0f, (float)w / (float)h, m_near, m_far);

}

void Camera::setViewDir(glm::fvec3 dir){
	m_view_direction = glm::normalize(dir);
	m_view = glm::lookAt(m_position, m_position + m_view_direction, glm::vec3(0.0f, 0.75f, 0.0f));

}

void Camera::setPosition(glm::fvec3 pos){
	m_position = pos;
}