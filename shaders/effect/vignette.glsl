// https://www.shadertoy.com/view/XlVSR1
#define innerRadius 0.15
#define outerRadius 1.35
#define opacity 0.85

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
	
	vec2 uv = fragCoord.xy / iResolution.xy;
    
    // Center the UV with the aspect ration taken into account so the outerRadius of 1.0 is the edge of the screen
    vec2 centered = (uv - vec2(0.5)) * (iResolution.x / iResolution.y);
    
    vec4 image = texture2D(iChannel0, uv);
    vec4 color = vec4(1.0);
    
    // Create the vignette effect in black and white
    color.rgb *= 1.0 - smoothstep(innerRadius, outerRadius, length(centered));
    
    // Apply the vignette to the image
    color *= image;
    
    // Mix between the vignette version and the original to change the vignette opacity
    color = mix(image, color, opacity);
    
    fragColor = color;
    
}
