//
//  CashewApp.m
//  cashew
//
//  Created by Xu, Shipeng on 23/11/14.
//  Copyright (c) 2014 Xu, Shipeng. All rights reserved.
//

#import <OpenGL/gl3.h>
#import "CashewOpenGLView.h"
#import "CashewShaderController.h"
#import "CashewTextureController.h"
#import "CashewInputController.h"
#include "Core/Math/Vectors.h"
#include "Core/Math/Matrices.h"
#include "Impl/Scene/Scene.h"

#include "Core/Camera/Camera.h"
#include "Impl/State/StateIdleImpl.h"
#include "Impl/State/StateSelectPlaneImpl.h"
#include "Core/Controller/Controller.h"
#include "Impl/UI/UIImpl.h"
#include "Impl/UI/UIButtonImpl.h"

GLuint program;
GLuint UIShaderProgram;
GLuint texture;

Controller *mController = &Controller::getInstance();

@interface CashewApp : NSObject <CashewOpenGLViewDelegate, CashewInputDelegate>

@end

@implementation CashewApp

void checkGlErr(int line)
{
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cout << "OpenGL error: " << err <<" "<<__FILE__<< " "<<line<<std::endl;
    }
}
- (BOOL)prepareRenderData
{
    [[CashewInputController sharedInputController] addEventDelegate:self];
    NSLog(@"prepareRenderData");
    CashewShaderController *shaderController = [CashewShaderController sharedShaderController];
    program = [shaderController programWithVertexShaderFile:@"Shader/default.vs" FragmentShaderFile:@"Shader/default.fs"];
    UIShaderProgram = [shaderController programWithVertexShaderFile:@"Shader/UI.vs" FragmentShaderFile:@"Shader/UI.fs"];
    
    CashewTextureController *textureController = [CashewTextureController sharedTextureController];
    texture = [textureController textureWithFileName:@"media/textures/button_confirm.png" useMipmap:YES];

    glUseProgram(program);
    cashew::prepareSceneAxis(1.0f);
    cashew::prepareSceneGrid(20.0f,1.0f);
    glUseProgram(UIShaderProgram);
    GLint local_image0 = glGetUniformLocation(program, "image0");
    checkGlErr(__LINE__);
    glActiveTexture(GL_TEXTURE0);
    checkGlErr(__LINE__);
    glEnable(GL_TEXTURE_2D);
    checkGlErr(__LINE__);
    glBindTexture(GL_TEXTURE_2D, texture);
    checkGlErr(__LINE__);
    glUniform1i(local_image0, 0);
    checkGlErr(__LINE__);
    glDisable(GL_TEXTURE_2D);
    checkGlErr(__LINE__);
    glUseProgram(0);
    mController->GUI = &UIImpl::getInstance();
    static_cast<UIImpl*>(mController->GUI)->setShader(UIShaderProgram);
    for(int i=0; i < State::STATE_ID_MAX; ++i)
    {
        State::statePool[i] = NULL;
    }
    mController->state_idle = new StateIdleImpl();
    mController->state_select_plane = new StateSelectPlaneImpl();
    State::enterState(mController->state_idle);
    
    mController->init();
    UIButtonImpl* button = mController->GUI->addButton(0, "BTN_ID_DOC_NEW",
                                                       0, 0, 0, "New Sketch", NULL, NULL);
    button->textureID_idle = texture;
    return YES;
}

- (void)mouseLeftUp:(NSPoint)locationInWindow;
{
    int x = (int)locationInWindow.x;
    int y = mController->windowHeight - (int)locationInWindow.y;
    mController->MouseButton(Controller::MOUSE_LEFT, Controller::MOUSE_UP, x, y);
}

- (void)mouseLeftDown:(NSPoint)locationInWindow;
{
    int x = (int)locationInWindow.x;
    int y = mController->windowHeight - (int)locationInWindow.y;
    mController->MouseButton(Controller::MOUSE_LEFT, Controller::MOUSE_DOWN, x, y);
}

- (void)mouseRightUp:(NSPoint)locationInWindow;
{
    int x = (int)locationInWindow.x;
    int y = mController->windowHeight - (int)locationInWindow.y;
    mController->MouseButton(Controller::MOUSE_RIGHT, Controller::MOUSE_UP, x, y);
}

- (void)mouseRightDown:(NSPoint)locationInWindow;
{
    int x = (int)locationInWindow.x;
    int y = mController->windowHeight - (int)locationInWindow.y;
    mController->MouseButton(Controller::MOUSE_RIGHT, Controller::MOUSE_DOWN, x, y);
}

- (void)mouseMoveWithX:(CGFloat)x andY:(CGFloat)y
{
    y = mController->windowHeight - y;
    mController->PassiveMotion(x, y);
}
- (void)mouseRightDragWithX:(CGFloat)x andY:(CGFloat)y
{
    mController->MouseRightDrag(x, y);
}

- (void)mouseLeftDragWithX:(CGFloat)x andY:(CGFloat)y
{
    mController->MouseLeftDrag(x, y);
}

- (void)mouseScrollWithX:(CGFloat)x andY:(CGFloat)y
{
    mController->MouseButton(Controller::MOUSE_SCROLL, (int)y,
                             mController->mouseX, mController->mouseY);
    
}
- (void)update:(NSTimeInterval)timeInterval
{
    mController->update(timeInterval * 1000.0f);
}

- (void)render;
{
    glUseProgram(program);
    GLint local_modelView = glGetUniformLocation(program, "modelView");
    glUniformMatrix4fv(local_modelView, 1, GL_FALSE, mController->modelView.get());
    GLint local_projection = glGetUniformLocation(program, "projection");
    glUniformMatrix4fv(local_projection, 1, GL_FALSE, mController->projection.get());
    mController->render();
    glUseProgram(UIShaderProgram);
    local_modelView = glGetUniformLocation(UIShaderProgram, "modelView");
    glUniformMatrix4fv(local_modelView, 1, GL_FALSE, mController->modelView.get());
//    glUniformMatrix4fv(local_modelView, 1, GL_FALSE, mController->GUI->getModelView().get());
    local_projection = glGetUniformLocation(UIShaderProgram, "projection");
    glUniformMatrix4fv(local_projection, 1, GL_FALSE, mController->projection.get());
//    glUniformMatrix4fv(local_projection, 1, GL_FALSE, mController->GUI->getProjection().get());
    mController->GUI->render();
    checkGlErr(__LINE__);
}

-(void)reshapeWidth:(int)width height:(int)height
{
    mController->resize(width, height);
    NSLog(@"reshape - width: %d height: %d", width, height);
}
@end

@implementation CashewOpenGLView(CashewMain)

- (void)prepareOpenGL
{
    NSLog(@"prepareOpenGL");
    [super prepareOpenGL];
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glClearColor(0.8, 0.8, 0.8, 1.0);
    NSString *resourcePath = [[NSBundle mainBundle] resourcePath];
    [[NSFileManager defaultManager] changeCurrentDirectoryPath:resourcePath];
    NSLog(@"%@", resourcePath);

    GLint range[2];
    glGetIntegerv(GL_ALIASED_LINE_WIDTH_RANGE, range);
    glGetIntegerv(GL_SMOOTH_LINE_WIDTH_RANGE, range);
    Set_OpenGLViewDelegate(CashewApp);
}

- (void)clearGLContext
{
    NSLog(@"clearGLContext");
    cashew::clearScene();
    glDeleteProgram(program);
    glDeleteProgram(UIShaderProgram);
    [super clearGLContext];
}

@end
