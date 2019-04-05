
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
      std::vector<std::vector<short>>{{}, {}, {}, {}, {}, {}},
      std::vector<std::vector<short>>{{}, {}, {}, {}, {}, {}},
      std::vector<std::vector<short>>{{}, {}, {}, {}, {}, {}},
      std::vector<std::vector<short>>{{}, {}, {}, {}, {}, {}},
      // 30
      std::vector<std::vector<short>>{{}, {}, {}, {}, {}, {}},
      std::vector<std::vector<short>>{{}, {}, {}, {}, {}, {}},
      std::vector<std::vector<short>>{{}, {}, {}, {}, {}, {}},
      std::vector<std::vector<short>>{{}, {}, {}, {}, {}, {}},
      std::vector<std::vector<short>>{{}, {}, {}, {}, {}, {}},
      // 35
      std::vector<std::vector<short>>{{}, {}, {}, {}, {}, {}},
      std::vector<std::vector<short>>{{}, {}, {}, {}, {}, {}},
      std::vector<std::vector<short>>{{}, {}, {}, {}, {}, {}},
      std::vector<std::vector<short>>{{}, {}, {}, {}, {}, {}},
      std::vector<std::vector<short>>{{}, {}, {}, {}, {}, {}},
      // 40
      std::vector<std::vector<short>>{{}, {}, {}, {}, {}, {}},
      std::vector<std::vector<short>>{{}, {}, {}, {}, {}, {}},
      std::vector<std::vector<short>>{{}, {}, {}, {}, {}, {}},
      std::vector<std::vector<short>>{{}, {}, {}, {}, {}, {}},
      std::vector<std::vector<short>>{{}, {}, {}, {}, {}, {}},
      // 45
      std::vector<std::vector<short>>{},
      std::vector<std::vector<short>>{{}, {}, {}, {}, {}, {}},
      std::vector<std::vector<short>>{}, std::vector<std::vector<short>>{},
      std::vector<std::vector<short>>{},
      // 50
      std::vector<std::vector<short>>{}, std::vector<std::vector<short>>{},
      std::vector<std::vector<short>>{}, std::vector<std::vector<short>>{},
      std::vector<std::vector<short>>{},
      // 55
      std::vector<std::vector<short>>{}, std::vector<std::vector<short>>{},
      std::vector<std::vector<short>>{}, std::vector<std::vector<short>>{},
      std::vector<std::vector<short>>{},
      // 60
      std::vector<std::vector<short>>{}, std::vector<std::vector<short>>{},
      std::vector<std::vector<short>>{}, std::vector<std::vector<short>>{},
      std::vector<std::vector<short>>{},
      // 65
      std::vector<std::vector<short>>{}, std::vector<std::vector<short>>{},
      std::vector<std::vector<short>>{}, std::vector<std::vector<short>>{},
      std::vector<std::vector<short>>{},
      // 70
      std::vector<std::vector<short>>{}, std::vector<std::vector<short>>{},
      std::vector<std::vector<short>>{}, std::vector<std::vector<short>>{},
      std::vector<std::vector<short>>{},
      // 75
      std::vector<std::vector<short>>{}, std::vector<std::vector<short>>{},
      std::vector<std::vector<short>>{}, std::vector<std::vector<short>>{},
      std::vector<std::vector<short>>{},
      // 80
      std::vector<std::vector<short>>{}, std::vector<std::vector<short>>{},
      std::vector<std::vector<short>>{}, std::vector<std::vector<short>>{},
      std::vector<std::vector<short>>{}};

}  // namespace

enum class Color : char
{
  black,
  white
};

enum class Mask : char
{
  first_ring = 0x01,
  first_puck = 0x02,
  first_white_color = 0x04,
  second_ring = 0x10,
  second_puck = 0x20,
  second_white_color = 0x40,
};

struct Board
{
  constexpr static int num_pos = 85;
  bool hasRing( const int pos )
  {
    assert( pos >= 0 && pos < num_pos * 2 );
    const int idx = std::floor( pos / 2 );
    const bool isFirstHalf = pos % 2 == 0;

    return isFirstHalf ? m_board[idx] &= static_cast<char>( Mask::first_ring )
                       : m_board[idx] &= static_cast<char>( Mask::second_ring );
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

    m_board[idx] = m_board[idx] |= static_cast<char>( Mask::second_ring );
  }

  bool hasPuck( const int pos )
  {
    assert( pos >= 0 && pos < num_pos * 2 );
    const int idx = std::floor( pos / 2 );
    const bool isFirstHalf = pos % 2 == 0;

    return isFirstHalf ? m_board[idx] &= static_cast<char>( Mask::first_puck )
                       : m_board[idx] &= static_cast<char>( Mask::second_puck );
  }

  bool hasPuck( const int pos, Color color )
  {
    assert( pos >= 0 && pos < num_pos * 2 );
    const int idx = std::floor( pos / 2 );
    const bool isFirstHalf = pos % 2 == 0;

    return ( ( m_board[idx] &= static_cast<char>( Mask::first_white_color ) &&
                               color == Color::white ) ||
             ( !( m_board[idx] &=
                  static_cast<char>( Mask::first_white_color ) ) &&
               color == Color::black ) ) &&
           ( isFirstHalf
                 ? m_board[idx] &= static_cast<char>( Mask::first_puck )
                 : m_board[idx] &= static_cast<char>( Mask::second_puck ) );
  }

  void setPuck( const int pos )
  {
    assert( pos >= 0 && pos < num_pos * 2 );
    const int idx = std::floor( pos / 2 );
    const bool isFirstHalf = pos % 2 == 0;

    if( isFirstHalf )
    {
      m_board[idx] = m_board[idx] |= static_cast<char>( Mask::first_puck );
    }

    m_board[idx] = m_board[idx] |= static_cast<char>( Mask::first_puck );
  }

  Color getColor( const int pos )
  {
    assert( pos >= 0 && pos < num_pos * 2 );
    const int idx = std::floor( pos / 2 );
    const bool isFirstHalf = pos % 2 == 0;

    if( isFirstHalf )
    {
      return ( m_board[idx] &= static_cast<char>( Mask::first_white_color ) )
                 ? Color::white
                 : Color::black;
    }
    return ( m_board[idx] &= static_cast<char>( Mask::second_white_color ) )
               ? Color::white
               : Color::black;
  }

  // char contains 2 pos
  // Bit: 1 -> ring, 2 -> puck, 3 -> color, 4 -> nothing
  std::array<char, num_pos / 2> m_board{
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
};

