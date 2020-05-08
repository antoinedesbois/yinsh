
#ifndef BOARD_H_
#define BOARD_H_

#include <algorithm>
#include <array>
#include <assert.h>
#include <chrono>
#include <cmath>
#include <random>
#include <bitset>

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <cstring>

namespace Moves
{
  constexpr char max_moves = 26;
  constexpr char max_directions = 6;
  constexpr char max_array_size = max_moves + max_directions;

  constexpr std::array<std::array<char, max_array_size>, 85> possibleMoves = {

      // 0
      std::array<char, max_array_size>{
          0,  3,  1,  2,  3,  6,  5,  12, 20, 29, 38, 47, 0,  9,  6,  14,
          23, 33, 43, 53, 63, 72, 80, 0,  -1, -1, -1, -1, -1, -1, -1, -1},
      std::array<char, max_array_size>{
          1,  0,  2,  2,  3,  7,  6,  13, 21, 30, 39, 48, 57, 0,  8,  7,
          15, 24, 34, 44, 54, 64, 73, 0,  -1, -1, -1, -1, -1, -1, -1, -1},
      std::array<char, max_array_size>{
          2, 1,  0,  1,  3,  8,  7,  14, 22, 31, 40, 49, 58, 66, 0,  7,
          8, 16, 25, 35, 45, 55, 65, 0,  -1, -1, -1, -1, -1, -1, -1, -1},
      std::array<char, max_array_size>{
          3, 2, 1,  0,  0,  9,  8,  15, 23, 32, 41, 50, 59, 67, 74, 0,
          6, 9, 17, 26, 36, 46, 56, 0,  -1, -1, -1, -1, -1, -1, -1, -1},
      std::array<char, max_array_size>{
          6,  5,  6,  7,  8,  9,  10, 0, 3,  11, 19, 28, 0,  9,  12, 21,
          31, 41, 51, 61, 70, 78, 84, 0, -1, -1, -1, -1, -1, -1, -1, -1},

      // 5
      std::array<char, max_array_size>{
          1, 4,  5,  6,  7,  8,  9,  10, 1,  0, 5,  12, 20, 29, 38, 47,
          8, 13, 22, 32, 42, 52, 62, 71, 79, 0, -1, -1, -1, -1, -1, -1},
      std::array<char, max_array_size>{
          2,  5, 4, 4, 7,  8,  9,  10, 1,  1,  6,  13, 21, 30, 39, 48,
          57, 1, 0, 8, 14, 23, 33, 43, 53, 63, 72, 80, -1, -1, -1, -1},
      std::array<char, max_array_size>{
          3,  6,  5, 4, 3, 8,  9,  10, 1,  2,  7,  14, 22, 31, 40, 49,
          58, 66, 1, 1, 7, 15, 24, 34, 44, 54, 64, 73, -1, -1, -1, -1},
      std::array<char, max_array_size>{4,  7,  6,  5,  4,  2,  9,  10, 1,  3, 8,
                                       15, 23, 32, 41, 50, 59, 67, 74, 1,  2, 6,
                                       16, 25, 35, 45, 55, 65, -1, -1, -1, -1},
      std::array<char, max_array_size>{
          5,  8, 7, 6, 5, 4,  1,  10, 8,  16, 24, 33, 42, 51, 60, 68,
          75, 0, 1, 3, 5, 17, 26, 36, 46, 56, -1, -1, -1, -1, -1, -1},

      // 10
      std::array<char, max_array_size>{
          6,  9,  8, 7, 6,  5,  4,  0, 9,  17, 25, 34, 43, 52, 61, 39,
          76, 81, 0, 3, 18, 27, 37, 0, -1, -1, -1, -1, -1, -1, -1, -1},
      std::array<char, max_array_size>{
          7,  12, 13, 14, 15, 16, 17, 18, 0,  1,  4,  2,  19, 28, 8,  20,
          30, 40, 50, 60, 69, 77, 83, 0,  -1, -1, -1, -1, -1, -1, -1, -1},
      std::array<char, max_array_size>{
          1,  11, 6, 13, 14, 15, 16, 17, 18, 2,  0,  5,  4,  20, 29, 38,
          47, 1,  4, 8,  21, 31, 41, 51, 61, 70, 78, 84, -1, -1, -1, -1},
      std::array<char, max_array_size>{
          2,  12, 11, 5, 14, 15, 16, 17, 18, 2,  6,  1,  5,  21, 30, 39,
          48, 57, 1,  5, 7,  22, 32, 42, 52, 62, 71, 79, -1, -1, -1, -1},
      std::array<char, max_array_size>{3, 13, 12, 11, 4,  15, 16, 17, 18, 2, 7,
                                       2, 6,  22, 31, 40, 49, 58, 66, 2,  6, 0,
                                       7, 23, 33, 43, 53, 63, 72, 80, -1, -1},

      // 15
      std::array<char, max_array_size>{4, 14, 13, 12, 11, 3,  16, 17, 18, 2, 8,
                                       3, 7,  23, 32, 41, 50, 59, 67, 74, 2, 7,
                                       1, 6,  24, 34, 44, 54, 64, 73, -1, -1},
      std::array<char, max_array_size>{5, 15, 14, 13, 12, 11, 2,  17, 18, 1, 9,
                                       7, 24, 33, 42, 51, 60, 68, 75, 2,  8, 2,
                                       5, 25, 35, 45, 55, 65, -1, -1, -1, -1},
      std::array<char, max_array_size>{6, 16, 15, 14, 13, 12, 11, 1,  18, 1, 10,
                                       8, 25, 34, 43, 52, 61, 69, 76, 81, 2, 9,
                                       3, 4,  26, 36, 46, 56, -1, -1, -1, -1},
      std::array<char, max_array_size>{
          7,  17, 16, 15, 14, 13, 12, 11, 0,  8,  26, 35, 44, 53, 62, 70,
          77, 82, 0,  1,  10, 2,  27, 37, -1, -1, -1, -1, -1, -1, -1, -1},
      std::array<char, max_array_size>{
          8,  20, 21, 22, 23, 24, 25, 26, 27, 0,  2,  11, 4,  1,  28, 7,
          29, 39, 49, 59, 68, 76, 82, 0,  -1, -1, -1, -1, -1, -1, -1, -1},

      // 20
      std::array<char, max_array_size>{
          1,  19, 7,  21, 22, 23, 24, 25, 26, 27, 2,  12, 5,  3,  29, 38,
          47, 1,  11, 7,  30, 40, 50, 60, 69, 77, 83, -1, -1, -1, -1, -1},
      std::array<char, max_array_size>{
          2,  20, 19, 6, 22, 23, 24, 25, 26, 27, 3,  13, 6,  1,  4,  30,
          39, 48, 57, 2, 12, 4,  7,  31, 41, 51, 61, 70, 78, 84, -1, -1},
      std::array<char, max_array_size>{
          3,  21, 20, 19, 5, 23, 24, 25, 26, 27, 3,  14, 7,  2,  5,  31,
          40, 49, 58, 66, 2, 13, 5,  6,  32, 42, 52, 62, 71, 79, -1, -1},
      std::array<char, max_array_size>{
          4,  22, 21, 20, 19, 4, 24, 25, 26, 27, 3,  15, 8,  3,  6,  32,
          41, 50, 59, 67, 74, 3, 14, 6,  0,  6,  33, 43, 53, 63, 72, 80},
      std::array<char, max_array_size>{
          5,  23, 22, 21, 20, 19, 3, 25, 26, 27, 2,  16, 9,  6,  33, 42,
          51, 60, 68, 75, 3,  15, 7, 1,  5,  34, 44, 54, 64, 73, -1, -1},

      // 25
      std::array<char, max_array_size>{
          6,  24, 23, 22, 21, 20, 19, 2, 26, 27, 2,  17, 10, 7,  34, 43,
          52, 61, 69, 76, 81, 3,  16, 8, 2,  4,  35, 45, 55, 65, -1, -1},
      std::array<char, max_array_size>{
          1,  27, 7,  25, 24, 23, 22, 21, 20, 19, 1,  18, 7,  35, 44, 53,
          62, 70, 77, 82, 3,  17, 9,  3,  3,  36, 46, 56, -1, -1, -1, -1},
      std::array<char, max_array_size>{
          8,  26, 25, 24, 23, 22, 21, 20, 19, 0,  7,  36, 45, 54, 63, 71,
          78, 83, 0,  2,  18, 10, 1,  37, -1, -1, -1, -1, -1, -1, -1, -1},
      std::array<char, max_array_size>{
          9, 29, 30, 31, 32, 33, 34, 35, 36, 37, 0,  3,  19, 11, 4,  0,
          6, 38, 48, 58, 67, 75, 81, 0,  -1, -1, -1, -1, -1, -1, -1, -1},
      // todo
      std::array<char, max_array_size>{
          1, 28, 8,  30, 31, 32, 33, 34, 35, 36, 37, 4,  20, 12, 5,  0,
          2, 38, 47, 1,  19, 6,  39, 49, 59, 68, 76, 82, -1, -1, -1, -1},

      // 30
      std::array<char, max_array_size>{
          2,  29, 28, 7,  31, 32, 33, 34, 35, 36, 37, 2,  20, 11, 6,  40,
          50, 60, 69, 77, 83, 4,  21, 13, 6,  1,  3,  39, 48, 57, -1, -1},
      std::array<char, max_array_size>{
          3, 30, 29, 28, 6,  32, 33, 34, 35, 36, 37, 4,  22, 14, 7,  2,
          4, 40, 49, 58, 66, 3,  21, 12, 4,  6,  41, 51, 61, 70, 78, 84},
      std::array<char, max_array_size>{
          4, 31, 30, 29, 28, 5,  33, 34, 35, 36, 37, 4,  23, 15, 8,  3,
          5, 41, 50, 59, 67, 74, 3,  22, 13, 5,  5,  42, 52, 62, 71, 79},
      std::array<char, max_array_size>{
          5,  32, 31, 30, 29, 28, 4,  34, 35, 36, 37, 3,  24, 16, 9,  5,
          42, 51, 60, 68, 75, 4,  23, 14, 6,  0,  5,  43, 53, 63, 72, 80},
      std::array<char, max_array_size>{
          6,  33, 32, 31, 30, 29, 28, 3,  35, 36, 37, 3, 25, 17, 10, 6,
          43, 52, 61, 69, 76, 81, 4,  24, 15, 7,  1,  4, 44, 54, 64, 73},

      // 35
      std::array<char, max_array_size>{
          7,  34, 33, 32, 31, 30, 29, 28, 2, 36, 37, 2,  26, 18, 6,  44,
          53, 62, 70, 77, 82, 4,  25, 16, 8, 2,  3,  45, 55, 65, -1, -1},
      std::array<char, max_array_size>{
          8,  35, 34, 33, 32, 31, 30, 29, 28, 1, 37, 1,  27, 6,  45, 54,
          63, 71, 78, 83, 4,  26, 17, 9,  3,  2, 46, 56, -1, -1, -1, -1},
      std::array<char, max_array_size>{
          9,  36, 35, 34, 33, 32, 31, 30, 29, 28, 0,  6,  46, 55, 64, 72,
          79, 84, 0,  3,  27, 18, 10, 0,  -1, -1, -1, -1, -1, -1, -1, -1},
      std::array<char, max_array_size>{
          8, 39, 40, 41, 42, 43, 44, 45, 46, 0,  5,  29, 20, 12, 5,  0,
          1, 47, 1,  28, 5,  48, 58, 67, 75, 81, -1, -1, -1, -1, -1, -1},
      std::array<char, max_array_size>{
          1, 38, 7,  40, 41, 42, 43, 44, 45, 46, 5,  30, 21, 13, 6,  1,
          2, 48, 57, 2,  29, 19, 5,  49, 59, 68, 76, 81, -1, -1, -1, -1},

      // 40
      std::array<char, max_array_size>{
          2, 39, 38, 6,  41, 42, 43, 44, 45, 46, 5,  31, 22, 14, 7,  2,
          3, 49, 58, 66, 3,  30, 20, 11, 5,  50, 60, 69, 77, 83, -1, -1},
      std::array<char, max_array_size>{3,  40, 39, 38, 5, 42, 43, 44, 45, 46, 5,
                                       32, 23, 15, 8,  3, 4,  50, 59, 67, 74, 4,
                                       31, 21, 12, 4,  5, 51, 61, 70, 78, 84},
      std::array<char, max_array_size>{
          4,  41, 40, 39, 38, 4,  43, 44, 45, 46, 4,  33, 24, 16, 9,  4,
          51, 60, 68, 75, 4,  32, 22, 13, 5,  4,  52, 62, 71, 79, -1, -1},
      std::array<char, max_array_size>{
          5,  42, 41, 40, 39, 38, 3,  44, 45, 46, 4, 34, 25, 17, 10, 5,
          52, 61, 69, 76, 81, 5,  33, 23, 14, 6,  0, 4,  53, 63, 72, 80},
      std::array<char, max_array_size>{
          6,  43, 42, 41, 40, 39, 38, 2,  45, 46, 3, 35, 26, 18, 5,  53,
          62, 70, 77, 82, 5,  34, 24, 15, 7,  1,  3, 54, 64, 73, -1, -1},

      // 45
      std::array<char, max_array_size>{
          7,  44, 43, 42, 41, 40, 39, 38, 1, 46, 2,  36, 27, 5,  54, 63,
          71, 78, 83, 5,  35, 25, 16, 8,  2, 2,  55, 65, -1, -1, -1, -1},
      std::array<char, max_array_size>{
          8,  45, 44, 43, 42, 41, 40, 39, 38, 0,  1,  37, 5,  55, 64, 72,
          79, 84, 5,  36, 26, 17, 9,  3,  1,  56, -1, -1, -1, -1, -1, -1},
      std::array<char, max_array_size>{
          9, 48, 49, 50, 51, 52, 53, 54, 55, 56, 0,  6,  38, 29, 20, 12,
          5, 0,  0,  3,  57, 66, 74, 0,  -1, -1, -1, -1, -1, -1, -1, -1},
      std::array<char, max_array_size>{
          1, 47, 8, 49, 50, 51, 52, 53, 54, 55, 56, 6,  39, 30, 21, 13,
          6, 1,  1, 57, 2,  38, 28, 4,  58, 67, 75, 81, -1, -1, -1, -1},
      std::array<char, max_array_size>{
          2, 48, 47, 7,  50, 51, 52, 53, 54, 55, 56, 6,  40, 31, 22, 14,
          7, 2,  2,  58, 66, 3,  39, 29, 19, 4,  59, 68, 76, 82, -1, -1},

      // 50
      std::array<char, max_array_size>{
          3, 49, 48, 47, 6,  51, 52, 53, 54, 55, 56, 6, 41, 32, 23, 15,
          8, 3,  3,  59, 67, 74, 4,  40, 30, 20, 11, 4, 60, 69, 77, 83},
      std::array<char, max_array_size>{
          4, 50, 49, 48, 47, 5, 52, 53, 54, 55, 56, 5, 42, 33, 24, 16,
          9, 3,  60, 68, 75, 5, 41, 31, 21, 12, 7,  4, 61, 70, 78, 84},
      std::array<char, max_array_size>{5, 51, 50, 49, 48, 47, 4, 53, 54, 55, 56,
                                       5, 43, 34, 25, 17, 10, 4, 61, 69, 76, 81,
                                       5, 42, 32, 22, 13, 5,  3, 62, 71, 79},
      std::array<char, max_array_size>{
          6, 52, 51, 50, 49, 48, 47, 3,  54, 55, 56, 4, 44, 35, 26, 18,
          4, 62, 70, 77, 82, 6,  43, 33, 23, 14, 6,  0, 3,  63, 72, 80},
      std::array<char, max_array_size>{
          7,  53, 52, 51, 50, 49, 48, 47, 2,  55, 56, 3, 45, 36, 27, 4,
          63, 71, 78, 83, 6,  44, 34, 24, 15, 7,  1,  2, 64, 73, -1, -1},

      // 55
      std::array<char, max_array_size>{
          8,  54, 53, 52, 51, 50, 49, 48, 47, 1, 56, 2,  46, 37, 4,  64,
          72, 79, 84, 6,  45, 35, 25, 16, 8,  2, 1,  65, -1, -1, -1, -1},
      std::array<char, max_array_size>{9, 55, 54, 53, 52, 51, 50, 49, 48, 47, 0,
                                       3, 65, 73, 80, 0,  6,  46, 36, 26, 17, 9,
                                       3, 0,  -1, -1, -1, -1, -1, -1, -1, -1},
      std::array<char, max_array_size>{
          8, 58, 59, 60, 61, 62, 63, 64, 65, 0,  7,  48, 39, 30, 21, 13,
          6, 1,  0,  1,  47, 2,  66, 74, -1, -1, -1, -1, -1, -1, -1, -1},
      std::array<char, max_array_size>{
          1, 57, 7, 59, 60, 61, 62, 63, 64, 65, 7,  49, 40, 31, 22, 14,
          7, 2,  1, 66, 3,  48, 38, 28, 3,  67, 75, 81, -1, -1, -1, -1},
      std::array<char, max_array_size>{
          2, 58, 57, 6,  60, 61, 62, 63, 64, 65, 7, 50, 41, 32, 23, 15,
          8, 3,  2,  67, 74, 4,  49, 39, 29, 19, 3, 68, 76, 82, -1, -1},

      // 60
      std::array<char, max_array_size>{
          3, 59, 58, 57, 5, 61, 62, 63, 64, 65, 6, 51, 42, 33, 24, 16,
          9, 2,  68, 75, 5, 50, 40, 30, 20, 11, 3, 69, 77, 83, -1, -1},
      std::array<char, max_array_size>{
          4,  60, 59, 58, 57, 4, 62, 63, 64, 65, 6,  52, 43, 34, 25, 17,
          10, 3,  69, 76, 81, 6, 51, 41, 31, 21, 12, 4,  3,  70, 78, 84},
      std::array<char, max_array_size>{
          5, 61, 60, 59, 58, 57, 3,  63, 64, 65, 5, 53, 44, 35, 26, 18,
          3, 70, 77, 82, 6,  52, 42, 32, 22, 13, 5, 2,  71, 79, -1, -1},
      std::array<char, max_array_size>{
          6,  62, 61, 60, 59, 58, 57, 2,  64, 65, 4, 54, 45, 36, 27, 3,
          71, 78, 83, 7,  53, 43, 33, 23, 14, 6,  0, 2,  72, 80, -1, -1},
      std::array<char, max_array_size>{
          7,  63, 62, 61, 60, 59, 58, 57, 1, 65, 3, 55, 46, 37, 3,  72,
          79, 84, 7,  54, 44, 34, 24, 15, 7, 1,  1, 73, -1, -1, -1, -1},

      // 65
      std::array<char, max_array_size>{
          8,  64, 63, 62, 61, 60, 59, 58, 57, 0,  1,  56, 2,  73, 80, 7,
          55, 45, 35, 25, 16, 8,  2,  0,  -1, -1, -1, -1, -1, -1, -1, -1},
      std::array<char, max_array_size>{
          7, 67, 68, 69, 70, 71, 72, 73, 0,  8,  58, 49, 40, 31, 22, 14,
          7, 2,  0,  2,  57, 47, 1,  74, -1, -1, -1, -1, -1, -1, -1, -1},
      std::array<char, max_array_size>{
          1, 66, 6, 68, 69, 70, 71, 72, 73, 8, 59, 50, 41, 32, 23, 15,
          8, 3,  1, 74, 4,  58, 48, 38, 28, 2, 75, 81, -1, -1, -1, -1},
      std::array<char, max_array_size>{
          2, 67, 66, 5, 69, 70, 71, 72, 73, 7, 60, 51, 42, 33, 24, 16,
          9, 1,  75, 5, 59, 49, 39, 29, 19, 2, 76, 82, -1, -1, -1, -1},
      std::array<char, max_array_size>{
          3,  68, 67, 66, 4, 70, 71, 72, 73, 7,  61, 52, 43, 34, 25, 17,
          10, 2,  76, 81, 6, 60, 50, 40, 30, 20, 11, 2,  77, 83, -1, -1},

      // 70
      std::array<char, max_array_size>{
          4, 69, 68, 67, 66, 3,  71, 72, 73, 6,  62, 53, 44, 35, 26, 18,
          2, 77, 82, 7,  61, 51, 41, 31, 21, 12, 4,  2,  78, 84, -1, -1},
      std::array<char, max_array_size>{
          5,  70, 69, 68, 67, 66, 2,  72, 73, 5, 63, 54, 45, 36, 27, 2,
          78, 83, 7,  62, 52, 42, 32, 22, 13, 5, 1,  79, -1, -1, -1, -1},
      std::array<char, max_array_size>{
          6,  71, 70, 69, 68, 67, 66, 1,  73, 4, 64, 55, 46, 37, 2,  79,
          84, 8,  63, 53, 43, 33, 23, 14, 6,  0, 1,  80, -1, -1, -1, -1},
      std::array<char, max_array_size>{
          7,  72, 71, 70, 69, 68, 67, 66, 0,  2,  65, 56, 1,  80, 8,  64,
          54, 44, 34, 24, 15, 7,  1,  0,  -1, -1, -1, -1, -1, -1, -1, -1},
      std::array<char, max_array_size>{
          6, 75, 76, 77, 78, 79, 80, 0, 9,  67, 59, 50, 41, 32, 23, 15,
          8, 3,  0,  3,  66, 57, 47, 0, -1, -1, -1, -1, -1, -1, -1, -1},

      // 75
      std::array<char, max_array_size>{
          1,  74, 6, 75, 76, 77, 78, 79, 80, 8, 68, 60, 51, 42, 33, 24,
          16, 9,  0, 5,  67, 58, 58, 38, 28, 1, 81, -1, -1, -1, -1, -1},
      std::array<char, max_array_size>{
          2,  75, 74, 4, 77, 78, 79, 80, 8,  69, 61, 52, 43, 34, 25, 17,
          10, 1,  81, 6, 68, 59, 49, 39, 29, 19, 1,  82, -1, -1, -1, -1},
      std::array<char, max_array_size>{
          3, 76, 75, 74, 3,  78, 79, 80, 7,  70, 62, 53, 44, 35, 26, 18,
          1, 82, 7,  69, 60, 50, 40, 30, 20, 11, 1,  83, -1, -1, -1, -1},
      std::array<char, max_array_size>{
          4,  77, 76, 75, 74, 2,  79, 80, 6,  71, 63, 54, 45, 36, 27, 1,
          83, 8,  70, 61, 51, 41, 31, 21, 12, 4,  1,  84, -1, -1, -1, -1},
      std::array<char, max_array_size>{
          5, 78, 77, 76, 75, 74, 1,  80, 5, 72, 64, 55, 46, 37, 1,  84,
          8, 71, 62, 52, 42, 32, 22, 13, 5, 0,  -1, -1, -1, -1, -1, -1},

      // 80
      std::array<char, max_array_size>{
          6,  79, 78, 77, 76, 75, 74, 0, 3,  73, 65, 56, 0,  9,  72, 63,
          53, 43, 33, 23, 14, 6,  0,  0, -1, -1, -1, -1, -1, -1, -1, -1},
      std::array<char, max_array_size>{
          3, 82, 83, 84, 0,  9,  76, 69, 61, 52, 43, 34, 25, 17, 10, 0,
          6, 75, 67, 58, 48, 38, 28, 0,  -1, -1, -1, -1, -1, -1, -1, -1},
      std::array<char, max_array_size>{
          1,  81, 2,  83, 84, 8,  77, 70, 62, 53, 44, 35, 26, 18, 0,  7,
          76, 68, 59, 49, 39, 29, 19, 0,  -1, -1, -1, -1, -1, -1, -1, -1},
      std::array<char, max_array_size>{
          2,  82, 81, 1,  84, 7,  78, 71, 63, 54, 45, 36, 27, 0,  8,  77,
          69, 60, 50, 40, 30, 20, 11, 0,  -1, -1, -1, -1, -1, -1, -1, -1},
      std::array<char, max_array_size>{
          3,  83, 82, 81, 0,  6,  79, 72, 64, 55, 46, 37, 0,  9,  78, 70,
          61, 51, 41, 31, 21, 12, 4,  0,  -1, -1, -1, -1, -1, -1, -1, -1}};

}  // namespace Moves

namespace
{
  constexpr int num_ring = 5;

}  // namespace

enum class Color : char
{
  black,
  white
};

struct Board
{
  constexpr static int num_pos = 85;
  constexpr static int num_ring = 5;

  // Initialize an empty board
  Board() : m_board() {}

  Board( const std::string& bits );

  Board( const Board& b );
  Board& operator=( const Board& b );

  bool operator==( const Board& other ) const;

  bool hasRing( int pos ) const;
  bool hasRing( bool isWhite, int pos ) const;
  void setRing( bool isWhite, int pos );
  void removeRing( const int pos );

  bool hasPuck( int pos ) const;
  bool hasPuck( bool isWhite, int pos ) const;
  void setPuck( bool isWhite, int pos );
  void removePuck( int pos );
  void flipPuck( int pos );

  // Check if there is any series containing the given position
  bool hasSeries( int pos ) const;
  bool hasSeries( bool isWhite, int pos ) const;

  // returns true if white
  bool getColor( int pos ) const;

#ifndef NDEBUG
  // Each position must have either a ring, a puck or nothing
  bool isValid( const Board& board );
#endif

  // 255 bit for the 85 position (3 bit each)
  std::bitset<85 * 3 + 1> m_board;
};

static_assert( sizeof( Board ) == 32, "Size has to be 32 bytes" );

struct Board2
{
  constexpr static int num_pos = 85;
  constexpr static int num_ring = 5;

  // Initialize an empty board
  Board2() : m_board()
  {
    std::memset( &m_board[0], 0xff, 10);
    std::memset( &m_board[10], 0x00, 22 );
  }

  Board2( const Board2& b );
  Board2& operator=( const Board2& b );

  bool operator==( const Board2& other ) const;

  bool hasRing( uint8_t pos ) const;
  bool hasRing( bool isWhite, uint8_t pos ) const;
  void setRing( uint8_t index, uint8_t pos );
  void removeRing( uint8_t index );

  bool hasPuck( uint8_t pos ) const;
  bool hasPuck( bool isWhite, uint8_t pos ) const;
  void setPuck( bool isWhite, uint8_t pos );
  void removePuck( uint8_t pos );
  void flipPuck( uint8_t pos );

  // Check if there is any series containing the given position
  bool hasSeries( uint8_t pos ) const;
  bool hasSeries( bool isWhite, uint8_t pos ) const;

  // [0..9,        10..20,           21, 31]
  // ^               ^               ^
  // 10 byte ring    11 byte puck    11 byte puck
  //  0xff => inexistant ring
  std::array<uint8_t, 32> m_board;
};

#endif  // BOARD_H_
