
attribute highp vec2 texCoord;
attribute lowp vec2 maskCoord;

varying vec2 texc;
varying vec2 maskc;
   
void main(void)
{
    texc = texCoord;
    maskc = maskCoord;

    gl_Position = ftransform();
}

