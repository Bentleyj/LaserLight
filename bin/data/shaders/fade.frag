#version 120

uniform sampler2DRect tex1;
uniform sampler2DRect tex2;
uniform vec2 resolution;
uniform float fadeAmount;


void main() {
    vec2 uv = gl_FragCoord.xy / resolution;
    
    uv.y = 1.0 - uv.y;
    
    vec2 uvAbs = uv * resolution;
    
    vec3 tc1 = texture2DRect(tex1, uvAbs).rgb;
    vec3 tc2 = texture2DRect(tex2, uvAbs).rgb;
    
    vec3 tc = mix(tc1, tc2, fadeAmount);
    
    gl_FragColor = vec4(tc, 1.0);
}
