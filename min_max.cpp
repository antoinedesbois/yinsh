

#include <min_max.h>

#include <cstdint>
#include <vector>
#include <stack>

namespace
{
}

namespace ai
{
  void getNextMoveDFS( const Board& board, bool isWhite )
  {
    constexpr size_t DEPTH = 4;
    std::vector<std::vector<Board>> to_visit {{board}};
    to_visit.reserve(DEPTH);
    std::vector<size_t> index_stack{ 0 };
    size_t current_depth = 0;

    while( !to_visit.empty() )
    {
      /////////////////
      // Compute successors for current depth, current element
      size_t index = index_stack.back();
      index_stack.pop_back();
      for( ; index < to_visit[current_depth].size(); ++index )
      {
        Board& b = to_visit[current_depth][index];
        if( current_depth == DEPTH )
        {
          evaluate(b, DEPTH % 2 == 0 ? !isWhite : isWhite);
          continue;
        }

        to_visit.push_back({});
        to_visit.back().reserve(100);

        // Get successors for a given board
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

              to_visit.back().push_back( b2 );
              to_visit.back().back().setRing( isWhite,
                                     Moves::possibleMoves[i][j + k + 1] );

              if( hasReachedPuck )
              {
                for( short p : puckPos )
                {
                  if( p == -1 ) break;
                  to_visit.back().back().flipPuck( p );
                }

                // TODO handle series removal search
                break;
              }
            }

            j = nextJ;
          }
        }

        index_stack.push_back( index + 1 );
        index = 0;
        ++current_depth;
      }

      to_visit.pop_back();

      --current_depth;
    }
  }

  // BFS style tree creation
  void getNextMove( const Board& board, bool isWhite )
  {
    std::vector<Board> boards{ board };

    int32_t depth = 0;
    int32_t range_begin = 0;
    int32_t range_end = 1;
    while( depth < 5 )
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
    printf("%d", boards.size());
  }

  void getSuccessors( const Board& board, const bool isWhite ) {}

  // given a color, check if the board is a good winning position
  int evaluate( Board& b, const bool isWhite )
  {
    // Place the value of the board in the first 12 bit
    // Take first
    int value = 0;
    for( int i = 0; i < Board::num_pos; ++i )
    {
      if( b.hasRing( isWhite, i ) )
        reinterpret_cast<int64_t>(&b) -= 10;
      else if( b.hasRing( i ) )
        reinterpret_cast<int64_t>(&b) += 10;
      else if( b.hasPuck( isWhite, i ) )
        reinterpret_cast<int64_t>(&b) += 1;
      else if( b.hasPuck( i ) )
        reinterpret_cast<int64_t>(&b) -= 1;
    }

    return 0;
  }
}  // namespace ai

