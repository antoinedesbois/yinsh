
#include <gameState.h>

namespace
{
  bool isValidPos( const int pos )
  {
    return pos >= 0 && pos < Board::num_pos;
  }

  int countRings( const bool color, const Board& board )
  {
    int count = 0;
    for( int i = 0; i < Board::num_pos; ++i )
    {
      if( board.hasRing( color, i ) ) ++count;
    }
    return count;
  }

  bool hasSeries( const Board& board )
  {
    for( int i = 0; i < Board::num_pos; ++i )
    {
      if( board.hasSeries( i ) )
      {
        return true;
      }
    }
    return false;
  }
}  // namespace

GameState::GameState()
    : m_board(),
      m_hasSerie(),
      m_isWhiteTurn( true ),
      m_isRingPlacementPhase( true ),
      m_isGameOver( false ),
      m_isDraw( false )
{
}

bool GameState::placeRing( const bool color, const int pos )
{
  assert( !m_hasSerie );
  if( color != m_isWhiteTurn || !m_isRingPlacementPhase || !isValidPos( pos ) ||
      m_board.hasRing( pos ) )
  {
    return false;
  }

  m_board.setRing( m_isWhiteTurn, pos );
  changeTurn();

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
      !isValidPos( endPos ) || !m_board.hasRing( m_isWhiteTurn, initialPos ) ||
      m_hasSerie )
  {
    return false;
  }

  short i = 0;
  while( i < 32 )
  {
    const short size = Moves::possibleMoves[initialPos][i];
    if( size < 0 ) return false;
    if( size == 0 )
    {
      i = i + 1;
      continue;
    }

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

        // Check if we have created any series by flipping pucks or moving the
        // ring
        m_hasSerie = m_board.hasSeries( initialPos );
        for( int p = 0; p < puckIdx && !m_hasSerie; ++p )
        {
          m_hasSerie = m_board.hasSeries( puckPos[p] );
        }

        changeTurn();
        return true;
      }
    }

    i = nextI;
  }

  return false;
}
bool GameState::removeSeries( const bool color,
                              const std::array<int, 5> puckPos,
                              const int ringPos )
{
  if( !m_hasSerie ) return false;

  // All puck must be the color we want to remove
  for( int i : puckPos )
  {
    if( !hasPuck( color, i ) ) return false;
  }

  if( !hasRing( color, ringPos ) ) return false;

  // Make sure puck are in an actual contiguous line
  short i = 0;
  while( i < 32 )
  {
    const short size = Moves::possibleMoves[puckPos[0]][i];
    if( size < 1 ) return false;

    int puckIdx = 1;
    for( int j = 0; j < size; ++j )
    {
      if( Moves::possibleMoves[puckPos[0]][i + j + 1] == puckPos[puckIdx] )
      {
        puckIdx++;
      }
      else  // We know this direction doesn't contain de series
      {
        break;
      }
    }

    if( puckIdx == 5 )
    {
      for( int p : puckPos )
      {
        m_board.removePuck( p );
      }
      m_board.removeRing( ringPos );

      // We have to keep playing till no series on the board
      m_hasSerie = hasSeries( m_board );

      // End game logic
      const int whiteRingCount = countRings( true, m_board );
      const int blackRingCount = countRings( false, m_board );
      if( whiteRingCount < 3 && blackRingCount < 3 )
      {
        m_isDraw = true;
        m_isGameOver = true;
        return true;
      }

      m_isGameOver =
          !m_hasSerie && ( whiteRingCount < 3 || blackRingCount < 3 );
      if( whiteRingCount < 3 ) m_isWhiteTurn = true;
      return true;
    }
    i += size + 1;
  }

  return false;
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

#ifndef NDEBUG
#include <iostream>
void GameState::dump() const
{
  for( int i = 0; i < 85; ++i )
  {
    std::cout << i << " : " << m_board.getColor( i ) << " : "
              << ( m_board.hasPuck( i ) ? "p"
                                        : m_board.hasRing( i ) ? "r" : " " )
              << std::endl;
  }
}
#endif

void GameState::changeTurn()
{
  m_isWhiteTurn = !m_isWhiteTurn;
}

