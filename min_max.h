
#ifndef MIN_MAX_H_
#define MIN_MAX_H_

#include <board.h>

namespace ai
{
  void getNextMove( const Board& board, bool isWhite );

  void getNextMoveDFS( const Board& board, bool isWhite);

  void getSuccessors( const Board& board, bool isWhite );

  int evaluate( Board& board, bool isWhite );

}  // namespace ai

#endif  // MIN_MAX_H_
