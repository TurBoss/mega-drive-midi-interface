#pragma once
#include <types.h>

void psg_noteOff(u8 channel);
void psg_noteOn(u8 channel, u16 freq);
void psg_attenuation(u8 channel, u8 attenuation);