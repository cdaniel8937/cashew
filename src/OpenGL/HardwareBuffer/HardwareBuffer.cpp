// Shipeng Xu
// billhsu.x@gmail.com

#include "HardwareBuffer.h"
#include <iostream>
#include "OpenGL/Util/Utility.h"

void HardwareBuffer::initVBO(VBOStruct vboStruct, unsigned int vboFlag) {
    VBOInfo = vboStruct;
    flags = vboFlag;
    if (vboFlag & FLAG_VERTEX_BUFFER) {
        bufferGenBind<float>(vertexBuffer, vboStruct.vertexBufferSize,
                             vboStruct.vertexBufferData, GL_ARRAY_BUFFER,
                             GL_STATIC_DRAW);
    }

    if (vboFlag & FLAG_UV_BUFFER) {
        bufferGenBind<float>(uvBuffer, vboStruct.uvBufferSize,
                             vboStruct.uvBufferData, GL_ARRAY_BUFFER,
                             GL_STATIC_DRAW);
    }

    if (vboFlag & FLAG_COLOR_BUFFER) {
        bufferGenBind<float>(colorBuffer, vboStruct.colorBufferSize,
                             vboStruct.colorBufferData, GL_ARRAY_BUFFER,
                             GL_STATIC_DRAW);
    }

    if (vboFlag & FLAG_INDEX_BUFFER) {
        bufferGenBind<int>(indexBuffer, vboStruct.indexBufferSize,
                           vboStruct.indexBufferData, GL_ELEMENT_ARRAY_BUFFER,
                           GL_STATIC_DRAW);
    }

    if (vboFlag & FLAG_EXTRA_BUFFER_1) {
        bufferGenBind<float>(extraBuffer1, vboStruct.extraBuffer1Size,
                             vboStruct.extraBuffer1Data, GL_ARRAY_BUFFER,
                             GL_STATIC_DRAW);
    }

    if (vboFlag & FLAG_EXTRA_BUFFER_2) {
        bufferGenBind<float>(extraBuffer2, vboStruct.extraBuffer2Size,
                             vboStruct.extraBuffer2Data, GL_ARRAY_BUFFER,
                             GL_STATIC_DRAW);
    }

    if (vboFlag & FLAG_EXTRA_BUFFER_3) {
        bufferGenBind<float>(extraBuffer3, vboStruct.extraBuffer3Size,
                             vboStruct.extraBuffer3Data, GL_ARRAY_BUFFER,
                             GL_STATIC_DRAW);
    }

    if (vboFlag & FLAG_EXTRA_BUFFER_4) {
        bufferGenBind<float>(extraBuffer4, vboStruct.extraBuffer4Size,
                             vboStruct.extraBuffer4Data, GL_ARRAY_BUFFER,
                             GL_STATIC_DRAW);
    }

    if (vboFlag & FLAG_EXTRA_BUFFER_5) {
        bufferGenBind<float>(extraBuffer5, vboStruct.extraBuffer5Size,
                             vboStruct.extraBuffer5Data, GL_ARRAY_BUFFER,
                             GL_STATIC_DRAW);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glGenVertexArrays(1, &vertexArrayObj);
}

void HardwareBuffer::updateVBO(const VBOStruct vboStruct,
                               unsigned int vboFlag) {
    checkGlErr(__FILE__, __LINE__);
    flags |= vboFlag;

    if (vboFlag & FLAG_VERTEX_BUFFER) {
        VBOInfo.vertexBufferData = vboStruct.vertexBufferData;
        VBOInfo.vertexBufferSize = vboStruct.vertexBufferSize;
        bufferUpdate<float>(vertexBuffer, vboStruct.vertexBufferSize,
                            vboStruct.vertexBufferData, GL_ARRAY_BUFFER,
                            GL_DYNAMIC_DRAW);
    }

    if (vboFlag & FLAG_UV_BUFFER) {
        VBOInfo.uvBufferData = vboStruct.uvBufferData;
        VBOInfo.uvBufferSize = vboStruct.uvBufferSize;
        bufferUpdate<float>(uvBuffer, vboStruct.uvBufferSize,
                            vboStruct.uvBufferData, GL_ARRAY_BUFFER,
                            GL_DYNAMIC_DRAW);
    }

    if (vboFlag & FLAG_COLOR_BUFFER) {
        VBOInfo.colorBufferData = vboStruct.colorBufferData;
        VBOInfo.colorBufferSize = vboStruct.colorBufferSize;
        bufferUpdate<float>(colorBuffer, vboStruct.colorBufferSize,
                            vboStruct.colorBufferData, GL_ARRAY_BUFFER,
                            GL_DYNAMIC_DRAW);
    }

    if (vboFlag & FLAG_INDEX_BUFFER) {
        VBOInfo.indexBufferData = vboStruct.indexBufferData;
        VBOInfo.indexBufferSize = vboStruct.indexBufferSize;
        bufferUpdate<int>(indexBuffer, vboStruct.indexBufferSize,
                          vboStruct.indexBufferData, GL_ELEMENT_ARRAY_BUFFER,
                          GL_DYNAMIC_DRAW);
    }

    if (vboFlag & FLAG_EXTRA_BUFFER_1) {
        VBOInfo.extraBuffer1Data = vboStruct.extraBuffer1Data;
        VBOInfo.extraBuffer1Size = vboStruct.extraBuffer1Size;
        bufferUpdate<float>(extraBuffer1, vboStruct.extraBuffer1Size,
                            vboStruct.extraBuffer1Data, GL_ARRAY_BUFFER,
                            GL_DYNAMIC_DRAW);
    }

    if (vboFlag & FLAG_EXTRA_BUFFER_2) {
        VBOInfo.extraBuffer2Data = vboStruct.extraBuffer2Data;
        VBOInfo.extraBuffer2Size = vboStruct.extraBuffer2Size;
        bufferUpdate<float>(extraBuffer2, vboStruct.extraBuffer2Size,
                            vboStruct.extraBuffer2Data, GL_ARRAY_BUFFER,
                            GL_DYNAMIC_DRAW);
    }

    if (vboFlag & FLAG_EXTRA_BUFFER_3) {
        VBOInfo.extraBuffer3Data = vboStruct.extraBuffer3Data;
        VBOInfo.extraBuffer3Size = vboStruct.extraBuffer3Size;
        bufferUpdate<float>(extraBuffer3, vboStruct.extraBuffer3Size,
                            vboStruct.extraBuffer3Data, GL_ARRAY_BUFFER,
                            GL_DYNAMIC_DRAW);
    }

    if (vboFlag & FLAG_EXTRA_BUFFER_4) {
        VBOInfo.extraBuffer4Data = vboStruct.extraBuffer4Data;
        VBOInfo.extraBuffer4Size = vboStruct.extraBuffer4Size;
        bufferUpdate<float>(extraBuffer4, vboStruct.extraBuffer4Size,
                            vboStruct.extraBuffer4Data, GL_ARRAY_BUFFER,
                            GL_DYNAMIC_DRAW);
    }

    if (vboFlag & FLAG_EXTRA_BUFFER_5) {
        VBOInfo.extraBuffer5Data = vboStruct.extraBuffer5Data;
        VBOInfo.extraBuffer5Size = vboStruct.extraBuffer5Size;
        bufferUpdate<float>(extraBuffer5, vboStruct.extraBuffer5Size,
                            vboStruct.extraBuffer5Data, GL_ARRAY_BUFFER,
                            GL_DYNAMIC_DRAW);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    checkGlErr(__FILE__, __LINE__);
}

void HardwareBuffer::setVBOLocation(unsigned int vboFlag, int location) {
    VBOLocation[vboFlag] = location;
}

void HardwareBuffer::setVBOUnitSize(unsigned int vboFlag, int unitSize) {
    VBOUnitSize[vboFlag] = unitSize;
}

void HardwareBuffer::render(GLenum mode, int unitSize) {
    checkGlErr(__FILE__, __LINE__);
    glBindVertexArray(vertexArrayObj);
    int index = 0;
    int tmp_loc[32];

    if (flags & FLAG_VERTEX_BUFFER) {
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glEnableVertexAttribArray(VBOLocation[FLAG_VERTEX_BUFFER]);
        glVertexAttribPointer(VBOLocation[FLAG_VERTEX_BUFFER],
                              VBOUnitSize[FLAG_VERTEX_BUFFER], GL_FLOAT,
                              GL_FALSE, 0, (GLvoid*)0);
        tmp_loc[index] = VBOLocation[FLAG_VERTEX_BUFFER];
        ++index;
    }

    if (flags & FLAG_EXTRA_BUFFER_1) {
        glBindBuffer(GL_ARRAY_BUFFER, extraBuffer1);
        glEnableVertexAttribArray(VBOLocation[FLAG_EXTRA_BUFFER_1]);
        glVertexAttribPointer(VBOLocation[FLAG_EXTRA_BUFFER_1],
                              VBOUnitSize[FLAG_EXTRA_BUFFER_1], GL_FLOAT,
                              GL_FALSE, 0, (GLvoid*)0);
        tmp_loc[index] = VBOLocation[FLAG_EXTRA_BUFFER_1];
        ++index;
    }

    if (flags & FLAG_EXTRA_BUFFER_2) {
        glBindBuffer(GL_ARRAY_BUFFER, extraBuffer2);
        glEnableVertexAttribArray(VBOLocation[FLAG_EXTRA_BUFFER_2]);
        glVertexAttribPointer(VBOLocation[FLAG_EXTRA_BUFFER_2],
                              VBOUnitSize[FLAG_EXTRA_BUFFER_2], GL_FLOAT,
                              GL_FALSE, 0, (GLvoid*)0);
        tmp_loc[index] = VBOLocation[FLAG_EXTRA_BUFFER_2];
        ++index;
    }

    if (flags & FLAG_EXTRA_BUFFER_3) {
        glBindBuffer(GL_ARRAY_BUFFER, extraBuffer3);
        glEnableVertexAttribArray(VBOLocation[FLAG_EXTRA_BUFFER_3]);
        glVertexAttribPointer(VBOLocation[FLAG_EXTRA_BUFFER_3],
                              VBOUnitSize[FLAG_EXTRA_BUFFER_3], GL_FLOAT,
                              GL_FALSE, 0, (GLvoid*)0);
        tmp_loc[index] = VBOLocation[FLAG_EXTRA_BUFFER_3];
        ++index;
    }

    if (flags & FLAG_EXTRA_BUFFER_4) {
        glBindBuffer(GL_ARRAY_BUFFER, extraBuffer4);
        glEnableVertexAttribArray(VBOLocation[FLAG_EXTRA_BUFFER_4]);
        glVertexAttribPointer(VBOLocation[FLAG_EXTRA_BUFFER_4],
                              VBOUnitSize[FLAG_EXTRA_BUFFER_4], GL_FLOAT,
                              GL_FALSE, 0, (GLvoid*)0);
        tmp_loc[index] = VBOLocation[FLAG_EXTRA_BUFFER_4];
        ++index;
    }

    if (flags & FLAG_EXTRA_BUFFER_5) {
        glBindBuffer(GL_ARRAY_BUFFER, extraBuffer5);
        glEnableVertexAttribArray(VBOLocation[FLAG_EXTRA_BUFFER_5]);
        glVertexAttribPointer(VBOLocation[FLAG_EXTRA_BUFFER_5],
                              VBOUnitSize[FLAG_EXTRA_BUFFER_5], GL_FLOAT,
                              GL_FALSE, 0, (GLvoid*)0);
        tmp_loc[index] = VBOLocation[FLAG_EXTRA_BUFFER_5];
        ++index;
    }

    if (flags & FLAG_UV_BUFFER) {
        glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
        glEnableVertexAttribArray(VBOLocation[FLAG_UV_BUFFER]);
        glVertexAttribPointer(VBOLocation[FLAG_UV_BUFFER],
                              VBOUnitSize[FLAG_UV_BUFFER], GL_FLOAT, GL_FALSE,
                              0, (GLvoid*)0);
        tmp_loc[index] = VBOLocation[FLAG_UV_BUFFER];
        ++index;
    }

    if (flags & FLAG_COLOR_BUFFER) {
        glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
        glEnableVertexAttribArray(VBOLocation[FLAG_COLOR_BUFFER]);
        glVertexAttribPointer(VBOLocation[FLAG_COLOR_BUFFER],
                              VBOUnitSize[FLAG_COLOR_BUFFER], GL_FLOAT,
                              GL_FALSE, 0, (GLvoid*)0);
        tmp_loc[index] = VBOLocation[FLAG_COLOR_BUFFER];
        ++index;
    }

    if (flags & FLAG_INDEX_BUFFER) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glDrawElements(mode, VBOInfo.indexBufferSize, GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(mode, 0, VBOInfo.vertexBufferSize / unitSize);
    }
    for (int i = 0; i < index; ++i) {
        glDisableVertexAttribArray(tmp_loc[i]);
    }
    checkGlErr(__FILE__, __LINE__);
}
template <typename T>
void HardwareBuffer::bufferGenBind(GLuint& bufferID, int bufferSize,
                                   T* bufferData, GLenum bufferType,
                                   GLenum bufferUsage) {
    checkGlErr(__FILE__, __LINE__);
    glGenBuffers(1, &bufferID);
    glBindBuffer(bufferType, bufferID);
    glBufferData(bufferType, bufferSize * sizeof(T), 0, bufferUsage);

    T* dataBufVertices = (T*)glMapBuffer(bufferType, GL_WRITE_ONLY);

    if (dataBufVertices == 0) {
        std::cerr << "glMapBuffer failed: " << __FILE__ << "[" << __LINE__
                  << "]" << std::endl;
    } else {
        for (int i = 0; i < bufferSize; i++) {
            dataBufVertices[i] = bufferData[i];
        }
        glUnmapBuffer(bufferType);
    }
    checkGlErr(__FILE__, __LINE__);
}

template <typename T>
void HardwareBuffer::bufferUpdate(GLuint& bufferID, int bufferSize,
                                  T* bufferData, GLenum bufferType,
                                  GLenum bufferUsage) {
    checkGlErr(__FILE__, __LINE__);
    glBindBuffer(bufferType, bufferID);
    checkGlErr(__FILE__, __LINE__);
    glBufferData(bufferType, bufferSize * sizeof(T), 0, bufferUsage);
    checkGlErr(__FILE__, __LINE__);
    T* dataBufVertices = (T*)glMapBuffer(bufferType, GL_WRITE_ONLY);
    checkGlErr(__FILE__, __LINE__);
    if (dataBufVertices == 0) {
        std::cerr << "glMapBuffer failed: " << __FILE__ << "[" << __LINE__
                  << "]" << std::endl;
    } else {
        for (int i = 0; i < bufferSize; i++) {
            dataBufVertices[i] = bufferData[i];
        }
        glUnmapBuffer(bufferType);
    }
    checkGlErr(__FILE__, __LINE__);
}