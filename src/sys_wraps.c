
#include "sys_wraps.h"
#include <stdbool.h>

static bool preventDisablingOfInts = false;

#ifndef UNIT_TESTS
extern void __real_SYS_disableInts(void);
extern void __real_SYS_enableInts(void);

void __wrap_SYS_disableInts(void)
{
    if (preventDisablingOfInts) {
        return;
    }
    __real_SYS_disableInts();
}

void __wrap_SYS_enableInts(void)
{
    if (preventDisablingOfInts) {
        return;
    }
    __real_SYS_enableInts();
}
#endif

void sys_wraps_preventDisablingOfInts(void)
{
    preventDisablingOfInts = true;
}