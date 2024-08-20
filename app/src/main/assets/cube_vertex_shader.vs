attribute vec4 vPosition;
attribute vec4 aColor;
varying vec4 vColor;
uniform mat4 U_ModelMatrix;
uniform mat4 U_ViewMatrix;
uniform mat4 U_ProjectionMatrix;
void main(){
    gl_Position=U_ProjectionMatrix*U_ViewMatrix*U_ModelMatrix*vPosition;
    vColor=aColor;
}