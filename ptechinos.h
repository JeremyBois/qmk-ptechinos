#pragma once

#if defined(KEYBOARD_ptechinos_2040)
#    include "2040.h"
#elif defined(KEYBOARD_ptechinos_promicro)
#    include "promicro.h"
#else
#    error "Unsuported hardware"
#endif

#include "quantum.h"
