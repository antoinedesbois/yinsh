

#include <min_max.h>

#include <cstdint>
#include <vector>

namespace ai
{
  // BFS style tree creation
  void getNextMove( const Board& board, bool isWhite )
  {
    std::vector<Board> boards{ board };
    //std::vector<int32_t> parents{ -1 };
    //std::vector<int32_t> values{ -1 };

    int32_t depth = 1;
    int32_t range_begin = 0;
    int32_t range_end = 1;
    while( depth < 7 )
    {
      // Compute successor boards for board in the range
      // When creating a new board, set its parent as "r"
      for( int32_t r = range_begin; r < range_end; ++r )
      {
        Board b = boards[r];

        for( short i = 0; i < Board::num_pos; ++i )
        {
          if( !b.hasRing( isWhite, i ) ) continue;
          short j = 0;

          // for every move of a given ring, we can safely place a puck and
          // remove the ring from it's current position
          Board b2 = b;
          b2.removeRing( i );
          b2.setPuck( isWhite, i );
          while( j < 32 )
          {
            const short size = Moves::possibleMoves[i][j];
            if( size < 1 ) break;

            const short nextJ = j + size + 1;
            bool hasReachedPuck = false;
            std::array<short, 9> puckPos = { -1, -1, -1, -1, -1,
                                             -1, -1, -1, -1 };
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

              boards.push_back( b2 );
              //parents.emplace_back(r);
              boards.back().setRing( isWhite,
                                     Moves::possibleMoves[i][j + k + 1] );

              if( hasReachedPuck )
              {
                for( short p : puckPos )
                {
                  if( p == -1 ) break;
                  boards.back().flipPuck( p );
                }

                // TODO handle series removal search
                break;
              }
            }

            j = nextJ;
          }
        }
      }

      // Slide the range
      range_begin = range_end;
      range_end = boards.size();
      ++depth;
      isWhite = !isWhite;
    }
  }

  void getSuccessors( const Board& board, const bool isWhite ) {}

  // given a color, check if the board is a good winning position
  int evaluate( const Board& b, const bool isWhite )
  {
    int value = 0;
    for( int i = 0; i < Board::num_pos; ++i )
    {
      if( b.hasRing( isWhite, i ) )
        value -= 10;
      else if( b.hasRing( i ) )
        value += 10;
      if( b.hasPuck( isWhite, i ) )
        value += 1;
      else if( b.hasPuck( i ) )
        value -= 1;
    }

    return value;
  }
}  // namespace ai

