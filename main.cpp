
#include <board.h>

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

std::vector<std::vector<short>> getMoves( const int ringPos )
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
