
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include "midi.h"
#include "psg_chip.h"
#include <cmocka.h>

extern void __real_psg_attenuation(u8 channel, u8 attenuation);
extern void __real_psg_noteOn(u8 channel, u16 freq);
extern void __real_psg_noteOff(u8 channel);

static void test_psg_chip_sets_note_on_psg(void** state)
{
    for (u8 chan = 0; chan < 3; chan++) {
        expect_value(__wrap_PSG_setFrequency, channel, chan);
        expect_value(__wrap_PSG_setFrequency, value, 440);
        expect_value(__wrap_PSG_setEnvelope, channel, chan);
        expect_value(__wrap_PSG_setEnvelope, value, 0);

        __real_psg_noteOn(chan, 440);
    }
}

static void test_psg_chip_sets_note_off_psg(void** state)
{
    for (u8 chan = 0; chan < 3; chan++) {
        expect_value(__wrap_PSG_setEnvelope, channel, chan);
        expect_value(__wrap_PSG_setEnvelope, value, 0xF);

        __real_psg_noteOff(chan);
    }
}

static void test_psg_chip_sets_attenuation(void** state)
{
    for (u8 chan = 0; chan < 3; chan++) {
        expect_value(__wrap_PSG_setEnvelope, channel, chan);
        expect_value(__wrap_PSG_setEnvelope, value, 2);

        __real_psg_attenuation(chan, 2);
    }
}
