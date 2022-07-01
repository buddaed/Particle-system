#include "Camera.h"

Camera::Camera(wolf::App *pApp)
{
    cameraPos = glm::vec3(0.0f, 0.0f, 10.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    nearPlane = 0.1f;
    farPlane = 1000.0f;
    fieldOfView = 45.0f;
    m_pApp = pApp;
    glfwSetInputMode(m_pApp->m_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Camera::~Camera()
{
}

wolf::App *const Camera::getApp()
{
    return m_pApp;
}

glm::mat4  Camera::getViewMatrix() const
{
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::setSpeed(float const inSpeed)
{
    speed = inSpeed;
}

void Camera::setFront(glm::vec3 const target)
{
    cameraFront = target;
}
void Camera::setPos(glm::vec3 const pos)
{
    cameraPos = pos;
}
void Camera::setFOV(float const fov)
{
    fieldOfView = fov;
}
void Camera::setNear(float const near)
{
    nearPlane = near;
}
void Camera::setFar(float const far)
{
    farPlane = far;
}
void Camera::setCameraUp(glm::vec3 const up)
{
    cameraUp = up;
}
glm::vec3  Camera::getPos() const
{
    return cameraPos;
}
float  Camera::getFOV() const
{
    return fieldOfView;
}
float  Camera::getNear() const
{
    return nearPlane;
}
float  Camera::getFar() const
{
    return farPlane;
}
glm::vec3 const Camera::getFront()
{
    return cameraFront;
}
glm::vec3 const Camera::getCameraUp()
{
    return cameraUp;
}
glm::mat4 const Camera::getPersProjection(float const width, float const height)
{
    if(persProjMatrix == glm::mat4(1)) 
    {
        persProjMatrix = glm::perspective(glm::radians(this->getFOV()), (float)width / (float)height, this->getNear(), this->getFar());
    }
    return persProjMatrix;
}

void Camera::updateCam(float const dt)
{
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glm::vec2 mousePos = m_pApp->getMousePos();
    speed = 100 * dt;
    if (m_pApp->isKeyDown('w'))
    {
        cameraPos += cameraFront * speed;
    }
    if (m_pApp->isKeyDown('s'))
    {
        cameraPos -= cameraFront * speed;
    }
    if (m_pApp->isKeyDown('a'))
    {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
    }
    if (m_pApp->isKeyDown('d'))
    {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
    }

    if (firstMouse)
    {
        lastX = mousePos.x;
        lastY = mousePos.y;
        firstMouse = false;
    }

    if (m_pApp->isLMBDown())
    {
        cameraPos.y += speed;
    }

    if (m_pApp->isRMBDown())
    {
        if (cameraPos.y > 0.1)
            cameraPos.y -= speed;
    }

    float xoffset = mousePos.x - lastX;
    float yoffset = lastY - mousePos.y; // reversed since y-coordinates go from bottom to top
    lastX = mousePos.x;
    lastY = mousePos.y;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}