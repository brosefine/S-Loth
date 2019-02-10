#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera
{
public:

	Camera(int w, int h, glm::vec3 camPos);
	~Camera();

	void mouseRotate(int x, int y);
	void mouseButton(int button, int state, int x, int y);

	void update();
	void stop() {m_speed = 0;}
    void forward() {m_speed += m_motion_speed;}
    void back() {m_speed -= m_motion_speed;}
	void setViewDir(glm::fvec3 dir);
	void setPosition(glm::fvec3 pos);
	void updateProjection(int w, int h);

	const glm::mat4& getViewMatrix() const;
	const glm::mat4& getProjectionMatrix() const;
	const glm::vec3& getPosition() const { return m_position;}
	glm::vec3 getViewDir() { return m_view_direction;}

private:
	int m_old_x;
    int m_old_y;
    glm::vec3 m_old_dir;
    float m_speed;

	float m_motion_speed;
    float m_near = 0.01f;
    float m_far = 10000.0f;

    int m_width, m_height;
    glm::vec3 m_position;
    glm::vec3 m_view_direction;
	glm::vec3 m_up;
	glm::vec3 m_right;

	glm::mat4 m_view;
	glm::mat4 m_projection;

	bool m_move = true;
};

#endif
