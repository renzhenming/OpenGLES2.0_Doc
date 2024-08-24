precision mediump float;
uniform sampler2D u_Texture;
uniform vec4 u_ImageSize;
varying vec4 v_Position;
varying vec2 v_Texcoord;

void main(){
    gl_FragColor = texture2D(u_Texture,v_Texcoord);
    if(v_Position.x > 0.0) {
        float texture_size_per_pixcel_s = 1.0 / 587.0;
        float texture_size_per_pixcel_t = 1.0 / 488.0;
        vec3 color = vec3(0);
        for(int i = -3; i <= 3; i++) {
            for(int j = -3; j <= 3; j++) {
                //图片模糊处理是采集周边多个点，然后利用这些点的色彩和这个点自身的色彩进行计算，得到一个新的色彩值作为目标色彩
                float texture_x = v_Texcoord.x + float(i) * texture_size_per_pixcel_s;
                float texture_y = v_Texcoord.y + float(j) * texture_size_per_pixcel_t;
                color += texture2D(u_Texture, vec2(texture_x, texture_y)).rgb;
            }
        }
        color = color / 49.0;
        gl_FragColor = vec4(color, texture2D(u_Texture,v_Texcoord).a);
    }
}