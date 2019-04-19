
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
#include <cstring>

namespace Moves
{
  constexpr int max_moves = 26;
  constexpr int max_directions = 6;
  constexpr int max_array_size = max_moves + max_directions;

  std::array<std::array<int, max_array_size>, 85> possibleMoves = {
      // 0
      std::array<int, max_array_size>{
          3,  1,  2,  3,  6,  5,  12, 20, 29, 38, 47, 9,  6,  14, 23, 33,
          43, 53, 63, 72, 80, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      std::array<int, max_array_size>{1,  0,  2, 2, 3,  7,  6,  13, 21, 30, 39,
                                      48, 57, 8, 7, 15, 24, 34, 44, 54, 64, 73},
      std::array<int, max_array_size>{2,  1,  0,  1, 3, 8,  7,  14, 22, 31, 40,
                                      49, 58, 66, 7, 8, 16, 25, 35, 45, 55, 66},
      std::array<int, max_array_size>{3,  2,  1,  0, 9, 8,  15, 23, 32, 41, 50,
                                      59, 67, 74, 6, 9, 17, 26, 36, 46, 56},
      std::array<int, max_array_size>{3,  11, 19, 28, 9, 12, 21, 31, 41, 51, 61,
                                      70, 78, 84, 6,  5, 6,  7,  8,  9,  10},
      // 5
      std::array<int, max_array_size>{2,  5,  4,  1,  0,  1,  1,  4,  7,  8,
                                      9,  10, 6,  13, 21, 30, 39, 48, 57, 8,
                                      14, 23, 33, 43, 53, 63, 72, 80},
      std::array<int, max_array_size>{3, 6,  5,  4,  1,  1,  1,  2,  3,  8,
                                      9, 10, 7,  14, 22, 31, 40, 49, 58, 66,
                                      7, 15, 24, 34, 44, 54, 64, 73},
      std::array<int, max_array_size>{1,  2,  1,  3,  4,  7,  6,  5,  4,  2,
                                      9,  10, 8,  15, 23, 32, 41, 50, 59, 67,
                                      74, 6,  16, 25, 35, 45, 55, 65},
      std::array<int, max_array_size>{1,  3, 5,  8,  7,  6,  5,  4,  1,
                                      10, 8, 16, 24, 33, 42, 51, 60, 68,
                                      75, 5, 17, 26, 36, 46, 56},
      std::array<int, max_array_size>{6, 9,  8,  7,  6,  5,  4,  3,  18, 27, 37,
                                      9, 17, 25, 34, 43, 52, 61, 39, 76, 81},
      // 10
      std::array<int, max_array_size>{1,  4,  2,  19, 28, 8,  20, 30,
                                      40, 50, 60, 69, 77, 83, 7,  12,
                                      13, 14, 15, 16, 17, 18},
      std::array<int, max_array_size>{1,  4,  1,  11, 4,  20, 29, 38, 47, 2,
                                      0,  5,  6,  13, 14, 15, 16, 17, 18, 8,
                                      21, 31, 41, 51, 61, 70, 78, 84},
      std::array<int, max_array_size>{2,  12, 11, 1,  5,  2,  6,  1,  5,  21,
                                      30, 39, 48, 57, 7,  22, 32, 42, 52, 62,
                                      71, 79, 5,  14, 15, 16, 17, 18},
      std::array<int, max_array_size>{3,  13, 12, 11, 2,  6,  0,  2,  7,  2,
                                      6,  22, 31, 40, 49, 58, 66, 4,  15, 16,
                                      17, 18, 7,  23, 33, 43, 53, 63, 72, 80},
      std::array<int, max_array_size>{2,  7,  1,  4,  14, 13, 12, 11, 7,  23,
                                      32, 41, 50, 59, 67, 74, 6,  24, 34, 44,
                                      54, 64, 73, 3,  16, 17, 18, 2,  8,  3},
      // 15
      std::array<int, max_array_size>{2,  8,  2,  5,  15, 14, 13, 12, 11, 7,
                                      24, 33, 42, 51, 60, 68, 75, 5,  25, 35,
                                      45, 55, 65, 2,  17, 18, 1,  9},
      std::array<int, max_array_size>{6,  16, 15, 14, 13, 12, 11, 2,  9,  3,
                                      8,  25, 34, 43, 52, 61, 69, 75, 81, 4,
                                      26, 36, 46, 56, 1,  18, 1,  10},
      std::array<int, max_array_size>{1,  10, 7,  17, 16, 15, 14, 13,
                                      12, 11, 8,  26, 35, 44, 53, 62,
                                      70, 77, 82, 2,  27, 37},
      std::array<int, max_array_size>{2,  11, 4,  1,  28, 8,  20, 21,
                                      22, 23, 24, 25, 26, 27, 7,  29,
                                      39, 49, 59, 68, 76, 82},
      std::array<int, max_array_size>{1,  19, 1,  11, 3,  29, 38, 47, 7,  21,
                                      22, 23, 24, 25, 26, 27, 7,  30, 40, 50,
                                      60, 69, 77, 83, 3,  22, 5,  0},
      // 20
      std::array<int, max_array_size>{2,  20, 19, 2, 12, 4,  4,  30, 39, 48,
                                      57, 3,  13, 6, 1,  7,  31, 41, 51, 61,
                                      70, 78, 84, 6, 22, 23, 24, 25, 26, 27},
      std::array<int, max_array_size>{3,  21, 20, 19, 5,  31, 40, 49, 58, 66,
                                      5,  23, 24, 25, 26, 27, 2,  13, 5,  3,
                                      14, 7,  2,  6,  32, 42, 52, 62, 71, 79},
      std::array<int, max_array_size>{
          4, 22, 21, 20, 19, 3,  14, 6, 0,  6,  32, 41, 50, 59, 67, 74,
          6, 33, 43, 53, 63, 72, 80, 4, 24, 25, 26, 27, 3,  15, 8,  3},
      std::array<int, max_array_size>{5, 23, 22, 21, 20, 19, 3,  25, 26, 27,
                                      3, 15, 7,  1,  5,  34, 44, 54, 64, 73,
                                      2, 16, 9,  6,  33, 42, 51, 60, 68, 75},
      std::array<int, max_array_size>{6,  24, 23, 22, 21, 20, 19, 2,  26, 27,
                                      3,  16, 8,  2,  2,  17, 10, 7,  34, 43,
                                      52, 61, 69, 76, 81, 4,  35, 45, 55, 65},
      // 25
      std::array<int, max_array_size>{127, 725, 24, 23, 22, 21, 20, 19, 317,
                                      9,   3,   3,  36, 46, 56, 7,  35, 44,
                                      53,  62,  70, 77, 82, 1,  18},
      std::array<int, max_array_size>{2,  18, 10, 1,  37, 8,  26, 25,
                                      24, 23, 22, 21, 20, 19, 7,  36,
                                      45, 54, 63, 71, 78, 83},
      std::array<int, max_array_size>{3,  19, 11, 4, 9,  29, 30, 31, 32, 33, 34,
                                      35, 36, 37, 6, 38, 48, 58, 67, 75, 81},
      std::array<int, max_array_size>{1,  28, 1,  19, 2,  38, 47, 4,  20, 12,
                                      5,  0,  8,  30, 31, 32, 33, 34, 35, 36,
                                      37, 6,  39, 49, 59, 68, 76, 82},
      std::array<int, max_array_size>{2,  29, 28, 2, 20, 11, 3,  39, 48, 57,
                                      4,  21, 13, 6, 1,  7,  31, 32, 33, 34,
                                      35, 36, 37, 6, 40, 50, 60, 69, 77, 83},
      // 30
      std::array<int, max_array_size>{3,  30, 29, 28, 2,  20, 11, 3,  39, 48,
                                      57, 4,  22, 14, 7,  2,  6,  32, 33, 34,
                                      35, 36, 37, 6,  41, 51, 61, 70, 78, 84},
      std::array<int, max_array_size>{
          4,  31, 30, 29, 28, 3, 22, 13, 5, 5, 41, 50, 59, 67, 74, 5,
          33, 34, 35, 36, 37, 4, 23, 15, 8, 3, 5,  42, 52, 62, 71, 79},
      std::array<int, max_array_size>{5,  32, 31, 30, 29, 28, 4,  23, 14, 6, 0,
                                      5,  42, 51, 60, 68, 75, 3,  24, 16, 9, 4,
                                      34, 35, 36, 37, 5,  43, 53, 63, 72, 80},
      std::array<int, max_array_size>{
          6,  33, 32, 31, 30, 29, 28, 4, 24, 15, 7,  1,  6, 43, 52, 61,
          69, 76, 81, 3,  35, 36, 37, 4, 44, 54, 64, 73, 3, 25, 17, 10},
      std::array<int, max_array_size>{7,  34, 33, 32, 31, 30, 29, 28, 4,  25,
                                      16, 8,  2,  6,  44, 53, 62, 70, 77, 82,
                                      2,  36, 37, 3,  45, 55, 65, 2,  26, 18},
      // 35
      std::array<int, max_array_size>{1,  37, 1,  27, 2,  46, 56, 8,  35, 34,
                                      33, 32, 31, 30, 29, 28, 4,  26, 17, 9,
                                      3,  6,  45, 54, 63, 71, 78, 83},
      std::array<int, max_array_size>{3,  27, 18, 10, 9,  36, 35,
                                      34, 33, 32, 31, 30, 29, 28,
                                      6,  46, 55, 64, 72, 79, 84},
      std::array<int, max_array_size>{1,  28, 1,  47, 5,  29, 20, 12, 5,
                                      0,  5,  48, 58, 67, 75, 81, 8,  39,
                                      40, 41, 42, 43, 44, 45, 46},
      std::array<int, max_array_size>{2,  29, 19, 2,  48, 57, 1, 38, 7,  40,
                                      41, 42, 43, 44, 45, 46, 5, 49, 59, 68,
                                      76, 82, 5,  30, 32, 13, 6, 1},
      std::array<int, max_array_size>{2,  39, 38, 3,  30, 20, 11, 3,  49, 58,
                                      66, 5,  50, 60, 69, 77, 83, 5,  31, 22,
                                      14, 7,  2,  6,  41, 42, 43, 44, 45, 46},
      // 40
      std::array<int, max_array_size>{3,  40, 39, 38, 4,  31, 21, 12, 4,  4, 50,
                                      59, 67, 74, 5,  42, 43, 44, 45, 46, 5, 32,
                                      23, 15, 8,  3,  5,  51, 61, 70, 78, 84},
      std::array<int, max_array_size>{4, 41, 40, 39, 38, 4, 43, 44, 45, 46,
                                      4, 32, 22, 13, 5,  4, 51, 60, 68, 75,
                                      4, 52, 62, 71, 79, 4, 33, 24, 16, 9},
      std::array<int, max_array_size>{
          5, 42, 41, 40, 39, 38, 3, 44, 45, 46, 5,  33, 23, 14, 6,  0,
          5, 52, 61, 69, 76, 81, 4, 34, 25, 17, 10, 4,  53, 63, 72, 80},
      std::array<int, max_array_size>{6,  43, 42, 41, 40, 39, 38, 5,  34, 24,
                                      15, 7,  1,  5,  53, 62, 70, 77, 82, 2,
                                      45, 46, 3,  54, 64, 73, 3,  35, 26, 18},
      std::array<int, max_array_size>{7,  44, 43, 42, 41, 40, 39, 38, 1,  46,
                                      2,  36, 17, 2,  55, 65, 5,  54, 63, 71,
                                      78, 83, 5,  35, 25, 16, 8,  2},
      // 45
      std::array<int, max_array_size>{8,  45, 44, 43, 42, 41, 40, 39, 38,
                                      1,  56, 1,  37, 5,  55, 64, 72, 79,
                                      84, 5,  36, 26, 17, 9,  3},
      std::array<int, max_array_size>{6, 38, 29, 20, 12, 5,  0,  3,  57, 66, 74,
                                      9, 48, 49, 50, 51, 52, 53, 54, 55, 56},
      std::array<int, max_array_size>{1,  47, 1,  57, 2,  38, 28, 4, 58, 67,
                                      75, 81, 6,  39, 30, 21, 13, 6, 1,  8,
                                      49, 50, 51, 52, 53, 54, 55, 56},
      std::array<int, max_array_size>{2,  48, 47, 7,  50, 51, 52, 53, 54, 55,
                                      56, 2,  58, 66, 4,  59, 68, 76, 82, 3,
                                      39, 29, 19, 6,  40, 31, 22, 14, 7,  2},
      std::array<int, max_array_size>{
          3,  49, 48, 47, 6, 51, 52, 53, 54, 55, 56, 3,  59, 67, 74, 4,
          60, 69, 77, 83, 4, 40, 30, 20, 11, 6,  41, 32, 23, 15, 8,  3},
      // 50
      std::array<int, max_array_size>{
          4,  50, 49, 48, 47, 5,  52, 53, 54, 55, 56, 3,  60, 68, 75, 4,
          61, 70, 78, 84, 5,  41, 31, 21, 12, 7,  5,  42, 33, 24, 16, 9},
      std::array<int, max_array_size>{
          5, 51, 50, 49, 48, 47, 4,  53, 54, 55, 56, 4,  61, 69, 76, 81,
          3, 62, 71, 79, 5,  42, 32, 22, 13, 5,  5,  43, 34, 25, 17, 10},
      std::array<int, max_array_size>{
          6, 52, 51, 50, 49, 48, 47, 3,  54, 55, 56, 4, 62, 70, 77, 82,
          3, 63, 72, 80, 6,  43, 33, 23, 14, 6,  0,  4, 44, 35, 26, 18},
      std::array<int, max_array_size>{7,  53, 52, 51, 50, 49, 48, 47, 2,  55,
                                      56, 4,  63, 71, 78, 83, 2,  64, 73, 6,
                                      44, 34, 24, 15, 7,  1,  3,  45, 36, 27},
      std::array<int, max_array_size>{8,  54, 53, 52, 51, 50, 49, 48, 47, 1,
                                      56, 1,  65, 6,  45, 35, 25, 16, 8,  2,
                                      2,  46, 37, 4,  64, 72, 79, 84},
      // 55
      std::array<int, max_array_size>{9,  55, 54, 53, 52, 51, 50, 49, 48, 47, 3,
                                      65, 73, 80, 6,  46, 36, 26, 17, 9,  3},
      std::array<int, max_array_size>{1, 47, 2, 66, 74, 7,  48, 39, 30, 21, 13,
                                      6, 1,  8, 58, 59, 60, 61, 62, 63, 64, 65},
      std::array<int, max_array_size>{1,  57, 1,  66, 3,  67, 75, 81, 7,  59,
                                      60, 61, 62, 63, 64, 65, 7,  49, 40, 31,
                                      22, 14, 7,  2,  3,  48, 38, 28},
      std::array<int, max_array_size>{2,  58, 57, 2,  67, 74, 3,  68, 76, 82,
                                      6,  60, 61, 62, 63, 64, 65, 7,  50, 41,
                                      32, 23, 15, 8,  3,  4,  49, 39, 29, 19},
      std::array<int, max_array_size>{3,  59, 58, 57, 2,  68, 75, 3,  69, 77,
                                      83, 5,  61, 62, 63, 64, 65, 6,  51, 42,
                                      33, 24, 16, 9,  5,  50, 40, 30, 20, 11},
      // 60
      std::array<int, max_array_size>{
          4,  60, 59, 58, 57, 3,  69, 76, 81, 3, 70, 78, 84, 4,  62, 63,
          64, 65, 6,  51, 41, 31, 21, 12, 4,  6, 52, 43, 34, 25, 17, 10},
      std::array<int, max_array_size>{5,  61, 60, 59, 58, 57, 3,  70, 77, 82,
                                      2,  71, 79, 3,  63, 64, 65, 5,  53, 44,
                                      35, 26, 18, 6,  52, 42, 32, 22, 13, 5},
      std::array<int, max_array_size>{6,  62, 61, 60, 59, 58, 57, 3,  71, 78,
                                      83, 2,  64, 65, 4,  54, 45, 36, 27, 2,
                                      72, 80, 7,  53, 43, 33, 23, 14, 6,  0},
      std::array<int, max_array_size>{7,  63, 62, 61, 60, 59, 58, 57, 3, 72,
                                      79, 84, 1,  65, 3,  55, 46, 37, 1, 73,
                                      7,  54, 44, 34, 24, 15, 7,  1},
      std::array<int, max_array_size>{8,  64, 63, 62, 61, 60, 59, 58, 57, 2, 73,
                                      80, 1,  56, 7,  55, 45, 35, 25, 16, 8, 2},
      // 65
      std::array<int, max_array_size>{1,  74, 7, 67, 68, 69, 70, 71,
                                      72, 73, 8, 58, 49, 40, 31, 22,
                                      14, 7,  2, 2,  57, 47},
      std::array<int, max_array_size>{1,  66, 1,  74, 2,  75, 81, 6,  68, 69,
                                      70, 71, 72, 73, 8,  59, 50, 41, 32, 23,
                                      15, 8,  3,  4,  58, 48, 38, 28},
      std::array<int, max_array_size>{2,  67, 66, 1,  75, 2,  76, 82, 5,  69,
                                      70, 71, 72, 73, 7,  60, 51, 42, 33, 24,
                                      16, 9,  5,  59, 49, 39, 29, 19},
      std::array<int, max_array_size>{3,  68, 67, 66, 2,  76, 81, 2,  77, 83,
                                      4,  70, 71, 72, 73, 7,  61, 52, 43, 34,
                                      25, 17, 10, 6,  60, 50, 40, 30, 20, 11},
      std::array<int, max_array_size>{4,  69, 68, 67, 66, 2,  77, 82, 2,  78,
                                      84, 3,  71, 72, 73, 6,  62, 53, 44, 35,
                                      26, 18, 7,  61, 51, 41, 31, 21, 12, 4},
      // 70
      std::array<int, max_array_size>{5,  70, 69, 68, 67, 66, 2,  72, 73, 2,
                                      78, 83, 1,  79, 5,  63, 54, 45, 36, 27,
                                      7,  62, 52, 42, 32, 22, 13, 5},
      std::array<int, max_array_size>{6,  71, 70, 69, 68, 67, 66, 1,  73, 2,
                                      79, 84, 1,  80, 4,  64, 55, 46, 37, 8,
                                      63, 53, 43, 33, 23, 14, 6,  0},
      std::array<int, max_array_size>{7,  72, 71, 70, 69, 68, 67, 66,
                                      1,  80, 2,  65, 56, 8,  64, 54,
                                      44, 34, 24, 15, 7,  1},
      std::array<int, max_array_size>{6,  75, 76, 77, 78, 79, 80,
                                      9,  67, 59, 50, 41, 32, 23,
                                      15, 8,  3,  3,  66, 57, 47},
      std::array<int, max_array_size>{1,  74, 6, 75, 76, 77, 78, 79, 80,
                                      1,  81, 8, 68, 60, 51, 42, 33, 24,
                                      16, 9,  5, 67, 58, 58, 38, 28},
      // 75
      std::array<int, max_array_size>{2,  75, 74, 1,  81, 1,  82, 4,  77, 78,
                                      79, 80, 8,  69, 61, 52, 43, 34, 25, 17,
                                      10, 6,  68, 59, 49, 39, 29, 19},
      std::array<int, max_array_size>{3, 76, 75, 74, 3,  78, 79, 80, 1,  82,
                                      1, 83, 7,  70, 62, 53, 44, 35, 26, 18,
                                      7, 69, 60, 50, 40, 30, 20, 11},
      std::array<int, max_array_size>{4,  77, 76, 75, 74, 2,  79, 80, 1,  83,
                                      1,  84, 6,  71, 63, 54, 45, 36, 27, 8,
                                      70, 61, 51, 41, 31, 21, 12, 4},
      std::array<int, max_array_size>{5,  78, 77, 76, 75, 74, 1,  80, 1,
                                      84, 5,  72, 64, 55, 46, 37, 8,  71,
                                      62, 52, 42, 32, 22, 13, 5},
      std::array<int, max_array_size>{6, 79, 78, 77, 76, 75, 74, 3,  73, 65, 56,
                                      9, 72, 63, 53, 43, 33, 23, 14, 6,  0},
      // 80
      std::array<int, max_array_size>{3,  82, 83, 84, 9,  76, 69,
                                      61, 52, 43, 34, 25, 17, 10,
                                      6,  75, 67, 58, 48, 38, 28},
      std::array<int, max_array_size>{1,  81, 2,  83, 84, 8,  77, 70,
                                      62, 53, 44, 35, 26, 18, 7,  76,
                                      68, 59, 49, 39, 29, 19},
      std::array<int, max_array_size>{2,  82, 81, 1,  84, 7, 78, 71,
                                      63, 54, 45, 36, 27, 8, 77, 69,
                                      60, 50, 40, 30, 20, 11},
      std::array<int, max_array_size>{3, 83, 82, 81, 6,  79, 72, 64, 55, 46, 37,
                                      9, 78, 70, 61, 51, 41, 31, 21, 12, 4}};

}  // namespace Moves

namespace
{
  std::array<int, 85> rand_num = {
      1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17,
      18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34,
      35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
      52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68,
      69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85};

  constexpr int num_ring = 5;
  constexpr int32_t constexprCeil( float num )
  {
    return ( static_cast<float>( static_cast<int32_t>( num ) ) == num )
               ? static_cast<int32_t>( num )
               : static_cast<int32_t>( num ) + ( ( num > 0 ) ? 1 : 0 );
  }
}  // namespace

enum class Color : char
{
  black,
  white
};

// 1st bit -> ring
// 2nd bit -> puck
// 3nd bit -> white = 1
enum class Mask : char
{
  empty = 0x0,

  first_ring = 0x01,                                  // 0000 0001
  first_puck = 0x02,                                  // 0000 0010
  first_white_color = 0x04,                           // 0000 0100
  first_white_ring = first_ring | first_white_color,  // 0000 0101
  first_white_puck = first_puck | first_white_color,  // 0000 0110

  second_ring = 0x10,                                    // 0001 0000
  second_puck = 0x20,                                    // 0010 0000
  second_white_color = 0x40,                             // 0100 0000
  second_white_ring = second_ring | second_white_color,  // 0000 0101
  second_white_puck = second_puck | second_white_color,  // 0000 0110

};

struct Board
{
  constexpr static int num_pos = 85;
  Board()
      : m_board{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0}
  {
  }

  char operator[]( const int i ) const
  {
    return m_board[i / 2];
  }

  bool operator==( const Board& other )
  {
    return !memcmp( &m_board, &other.m_board, std::ceil( num_pos / 2.0 ) );
  }

  bool hasRing( const int pos ) const
  {
    assert( pos >= 0 && pos < num_pos * 2 );
    const int idx = std::floor( pos / 2 );
    const bool isFirstHalf = pos % 2 == 0;

    return isFirstHalf ? m_board[idx] & static_cast<char>( Mask::first_ring )
                       : m_board[idx] & static_cast<char>( Mask::second_ring );
  }

  bool hasRing( const int pos, Color color ) const
  {
    assert( pos >= 0 && pos < num_pos * 2 );
    const int idx = std::floor( pos / 2 );
    const bool isFirstHalf = pos % 2 == 0;

    if( isFirstHalf )
    {
      return color == Color::white
                 ? m_board[idx] == static_cast<char>( Mask::first_white_ring )
                 : m_board[idx] == static_cast<char>( Mask::first_ring );
    }
    else
    {
      return color == Color::white
                 ? m_board[idx] == static_cast<char>( Mask::second_white_ring )
                 : m_board[idx] == static_cast<char>( Mask::second_ring );
    }
  }

  void setRing( const int pos, Color color )
  {
    assert( pos >= 0 && pos < num_pos * 2 );
    const int idx = std::floor( pos / 2 );
    const bool isFirstHalf = pos % 2 == 0;

    if( isFirstHalf )
    {
      m_board[idx] &= 0xf0;
      m_board[idx] |= color == Color::white
                          ? static_cast<char>( Mask::first_white_ring )
                          : static_cast<char>( Mask::first_ring );
    }
    else
    {
      m_board[idx] &= 0x0f;
      m_board[idx] |= color == Color::white
                          ? static_cast<char>( Mask::second_white_ring )
                          : static_cast<char>( Mask::second_ring );
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

  void setPuck( const int pos, Color color )
  {
    assert( pos >= 0 && pos < num_pos * 2 );
    const int idx = std::floor( pos / 2 );
    const bool isFirstHalf = pos % 2 == 0;

    if( isFirstHalf )
    {
      m_board[idx] &= 0xf0;
      m_board[idx] |= color == Color::white
                          ? static_cast<char>( Mask::first_white_puck )
                          : static_cast<char>( Mask::first_puck );
    }
    else
    {
      m_board[idx] &= 0x0f;
      m_board[idx] = color == Color::white
                         ? static_cast<char>( Mask::second_white_puck )
                         : static_cast<char>( Mask::second_puck );
    }
  }

  void flipPuck( const int pos )
  {
    assert( pos >= 0 && pos < num_pos * 2 );
    const int idx = std::floor( pos / 2 );
    const bool isFirstHalf = pos % 2 == 0;

    isFirstHalf ? m_board[idx] ^= static_cast<char>( Mask::first_white_color )
                : m_board[idx] ^= static_cast<char>( Mask::second_white_color );
  }

  void removePuck( const int pos )
  {
    assert( pos >= 0 && pos < num_pos * 2 );
    const int idx = std::floor( pos / 2 );
    const bool isFirstHalf = pos % 2 == 0;

    if( isFirstHalf )
    {
      m_board[idx] &= static_cast<char>( ~( 0x02 ) );
    }
    else
    {
      m_board[idx] &= static_cast<char>( ~( 0x20 ) );
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
  std::array<char, constexprCeil( num_pos / 2.0 )> m_board;
};

static_assert( sizeof( Board ) == 43, "Size has to be 43 bytes" );
