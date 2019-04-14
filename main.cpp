
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

void randomPos( char& c ) {}

// 5 ring for each color
auto generateRandomStartingBoard() -> Board
{
  std::array<int, num_ring * 2> randPos;
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
    while( std::find( puckPos.begin(), puckPos.end(), randIdx ) !=
           puckPos.end() )
    {
      randIdx = rand() % Board::num_pos;
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

std::vector<std::vector<int>> getMoves( const int ringPos )
{
  return Moves::possibleMoves[ringPos];
}

// given a board, return every possible board considering it is the color's turn
std::vector<Board> getSuccessors( Board b, Color color )
{
  std::vector<Board> successors;
  successors.reserve( 100 );

  for( int i = 0; i < Board::num_pos; ++i )
  {
    if( !b.hasRing( i ) ) continue;
    if( b.getColor( i ) != color ) continue;

    assert( b.hasRing( i ) && b.getColor( i ) == color );
    for( int j = 0; i < Moves::possibleMoves[i].size(); ++i )
    {
      bool hasReachedPuck = false;
      std::vector<int> puckPos;  // contains all the position where there is a
                                 // puck on a given direction
      for( int k = 0; j < Moves::possibleMoves[i][j].size(); ++j )
      {
        if( b.hasRing( Moves::possibleMoves[i][j][k] ) ) break;
        if( b.hasPuck( Moves::possibleMoves[i][j][k] ) )
        {
          hasReachedPuck = true;
          puckPos.push_back( Moves::possibleMoves[i][j][k] );
          continue;
        }

        Board successorBoard( b );
        successorBoard.setPuck( i );
        successorBoard.removeRing( i );
        successorBoard.setRing( Moves::possibleMoves[i][j][k] );

        if( hasReachedPuck )
        {
          // TODO flip all puck
          successors.push_back( successorBoard );
          break;
        }

        successors.push_back( successorBoard );
      }
    }
  }

  return successors;
}

// given a color, check if the board is a good winning position
int evaluate( Board b, Color color )
{
  bool isFirstHalf = true;
  int value = 0;
  for( int i = 0; i < Board::num_pos / 2; ++i )
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
