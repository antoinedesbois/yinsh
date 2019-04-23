
#include <gtest/gtest.h>
#include <board.h>

namespace
{
  constexpr Color defaultColor = Color::white;
  constexpr Color secondColor = Color::black;

  // ring [13]
  // puck [60]
  const std::string boardExample1 =
      "000000000000000000000000000000000000000000000000000000000000000000000000"
      "110000000000000000000000000000000000000000000000000000000000000000000000"
      "000000000000000000000000000000000000000000000000000000000000000000000101"
      "000000000000000000000000000000000000000";
}  // namespace

TEST( emptyBoard, shouldBeEmpty )
{
  Board board;
  for( int i = 0; i < Board::num_pos; ++i )
  {
    EXPECT_FALSE( board.hasPuck( i ) );
    EXPECT_FALSE( board.hasRing( i ) );
  }
}

TEST( boardString, asExpected )
{
  Board b( boardExample1 );
  EXPECT_TRUE( b.hasRing( 13 ) );
  EXPECT_TRUE( b.hasPuck( 60 ) );

  for( int i = 0; i < Board::num_pos; ++i )
  {
    if( i != 13 )
    {
      EXPECT_FALSE( b.hasRing( i ) );
    }
    if( i != 60 )
    {
      EXPECT_FALSE( b.hasPuck( i ) );
    }
  }
}

TEST( boardCopy, asExpected )
{
  Board b1;
  b1.setRing( 13, defaultColor );
  b1.setPuck( 60, defaultColor );

  const Board b2( b1 );
  for( int i = 0; i < Board::num_pos; ++i )
  {
    EXPECT_TRUE( b1.hasRing( i ) == b2.hasRing( i ) );
    EXPECT_TRUE( b1.hasPuck( i ) == b2.hasPuck( i ) );
  }
}

TEST( boardOperatorEqual, asExpected )
{
  Board b1;
  b1.setRing( 13, defaultColor );
  b1.setPuck( 60, defaultColor );
  Board b2( b1 );

  EXPECT_TRUE( b1 == b2 );
  b2.setRing( 10, defaultColor );

  EXPECT_FALSE( b1 == b2 );
}

TEST( setEvenPuck, asExpected )
{
  Board b;
  b.setPuck( 0, defaultColor );
  EXPECT_TRUE( b.hasPuck( 0 ) );

  for( int i = 1; i < Board::num_pos; ++i )
  {
    EXPECT_FALSE( b.hasPuck( i ) );
  }
}

TEST( setOddPuck, asExpected )
{
  Board b;
  b.setPuck( 1, defaultColor );
  EXPECT_TRUE( b.hasPuck( 1 ) );

  for( int i = 0; i < Board::num_pos; ++i )
  {
    if( i == 1 ) continue;
    EXPECT_FALSE( b.hasPuck( i ) );
  }
}

TEST( setEvenAndOddPuckSameByte, setGetPuck_AsExpected )
{
  Board b;
  b.setPuck( 1, defaultColor );
  b.setPuck( 0, defaultColor );
  EXPECT_TRUE( b.hasPuck( 1 ) );
  EXPECT_TRUE( b.hasPuck( 0 ) );

  for( int i = 0; i < Board::num_pos; ++i )
  {
    if( i == 0 || i == 1 ) continue;
    EXPECT_FALSE( b.hasPuck( i ) );
  }
}

TEST( setPuckOnPuck, shouldCrash )
{
  Board b;
  b.setPuck( 0, defaultColor );
#ifndef NDEBUG
  EXPECT_DEATH( b.setPuck( 0, secondColor ), "" );
#else
  b.setPuck( 0, secondColor );
  EXPECT_TRUE( b.hasPuck( 0, secondColor ) );
#endif
}

TEST( setPuckOnRing, shouldCrash )
{
  Board b;
  b.setRing( 0, defaultColor );
#ifndef NDEBUG
  EXPECT_DEATH( b.setPuck( 0, defaultColor ), "" );
#else
  b.setPuck( 0, defaultColor );
  EXPECT_TRUE( b.hasPuck( 0, defaultColor ) );
#endif
}

TEST( setEvenRing, asExpected )
{
  Board b;
  b.setRing( 0, defaultColor );
  EXPECT_TRUE( b.hasRing( 0 ) );

  for( int i = 1; i < Board::num_pos; ++i )
  {
    EXPECT_FALSE( b.hasRing( i ) );
  }
}

TEST( setOddRing, asExpected )
{
  const int oddPos = 7;
  Board b;
  b.setRing( oddPos, defaultColor );
  EXPECT_TRUE( b.hasRing( oddPos ) );

  for( int i = 1; i < Board::num_pos; ++i )
  {
    if( i == oddPos ) continue;
    EXPECT_FALSE( b.hasRing( i ) );
  }
}

TEST( setEvenAndOddRingSameByte, asExpected )
{
  const int evenPos = 72;
  const int oddPos = 73;
  Board b;
  b.setRing( evenPos, defaultColor );
  b.setRing( oddPos, defaultColor );
  EXPECT_TRUE( b.hasRing( evenPos ) );
  EXPECT_TRUE( b.hasRing( oddPos ) );

  for( int i = 0; i < Board::num_pos; ++i )
  {
    if( i == evenPos || i == oddPos ) continue;
    EXPECT_FALSE( b.hasRing( i ) );
  }
}

TEST( removeRingOdd, asExpected )
{
  Board b;
  b.setRing( 0, defaultColor );
  EXPECT_TRUE( b.hasRing( 0 ) );
  b.removeRing( 0 );
  EXPECT_FALSE( b.hasRing( 0 ) );
}

TEST( setRingOnPuck, shouldCrash )
{
  Board b;
  b.setPuck( 60, defaultColor );
#ifndef NDEBUG
  EXPECT_DEATH( b.setRing( 60, defaultColor ), "" );
#else
  b.setRing( 60, defaultColor );
  EXPECT_TRUE( b.hasRing( 60, defaultColor ) );
#endif
}

TEST( setRingOnRing, shouldCrash )
{
  Board b;
  b.setRing( 60, defaultColor );
#ifndef NDEBUG
  EXPECT_DEATH( b.setRing( 60, secondColor ), "" );
#else
  b.setRing( 60, defaultColor );
  EXPECT_TRUE( b.hasRing( 60, defaultColor ) );
#endif
}

TEST( removeRingWhereNone, shouldCrash )
{
  Board b;
  EXPECT_FALSE( b.hasRing( 55 ) );
#ifndef NDEBUG
  EXPECT_DEATH( b.removeRing( 55 ), "" );
#else
  b.removeRing( 55 );
  EXPECT_FALSE( b.hasRing( 55 ) );
#endif
}

TEST( flipPuck, asExpected )
{
  Board b;
  b.setPuck( 10, defaultColor );
  b.flipPuck( 10 );
  EXPECT_TRUE( b.hasPuck( 10, secondColor ) );
  b.flipPuck( 10 );
  EXPECT_TRUE( b.hasPuck( 10, defaultColor ) );
}

int main( int argc, char* argv[] )
{
  ::testing::InitGoogleTest( &argc, argv );
  return RUN_ALL_TESTS();
}

