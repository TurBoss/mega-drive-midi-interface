#pragma once
#include "synth.h"

const Channel PRESET_DEFAULT = { .algorithm = 2,
    .feedback = 6,
    .stereo = 3,
    .ams = 0,
    .fms = 0,
    .octave = 0,
    .freqNumber = 0,
    .operators = { { .multiple = 1,
                       .detune = 7,
                       .attackRate = 31,
                       .rateScaling = 1,
                       .amplitudeModulation = 0,
                       .firstDecayRate = 5,
                       .releaseRate = 1,
                       .secondaryAmplitude = 1,
                       .secondaryDecayRate = 2,
                       .totalLevel = 0x23 },
        { .multiple = 13,
            .detune = 0,
            .attackRate = 25,
            .rateScaling = 2,
            .amplitudeModulation = 0,
            .firstDecayRate = 5,
            .releaseRate = 1,
            .secondaryAmplitude = 1,
            .secondaryDecayRate = 2,
            .totalLevel = 0x2D },
        { .multiple = 3,
            .detune = 2,
            .attackRate = 31,
            .rateScaling = 1,
            .amplitudeModulation = 0,
            .firstDecayRate = 5,
            .releaseRate = 1,
            .secondaryAmplitude = 1,
            .secondaryDecayRate = 2,
            .totalLevel = 0x26 },
        { .multiple = 1,
            .detune = 0,
            .attackRate = 25,
            .rateScaling = 2,
            .amplitudeModulation = 0,
            .firstDecayRate = 7,
            .releaseRate = 6,
            .secondaryAmplitude = 10,
            .secondaryDecayRate = 2,
            .totalLevel = 0 } } };

const Channel PRESET_DEEP_PAD = { 5, 0, 3, 0, 0, 0, 0,
    { { 1, 0, 20, 1, 6, 0, 2, 5, 9, 19 }, { 1, 3, 18, 0, 4, 0, 1, 3, 9, 19 },
        { 7, 5, 7, 2, 8, 0, 1, 10, 9, 19 },
        { 1, 3, 21, 1, 4, 0, 1, 6, 9, 19 } } };
