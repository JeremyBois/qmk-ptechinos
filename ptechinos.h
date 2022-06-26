#pragma once

#include "quantum.h"

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
// clang-format off
#define LAYOUT(\
          L12, L13, L14, L15,             R15, R14, R13, R12,\
L11, L21, L22, L23, L24, L25,             R25, R24, R23, R22, R21, R11,\
     L31, L32, L33, L34, L35, L45,   R45, R35, R34, R33, R32, R31,\
               L42, L43, L44,             R44, R43, R42\
){\
    {L11, L12, L13, L14, L15 },\
    {L21, L22, L23, L24, L25 },\
    {L31, L32, L33, L34, L35 },\
    {KC_NO, L42, L43, L44, L45 },\
    {R11, R12, R13, R14, R15 },\
    {R21, R22, R23, R24, R25 },\
    {R31, R32, R33, R34, R35 },\
    {KC_NO, R42, R43, R44, R45 }\
}
// clang-format on
