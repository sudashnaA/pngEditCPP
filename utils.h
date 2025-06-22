#ifndef UTILS_H
#define UTILS_H

struct HSV
{
    float h;  // Hue [0, 360)
    float s;  // Saturation [0, 1]
    float v;  // Value [0, 1]
};

HSV rgbToHsv(int r, int g, int b);

#endif
