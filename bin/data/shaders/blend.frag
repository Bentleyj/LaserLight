#version 120

uniform sampler2DRect imgTex;
uniform sampler2DRect vidTex;
uniform vec2 resolution;
uniform vec2 imgSize;
uniform vec2 vidSize;
uniform vec2 imgHotspot;
uniform vec2 vidHotspot;
uniform float vidScale;
uniform float scale;
uniform vec2 imageOffset;

float length(vec3 v) {
    return sqrt(v.x * v.x + v.y * v.y + v.x * v.z);
}

void main() {
    
    float width = 20;
    
    vec2 uv = gl_FragCoord.xy / resolution;
    
//    uv.y = 1.0 - uv.y;
    
    
    vec2 uvAbs = uv * resolution;
    
    uvAbs -= imageOffset;
    
    uvAbs /= scale;
    
    vec2 imgPix = uvAbs;
    vec2 vidPix = uvAbs;
    
    vec2 diff = imgHotspot - vidHotspot;
    
    vidPix -= diff;
    
    vidPix -= vidHotspot;
    vidPix /= vidScale;
    vidPix += vidHotspot;
    
    vec3 tc1 = texture2DRect(imgTex, imgPix).rgb;
    vec3 tc2 = texture2DRect(vidTex, vidPix).rgb;
    
    vec3 tc = mix(tc1 * tc2, tc2, tc1);

    if(uvAbs.x > imgSize.x || uvAbs.x < 0 || uvAbs.y > imgSize.y || uvAbs.y < 0) {
        if(uvAbs.x > imgSize.x + width || uvAbs.x < 0 - width || uvAbs.y > imgSize.y + width || uvAbs.y < 0 - width) {
            tc = vec3(0.0);
        } else {
            tc = vec3(1.0);
        }
    }
    
    
    gl_FragColor = vec4(tc, 1.0);
}
