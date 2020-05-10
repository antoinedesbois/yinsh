
#include <gameState.h>
#include <min_max.h>

namespace
{
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

  auto generateRandomStartingBoard2() -> Board2
  {
    Board2 b;
    for( int i = 0; i < 10; ++i )
    {
      int randIdx = rand() % Board::num_pos;
      if( !b.hasRing( randIdx ) )
      {
        b.setRing( i, randIdx );
      }
    }

    return b;
  }
}  // namespace

int main()
{
  ai::getNextMoveDFS2( generateRandomStartingBoard2(), true );
  //ai::getNextMoveDFS( generateRandomStartingBoard(), true );

  return 0;
}
