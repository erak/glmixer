void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 uv = fragCoord.xy / iResolution.xy;
    vec4 color =  texture2D(iChannel0, uv);
    float interval = 6.0;
    float a = step(mod(fragCoord.x + fragCoord.y, interval) / (interval - 1.0), 0.5);
	fragColor = vec4(color.rgb * a,1.0);
}