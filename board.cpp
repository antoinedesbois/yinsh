

#include <board.h>

Board::Board( const std::string& bits ) : m_board( bits ) {}

Board::Board( const Board& b ) : m_board( b.m_board )
{
  assert( isValid( *this ) );
}

Board& Board::operator=( const Board& b )
{
  m_board = b.m_board;
  return *this;
}

bool Board::operator==( const Board& other ) const
{
  return m_board == other.m_board;
}

bool Board::hasRing( const int pos ) const
{
  assert( pos >= 0 && pos < num_pos );
  const int idx = pos * 3;

  return m_board[idx];
}

bool Board::hasRing( const bool isWhite, const int pos ) const
{
  assert( pos >= 0 && pos < num_pos );
  const int idx = pos * 3;

  return m_board[idx] && ( isWhite ? m_board[idx + 2] : !m_board[idx + 2] );
}

void Board::setRing( const bool isWhite, const int pos )
{
  assert( pos >= 0 && pos < num_pos && !hasRing( pos ) && !hasPuck( pos ) );
  const int idx = pos * 3;

  m_board.set( idx );
  isWhite ? m_board.set( idx + 2 ) : m_board.reset( idx + 2 );
}

void Board::removeRing( const int pos )
{
  assert( hasRing( pos ) );
  const int idx = pos * 3;

  m_board.reset( idx );
}

bool Board::hasPuck( const int pos ) const
{
  assert( pos >= 0 && pos < num_pos );
  const int idx = pos * 3;
  return m_board[idx + 1];
}

bool Board::hasPuck( const bool isWhite, const int pos ) const
{
  assert( pos >= 0 && pos < num_pos );
  const int idx = pos * 3;
  return m_board[idx + 1] && ( isWhite ? m_board[idx + 2] : !m_board[idx + 2] );
}

void Board::setPuck( const bool isWhite, const int pos )
{
  assert( pos >= 0 && pos < num_pos && !hasRing( pos ) && !hasPuck( pos ) );
  const int idx = pos * 3;
  m_board.set( idx + 1 );
  isWhite ? m_board.set( idx + 2 ) : m_board.reset( idx + 2 );
}

void Board::removePuck( const int pos )
{
  assert( pos >= 0 && pos < num_pos && hasPuck( pos ) && !hasRing( pos ) );
  const int idx = pos * 3;
  m_board.reset( idx + 1 );
}

void Board::flipPuck( const int pos )
{
  assert( pos >= 0 && pos < num_pos && hasPuck( pos ) && !hasRing( pos ) );
  const int idx = pos * 3;
  m_board.flip( idx + 2 );  // flip the color bit
}

bool Board::hasSeries( const int pos ) const
{
  const bool color = getColor( pos );
  return hasSeries( color, pos );
}

bool Board::hasSeries( const bool color, const int pos ) const
{
  if( !hasPuck( color, pos ) ) return false;

  // We will reset the count for every direction
  // It is initially 1 because "pos" contains a puck
  int count = 1;

  bool up = true;
  int i = 0;
  while( i < 32 )
  {
    const int size = Moves::possibleMoves[pos][i];
    if( size == -1 ) return false;

    const int nextI = i + size + 1;

    for( int j = 0; j < size; ++j )
    {
      if( hasRing( Moves::possibleMoves[pos][i + j + 1] ) ||
          !hasPuck( color, Moves::possibleMoves[pos][i + j + 1] ) )
      {
        break;
      }

      ++count;
    }

    if( count >= 5 ) return true;

    if( !up ) count = 1;
    i = nextI;
    up = !up;
  }

  return false;
}

// returns true if white
bool Board::getColor( const int pos ) const
{
  assert( pos >= 0 && pos < num_pos );
  const int idx = pos * 3;
  return m_board[idx + 2];
}

#ifndef NDEBUG
// Each position must have either a ring, a puck or nothing
bool Board::isValid( const Board& board )
{
  for( int i = 0; i < 85; ++i )
  {
    if( board.hasRing( i ) && board.hasPuck( i ) ) return false;
  }
  return true;
}
#endif

Board2::Board2( const Board2& b ) : m_board( b.m_board ) {}

Board2& Board2::operator=( const Board2& b )
{
  m_board = b.m_board;
  return *this;
}

bool Board2::operator==( const Board2& other ) const
{
  return m_board == other.m_board;
}

bool Board2::hasRing( const uint8_t pos ) const
{
  assert( pos >= 0 && pos < num_pos );
  // white
  return m_board[0] == pos || m_board[1] == pos || m_board[2] == pos ||
         m_board[3] == pos || m_board[4] == pos ||

         // black
         m_board[5] == pos || m_board[6] == pos || m_board[7] == pos ||
         m_board[8] == pos || m_board[9] == pos;
}

bool Board2::hasRing( const bool isWhite, const uint8_t pos ) const
{
  assert( pos >= 0 && pos < num_pos );
  const uint8_t offset = isWhite ? 0 : 5;
  return m_board[0 + offset] == pos || m_board[1 + offset] == pos ||
         m_board[2 + offset] == pos || m_board[3 + offset] == pos ||
         m_board[4 + offset] == pos;
}

void Board2::setRing( const uint8_t index, uint8_t pos )
{
  m_board[index] = pos;
}

void Board2::removeRing( const uint8_t index )
{
  m_board[index] = 0xff;
}

bool Board2::hasPuck( const uint8_t pos ) const
{
  assert( pos >= 0 && pos < num_pos );
  return m_board[10 + pos / 8] & 1 << pos % 8 ||
         m_board[21 + pos / 8] & 1 << pos % 8;
}

bool Board2::hasPuck( const bool isWhite, const uint8_t pos ) const
{
  assert( pos >= 0 && pos < num_pos );
  return isWhite ? m_board[10 + pos / 8] & (1 << pos % 8)
                 : m_board[21 + pos / 8] & (1 << pos % 8);
}

void Board2::setPuck( const bool isWhite, const uint8_t pos )
{
  assert( pos >= 0 && pos < num_pos && !hasRing( pos ) && !hasPuck( pos ) );
  isWhite ? m_board[10 + pos / 8] |= ( 1 << pos % 8 )
          : m_board[21 + pos / 8] |= ( 1 << pos % 8 );
}

void Board2::removePuck( const uint8_t pos )
{
  assert( pos >= 0 && pos < num_pos && hasPuck( pos ) && !hasRing( pos ) );
  m_board[10 + pos / 8] &= ~( 1 << pos % 8 );
  m_board[21 + pos / 8] &= ~( 1 << pos % 8 );
}

void Board2::flipPuck( const uint8_t pos )
{
  assert( pos >= 0 && pos < num_pos && hasPuck( pos ) && !hasRing( pos ) );
  m_board[10 + pos / 8] ^= 1UL << pos % 8;
  m_board[21 + pos / 8] ^= 1UL << pos % 8;
}

// bool Board2::hasSeries( const uint8_t pos ) const
//{
//  const bool color = getColor( pos );
//  return hasSeries( color, pos );
//}
//
// bool Board2::hasSeries( const bool color, const int pos ) const
//{
//  if( !hasPuck( color, pos ) ) return false;
//
//  // We will reset the count for every direction
//  // It is initially 1 because "pos" contains a puck
//  int count = 1;
//
//  bool up = true;
//  int i = 0;
//  while( i < 32 )
//  {
//    const int size = Moves::possibleMoves[pos][i];
//    if( size == -1 ) return false;
//
//    const int nextI = i + size + 1;
//
//    for( int j = 0; j < size; ++j )
//    {
//      if( hasRing( Moves::possibleMoves[pos][i + j + 1] ) ||
//          !hasPuck( color, Moves::possibleMoves[pos][i + j + 1] ) )
//      {
//        break;
//      }
//
//      ++count;
//    }
//
//    if( count >= 5 ) return true;
//
//    if( !up ) count = 1;
//    i = nextI;
//    up = !up;
//  }
//
//  return false;
//}

// returns true if white
// bool Board::getColor( const int pos ) const
//{
//  assert( pos >= 0 && pos < num_pos );
//  const int idx = pos * 3;
//  return m_board[idx + 2];
//}
//
//#ifndef NDEBUG
//// Each position must have either a ring, a puck or nothing
// bool Board::isValid( const Board& board )
//{
//  for( int i = 0; i < 85; ++i )
//  {
//    if( board.hasRing( i ) && board.hasPuck( i ) ) return false;
//  }
//  return true;
//}
//#endif
void Board2::print() const {
 for (int i = 0; i < 32; ++i) {
   printf("%#04x ", m_board[i]);
 }
}

