#pragma once

#include "quantum.h"

// ┌─────────────────────────────────────────────────┐
// │ Layouts                                         │
// └─────────────────────────────────────────────────┘
// clang-format off
// Layout for Ptechinos 0.6 (reversible and rp2040 based)
//     |S01|S05|S09|S13|S17|                  |S17|S13|S09|S05|S01|
// |S04|S02|S06|S10|S14|S18|                  |S18|S14|S10|S06|S02|S04|
//     |S03|S07|S11|S15|S19|S20|          |S20|S19|S15|S11|S07|S03|
//                     |S08|S12|S16|  |S16|S12|S08|
#define LAYOUT_v06(\
     L11, L12, L13, L14, L15,                       R15, R14, R13, R12, R11,\
L41, L21, L22, L23, L24, L25,                       R25, R24, R23, R22, R21, R41,\
     L31, L32, L33, L34, L35, L45,             R45, R35, R34, R33, R32, R31,\
                         L42, L43, L44,   R44, R43, R42\
){\
    {L11, L12, L13, L14, L15 },\
    {L21, L22, L23, L24, L25 },\
    {L31, L32, L33, L34, L35 },\
    {L41, L42, L43, L44, L45 },\
    {R11, R12, R13, R14, R15 },\
    {R21, R22, R23, R24, R25 },\
    {R31, R32, R33, R34, R35 },\
    {R41, R42, R43, R44, R45 }\
}

#define LAYOUT LAYOUT_v06
// clang-format on
