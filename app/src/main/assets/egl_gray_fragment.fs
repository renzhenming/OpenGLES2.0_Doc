
precision mediump float;
uniform sampler2D vTexture;
varying vec2 aCoordinate;

void main(){
    vec4 originColor = texture2D(vTexture,aCoordinate);
    float v = originColor.g;
    gl_FragColor = vec4(v,v,v,originColor.a);
}