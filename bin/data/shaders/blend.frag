#version 120

uniform sampler2DRect imgTex;
uniform sampler2DRect vidTex;
uniform vec2 resolution;
uniform float imgScale;
uniform float vidScale;
uniform vec2 imgOffset;

float length(vec3 v) {
    return sqrt(v.x * v.x + v.y * v.y + v.x * v.z);
}

void main() {
    
    vec2 uv = gl_FragCoord.xy / resolution;
    
    uv.y = 1.0 - uv.y;
    
    vec2 uvAbs = uv * resolution;

    vec3 tc1 = texture2DRect(imgTex, uvAbs / imgScale - imgOffset).rgb;
    vec3 tc2 = texture2DRect(vidTex, uvAbs / vidScale).rgb;
    
    vec3 tc = mix(tc1 * tc2, tc2, tc1);
    
    gl_FragColor = vec4(tc, 1.0);
}
