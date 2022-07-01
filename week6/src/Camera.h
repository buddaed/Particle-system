#pragma once
#include "../wolf/wolf.h"

class Camera
{
public:
    Camera(wolf::App *);
    ~Camera();
    void updateCam(float const pfdelta);
    glm::mat4 getViewMatrix() const;
    void setSpeed(float const);
    void setPos(glm::vec3 const);
    void setFOV(float const);
    void setNear(float const);
    void setFar(float const);
    void setFront(glm::vec3 const);
    void setCameraUp(glm::vec3 const);
    glm::vec3 getPos() const;
    float getFOV() const;
    float getNear() const;
    float getFar() const;
    glm::mat4 const getPersProjection(float const width, float const height);
    glm::vec3 const getFront();
    glm::vec3 const getCameraUp();
    wolf::App* const getApp();

private:
    wolf::App *m_pApp;

    glm::mat4 persProjMatrix = glm::mat4(1);
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;

    float fieldOfView;
    float nearPlane;
    float farPlane;
    float deltaTime = 0.0f; // time between current frame and last frame
    float lastFrame = 0.0f;
    float camx = 0.0f;
    float camz = 0.0f;
    bool firstMouse = true;
    float yaw = -90.0f; // yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
    float pitch = 0.0f;
    float lastX = 800.0f / 2.0;
    float lastY = 600.0 / 2.0;
    float speed = 1;
};