attribute vec4 vPosition;
attribute vec2 vCoordinate;
varying vec2 aCoord;
uniform mat4 U_ModelMatrix;
uniform mat4 U_ViewMatrix;
uniform mat4 U_ProjectionMatrix;

void main(){
    aCoord = vCoordinate;
    gl_Position = U_ProjectionMatrix*U_ViewMatrix*U_ModelMatrix*vPosition;
}