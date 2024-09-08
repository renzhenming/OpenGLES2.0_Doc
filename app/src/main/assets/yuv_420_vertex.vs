attribute vec4 a_Position;
attribute vec4 a_Texcoord;
varying vec4 v_TexCoord;

uniform mat4 U_ModelMatrix;
uniform mat4 U_ViewMatrix;
uniform mat4 U_ProjectionMatrix;

void main(){
    gl_Position = U_ProjectionMatrix*U_ViewMatrix*U_ModelMatrix*a_Position;
    v_TexCoord = a_Texcoord;
}