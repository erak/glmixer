// https://www.shadertoy.com/view/MtyXRh
void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
	vec2 uv = (fragCoord.xy/iResolution.xy);
    vec4 sample = texture2D(iChannel0, uv);
   
    vec3 filterColorLevel = vec3(0.5, 0.5, 0.5);
    float bloomLevel = 0.2;
    float softLevel = 0.5;
    float overbright = 1.5;
    float softFactor = 0.5;
    
    float brightenRatio = 1.0-dot(filterColorLevel, sample.rgb) ;
    float fade = step(brightenRatio, softLevel);
    float bloom = step(brightenRatio, bloomLevel);
    float fadedBloom = bloom*overbright-fade+fade*softFactor;
    fragColor = sample*fadedBloom;        
}
