attribute vec4 vPosition;
attribute vec2 vCoordinate;
uniform mat4 U_ModelMatrix;
uniform mat4 U_ViewMatrix;
uniform mat4 U_ProjectionMatrix;

varying vec2 aCoordinate;
void main(){
    gl_Position = U_ProjectionMatrix*U_ViewMatrix*U_ModelMatrix*vPosition;
    aCoordinate = vCoordinate;
}