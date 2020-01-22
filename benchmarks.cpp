
#include <board.h>

#include <benchmark/benchmark.h>

#include <algorithm>
#include <array>
#include <assert.h>
#include <chrono>
#include <cmath>
#include <random>

#include <stdlib.h>
#include <time.h>
#include <stdio.h> /* printf, scanf, puts, NULL */

namespace
{
  std::array<char, 85> rand_num = {
      0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16,
      17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33,
      34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
      51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67,
      68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84};
}

void randomPos( char& c ) {}

// 5 ring for each color
auto generateRandomStartingBoard() -> Board
{
  std::array<int, Board::num_ring * 2> randPos;
  for( auto& r : randPos )
  {
    int randIdx = rand() % Board::num_pos;
    while( std::find( randPos.begin(), randPos.end(), randIdx ) !=
           randPos.end() )
    {
      randIdx = rand() % Board::num_pos;
    }

    r = randIdx;
  }

  Board b;
  for( size_t i = 0; i < randPos.size(); ++i )
  {
    b.setRing( i % 2 == 0, randPos[i] );
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
  for( int i = 0; i < Board::num_ring * 2; ++i )
  {
    b.setRing( i % 2 == 0, rand_num[i] );
  }

  return b;
}

auto generateRandomBoard() -> Board
{
  // generate random number of ring
  const int numBlackRing = rand() % 5 + 1;
  const int numWhiteRing = rand() % 5 + 1;
  std::vector<int> ringPos( numBlackRing + numWhiteRing );
  for( auto& p : ringPos )
  {
    int randIdx = rand() % Board::num_pos;
    while( std::find( ringPos.begin(), ringPos.end(), randIdx ) !=
           ringPos.end() )
    {
      randIdx = rand() % Board::num_pos;
    }

    p = randIdx;
  }

  // generate random number of puck
  const int numPuck = rand() % 50;  // [0- 50[ puck
  std::vector<int> puckPos( numPuck );
  for( auto& p : puckPos )
  {
    int randIdx = rand() % Board::num_pos;
    while(
        std::find( puckPos.begin(), puckPos.end(), randIdx ) != puckPos.end() ||
        std::find( ringPos.begin(), ringPos.end(), randIdx ) != ringPos.end() )
    {
      randIdx = rand() % Board::num_pos;
    }

    p = randIdx;
  }

  Board b;
  for( size_t i = 0; i < ringPos.size(); ++i )
  {
    b.setRing( i % 2 == 0, ringPos[i] );
  }

  for( size_t i = 0; i < puckPos.size(); ++i )
  {
    b.setPuck( i % 2 == 0, puckPos[i] );
  }

  return b;
}

#include <iostream>
std::array<Board, 26 * 5> getSuccessors( Board b, bool color )
{
  std::array<Board, 26 * 5> successors;
  short successorIdx = 0;
  for( short i = 0; i < Board::num_pos; ++i )
  {
    if( !b.hasRing( color, i ) ) continue;
    short j = 0;

    // for every move of a given ring, we can safely place a puck and remove the
    // ring from it's current position
    Board b2 = b;
    b2.removeRing( i );
    b2.setPuck( color, i );
    while( j < 32 )
    {
      const short size = Moves::possibleMoves[i][j];
      if( size < 1 ) break;

      const short nextJ = j + size + 1;
      bool hasReachedPuck = false;
      std::array<short, 9> puckPos = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
      int puckIdx = 0;
      for( short k = 0; k < size; ++k )
      {
        if( b.hasRing( Moves::possibleMoves[i][j + k + 1] ) ) break;
        if( b.hasPuck( Moves::possibleMoves[i][j + k + 1] ) )
        {
          hasReachedPuck = true;
          puckPos[puckIdx] = Moves::possibleMoves[i][j + k + 1];
          puckIdx++;
          continue;
        }

        successors[successorIdx] = b2;
        successors[successorIdx].setRing( color,
                                          Moves::possibleMoves[i][j + k + 1] );

        if( hasReachedPuck )
        {
          for( short p : puckPos )
          {
            if( p == -1 ) break;
            successors[successorIdx].flipPuck( p );
          }

          ++successorIdx;
          break;
        }

        ++successorIdx;
      }

      j = nextJ;
    }
  }

  return successors;
}

// given a color, check if the board is a good winning position
int evaluate( Board b, const bool color )
{
  int value = 0;
  for( int i = 0; i < Board::num_pos; ++i )
  {
    if( b.hasRing( color, i ) )
      value -= 10;
    else if( b.hasRing( i ) )
      value += 10;
    if( b.hasPuck( color, i ) )
      value += 1;
    else if( b.hasPuck( i ) )
      value -= 1;
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

static void BM_Evaluate( benchmark::State& state )
{
  Board b = generateRandomBoard();
  for( auto _ : state )
  {
    static_cast<void>( evaluate( b, true ) );
  }
}

static void BM_GetSuccessors( benchmark::State& state )
{
  Board b = generateRandomBoard();
  for( auto _ : state )
  {
    getSuccessors( b, true );
  }
}

BENCHMARK( BM_Evaluate );
BENCHMARK( BM_GenerateRandomStartingBoard );
BENCHMARK( BM_GenerateRandomStartingBoard2 );
BENCHMARK( BM_GenerateRandomBoard );

BENCHMARK( BM_GetSuccessors );

// disable cpu scaling
// sudo cpupower frequency-set --governor performance

// BENCHMARK_MAIN();
int main( int argc, char** argv )
{
  // srand( time( NULL ) );

  benchmark::Initialize( &argc, argv );
  benchmark::RunSpecifiedBenchmarks();

  return 0;
}
