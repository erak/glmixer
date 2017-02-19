/*
** Gamma correction
** Details: http://blog.mouaif.org/2009/01/22/photoshop-gamma-correction-shader/
*/
#define GammaCorrection(color, gamma) pow( color, 1.0 / vec3(gamma))

/*
** Levels control (input (+gamma), output)
** Details: http://blog.mouaif.org/2009/01/28/levels-control-shader/
*/
#define LevelsControlInputRange(color, minInput, maxInput)  min(max(color - vec3(minInput), 0.0) / (vec3(maxInput) - vec3(minInput)), 1.0)
#define LevelsControlInput(color, minInput, gamma, maxInput) GammaCorrection(LevelsControlInputRange(color, minInput, maxInput), gamma)
#define LevelsControlOutputRange(color, minOutput, maxOutput)  mix(vec3(minOutput), vec3(maxOutput), color)
#define LevelsControl(color, minInput, gamma, maxInput, minOutput, maxOutput)   LevelsControlOutputRange(LevelsControlInput(color, minInput, gamma, maxInput), minOutput, maxOutput)

#define ONETHIRD 0.333333
#define TWOTHIRD 0.666666
#define EPSILON  0.000001

varying vec2 texc;
varying vec2 maskc;

uniform sampler2D sourceTexture;
uniform sampler2D maskTexture;

uniform vec4 baseColor;
uniform float baseAlpha;
uniform float stippling;
uniform float contrast;
uniform float saturation;
uniform float brightness;
uniform float gamma;
uniform vec4 levels;
uniform float hueshift;
uniform vec4 chromakey;
uniform float chromadelta;
uniform float threshold;
uniform int nbColors;
uniform int invertMode;

uniform vec2 filter_step;
uniform int filter;
uniform mat3 filter_kernel;


vec3 erosion(int N)
{
    vec3 minValue = vec3(1.0);

        minValue = min(texture2D(sourceTexture, texc + vec2 (0.0,0.0) * filter_step ).rgb, minValue);
        minValue = min(texture2D(sourceTexture, texc + vec2 (0.0,-1.0) * filter_step ).rgb, minValue);
        minValue = min(texture2D(sourceTexture, texc + vec2 (-1.0, 0.0) * filter_step ).rgb, minValue);
        minValue = min(texture2D(sourceTexture, texc + vec2 (1.0, 0.0) * filter_step ).rgb, minValue);
        minValue = min(texture2D(sourceTexture, texc + vec2 (0.0, 1.0) * filter_step ).rgb, minValue);
        if (N == 3)
                return minValue;
        minValue = min(texture2D(sourceTexture, texc + vec2 (-1.0, -2.0) * filter_step ).rgb, minValue);
        minValue = min(texture2D(sourceTexture, texc + vec2 (0.0,-2.0) * filter_step ).rgb, minValue);
        minValue = min(texture2D(sourceTexture, texc + vec2 (1.0,-2.0) * filter_step ).rgb, minValue);
        minValue = min(texture2D(sourceTexture, texc + vec2 (-1.0,2.0) * filter_step ).rgb, minValue);
        minValue = min(texture2D(sourceTexture, texc + vec2 (0.0, 2.0) * filter_step ).rgb, minValue);
        minValue = min(texture2D(sourceTexture, texc + vec2 (1.0, 2.0) * filter_step ).rgb, minValue);
        minValue = min(texture2D(sourceTexture, texc + vec2 (-2.0, 1.0) * filter_step ).rgb, minValue);
        minValue = min(texture2D(sourceTexture, texc + vec2 (-1.0, 1.0) * filter_step ).rgb, minValue);
        minValue = min(texture2D(sourceTexture, texc + vec2 ( 1.0, 1.0) * filter_step ).rgb, minValue);
        minValue = min(texture2D(sourceTexture, texc + vec2 ( 2.0, 1.0) * filter_step ).rgb, minValue);
        minValue = min(texture2D(sourceTexture, texc + vec2 (-2.0, -1.0) * filter_step ).rgb, minValue);
        minValue = min(texture2D(sourceTexture, texc + vec2 (-1.0, -1.0) * filter_step ).rgb, minValue);
        minValue = min(texture2D(sourceTexture, texc + vec2 ( 1.0, -1.0) * filter_step ).rgb, minValue);
        minValue = min(texture2D(sourceTexture, texc + vec2 ( 2.0, -1.0) * filter_step ).rgb, minValue);
        minValue = min(texture2D(sourceTexture, texc + vec2 (-2.0, 0.0) * filter_step ).rgb, minValue);
        minValue = min(texture2D(sourceTexture, texc + vec2 ( 2.0, 0.0) * filter_step ).rgb, minValue);
        if (N == 5)
                return minValue;
        minValue = min(texture2D(sourceTexture, texc + vec2 (-1.0, -3.0) * filter_step ).rgb, minValue);
        minValue = min(texture2D(sourceTexture, texc + vec2 (0.0,-3.0) * filter_step ).rgb, minValue);
        minValue = min(texture2D(sourceTexture, texc + vec2 (1.0,-3.0) * filter_step ).rgb, minValue);
        minValue = min(texture2D(sourceTexture, texc + vec2 (-1.0,3.0) * filter_step ).rgb, minValue);
        minValue = min(texture2D(sourceTexture, texc + vec2 (0.0, 3.0) * filter_step ).rgb, minValue);
        minValue = min(texture2D(sourceTexture, texc + vec2 (1.0, 3.0) * filter_step ).rgb, minValue);
        minValue = min(texture2D(sourceTexture, texc + vec2 (-2.0, 2.0) * filter_step ).rgb, minValue);
        minValue = min(texture2D(sourceTexture, texc + vec2 ( 2.0, 2.0) * filter_step ).rgb, minValue);
        minValue = min(texture2D(sourceTexture, texc + vec2 (-2.0, -2.0) * filter_step ).rgb, minValue);
        minValue = min(texture2D(sourceTexture, texc + vec2 ( 2.0, -2.0) * filter_step ).rgb, minValue);
        minValue = min(texture2D(sourceTexture, texc + vec2 (-3.0, -1.0) * filter_step ).rgb, minValue);
        minValue = min(texture2D(sourceTexture, texc + vec2 (3.0, -1.0) * filter_step ).rgb, minValue);
        minValue = min(texture2D(sourceTexture, texc + vec2 (-3.0, 1.0) * filter_step ).rgb, minValue);
        minValue = min(texture2D(sourceTexture, texc + vec2 ( 3.0, 1.0) * filter_step ).rgb, minValue);
        minValue = min(texture2D(sourceTexture, texc + vec2 (-3.0, 0.0) * filter_step ).rgb, minValue);
        minValue = min(texture2D(sourceTexture, texc + vec2 ( 3.0, 0.0) * filter_step ).rgb, minValue);

    return minValue;
}

vec3 dilation(int N)
{
    vec3 maxValue = vec3(0.0);

        maxValue = max(texture2D(sourceTexture, texc + vec2 (0.0, 0.0) * filter_step ).rgb, maxValue);
        maxValue = max(texture2D(sourceTexture, texc + vec2 (0.0,-1.0) * filter_step ).rgb, maxValue);
        maxValue = max(texture2D(sourceTexture, texc + vec2 (-1.0, 0.0) * filter_step ).rgb, maxValue);
        maxValue = max(texture2D(sourceTexture, texc + vec2 (1.0, 0.0) * filter_step ).rgb, maxValue);
        maxValue = max(texture2D(sourceTexture, texc + vec2 (0.0, 1.0) * filter_step ).rgb, maxValue);
        if (N == 3)
                return maxValue;
        maxValue = max(texture2D(sourceTexture, texc + vec2 (-1.0, -2.0) * filter_step ).rgb, maxValue);
        maxValue = max(texture2D(sourceTexture, texc + vec2 (0.0,-2.0) * filter_step ).rgb, maxValue);
        maxValue = max(texture2D(sourceTexture, texc + vec2 (1.0,-2.0) * filter_step ).rgb, maxValue);
        maxValue = max(texture2D(sourceTexture, texc + vec2 (-1.0,2.0) * filter_step ).rgb, maxValue);
        maxValue = max(texture2D(sourceTexture, texc + vec2 (0.0, 2.0) * filter_step ).rgb, maxValue);
        maxValue = max(texture2D(sourceTexture, texc + vec2 (1.0, 2.0) * filter_step ).rgb, maxValue);
        maxValue = max(texture2D(sourceTexture, texc + vec2 (-2.0, 1.0) * filter_step ).rgb, maxValue);
        maxValue = max(texture2D(sourceTexture, texc + vec2 (-1.0, 1.0) * filter_step ).rgb, maxValue);
        maxValue = max(texture2D(sourceTexture, texc + vec2 ( 1.0, 1.0) * filter_step ).rgb, maxValue);
        maxValue = max(texture2D(sourceTexture, texc + vec2 ( 2.0, 1.0) * filter_step ).rgb, maxValue);
        maxValue = max(texture2D(sourceTexture, texc + vec2 (-2.0, -1.0) * filter_step ).rgb, maxValue);
        maxValue = max(texture2D(sourceTexture, texc + vec2 (-1.0, -1.0) * filter_step ).rgb, maxValue);
        maxValue = max(texture2D(sourceTexture, texc + vec2 ( 1.0, -1.0) * filter_step ).rgb, maxValue);
        maxValue = max(texture2D(sourceTexture, texc + vec2 ( 2.0, -1.0) * filter_step ).rgb, maxValue);
        maxValue = max(texture2D(sourceTexture, texc + vec2 (-2.0, 0.0) * filter_step ).rgb, maxValue);
        maxValue = max(texture2D(sourceTexture, texc + vec2 ( 2.0, 0.0) * filter_step ).rgb, maxValue);
        if (N == 5)
                return maxValue;
        maxValue = max(texture2D(sourceTexture, texc + vec2 (-1.0, -3.0) * filter_step ).rgb, maxValue);
        maxValue = max(texture2D(sourceTexture, texc + vec2 (0.0,-3.0) * filter_step ).rgb, maxValue);
        maxValue = max(texture2D(sourceTexture, texc + vec2 (1.0,-3.0) * filter_step ).rgb, maxValue);
        maxValue = max(texture2D(sourceTexture, texc + vec2 (-1.0,3.0) * filter_step ).rgb, maxValue);
        maxValue = max(texture2D(sourceTexture, texc + vec2 (0.0, 3.0) * filter_step ).rgb, maxValue);
        maxValue = max(texture2D(sourceTexture, texc + vec2 (1.0, 3.0) * filter_step ).rgb, maxValue);
        maxValue = max(texture2D(sourceTexture, texc + vec2 (-2.0, 2.0) * filter_step ).rgb, maxValue);
        maxValue = max(texture2D(sourceTexture, texc + vec2 ( 2.0, 2.0) * filter_step ).rgb, maxValue);
        maxValue = max(texture2D(sourceTexture, texc + vec2 (-2.0, -2.0) * filter_step ).rgb, maxValue);
        maxValue = max(texture2D(sourceTexture, texc + vec2 ( 2.0, -2.0) * filter_step ).rgb, maxValue);
        maxValue = max(texture2D(sourceTexture, texc + vec2 (-3.0, -1.0) * filter_step ).rgb, maxValue);
        maxValue = max(texture2D(sourceTexture, texc + vec2 (3.0, -1.0) * filter_step ).rgb, maxValue);
        maxValue = max(texture2D(sourceTexture, texc + vec2 (-3.0, 1.0) * filter_step ).rgb, maxValue);
        maxValue = max(texture2D(sourceTexture, texc + vec2 ( 3.0, 1.0) * filter_step ).rgb, maxValue);
        maxValue = max(texture2D(sourceTexture, texc + vec2 (-3.0, 0.0) * filter_step ).rgb, maxValue);
        maxValue = max(texture2D(sourceTexture, texc + vec2 ( 3.0, 0.0) * filter_step ).rgb, maxValue);

    return maxValue;
}

vec3 convolution()
{
    int i = 0, j = 0;
    vec3 sum = vec3(0.0);

    for (i = 0; i<3; ++i)
        for (j = 0; j<3; ++j)
            sum += texture2D(sourceTexture, texc + filter_step * vec2 (i-1, j-1) ).rgb * filter_kernel[i][j];

    return sum;
}

vec3 apply_filter() {

    if (filter < 1 || filter > 15)
        return texture2D(sourceTexture, texc).rgb;
    else if (filter < 10)
        return convolution();
    else if (filter < 13)
        return erosion( 3 + (filter -10) * 2 );
    else
        return dilation( 3 + (filter -13) * 2  );
}

/*
** Hue, saturation, luminance <=> Red Green Blue
*/

float HueToRGB(float f1, float f2, float hue)
{
    float res;

    hue += mix( -float( hue > 1.0 ), 1.0, float(hue < 0.0) );

    res = mix( f1, mix( clamp( f1 + (f2 - f1) * ((2.0 / 3.0) - hue) * 6.0, 0.0, 1.0) , mix( f2,  clamp(f1 + (f2 - f1) * 6.0 * hue, 0.0, 1.0), float((6.0 * hue) < 1.0)),  float((2.0 * hue) < 1.0)), float((3.0 * hue) < 2.0) );

    return res;
}

vec3 HSV2RGB(vec3 hsl)
{
    vec3 rgb;
    float f1, f2;

    f2 = mix( (hsl.z + hsl.y) - (hsl.y * hsl.z), hsl.z * (1.0 + hsl.y), float(hsl.z < 0.5) );

    f1 = 2.0 * hsl.z - f2;

    rgb.r = HueToRGB(f1, f2, hsl.x + ONETHIRD);
    rgb.g = HueToRGB(f1, f2, hsl.x);
    rgb.b = HueToRGB(f1, f2, hsl.x - ONETHIRD);

    rgb =  mix( rgb, vec3(hsl.z), float(hsl.y < EPSILON));

    return rgb;
}

vec3 RGB2HSV( vec3 color )
{
    vec3 hsl = vec3(0.0); // init to 0

    float fmin = min(min(color.r, color.g), color.b);    //Min. value of RGB
    float fmax = max(max(color.r, color.g), color.b);    //Max. value of RGB
    float delta = fmax - fmin + EPSILON;             //Delta RGB value

    vec3 deltaRGB = ( ( vec3(fmax) - color ) / 6.0  + vec3(delta) / 2.0 ) / delta ;

    hsl.z = (fmax + fmin) / 2.0; // Luminance

    hsl.y = delta / ( EPSILON + mix( 2.0 - fmax - fmin, fmax + fmin, float(hsl.z < 0.5)) );

    hsl.x = mix( hsl.x, TWOTHIRD + deltaRGB.g - deltaRGB.r, float(color.b == fmax));
    hsl.x = mix( hsl.x, ONETHIRD + deltaRGB.r - deltaRGB.b, float(color.g == fmax));
    hsl.x = mix( hsl.x, deltaRGB.b - deltaRGB.g,  float(color.r == fmax));

    hsl.x += mix( - float( hsl.x > 1.0 ), 1.0, float(hsl.x < 0.0) );

    hsl = mix ( hsl, vec3(-1.0, 0.0, hsl.z), float(delta<EPSILON) );

    return hsl;
}


void main(void)
{
    // deal with alpha separately
    float alpha = texture2D(maskTexture, maskc).a * texture2D(sourceTexture, texc).a * baseAlpha;
    vec3 transformedRGB;

    transformedRGB = mix(vec3(0.62), apply_filter(), contrast) + brightness;
    transformedRGB = LevelsControl(transformedRGB, levels.x, gamma, levels.y, levels.z, levels.w);

    // RGB invert
    transformedRGB = vec3(float(invertMode==1)) + ( transformedRGB * vec3(1.0 - 2.0 * float(invertMode==1)) );

    // Convert to HSL
    vec3 transformedHSL = RGB2HSV( transformedRGB );

    // Luminance invert
    transformedHSL.z = float(invertMode==2) +  transformedHSL.z * (1.0 - 2.0 * float(invertMode==2) );

    // perform hue shift
    transformedHSL.x = transformedHSL.x + hueshift;

    // Saturation
    transformedHSL.y *= saturation;

    // perform reduction of colors
    transformedHSL = mix( transformedHSL, floor(transformedHSL * vec3(nbColors)) / vec3(nbColors-1),  float( nbColors > 0 ) );

    // level threshold
    transformedHSL = mix( transformedHSL, vec3(0.0, 0.0, step( transformedHSL.z, threshold )), float(threshold > 0.0));

    // after operations on HSL, convert back to RGB
    transformedRGB = HSV2RGB(transformedHSL);

    // chromakey
    alpha -= mix( 0.0, step( length( normalize(chromakey.xyz) - normalize(transformedRGB) ), chromadelta ), float(chromakey.w > 0.0) );

    // stippling
    alpha += mod( floor(gl_FragCoord.x * stippling) + floor(gl_FragCoord.y * stippling), 2.0);

    // apply base color and alpha for final fragment color
    gl_FragColor = vec4(transformedRGB * baseColor.rgb, clamp(alpha, 0.0, 1.0) );

}



