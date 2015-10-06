/*
Shipeng Xu
billhsu.x@gmail.com
*/
#pragma once
#include <iostream>
#include <vector>
#include "Core/Math/Vectors.h"
#include "Core/Basic/Plane.h"
#include "Core/Basic/Ray.h"
#include "Core/Basic/LineSegment.h"
#include "Core/Math/Matrices.h"

class State;
class Camera;
class UI;
class lua_State;
class Texture;

class Controller {
   public:
    static Controller& getInstance() {
        static Controller instance;
        return instance;
    }

    void MouseButton(int button, int state, int x, int y);
    void MouseLeftDrag(int x, int y, int dx, int dy);
    void MouseRightDrag(int x, int y, int dx, int dy);
    void PassiveMotion(int x, int y);
    enum { KEY_UP, KEY_DOWN };
    void Keyboard(unsigned char key, unsigned char status);
    void update(float timeDelta);
    void render();

    void init();

    void resize(int _width, int _heigth);

    enum { OPERATION_ADD_LINE = 1, OPERATION_DELETE_LINE };
    struct LineOperation {
        int lineID;
        int operation;
    };

    static std::vector<LineSegment> sketchLines;
    static std::vector<LineSegment> deletedLines;
    static std::vector<LineSegment> redoLines;
    static std::vector<LineOperation> lineOperations;
    static std::vector<LineOperation> redoOperations;
    static void addLine(LineSegment l) {
        static int IDCounter = 0;
        l.ID = IDCounter++;
        LineOperation lineOp;
        lineOp.lineID = l.ID;
        lineOp.operation = OPERATION_ADD_LINE;
        lineOperations.push_back(lineOp);
        sketchLines.push_back(l);
    }
    static void delLine(LineSegment& l) {
        for (int i = 0; i < sketchLines.size(); ++i) {
            if (sketchLines[i].ID == l.ID) {
                LineOperation lineOp;
                lineOp.lineID = l.ID;
                lineOp.operation = OPERATION_DELETE_LINE;
                lineOperations.push_back(lineOp);
                deletedLines.push_back(sketchLines[i]);
                sketchLines.erase(Controller::sketchLines.begin() + i);
                break;
            }
        }
    }
    static void undoLastOperation();
    static void redoLastOperation();
    static Plane currPlane;  // Plane to draw
    static Vector3 currPoint;
    static bool bCurrPoint;

    int status;

    static int windowWidth, windowHeight;
    static Matrix4 modelView;
    static Matrix4 projection;
    static int originWidth, originHeight;
    static int mouseX, mouseY;
    static int mouseButton, mouseState;  // mouse status

    static State* state_idle;
    static State* state_select_plane;
    static State* state_draw;
    static State* state_delete;
    static State* state_mirror;
    enum {
        MIRROR_MODE_X = 0x00000001,
        MIRROR_MODE_Y = 0x00000002,
        MIRROR_MODE_Z = 0x00000004,
        MIRROR_MODE_NONE = 0x00000000
    };
    static int mirrorMode;

    Camera* camera;
    bool getCameraPoint(Vector3& p, const Plane& plane);
    Ray getCameraRay();
    static bool enableLight;
    static Vector3 rotate;
    static lua_State* luaState;
    enum {
        BTN_ID_DOC_NEW = 10,
        BTN_ID_DOC_OPEN,
        BTN_ID_DOC_SAVE,
        BTN_ID_STANDARD_VIEW,
        BTN_ID_UNDO,
        BTN_ID_DELETE_LINE,
        BTN_ID_MIRROR
    };

   private:
    Controller();
    ~Controller();
    Controller(Controller const&);
    void operator=(Controller const&);
};
