
#include <benchmark/benchmark.h>

#include <algorithm>
#include <array>
#include <assert.h>
#include <cmath>
#include <iostream>

#include <stdlib.h>
#include <time.h>
#include <stdio.h> /* printf, scanf, puts, NULL */

namespace
{
  const int num_pos = 160;  // 85 pos, 2 pos per char
  const int num_ring = 5;
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
  std::array<char, num_pos / 2> m_board{0};
};

void randomPos( char& c ) {}

// 5 ring for each color
auto generateRandomStartingBoard() -> Board
{
  std::array<int, num_ring * 2> randPos;
  for( auto& r : randPos )
  {
    int randIdx = rand() % num_pos;
    while( std::find( randPos.begin(), randPos.end(), randIdx ) !=
           randPos.end() )
    {
      randIdx = rand() % num_pos;
    }

    r = randIdx;
  }

  Board b;
  for( auto& pos : randPos )
  {
    b.setRing( pos );
  }

  return b;
}

// std::vector<int> getMoves( const Board& board, const int ringPos ) {}

static void BM_GenerateRandomBoard( benchmark::State& state )
{
  for( auto _ : state )
  {
    generateRandomStartingBoard();
  }
}

static void BM_AddPuck( benchmark::State& state )
{
  auto b = generateRandomStartingBoard();
  for( auto _ : state )
  {
    b.setPuck( 50 );
  }
}

BENCHMARK( BM_GenerateRandomBoard );
BENCHMARK( BM_AddPuck );

// disable cpu scaling
// sudo cpupower frequency-set --governor performance

BENCHMARK_MAIN();
// int main()
// {
// srand( time( NULL ) );
//   Board b;
//   std::cout << "Yinsh starting" << std::endl;

//   return 0;
// }
