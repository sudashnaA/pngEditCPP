#include "utils.h"
#include <algorithm>

HSV rgbToHsv(int r, int g, int b) 
{
    float r_f = r / 255.0f;
    float g_f = g / 255.0f;
    float b_f = b / 255.0f;

    float max = std::max({ r_f, g_f, b_f });
    float min = std::min({ r_f, g_f, b_f });
    float delta = max - min;

    HSV hsv;
    hsv.v = max;

    if (max == 0.0f) {
        hsv.s = 0.0f;
        hsv.h = 0.0f;  // Undefined hue
    }
    else {
        hsv.s = delta / max;

        if (delta == 0.0f) {
            hsv.h = 0.0f;
        }
        else if (max == r_f) {
            hsv.h = 60.0f * (fmod(((g_f - b_f) / delta), 6.0f));
        }
        else if (max == g_f) {
            hsv.h = 60.0f * (((b_f - r_f) / delta) + 2.0f);
        }
        else {
            hsv.h = 60.0f * (((r_f - g_f) / delta) + 4.0f);
        }

        if (hsv.h < 0.0f)
            hsv.h += 360.0f;
    }

    return hsv;
}