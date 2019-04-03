
#include <benchmark/benchmark.h>

#include <algorithm>
#include <array>
#include <assert.h>
#include <chrono>
#include <cmath>
#include <iostream>
#include <random>

#include <stdlib.h>
#include <time.h>
#include <stdio.h> /* printf, scanf, puts, NULL */

namespace
{
  const int num_pos = 85;  // 85 pos, 2 pos per char
  const int num_ring = 5;
  constexpr short no_dependency = -1;
  std::array<int, num_pos> rand_num = {
      1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17,
      18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34,
      35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
      52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68,
      69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85};

  // for each position, put every reachable position
  // [short, short] where first = dependency index, second = pos
  std::array<std::vector<short>, 85> possibleMoves = {
      std::vector<short>{no_dependency, 1, 1, 2, 2, 3, no_dependency, 5, 7, 12,
                         9, 20, 11, 29, 13, 38, 15, 47},
      std::vector<short>{no_dependency,
                         0,
                         no_dependency,
                         2,
                         3,
                         3,
                         no_dependency,
                         6,
                         7,
                         13,
                         9,
                         21,
                         11,
                         30,
                         13,
                         39,
                         15,
                         48,
                         17,
                         57},
      std::vector<short>{no_dependency,
                         1,
                         1,
                         0,
                         no_dependency,
                         3,
                         no_dependency,
                         7,
                         7,
                         14,
                         9,
                         22,
                         11,
                         31,
                         13,
                         40,
                         15,
                         49,
                         17,
                         58,
                         19,
                         66},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{},
      std::vector<short>{}};

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

auto generateRandomStartingBoard2() -> Board
{
  const unsigned seed =
      std::chrono::system_clock::now().time_since_epoch().count();
  std::shuffle( begin( rand_num ), end( rand_num ),
                std::default_random_engine( seed ) );

  Board b;
  for( int i = 0; i < num_ring * 2; ++i )
  {
    b.setRing( rand_num[i] );
  }

  return b;
}

auto generateRandomBoard() -> Board
{
  // generate random number of ring
  const int numBlackRing = rand() % 3 + 5;
  const int numWhiteRing = rand() % 3 + 5;
  std::vector<int> ringPos( numBlackRing + numWhiteRing );
  for( auto& p : ringPos )
  {
    int randIdx = rand() % num_pos;
    while( std::find( ringPos.begin(), ringPos.end(), randIdx ) !=
           ringPos.end() )
    {
      randIdx = rand() % num_pos;
    }

    p = randIdx;
  }

  // generate random number of puck
  const int numPuck = rand() % 50;  // [0- 50[ puck
  std::vector<int> puckPos( numPuck );
  for( auto& p : puckPos )
  {
    int randIdx = rand() % num_pos;
    while( std::find( puckPos.begin(), puckPos.end(), randIdx ) !=
           puckPos.end() )
    {
      randIdx = rand() % num_pos;
    }

    p = randIdx;
  }

  Board b;
  for( auto& pos : ringPos )
  {
    b.setRing( pos );
  }

  for( auto& pos : puckPos )
  {
    b.setPuck( pos );
  }

  return b;
}

std::vector<short> getMoves( const int ringPos )
{
  return possibleMoves[ringPos];
}

// given a board, return every possible board considering it is the color's turn
std::vector<Board> getSuccessors( Board b, Color color )
{
  std::vector<Board> successors;
  successors.reserve( 100 );

  bool isFirstHalf = true;
  for( int i = 0; i < num_pos / 2; ++i )
  {
    if( ( isFirstHalf &&
          ( b.m_board[i] &= static_cast<char>( Mask::first_ring ) ) ) ||
        ( !isFirstHalf &&
          ( b.m_board[i] &= static_cast<char>( Mask::second_ring ) ) ) )
    {
      const Color currentColor =
          ( b.m_board[i] &= static_cast<char>( Mask::first_white_color ) )
              ? Color::white
              : Color::black;
      if( currentColor == color )
      {
        // todo get positions
      }
    }

    isFirstHalf = !isFirstHalf;
  }

  return successors;
}

// given a color, check if the board is a good winning position
int evaluate( Board b, Color color )
{
  bool isFirstHalf = true;
  int value = 0;
  for( int i = 0; i < num_pos / 2; ++i )
  {
    if( ( isFirstHalf &&
          ( b.m_board[i] &= static_cast<char>( Mask::first_puck ) ) ) ||
        ( !isFirstHalf &&
          ( b.m_board[i] &= static_cast<char>( Mask::second_puck ) ) ) )
    {
      Color currentColor =
          ( b.m_board[i] &= static_cast<char>( Mask::first_white_color ) )
              ? Color::white
              : Color::black;
      if( currentColor == color )
      {
        value += 1;
      }
      else
      {
        value -= 1;
      }
    }
    else if( ( isFirstHalf &&
               ( b.m_board[i] &= static_cast<char>( Mask::first_ring ) ) ) ||
             ( !isFirstHalf &&
               ( b.m_board[i] &= static_cast<char>( Mask::second_ring ) ) ) )
    {
      Color currentColor =
          ( b.m_board[i] &= static_cast<char>( Mask::first_white_color ) )
              ? Color::white
              : Color::black;
      if( currentColor == color )
      {
        value -= 5;
      }
      else
      {
        value += 5;
      }
    }

    isFirstHalf = !isFirstHalf;
  }

  return value;
}

static void BM_GenerateRandomStartingBoard( benchmark::State& state )
{
  for( auto _ : state )
  {
    generateRandomStartingBoard();
  }
}

static void BM_GenerateRandomStartingBoard2( benchmark::State& state )
{
  for( auto _ : state )
  {
    generateRandomStartingBoard2();
  }
}

static void BM_GenerateRandomBoard( benchmark::State& state )
{
  for( auto _ : state )
  {
    generateRandomBoard();
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

static void BM_GetMoves( benchmark::State& state )
{
  for( auto _ : state )
  {
    static_cast<void>( getMoves( 84 ) );
  }
}

static void BM_Evaluate( benchmark::State& state )
{
  Board b = generateRandomBoard();
  for( auto _ : state )
  {
    evaluate( b, Color::black );
  }
}

static void BM_GetSuccessors( benchmark::State& state )
{
  Board b = generateRandomBoard();
  for( auto _ : state )
  {
    getSuccessors( b, Color::black );
  }
}

BENCHMARK( BM_Evaluate );
BENCHMARK( BM_GenerateRandomStartingBoard );
BENCHMARK( BM_GenerateRandomStartingBoard2 );
BENCHMARK( BM_GenerateRandomBoard );
BENCHMARK( BM_AddPuck );
BENCHMARK( BM_GetMoves );

BENCHMARK( BM_GetSuccessors );

// disable cpu scaling
// sudo cpupower frequency-set --governor performance

// BENCHMARK_MAIN();
int main( int argc, char** argv )
{
  srand( time( NULL ) );

  benchmark::Initialize( &argc, argv );
  benchmark::RunSpecifiedBenchmarks();

  return 0;
}