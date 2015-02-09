// Shipeng Xu
// billhsu.x@gmail.com

#include "StateIdleImpl.h"
#include "OpenGL/Impl/Scene/Scene.h"
#include <OpenGL/gl3.h>

void StateIdleImpl::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Scene::drawScene();
}