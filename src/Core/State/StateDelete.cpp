// Shipeng Xu
// billhsu.x@gmail.com

#include "StateDelete.h"
#include "Core/Camera/Camera.h"
#include "Core/Controller/Controller.h"
#include "Core/Controller/Mouse.h"
#include "Core/Basic/Plane.h"
#include "Core/UI/UI.h"
#include "Core/UI/UIButton.h"

StateDelete::StateDelete() {
    stateID = STATE_DELETE;
    assert(statePool[stateID] == NULL);
    statePool[stateID] = this;
    btnDeleteDone = Controller::GUI->addButton(stateID*100 + 100 + BTN_ID_DELETE_LINE_DONE, "BTN_ID_DELETE_LINE_DONE", btnDeleteDoneEvent, this);
    btnDeleteDone->setVisibility(false);
}
void StateDelete::MouseButton(int button, int state, int x, int y) {
    if(button == Mouse::MOUSE_SCROLL) {
        mCamera->setCamDist(mCamera->distance + 0.1f * state);
    }
}

void StateDelete::MouseRightDrag(int dx, int dy) {
    Controller::rotate.x -= dy;
    Controller::rotate.y += dx;
    mCamera->rotateCam(Controller::rotate);
}

void StateDelete::prepareState() {
    btnDeleteDone->appearIn();
}

void StateDelete::postState() {
    btnDeleteDone->appearOut();
}
void StateDelete::UIEvent(UINode* sender, int event) {
    if(sender->nodeID == Controller::BTN_ID_STANDARD_VIEW) {
        Quaternion q = Quaternion::fromEuler(Vector3(-90,0,0));
        mCamera->setCamCenterTo(Vector3(0,0,0));
        mCamera->rotateCamTo(q);
    }
}

void StateDelete::btnDeleteDoneEvent(void* data) {
    
}
