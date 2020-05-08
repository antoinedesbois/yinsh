
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
}  // namespace

int main()
{
  Board2 b;
  b.setRing(0, 0);
  b.setRing(1, 1);
  b.setRing(2, 2);
  ai::evaluate2(b, true);
  //ai::getNextMoveDFS(generateRandomStartingBoard(), true);
  //ai::getNextMove(generateRandomStartingBoard(), true);
  
  return 0;
}
