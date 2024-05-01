#pragma once

#include <array>

#include "pico/types.h"

constexpr uint C1  = 130;
constexpr uint Db1 = 138;
constexpr uint D1  = 146;
constexpr uint Eb1 = 155;
constexpr uint E1  = 164;
constexpr uint F1  = 174;
constexpr uint Gb1 = 185;
constexpr uint G1  = 196;
constexpr uint Ab1 = 207;
constexpr uint A1  = 220;
constexpr uint Bb1 = 233;
constexpr uint B1  = 246;
constexpr uint C2  = 261;
constexpr uint Db2 = 277;
constexpr uint D2  = 293;
constexpr uint Eb2 = 311;
constexpr uint E2  = 329;
constexpr uint F2  = 349;
constexpr uint Gb2 = 369;
constexpr uint G2  = 392;
constexpr uint Ab2 = 415;
constexpr uint A2  = 440;
constexpr uint Bb2 = 466;
constexpr uint B2  = 493;
constexpr uint C3  = 522;
constexpr uint Db3 = 553;
constexpr uint D3  = 586;
constexpr uint Eb3 = 621;
constexpr uint E3  = 658;
constexpr uint F3  = 697;
constexpr uint Gb3 = 738;
constexpr uint G3  = 782;
constexpr uint Ab3 = 829;
constexpr uint A3  = 879;
constexpr uint Bb3 = 931;
constexpr uint B3  = 986;

constexpr std::array allnotes {
    C1, Db1, D1, Eb1, E1, F1, Gb1, G1, Ab1, A1, Bb1, B1,
    C2, Db2, D2, Eb2, E2, F2, Gb2, G2, Ab2, A2, Bb2, B2,
    C3, Db3, D3, Eb3, E3, F3, Gb3, G3, Ab3, A3, Bb3, B3,
};
