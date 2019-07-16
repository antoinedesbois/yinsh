

#include <board.h>
#include <bitset>

class GameState
{
 public:
   GameState();

   bool placeRing(bool color, int pos);
   bool moveRing(bool color, int initialPos, int endPos);

   // This is the action of removing a series and a ring
   bool removeSeries(bool color, std::array<int, 5> puckPos, int ringPos);

   bool isWhiteTurn() const;
   bool isRingPlacementPhase() const;
   bool isGameOver() const;

   bool hasRing(int pos) const;
   bool hasRing(bool color, int pos) const;
   bool hasPuck(int pos) const;
   bool hasPuck(bool color, int pos) const;
 
 private:
   inline void changeTurn();
  
 private:
  Board m_board;
  bool m_isWhiteTurn;
  bool m_isRingPlacementPhase;
  bool m_isGameOver;
};

