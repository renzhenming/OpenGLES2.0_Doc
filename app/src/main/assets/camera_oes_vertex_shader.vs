attribute vec4 vPosition;
attribute vec2 vCoord;

uniform mat4 U_ModelMatrix;
uniform mat4 U_ViewMatrix;
uniform mat4 U_ProjectionMatrix;

varying vec2 textureCoordinate;

void main(){
    gl_Position = U_ProjectionMatrix*U_ViewMatrix*U_ModelMatrix*vPosition;
    textureCoordinate = vCoord;
}