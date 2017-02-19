// https://www.shadertoy.com/view/XdySWm
void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
	vec2 uv = fragCoord.xy / iResolution.xy;
    
    vec4 left = texture2D(iChannel0, uv);
    vec4 right = texture2D(iChannel0, uv + vec2(0.015, 0.0));
	
    vec3 color = vec3(left.r, right.gb);
    color = clamp(color, 0.0, 1.0);
    fragColor = vec4(color, 1.0);
}
