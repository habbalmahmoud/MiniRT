#include "../includes/miniRT.h"

 float dot( float a[3], float b[3])
{
    return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

 void subtract(float a[3], float b[3], float out[3])
{
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
    out[2] = a[2] - b[2];
}

 void add(float a[3],  float b[3], float out[3])
{
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
    out[2] = a[2] + b[2];
}

 void scale( float v[3], float s, float out[3])
{
    out[0] = v[0] * s;
    out[1] = v[1] * s;
    out[2] = v[2] * s;
}

 void normalize( float in[3], float out[3])
{
    float len = sqrt(dot(in, in));
    if (len == 0)
        return;
    out[0] = in[0] / len;
    out[1] = in[1] / len;
    out[2] = in[2] / len;
}

 void cross( float a[3], float b[3], float out[3])
{
    out[0] = a[1]*b[2] - a[2]*b[1];
    out[1] = a[2]*b[0] - a[0]*b[2];
    out[2] = a[0]*b[1] - a[1]*b[0];
}
