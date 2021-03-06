/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#include "cashew/UI/UI.h"
#include <iostream>
#include "cashew/scene/Controller.h"
#include "cashew/scripting/luaUtility.h"
#include "cashew/scripting/luatables.h"

char UI::uiHintText[128];
int UI::hintTextPosX, UI::hintTextPosY;

UI::UI()
{
    mRootNode = new UINode(NULL);
    UILayout = LuaTable::fromFile("UILayout.lua");
    std::cout <<"UI()"<<std::endl;
}

UI::~UI()
{
    delete mRootNode;
    std::cout <<"~UI()"<<std::endl;
}
int UI::luaGetNodePosX(const char *nodeName)
{
    std::string stringValue = (*UILayout)[nodeName]["pos"]["x"].get<std::string> ();
    lua_evaluate_expression(UILayout->L, stringValue.c_str());
    int result = lua_tonumber(UILayout->L, -1);
    lua_pop(UILayout->L, 1);
    return result;
}

int UI::luaGetNodePosY(const char *nodeName)
{
    std::string stringValue = (*UILayout)[nodeName]["pos"]["y"].get<std::string> ();
    lua_evaluate_expression(UILayout->L, stringValue.c_str());
    int result = lua_tonumber(UILayout->L, -1);
    lua_pop(UILayout->L, 1);
    return result;
}

int UI::luaGetNodeWidth(const char *nodeName)
{
    std::string stringValue = (*UILayout)[nodeName]["size"]["width"].get<std::string> ();
    lua_evaluate_expression(UILayout->L, stringValue.c_str());
    int result = lua_tonumber(UILayout->L, -1);
    lua_pop(UILayout->L, 1);
    return result;
}

int UI::luaGetNodeHeight(const char *nodeName)
{
    std::string stringValue = (*UILayout)[nodeName]["size"]["height"].get<std::string> ();
    lua_evaluate_expression(UILayout->L, stringValue.c_str());
    int result = lua_tonumber(UILayout->L, -1);
    lua_pop(UILayout->L, 1);
    return result;
}

void UI::resize(int width, int height)
{
    mWindowWidth = width;
    mWindowHeight = height;
    lua_pushnumber(UILayout->L, width);
    lua_setglobal(UILayout->L, "window_width");
    lua_pushnumber(UILayout->L, height);
    lua_setglobal(UILayout->L, "window_height");
    for(int i=0; i<nodeList.size(); ++i)
    {
        if(strcmp(nodeList[i]->strID,"")==0) continue;
        nodeList[i]->setPos(luaGetNodePosX(nodeList[i]->strID), 
            luaGetNodePosY(nodeList[i]->strID));
        nodeList[i]->setSize(luaGetNodeWidth(nodeList[i]->strID), 
            luaGetNodeHeight(nodeList[i]->strID));
    }
}

UINode* UI::getNodeByPos(int x, int y)
{
    return mRootNode->getNodeByPos(x, y);
}

UIButton* UI::addButton(int id, int x, int y, int width, int height, 
            uint32_t textureID_idle, uint32_t textureID_hover, uint32_t textureID_press,  
            const char* text, void (*callback)(UINode* Sender), UINode* parent)
{
    UIButton* button;
    if(parent==NULL) button = new UIButton(mRootNode);
    else button = new UIButton(parent);
    button->nodeID = id;
    button->textureID_idle = textureID_idle;
    button->textureID_hover = textureID_hover;
    button->textureID_press = textureID_press;
    button->setPos(x, y);
    button->setText(text);
    button->setSize(width, height);
    button->setCallback(callback);
    nodeList.push_back(button);
    return button;
}

UIButton* UI::addButton(int id, const char* strID, 
            uint32_t textureID_idle, uint32_t textureID_hover, uint32_t textureID_press,  
            const char* text, void (*callback)(UINode* Sender), UINode* parent)
{
    int x = luaGetNodePosX(strID);
    int y = luaGetNodePosY(strID);
    int width  = luaGetNodeWidth (strID);
    int height = luaGetNodeHeight(strID);
    UIButton* button = addButton(id, x, y, width, height, 
                        textureID_idle, textureID_hover, textureID_press,  
                        text, callback, parent);
    strcpy(button->strID, strID);
    return button;
}
UIRadioButton* UI::addRadioButton(int id, int x, int y, int width, int height)
{
    UIRadioButton* radioBtn = new UIRadioButton(mRootNode);
    radioBtn->nodeID = id;
    radioBtn->setPos(x, y);
    radioBtn->setSize(width, height);
    nodeList.push_back(radioBtn);
    return radioBtn;
}
UILabel* UI::addLabel(int id, int x, int y, int width, int height, const char* text)
{
    UILabel* label = new UILabel(mRootNode);
    label->nodeID = id;
    label->setPos(x, y);
    label->setText(text);
    label->setSize(width, height);
    nodeList.push_back(label);
    return label;
}

UINode* UI::MouseButton(int button, int state, int x, int y)
{
    UINode* node = getNodeByPos(x, y);

    if(node!=NULL && state == 0)
    {
        node->MouseButton(button, state, x, y);
        mRootNode->previousPressed = node;
        return node;
    }

    if(state == 1 && mRootNode->previousPressed != NULL)
    {
        mRootNode->previousPressed->MouseButton(button, state, x, y);
        mRootNode->previousPressed = NULL;
    }

    return NULL;
}

UINode* UI::PassiveMotion(int x, int y)
{
    UINode* node = getNodeByPos(x, y);
    if(node!=NULL)
    {
        if(mRootNode->previousHover == NULL)
        {
            node->PassiveMotion(x, y);
            mRootNode->previousHover = node;
            return node;
        }
        else if(mRootNode->previousHover != node)
        {
            mRootNode->previousHover->PassiveMotion(x, y);
            node->PassiveMotion(x, y);
            mRootNode->previousHover = node;
            return node;
        }
        else
        {
            node->PassiveMotion(x, y);
        }
    }
    else if(mRootNode->previousHover != NULL)
    {
        mRootNode->previousHover->PassiveMotion(x, y);
        mRootNode->previousHover = NULL;
    }
    return NULL;
}