// Shipeng Xu
// billhsu.x@gmail.com

#version 330 core

layout (lines) in;
layout (triangle_strip) out;
layout (max_vertices = 24) out;

uniform mat4 modelView;
uniform mat4 projection;

uniform float thickness;
uniform vec4 lineColor;
out vec4 colorGs;

void vectorsToRect(vec4 vector1, vec4 vector2, vec4 vector3, vec4 vector4) {
    gl_Position = projection * vector1;
    colorGs = lineColor;
    EmitVertex();
    
    gl_Position = projection * vector2;
    colorGs = lineColor;
    EmitVertex();
    
    gl_Position = projection * vector3;
    colorGs = lineColor;
    EmitVertex();
    
    gl_Position = projection * vector4;
    colorGs = lineColor;
    EmitVertex();
}

void main (void)
{
    vec4 P = gl_in[0].gl_Position;
    vec4 Q = gl_in[1].gl_Position;
    vec3 PQ = Q.xyz - P.xyz;
    
    vec3 xBase = cross(vec3(1, 0, 0), PQ);
    vec3 yBase = cross(vec3(0, 1, 0), PQ);
    vec3 zBase = cross(vec3(0, 0, 1), PQ);
    
    vec3 hBase, vBase;
    if (length(xBase) <= length(yBase) && length(xBase) <= length(zBase)) {
        hBase = normalize(yBase) * thickness;
        vBase = normalize(zBase) * thickness;
    } else if (length(yBase) <= length(xBase) &&
               length(yBase) <= length(zBase)) {
        hBase = normalize(xBase) * thickness;
        vBase = normalize(zBase) * thickness;
    } else if (length(zBase) <= length(xBase) &&
               length(zBase) <= length(yBase)) {
        hBase = normalize(xBase) * thickness;
        vBase = normalize(yBase) * thickness;
    }
    
    vec4 vector0 = P + vec4(hBase, 0);
    vec4 vector1 = P + vec4(vBase, 0);
    vec4 vector2 = P - vec4(hBase, 0);
    vec4 vector3 = P - vec4(vBase, 0);
    
    vec4 vector4 = Q + vec4(hBase, 0);
    vec4 vector5 = Q + vec4(vBase, 0);
    vec4 vector6 = Q - vec4(hBase, 0);
    vec4 vector7 = Q - vec4(vBase, 0);
    
    // up
    vectorsToRect(vector0, vector1, vector2, vector3);
    // bottom
    vectorsToRect(vector4, vector5, vector6, vector7);
    // front
    vectorsToRect(vector0, vector1, vector5, vector4);
    // back
    vectorsToRect(vector2, vector3, vector7, vector6);
    // left
    vectorsToRect(vector0, vector3, vector7, vector4);
    // up
    vectorsToRect(vector1, vector2, vector6, vector5);
    EndPrimitive();
}
