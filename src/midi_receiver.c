#include "midi_receiver.h"
#include "comm.h"
#include "midi.h"
#include "scheduler.h"
#include "synth.h"
#include <string.h>

#define STATUS_LOWER(status) (status & 0x0F)
#define STATUS_UPPER(status) (status >> 4)

#define EVENT_PITCH_BEND 0xE
#define EVENT_NOTE_ON 0x9
#define EVENT_NODE_OFF 0x8
#define EVENT_CC 0xB
#define EVENT_PROGRAM 0xC
#define EVENT_SYSTEM 0xF

#define SYSTEM_CLOCK 0x8
#define SYSTEM_START 0xA
#define SYSTEM_STOP 0xC
#define SYSTEM_CONTINUE 0xB
#define SYSTEM_SONG_POSITION 0x2
#define SYSTEM_SYSEX 0x0

static u8 lastUnknownStatus = 0;

static void noteOn(u8 status);
static void noteOff(u8 status);
static void controlChange(u8 status);
static void pitchBend(u8 status);
static void systemMessage(u8 status);
static void setUnknownStatus(u8 status);
static void program(u8 status);
static u16 read14bitValue(void);
static void readSysEx(void);

void midi_receiver_init(void)
{
    lastUnknownStatus = 0;
}

void midi_receiver_perpectual_read(void)
{
    while (TRUE) {
        while (comm_readReady()) {
            midi_receiver_read();
        }
        scheduler_doEvents();
    }
}

void midi_receiver_read(void)
{
    u8 status = comm_read();
    u8 event = STATUS_UPPER(status);
    switch (event) {
    case EVENT_NOTE_ON:
        noteOn(status);
        break;
    case EVENT_NODE_OFF:
        noteOff(status);
        break;
    case EVENT_CC:
        controlChange(status);
        break;
    case EVENT_PITCH_BEND:
        pitchBend(status);
        break;
    case EVENT_PROGRAM:
        program(status);
        break;
    case EVENT_SYSTEM:
        systemMessage(status);
        break;
    default:
        setUnknownStatus(status);
        break;
    }
}

u8 midi_receiver_lastUnknownStatus(void)
{
    return lastUnknownStatus;
}

static void setUnknownStatus(u8 status)
{
    lastUnknownStatus = status;
}

static void controlChange(u8 status)
{
    u8 chan = STATUS_LOWER(status);
    u8 controller = comm_read();
    u8 value = comm_read();
    midi_cc(chan, controller, value);
}

static void noteOn(u8 status)
{
    u8 chan = STATUS_LOWER(status);
    u8 pitch = comm_read();
    u8 velocity = comm_read();
    midi_noteOn(chan, pitch, velocity);
}

static void noteOff(u8 status)
{
    u8 chan = STATUS_LOWER(status);
    u8 pitch = comm_read();
    comm_read();
    midi_noteOff(chan, pitch);
}

static void pitchBend(u8 status)
{
    u8 chan = STATUS_LOWER(status);
    u16 bend = read14bitValue();
    midi_pitchBend(chan, bend);
}

static void program(u8 status)
{
    u8 chan = STATUS_LOWER(status);
    u8 program = comm_read();
    midi_program(chan, program);
}

static u16 read14bitValue(void)
{
    u16 lower = comm_read();
    u16 upper = comm_read();
    return (upper << 7) + lower;
}

static void systemMessage(u8 status)
{
    u8 type = STATUS_LOWER(status);
    switch (type) {
    case SYSTEM_SONG_POSITION:
        read14bitValue();
        break;
    case SYSTEM_CLOCK:
    case SYSTEM_START:
    case SYSTEM_CONTINUE:
    case SYSTEM_STOP:
        break;
    case SYSTEM_SYSEX:
        readSysEx();
        break;
    default:
        setUnknownStatus(status);
        break;
    }
}

static void readSysEx(void)
{
    const u16 BUFFER_LENGTH = 256;
    const u8 SYSEX_END = 0xF7;

    u8 buffer[BUFFER_LENGTH];
    u8 data;
    u8 index = 0;
    while ((data = comm_read()) != SYSEX_END) {
        buffer[index] = data;
        index++;
    }
    midi_sysex(buffer, index);
}
