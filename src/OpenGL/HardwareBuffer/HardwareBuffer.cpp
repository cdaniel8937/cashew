// Shipeng Xu
// billhsu.x@gmail.com

#include "HardwareBuffer.h"
#include <iostream>

void HardwareBuffer::initVBO(VBOStruct vboStruct, unsigned int vboFlag)
{
    VBOInfo = vboStruct;
    flags = vboFlag;
    if(vboFlag & FLAG_VERTEX_BUFFER)
    {
        bufferGenBind<float>(vertexBuffer, vboStruct.vertexBufferSize, vboStruct.vertexBufferData,
                             GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    }
    
    if(vboFlag & FLAG_UV_BUFFER)
    {
        bufferGenBind<float>(uvBuffer, vboStruct.uvBufferSize, vboStruct.uvBufferData,
                             GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    }
    
    if(vboFlag & FLAG_COLOR_BUFFER)
    {
        bufferGenBind<float>(colorBuffer, vboStruct.colorBufferSize, vboStruct.colorBufferData,
                             GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    }
    
    if(vboFlag & FLAG_INDEX_BUFFER)
    {
        bufferGenBind<int>(indexBuffer, vboStruct.indexBufferSize, vboStruct.indexBufferData,
                           GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glGenVertexArrays(1, &vertexArrayObj);
}

void HardwareBuffer::updateVBO(const VBOStruct vboStruct, unsigned int vboFlag)
{
    flags |= vboFlag;
    if(vboFlag & FLAG_VERTEX_BUFFER)
    {
        VBOInfo.vertexBufferData = vboStruct.vertexBufferData;
        VBOInfo.vertexBufferSize = vboStruct.vertexBufferSize;
        bufferGenBind<float>(vertexBuffer, vboStruct.vertexBufferSize, vboStruct.vertexBufferData,
                             GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW);
    }
    if(vboFlag & FLAG_UV_BUFFER)
    {
        VBOInfo.uvBufferData = vboStruct.uvBufferData;
        VBOInfo.uvBufferSize = vboStruct.uvBufferSize;
        bufferGenBind<float>(uvBuffer, vboStruct.uvBufferSize, vboStruct.uvBufferData,
                             GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW);
    }
    if(vboFlag & FLAG_COLOR_BUFFER)
    {
        VBOInfo.colorBufferData = vboStruct.colorBufferData;
        VBOInfo.colorBufferSize = vboStruct.colorBufferSize;
        bufferGenBind<float>(colorBuffer, vboStruct.colorBufferSize, vboStruct.colorBufferData,
                             GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW);
    }
    if(vboFlag & FLAG_INDEX_BUFFER)
    {
        VBOInfo.indexBufferData = vboStruct.indexBufferData;
        VBOInfo.indexBufferSize = vboStruct.indexBufferSize;
        bufferGenBind<int>(indexBuffer, vboStruct.indexBufferSize, vboStruct.indexBufferData,
                           GL_ELEMENT_ARRAY_BUFFER, GL_DYNAMIC_DRAW);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void HardwareBuffer::setVBOLocation(unsigned int vboFlag, int location)
{
    VBOLocation[vboFlag] = location;
}

void HardwareBuffer::setVBOUnitSize(unsigned int vboFlag, int unitSize)
{
    VBOUnitSize[vboFlag] = unitSize;
}

void HardwareBuffer::render()
{
    glBindVertexArray(vertexArrayObj);
    int index = 0;
    int tmp_loc[32];

    if(flags & FLAG_VERTEX_BUFFER)
    {
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glEnableVertexAttribArray(VBOLocation[FLAG_VERTEX_BUFFER]);
        glVertexAttribPointer(index, VBOUnitSize[FLAG_VERTEX_BUFFER], GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
        tmp_loc[index] = VBOLocation[FLAG_VERTEX_BUFFER];
        ++index;
    }
    if(flags & FLAG_UV_BUFFER)
    {
        glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
        glEnableVertexAttribArray(VBOLocation[FLAG_UV_BUFFER]);
        glVertexAttribPointer(index, VBOUnitSize[FLAG_UV_BUFFER], GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
        tmp_loc[index] = VBOLocation[FLAG_UV_BUFFER];
        ++index;
    }
    if(flags & FLAG_COLOR_BUFFER)
    {
        glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
        glEnableVertexAttribArray(VBOLocation[FLAG_COLOR_BUFFER]);
        glVertexAttribPointer(index, VBOUnitSize[FLAG_COLOR_BUFFER], GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
        tmp_loc[index] = VBOLocation[FLAG_COLOR_BUFFER];
        ++index;
    }
    if(flags & FLAG_INDEX_BUFFER)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glDrawElements(GL_TRIANGLES, VBOInfo.indexBufferSize, GL_UNSIGNED_INT, 0);
    }
    else
    {
        glDrawArrays(GL_TRIANGLES, 0, VBOInfo.vertexBufferSize / 3);
    }
    for(int i = 0; i< index; ++i)
    {
        glDisableVertexAttribArray(tmp_loc[i]);
    }
}
template<typename T>
void HardwareBuffer::bufferGenBind(GLuint& bufferID, int bufferSize, T* bufferData,
                                   GLenum bufferType, GLenum bufferUsage)
{
    glGenBuffers(1, &bufferID);
    glBindBuffer(bufferType, bufferID);
    glBufferData(bufferType, bufferSize * sizeof(T), 0, bufferUsage);
    T* dataBufVertices = (T*)glMapBuffer(bufferType, GL_WRITE_ONLY);
    if(dataBufVertices == 0)
    {
        std::cerr<<"glMapBuffer failed: "<<__FILE__<<"["<<__LINE__<<"]"<<std::endl;
    }
    else
    {
        for(int i=0; i<bufferSize; i++)
        {
            dataBufVertices[i] = bufferData[i];
        }
        glUnmapBuffer(bufferType);
    }
}