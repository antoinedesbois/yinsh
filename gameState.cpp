
#include <gameState.h>

namespace
{
  bool isValidPos( const int pos )
  {
    return pos >= 0 && pos < Board::num_pos;
  }
}  // namespace

GameState::GameState()
    : m_board(),
      m_isWhiteTurn( true ),
      m_isRingPlacementPhase( true ),
      m_isGameOver( false )
{
}

bool GameState::placeRing( const bool color, const int pos )
{
  if( color != m_isWhiteTurn || !m_isRingPlacementPhase || !isValidPos( pos ) ||
      m_board.hasRing( pos ) )
  {
    return false;
  }

  m_board.setRing( m_isWhiteTurn, pos );
  m_isWhiteTurn = !m_isWhiteTurn;

  int numRing = 0;
  for( int pos = 0; pos < Board::num_pos; ++pos )
  {
    numRing += m_board.hasRing( pos ) ? 1 : 0;
  }
  assert( numRing <= 10 );

  if( numRing == 10 )
  {
    m_isRingPlacementPhase = false;
  }
  return true;
}

bool GameState::moveRing( const bool color, const int initialPos,
                          const int endPos )
{
  if( color != m_isWhiteTurn || !isValidPos( initialPos ) ||
      !isValidPos( endPos ) || !m_board.hasRing( m_isWhiteTurn, initialPos ) )
  {
    return false;
  }

  short i = 0;
  while( i < 32 )
  {
    const short size = Moves::possibleMoves[initialPos][i];
    if( size < 1 ) return false;

    const short nextI = i + size + 1;
    bool hasReachedPuck = false;
    std::array<short, 9> puckPos = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
    int puckIdx = 0;

    for( int j = 0; j < size; ++j )
    {
      if( m_board.hasRing( Moves::possibleMoves[initialPos][i + j + 1] ) )
      {
        break;
      }
      if( m_board.hasPuck( Moves::possibleMoves[initialPos][i + j + 1] ) )
      {
        hasReachedPuck = true;
        puckPos[puckIdx] = Moves::possibleMoves[initialPos][i + j + 1];
        ++puckIdx;
        continue;
      }

      if( hasReachedPuck &&
          static_cast<int>( Moves::possibleMoves[initialPos][i + j + 1] ) !=
              endPos )
      {
        break;
      }

      if( static_cast<int>( Moves::possibleMoves[initialPos][i + j + 1] ) ==
          endPos )
      {
        // we can execute the move
        for( int p = 0; p < puckIdx; ++p )
        {
          m_board.flipPuck( puckPos[p] );
        }

        m_board.removeRing( initialPos );
        m_board.setPuck( color, initialPos );
        m_board.setRing( color, endPos );

        // Might have created a series, do not switch turn if it is the case
        if( !m_board.hasSeries( initialPos ) )
        {
          m_isWhiteTurn = !m_isWhiteTurn;
        }
        return true;
      }
    }

    i = nextI;
  }

  return false;
}
bool GameState::removeSeries( const bool color, const std::array<int, 5> puckPos,
                              const int ringPos )
{
  // TODO check if every specified position in is a straight line
  // Make sure the colors match
  return true;
}

bool GameState::isWhiteTurn() const
{
  return m_isWhiteTurn;
}

bool GameState::isRingPlacementPhase() const
{
  return m_isRingPlacementPhase;
}

bool GameState::isGameOver() const
{
  return m_isGameOver;
}

bool GameState::hasRing( const int pos ) const
{
  return m_board.hasRing( pos );
}

bool GameState::hasRing( const bool color, const int pos ) const
{
  return m_board.hasRing( color, pos );
}

bool GameState::hasPuck( const int pos ) const
{
  return m_board.hasPuck( pos );
}

bool GameState::hasPuck( const bool color, const int pos ) const
{
  return m_board.hasPuck( color, pos );
}

