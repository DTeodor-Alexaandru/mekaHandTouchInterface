#include "lpf.h"
#include <math.h>

void lpf2_init(lpf2_t* f, float fs, float fc)
{
    // compute first‑order α = RC/(RC+dt)
    float dt = 1.0f / fs;
    float RC = 1.0f / (2.0f * M_PI * fc);
    f->alpha = RC / (RC + dt);

    // zero both stages
    for (int i = 0; i < DAQ_TOTAL_SENSORS; i++) {
        f->z1[i] = 0.0f;
        f->z2[i] = 0.0f;
    }
}

void lpf2_apply(lpf2_t* f,
                const uint32_t raw[],
                float          out[])
{
    float a = f->alpha;
    float b = 1.0f - a;

    for (int i = 0; i < DAQ_TOTAL_SENSORS; i++) {
        // first pole
        float x1 = (float)raw[i];
        float y1 = a * f->z1[i] + b * x1;
        f->z1[i] = y1;

        // second pole
        float y2 = a * f->z2[i] + b * y1;
        f->z2[i] = y2;

        out[i] = y2;
    }
}
