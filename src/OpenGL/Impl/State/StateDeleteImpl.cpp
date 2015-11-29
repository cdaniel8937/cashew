// Shipeng Xu
// billhsu.x@gmail.com

#include "StateDeleteImpl.h"
#include "OpenGL/DepthPeeling/DepthPeeling.h"
#include "OpenGL/TextureManager/TextureManager.h"
#include "OpenGL/Impl/Basic/LineSegmentRenderer.h"
#include "Core/Controller/Controller.h"
#include "OpenGL/Impl/Scene/Scene.h"
#include "OpenGL/Impl/Scene/DrawLineSegment.h"
#include <OpenGL/gl3.h>
#include "OpenGL/DepthPeeling/DepthPeeling.h"
#include "Core/Basic/SketchLine.h"

StateDeleteImpl::StateDeleteImpl() {
    depthPeeling = &DepthPeeling::getInstance();
    textureManager = &TextureManager::getInstance();
}

StateDeleteImpl::~StateDeleteImpl() {
}

void StateDeleteImpl::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Scene::renderLineSegments(NULL);
    renderCurrentLine();
    depthPeeling->addToRenderCallbackList(Scene::drawSceneWrapper);
    depthPeeling->addToRenderCallbackList(Scene::renderCurrentPoint);
}

void StateDeleteImpl::renderCurrentLine() {
    if (!Controller::bCurrLine) {
        return;
    }
    glDisable(GL_DEPTH_TEST);
    SketchLine* sketchLine =
        SketchLine::lineSegmentToSkectLine(Controller::currLine.ID);
    if (sketchLine != NULL) {
        Scene::renderSingleSketchLine(*sketchLine, Vector4(1, 0, 0, 0.5f),
                                      0.15f);
    }
    glEnable(GL_DEPTH_TEST);
}