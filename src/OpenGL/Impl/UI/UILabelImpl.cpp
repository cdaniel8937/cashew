// Shipeng Xu
// billhsu.x@gmail.com

#include "UILabelImpl.h"

UILabelImpl::~UILabelImpl() {
    std::cout<<"~UILabelImpl("<<this<<")"<<std::endl;
}
void UILabelImpl::render() {
    verticesArray[0] = vertices[0].x; verticesArray[1] = vertices[0].y;
    verticesArray[2] = vertices[1].x; verticesArray[3] = vertices[1].y;
    verticesArray[4] = vertices[2].x; verticesArray[5] = vertices[2].y;
    verticesArray[6] = vertices[3].x; verticesArray[7] = vertices[3].y;
    
    HardwareBuffer::VBOStruct _VBO;
    _VBO.vertexBufferData = verticesArray;
    _VBO.vertexBufferSize = sizeof(verticesArray) / sizeof(float);
    buffer.updateVBO(_VBO, HardwareBuffer::FLAG_VERTEX_BUFFER);
    buffer.render();
}

void UILabelImpl::prepareRenderData() {
    colorArray[ 0] = mR; colorArray[ 1] = mG;  colorArray[ 2] = mB; colorArray[ 3] = mAlpha;
    colorArray[ 4] = mR; colorArray[ 5] = mG;  colorArray[ 6] = mB; colorArray[ 7] = mAlpha;
    colorArray[ 8] = mR; colorArray[ 9] = mG;  colorArray[10] = mB; colorArray[11] = mAlpha;
    colorArray[12] = mR; colorArray[13] = mG;  colorArray[14] = mB; colorArray[15] = mAlpha;
    VBOInfo.vertexBufferSize = sizeof(verticesArray) / sizeof(float);
    VBOInfo.vertexBufferData = verticesArray;
    VBOInfo.colorBufferSize = sizeof(colorArray) / sizeof(float);
    VBOInfo.colorBufferData = colorArray;
    VBOInfo.indexBufferSize = sizeof(indices) / sizeof(int);
    VBOInfo.indexBufferData = indices;
    unsigned int flags = HardwareBuffer::FLAG_VERTEX_BUFFER
    | HardwareBuffer::FLAG_COLOR_BUFFER
    | HardwareBuffer::FLAG_INDEX_BUFFER;
    
    buffer.initVBO(VBOInfo, flags);
    buffer.setVBOLocation(HardwareBuffer::FLAG_VERTEX_BUFFER, 0);
    buffer.setVBOLocation(HardwareBuffer::FLAG_COLOR_BUFFER, 2);
    
    buffer.setVBOUnitSize(HardwareBuffer::FLAG_VERTEX_BUFFER, 2);
    buffer.setVBOUnitSize(HardwareBuffer::FLAG_COLOR_BUFFER, 4);
}