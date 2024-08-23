
precision mediump float;
uniform sampler2D vTexture;
varying vec2 aCoordinate;
varying vec2 v_Coord;
varying vec4 v_Position;

void fixColor(vec4 color){
    color.r = max(min(color.r,1.0),0.0);
    color.g = max(min(color.g,1.0),0.0);
    color.b = max(min(color.b,1.0),0.0);
    color.a = max(min(color.a,1.0),0.0);
}

void main(){
    vec4 originColor = texture2D(vTexture,aCoordinate);
    if(v_Position.x > 0.0){
        //暖色调的处理就是单一增加红色绿色通道的值
        vec4 v = originColor + vec4(0.2,0.2,0.0,0.0);
        fixColor(v);
        gl_FragColor = v;
    } else {
        gl_FragColor = originColor;
    }
}