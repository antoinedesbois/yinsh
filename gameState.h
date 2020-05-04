
#ifndef GAME_STATE_H_
#define GAME_STATE_H_

#include <board.h>

#include <bitset>
#include <utility>

class GameState
{
  using Success = bool;
  using IsWhiteWinner = bool;

 public:
  GameState();

  bool placeRing( bool color, int pos );
  bool moveRing( bool color, int initialPos, int endPos );

  // This is the action of removing a series and a ring
  bool removeSeries( bool color, std::array<int, 5> puckPos, int ringPos );

  bool isWhiteTurn() const;
  bool isRingPlacementPhase() const;
  bool isGameOver() const;
  std::pair<Success, IsWhiteWinner> isWhiteWinner();

  bool hasRing( int pos ) const;
  bool hasRing( bool color, int pos ) const;
  bool hasPuck( int pos ) const;
  bool hasPuck( bool color, int pos ) const;

#ifndef NDEBUG
  void dump() const;
#endif
 private:
  inline void changeTurn();

 private:
  Board m_board;
  bool m_hasSerie;
  bool m_isWhiteTurn;
  bool m_isRingPlacementPhase;
  bool m_isGameOver;
  bool m_isDraw;
};

#endif // GAME_STATE_H_
