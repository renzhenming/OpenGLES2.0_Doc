
precision mediump float;
uniform sampler2D vTexture;
varying vec2 aCoordinate;
varying vec4 gPosition;
uniform float ratio;

void fixColor(vec4 color){
    color.r = max(min(color.r,1.0),0.0);
    color.g = max(min(color.g,1.0),0.0);
    color.b = max(min(color.b,1.0),0.0);
    color.a = max(min(color.a,1.0),0.0);
}

void main(){
    vec4 originColor = texture2D(vTexture,aCoordinate);
    float dis=distance(vec2(gPosition.x,gPosition.y*ratio),vec2(0.0,0.0));
     if(dis<0.5){
        //把原来应该显示坐标1位置像素的位置显示0.75位置的像素，就像放大了4分之1一样
        originColor=texture2D(vTexture,vec2(aCoordinate.x/2.0+0.25,aCoordinate.y/2.0+0.25));
     }
    gl_FragColor = originColor;
}