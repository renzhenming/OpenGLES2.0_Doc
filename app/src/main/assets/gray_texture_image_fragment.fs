
precision mediump float;
uniform sampler2D vTexture;
varying vec2 aCoordinate;
varying vec2 v_Coord;
varying vec4 v_Position;

void main(){
    vec4 originColor = texture2D(vTexture,aCoordinate);
    if(v_Position.x > 0.0){
        float v = originColor.r*0.3 + originColor.g * 0.59+originColor.b*0.11;//Gray = R * 0.3 + G * 0.59 + B * 0.11
        //float v = originColor.g;//仅取绿色： Gray = G
        gl_FragColor = vec4(v,v,v,originColor.a);
    } else {
        gl_FragColor = originColor;
    }
}