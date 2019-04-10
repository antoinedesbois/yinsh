
#include <algorithm>
#include <array>
#include <assert.h>
#include <chrono>
#include <cmath>
#include <iostream>
#include <random>

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

namespace
{
  const int num_ring = 5;
  std::array<int, 85> rand_num = {
      1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17,
      18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34,
      35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
      52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68,
      69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85};

  // for each position, put every reachable position, every vector represents a
  // line of movement
  std::array<std::vector<std::vector<short>>, 85> possibleMoves = {
      // 0
      std::vector<std::vector<short>>{{1, 2, 3},
                                      {5, 12, 20, 29, 38, 47},
                                      {6, 14, 23, 33, 43, 53, 63, 72, 80}},
      std::vector<std::vector<short>>{{0},
                                      {2, 3},
                                      {6, 13, 21, 30, 39, 48, 57},
                                      {7, 15, 24, 34, 44, 54, 64, 73}},
      std::vector<std::vector<short>>{{1, 0},
                                      {3},
                                      {7, 14, 22, 31, 40, 49, 58, 66},
                                      {8, 16, 25, 35, 45, 55, 66}},
      std::vector<std::vector<short>>{{2, 1, 0},
                                      {8, 15, 23, 32, 41, 50, 59, 67, 74},
                                      {9, 17, 26, 36, 46, 56}},
      std::vector<std::vector<short>>{{11, 19, 28},
                                      {12, 21, 31, 41, 51, 61, 70, 78, 84},
                                      {5, 6, 7, 8, 9, 10}},
      // 5
      std::vector<std::vector<short>>{{5, 4},
                                      {0},
                                      {1},
                                      {7, 8, 9, 10},
                                      {13, 21, 30, 39, 48, 57},
                                      {14, 23, 33, 43, 53, 63, 72, 80}},
      std::vector<std::vector<short>>{{6, 5, 4},
                                      {1},
                                      {2},
                                      {8, 9, 10},
                                      {14, 22, 31, 40, 49, 58, 66},
                                      {15, 24, 34, 44, 54, 64, 73}},
      std::vector<std::vector<short>>{{2},
                                      {3},
                                      {7, 6, 5, 4},
                                      {9, 10},
                                      {15, 23, 32, 41, 50, 59, 67, 74},
                                      {16, 25, 35, 45, 55, 65}},
      std::vector<std::vector<short>>{
          {3},
          {8, 7, 6, 5, 4},
          {10},
          {16, 24, 33, 42, 51, 60, 68, 75},
          {17, 26, 36, 46, 56}},
      std::vector<std::vector<short>>{{9, 8, 7, 6, 5, 4},
                                      {18, 27, 37},
                                      {17, 25, 34, 43, 52, 61, 39, 76, 81}},
      // 10
      std::vector<std::vector<short>>{{4},
                                      {19, 28},
                                      {20, 30, 40, 50, 60, 69, 77, 83},
                                      {12, 13, 14, 15, 16, 17, 18}},
      std::vector<std::vector<short>>{{4},
                                      {11},
                                      {20, 29, 38, 47},
                                      {0, 5},
                                      {13, 14, 15, 16, 17, 18},
                                      {21, 31, 41, 51, 61, 70, 78, 84}},
      std::vector<std::vector<short>>{{11, 12},
                                      {5},
                                      {21, 30, 39, 48, 57},
                                      {22, 32, 42, 52, 62, 71, 79},
                                      {}},
      std::vector<std::vector<short>>{{13, 12, 11},
                                      {6, 0},
                                      {7, 2},
                                      {22, 31, 40, 49, 58, 66},
                                      {15, 16, 17, 18},
                                      {23, 33, 43, 53, 63, 72, 80}},
      std::vector<std::vector<short>>{{7, 1},
                                      {14, 13, 12, 11},
                                      {23, 32, 41, 50, 59, 67, 74},
                                      {24, 34, 44, 54, 64, 73},
                                      {16, 17, 18},
                                      {8, 3}},
      // 15
      std::vector<std::vector<short>>{{8, 2},
                                      {15, 14, 13, 12, 11},
                                      {24, 33, 42, 51, 60, 68, 75},
                                      {25, 35, 45, 55, 65},
                                      {17, 18},
                                      {9}},
      std::vector<std::vector<short>>{{16, 15, 14, 13, 12, 11},
                                      {9, 3},
                                      {25, 34, 43, 52, 61, 69, 75, 81},
                                      {26, 36, 46, 56},
                                      {18},
                                      {10}},
      std::vector<std::vector<short>>{{10},
                                      {17, 16, 15, 14, 13, 12, 11},
                                      {26, 35, 44, 53, 62, 70, 77, 82},
                                      {27, 37}},
      std::vector<std::vector<short>>{{11, 4},
                                      {28},
                                      {20, 21, 22, 23, 24, 25, 26, 27},
                                      {29, 39, 49, 59, 68, 76, 82}},
      std::vector<std::vector<short>>{{19},
                                      {11},
                                      {29, 38, 47},
                                      {21, 22, 23, 24, 25, 26, 27},
                                      {30, 40, 50, 60, 69, 77, 83},
                                      {22, 5, 0}},
      // 20
      std::vector<std::vector<short>>{{20, 19},
                                      {12, 4},
                                      {30, 39, 48, 57},
                                      {13, 6, 1},
                                      {31, 41, 51, 61, 70, 78, 84},
                                      {22, 23, 24, 25, 26, 27}},
      std::vector<std::vector<short>>{{21, 20, 19},
                                      {31, 40, 49, 58, 66},
                                      {23, 24, 25, 26, 27},
                                      {13, 5},
                                      {14, 7, 2},
                                      {32, 42, 52, 62, 71, 79}},
      std::vector<std::vector<short>>{{22, 21, 20, 19},
                                      {14, 6, 0},
                                      {32, 41, 50, 59, 67, 74},
                                      {33, 43, 53, 63, 72, 80},
                                      {24, 25, 26, 27},
                                      {15, 8, 3}},
      std::vector<std::vector<short>>{{23, 22, 21, 20, 19},
                                      {25, 26, 27},
                                      {15, 7, 1},
                                      {34, 44, 54, 64, 73},
                                      {16, 9},
                                      {33, 42, 51, 60, 68, 75}},
      std::vector<std::vector<short>>{{24, 23, 22, 21, 20, 19},
                                      {26, 27},
                                      {16, 8, 2},
                                      {17, 10},
                                      {34, 43, 52, 61, 69, 76, 81},
                                      {35, 45, 55, 65}},
      // 25
      std::vector<std::vector<short>>{{27},
                                      {25, 24, 23, 22, 21, 20, 19},
                                      {17, 9, 3},
                                      {36, 46, 56},
                                      {35, 44, 53, 62, 70, 77, 82},
                                      {18}},
      std::vector<std::vector<short>>{{18, 10},
                                      {37},
                                      {26, 25, 24, 23, 22, 21, 20, 19},
                                      {36, 45, 54, 63, 71, 78, 83}},
      std::vector<std::vector<short>>{{19, 11, 4},
                                      {29, 30, 31, 32, 33, 34, 35, 36, 37},
                                      {38, 48, 58, 67, 75, 81}},
      std::vector<std::vector<short>>{{28},
                                      {19},
                                      {38, 47},
                                      {20, 12, 5, 0},
                                      {30, 31, 32, 33, 34, 35, 36, 37},
                                      {39, 49, 59, 68, 76, 82}},
      std::vector<std::vector<short>>{{29, 28},
                                      {20, 11},
                                      {39, 48, 57},
                                      {21, 13, 6, 1},
                                      {31, 32, 33, 34, 35, 36, 37},
                                      {40, 50, 60, 69, 77, 83}},
      // 30
      std::vector<std::vector<short>>{{30, 29, 28},
                                      {20, 11},
                                      {39, 48, 57},
                                      {22, 14, 7, 2},
                                      {32, 33, 34, 35, 36, 37},
                                      {41, 51, 61, 70, 78, 84}},
      std::vector<std::vector<short>>{{31, 30, 29, 28},
                                      {22, 13, 5},
                                      {41, 50, 59, 67, 74},
                                      {33, 34, 35, 36, 37},
                                      {23, 15, 8, 3},
                                      {42, 52, 62, 71, 79}},
      std::vector<std::vector<short>>{{32, 31, 30, 29, 28},
                                      {23, 14, 6, 0},
                                      {42, 51, 60, 68, 75},
                                      {24, 16, 9},
                                      {34, 35, 36, 37},
                                      {43, 53, 63, 72, 80}},
      std::vector<std::vector<short>>{{33, 32, 31, 30, 29, 28},
                                      {24, 15, 7, 1},
                                      {43, 52, 61, 69, 76, 81},
                                      {35, 36, 37},
                                      {44, 54, 64, 73},
                                      {25, 17, 10}},
      std::vector<std::vector<short>>{{34, 33, 32, 31, 30, 29, 28},
                                      {25, 16, 8, 2},
                                      {44, 53, 62, 70, 77, 82},
                                      {36, 37},
                                      {45, 55, 65},
                                      {26, 18}},
      // 35
      std::vector<std::vector<short>>{{37},
                                      {27},
                                      {46, 56},
                                      {35, 34, 33, 32, 31, 30, 29, 28},
                                      {26, 17, 9, 3},
                                      {45, 54, 63, 71, 78, 83}},
      std::vector<std::vector<short>>{{27, 18, 10},
                                      {36, 35, 34, 33, 32, 31, 30, 29, 28},
                                      {46, 55, 64, 72, 79, 84}},
      std::vector<std::vector<short>>{{28},
                                      {47},
                                      {29, 20, 12, 5, 0},
                                      {48, 58, 67, 75, 81},
                                      {39, 40, 41, 42, 43, 44, 45, 46}},
      std::vector<std::vector<short>>{{29, 19},
                                      {48, 57},
                                      {38},
                                      {40, 41, 42, 43, 44, 45, 46},
                                      {49, 59, 68, 76, 82},
                                      {30, 32, 13, 6, 1}},
      std::vector<std::vector<short>>{{39, 38},
                                      {30, 20, 11},
                                      {49, 58, 66},
                                      {50, 60, 69, 77, 83},
                                      {31, 22, 14, 7, 2},
                                      {41, 42, 43, 44, 45, 46}},
      // 40
      std::vector<std::vector<short>>{{40, 39, 38},
                                      {31, 21, 12, 4},
                                      {50, 59, 67, 74},
                                      {42, 43, 44, 45, 46},
                                      {32, 23, 15, 8, 3},
                                      {51, 61, 70, 78, 84}},
      std::vector<std::vector<short>>{{41, 40, 39, 38},
                                      {43, 44, 45, 46},
                                      {32, 22, 13, 5},
                                      {51, 60, 68, 75},
                                      {52, 62, 71, 79},
                                      {33, 24, 16, 9}},
      std::vector<std::vector<short>>{{42, 41, 40, 39, 38},
                                      {44, 45, 46},
                                      {33, 23, 14, 6, 0},
                                      {52, 61, 69, 76, 81},
                                      {34, 25, 17, 10},
                                      {53, 63, 72, 80}},
      std::vector<std::vector<short>>{{43, 42, 41, 40, 39, 38},
                                      {34, 24, 15, 7, 1},
                                      {53, 62, 70, 77, 82},
                                      {45, 46},
                                      {54, 64, 73},
                                      {35, 26, 18}},
      std::vector<std::vector<short>>{{44, 43, 42, 41, 40, 39, 38},
                                      {46},
                                      {36, 17},
                                      {55, 65},
                                      {54, 63, 71, 78, 83},
                                      {35, 25, 16, 8, 2}},
      // 45
      std::vector<std::vector<short>>{{45, 44, 43, 42, 41, 40, 39, 38},
                                      {56},
                                      {37},
                                      {55, 64, 72, 79, 84},
                                      {36, 26, 17, 9, 3}},
      std::vector<std::vector<short>>{{38, 29, 20, 12, 5, 0},
                                      {57, 66, 74},
                                      {48, 49, 50, 51, 52, 53, 54, 55, 56}},
      std::vector<std::vector<short>>{{47},
                                      {57},
                                      {38, 28},
                                      {58, 67, 75, 81},
                                      {39, 30, 21, 13, 6, 1},
                                      {49, 50, 51, 52, 53, 54, 55, 56}},
      std::vector<std::vector<short>>{{48, 47},
                                      {50, 51, 52, 53, 54, 55, 56},
                                      {58, 66},
                                      {59, 68, 76, 82},
                                      {39, 29, 19},
                                      {40, 31, 22, 14, 7, 2}},
      std::vector<std::vector<short>>{{49, 48, 47},
                                      {51, 52, 53, 54, 55, 56},
                                      {59, 67, 74},
                                      {60, 69, 77, 83},
                                      {40, 30, 20, 11},
                                      {41, 32, 23, 15, 8, 3}},
      // 50
      std::vector<std::vector<short>>{{50, 49, 48, 47},
                                      {52, 53, 54, 55, 56},
                                      {60, 68, 75},
                                      {61, 70, 78, 84},
                                      {41, 31, 21, 12, 7},
                                      {42, 33, 24, 16, 9}},
      std::vector<std::vector<short>>{{51, 50, 49, 48, 47},
                                      {53, 54, 55, 56},
                                      {61, 69, 76, 81},
                                      {62, 71, 79},
                                      {42, 32, 22, 13, 5},
                                      {43, 34, 25, 17, 10}},
      std::vector<std::vector<short>>{{52, 51, 50, 49, 48, 47},
                                      {54, 55, 56},
                                      {62, 70, 77, 82},
                                      {63, 72, 80},
                                      {43, 33, 23, 14, 6, 0},
                                      {44, 35, 26, 18}},
      std::vector<std::vector<short>>{{53, 52, 51, 50, 49, 48, 47},
                                      {55, 56},
                                      {63, 71, 78, 83},
                                      {64, 73},
                                      {44, 34, 24, 15, 7, 1},
                                      {45, 36, 27}},
      std::vector<std::vector<short>>{{54, 53, 52, 51, 50, 49, 48, 47},
                                      {56},
                                      {65},
                                      {45, 35, 25, 16, 8, 2},
                                      {46, 37},
                                      {64, 72, 79, 84}},
      // 55
      std::vector<std::vector<short>>{{55, 54, 53, 52, 51, 50, 49, 48, 47},
                                      {65, 73, 80},
                                      {46, 36, 26, 17, 9, 3}},
      std::vector<std::vector<short>>{{47},
                                      {66, 74},
                                      {48, 39, 30, 21, 13, 6, 1},
                                      {58, 59, 60, 61, 62, 63, 64, 65}},
      std::vector<std::vector<short>>{{57},
                                      {66},
                                      {67, 75, 81},
                                      {59, 60, 61, 62, 63, 64, 65},
                                      {49, 40, 31, 22, 14, 7, 2},
                                      {48, 38, 28}},
      std::vector<std::vector<short>>{{58, 57},
                                      {67, 74},
                                      {68, 76, 82},
                                      {60, 61, 62, 63, 64, 65},
                                      {50, 41, 32, 23, 15, 8, 3},
                                      {49, 39, 29, 19}},
      std::vector<std::vector<short>>{{59, 58, 57},
                                      {68, 75},
                                      {69, 77, 83},
                                      {61, 62, 63, 64, 65},
                                      {51, 42, 33, 24, 16, 9},
                                      {50, 40, 30, 20, 11}},
      // 60
      std::vector<std::vector<short>>{{60, 59, 58, 57},
                                      {69, 76, 81},
                                      {70, 78, 84},
                                      {62, 63, 64, 65},
                                      {51, 41, 31, 21, 12, 4},
                                      {52, 43, 34, 25, 17, 10}},
      std::vector<std::vector<short>>{{61, 60, 59, 58, 57},
                                      {70, 77, 82},
                                      {71, 79},
                                      {63, 64, 65},
                                      {53, 44, 35, 26, 18},
                                      {52, 42, 32, 22, 13, 5}},
      std::vector<std::vector<short>>{{62, 61, 60, 59, 58, 57},
                                      {71, 78, 83},
                                      {64, 65},
                                      {54, 45, 36, 27},
                                      {72, 80},
                                      {53, 43, 33, 23, 14, 6, 0}},
      std::vector<std::vector<short>>{{63, 62, 61, 60, 59, 58, 57},
                                      {72, 79, 84},
                                      {65},
                                      {55, 46, 37},
                                      {73},
                                      {54, 44, 34, 24, 15, 7, 1}},
      std::vector<std::vector<short>>{{64, 63, 62, 61, 60, 59, 58, 57},
                                      {73, 80},
                                      {56},
                                      {55, 45, 35, 25, 16, 8, 2}},
      // 65
      std::vector<std::vector<short>>{{74},
                                      {67, 68, 69, 70, 71, 72, 73},
                                      {58, 49, 40, 31, 22, 14, 7, 2},
                                      {57, 47}},
      std::vector<std::vector<short>>{{66},
                                      {74},
                                      {75, 81},
                                      {68, 69, 70, 71, 72, 73},
                                      {59, 50, 41, 32, 23, 15, 8, 3},
                                      {58, 48, 38, 28}},
      std::vector<std::vector<short>>{{67, 66},
                                      {75},
                                      {76, 82},
                                      {69, 70, 71, 72, 73},
                                      {60, 51, 42, 33, 24, 16, 9},
                                      {59, 49, 39, 29, 19}},
      std::vector<std::vector<short>>{{68, 67, 66},
                                      {76, 81},
                                      {77, 83},
                                      {70, 71, 72, 73},
                                      {61, 52, 43, 34, 25, 17, 10},
                                      {60, 50, 40, 30, 20, 11}},
      std::vector<std::vector<short>>{
          {69, 68, 67, 66},
          {77, 82},
          {78, 84},
          {71, 72, 73},
          {62, 53, 44, 35, 26, 18},
          {61, 51, 41, 31, 21, 12, 4}},
      // 70
      std::vector<std::vector<short>>{{70, 69, 68, 67, 66},
                                      {72, 73},
                                      {78, 83},
                                      {79},
                                      {63, 54, 45, 36, 27},
                                      {62, 52, 42, 32, 22, 13, 5}},
      std::vector<std::vector<short>>{{71, 70, 69, 68, 67, 66},
                                      {73},
                                      {79, 84},
                                      {80},
                                      {64, 55, 46, 37},
                                      {63, 53, 43, 33, 23, 14, 6, 0}},
      std::vector<std::vector<short>>{{72, 71, 70, 69, 68, 67, 66},
                                      {80},
                                      {65, 56},
                                      {64, 54, 44, 34, 24, 15, 7, 1}},
      std::vector<std::vector<short>>{{75, 76, 77, 78, 79, 80},
                                      {67, 59, 50, 41, 32, 23, 15, 8, 3},
                                      {66, 57, 47}},
      std::vector<std::vector<short>>{{74},
                                      {75, 76, 77, 78, 79, 80},
                                      {81},
                                      {68, 60, 51, 42, 33, 24, 16, 9},
                                      {67, 58, 58, 38, 28}},
      // 75
      std::vector<std::vector<short>>{{75, 74},
                                      {81},
                                      {82},
                                      {77, 78, 79, 80},
                                      {69, 61, 52, 43, 34, 25, 17, 10},
                                      {68, 59, 49, 39, 29, 19}},
      std::vector<std::vector<short>>{
          {76, 75, 74},
          {78, 79, 80},
          {82},
          {83},
          {70, 62, 53, 44, 35, 26, 18},
          {69, 60, 50, 40, 30, 20, 11}},
      std::vector<std::vector<short>>{
          {77, 76, 75, 74},
          {79, 80},
          {83},
          {84},
          {71, 63, 54, 45, 36, 27},
          {70, 61, 51, 41, 31, 21, 12, 4}},
      std::vector<std::vector<short>>{
          {78, 77, 76, 75, 74},
          {80},
          {84},
          {72, 64, 55, 46, 37},
          {71, 62, 52, 42, 32, 22, 13, 5}},
      std::vector<std::vector<short>>{{79, 78, 77, 76, 75, 74},
                                      {73, 65, 56},
                                      {72, 63, 53, 43, 33, 23, 14, 6, 0}},
      // 80
      std::vector<std::vector<short>>{{82, 83, 84},
                                      {76, 69, 61, 52, 43, 34, 25, 17, 10},
                                      {75, 67, 58, 48, 38, 28}},
      std::vector<std::vector<short>>{{81},
                                      {83, 84},
                                      {77, 70, 62, 53, 44, 35, 26, 18},
                                      {76, 68, 59, 49, 39, 29, 19}},
      std::vector<std::vector<short>>{{82, 81},
                                      {84},
                                      {78, 71, 63, 54, 45, 36, 27},
                                      {77, 69, 60, 50, 40, 30, 20, 11}},
      std::vector<std::vector<short>>{{83, 82, 81},
                                      {79, 72, 64, 55, 46, 37},
                                      {78, 70, 61, 51, 41, 31, 21, 12, 4}}};

}  // namespace

enum class Color : char
{
  black,
  white
};

enum class Mask : char
{
  first_ring = 0x01,          // 0000 0001
  first_puck = 0x02,          // 0000 0010
  first_white_color = 0x04,   // 0000 0100
  second_ring = 0x10,         // 0001 0000
  second_puck = 0x20,         // 0010 0000
  second_white_color = 0x40,  // 0100 0000
};

struct Board
{
  constexpr static int num_pos = 85;
  bool hasRing( const int pos ) const
  {
    assert( pos >= 0 && pos < num_pos * 2 );
    const int idx = std::floor( pos / 2 );
    const bool isFirstHalf = pos % 2 == 0;

    return isFirstHalf ? m_board[idx] & static_cast<char>( Mask::first_ring )
                       : m_board[idx] & static_cast<char>( Mask::second_ring );
  }

  void setRing( const int pos )
  {
    assert( pos >= 0 && pos < num_pos * 2 );
    const int idx = std::floor( pos / 2 );
    const bool isFirstHalf = pos % 2 == 0;

    if( isFirstHalf )
    {
      m_board[idx] = m_board[idx] |= static_cast<char>( Mask::first_ring );
    }
    else
    {
      m_board[idx] = m_board[idx] |= static_cast<char>( Mask::second_ring );
    }
  }

  void removeRing( const int pos )
  {
    assert( hasRing( pos ) );

    const int idx = std::floor( pos / 2 );
    const bool isFirstHalf = pos % 2 == 0;

    if( isFirstHalf )
    {
      m_board[idx] = m_board[idx] &= static_cast<char>( ~( 0x01 ) );
    }
    else
    {
      m_board[idx] = m_board[idx] &= static_cast<char>( ~( 0x10 ) );
    }
  }

  bool hasPuck( const int pos ) const
  {
    assert( pos >= 0 && pos < num_pos * 2 );
    const int idx = std::floor( pos / 2 );
    const bool isFirstHalf = pos % 2 == 0;

    return isFirstHalf ? m_board[idx] & static_cast<char>( Mask::first_puck )
                       : m_board[idx] & static_cast<char>( Mask::second_puck );
  }

  bool hasPuck( const int pos, Color color ) const
  {
    assert( pos >= 0 && pos < num_pos * 2 );
    const int idx = std::floor( pos / 2 );
    const bool isFirstHalf = pos % 2 == 0;

    return ( ( m_board[idx] & static_cast<char>( Mask::first_white_color ) &&
                               color == Color::white ) ||
             ( !( m_board[idx] &
                  static_cast<char>( Mask::first_white_color ) ) &&
               color == Color::black ) ) &&
           ( isFirstHalf
                 ? m_board[idx] & static_cast<char>( Mask::first_puck )
                 : m_board[idx] & static_cast<char>( Mask::second_puck ) );
  }

  void setPuck( const int pos )
  {
    assert( pos >= 0 && pos < num_pos * 2 );
    const int idx = std::floor( pos / 2 );
    const bool isFirstHalf = pos % 2 == 0;

    if( isFirstHalf )
    {
      m_board[idx] |= static_cast<char>( Mask::first_puck );
    }
    else
    {
      m_board[idx] |= static_cast<char>( Mask::second_puck );
    }
  }

  Color getColor( const int pos ) const
  {
    assert( pos >= 0 && pos < num_pos * 2 );
    const int idx = std::floor( pos / 2 );
    const bool isFirstHalf = pos % 2 == 0;

    if( isFirstHalf )
    {
      return ( m_board[idx] & static_cast<char>( Mask::first_white_color ) )
                 ? Color::white
                 : Color::black;
    }
    return ( m_board[idx] & static_cast<char>( Mask::second_white_color ) )
               ? Color::white
               : Color::black;
  }

  // char contains 2 pos
  // Bit: 1 -> ring, 2 -> puck, 3 -> color, 4 -> nothing
  std::array<char, num_pos / 2> m_board{
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
};

