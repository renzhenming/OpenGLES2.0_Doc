
precision mediump float;
uniform sampler2D vTexture;
varying vec2 aCoordinate;
varying vec2 v_Coord;
varying vec4 v_Position;

void main(){
    vec4 originColor = texture2D(vTexture,aCoordinate);
    if(v_Position.x > 0.0){
        //黑白图片上，每个像素点的RGB三个通道值应该是相等的。知道了这个，将彩色图片处理成黑白图片就非常简单了。
        //我们直接出处像素点的RGB三个通道，相加然后除以3作为处理后每个通道的值就可以得到一个黑白图片了。
        //这是均值的方式是常见黑白图片处理的一种方法。类似的还有权值方法（给予RGB三个通道不同的比例）、只取绿色通道等方式。
        float v = originColor.r*0.3 + originColor.g * 0.59+originColor.b*0.11;//Gray = R * 0.3 + G * 0.59 + B * 0.11
        //float v = originColor.g;//仅取绿色： Gray = G
        gl_FragColor = vec4(v,v,v,originColor.a);
    } else {
        gl_FragColor = originColor;
    }
}