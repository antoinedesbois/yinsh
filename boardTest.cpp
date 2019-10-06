
#include <gtest/gtest.h>
#include <board.h>

namespace
{
  constexpr bool defaultColor = false;
  constexpr bool secondColor = true;

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
  b1.setRing( defaultColor, 13 );
  b1.setPuck( defaultColor, 60 );

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
  b1.setRing( defaultColor, 13 );
  b1.setPuck( defaultColor, 60 );
  Board b2( b1 );

  EXPECT_TRUE( b1 == b2 );
  b2.setRing( defaultColor, 10 );

  EXPECT_FALSE( b1 == b2 );
}

TEST( setEvenPuck, asExpected )
{
  Board b;
  b.setPuck( defaultColor, 0 );
  EXPECT_TRUE( b.hasPuck( defaultColor, 0 ) );

  for( int i = 1; i < Board::num_pos; ++i )
  {
    EXPECT_FALSE( b.hasPuck( i ) );
  }
}

TEST( setOddPuck, asExpected )
{
  Board b;
  b.setPuck( defaultColor, 1 );
  EXPECT_TRUE( b.hasPuck( defaultColor, 1 ) );

  for( int i = 0; i < Board::num_pos; ++i )
  {
    if( i == 1 ) continue;
    EXPECT_FALSE( b.hasPuck( i ) );
  }
}

TEST( setEvenAndOddPuckSameByte, setGetPuck_AsExpected )
{
  Board b;
  b.setPuck( defaultColor, 1 );
  b.setPuck( defaultColor, 0 );
  EXPECT_TRUE( b.hasPuck( defaultColor, 1 ) );
  EXPECT_TRUE( b.hasPuck( defaultColor, 0 ) );

  for( int i = 0; i < Board::num_pos; ++i )
  {
    if( i == 0 || i == 1 ) continue;
    EXPECT_FALSE( b.hasPuck( i ) );
  }
}

TEST( setPuckOnPuck, shouldCrash )
{
  Board b;
  b.setPuck( defaultColor, 0 );
#ifndef NDEBUG
  EXPECT_DEATH( b.setPuck( defaultColor, 0 ), "" );
#else
  b.setPuck( secondColor, 0 );
  EXPECT_TRUE( b.hasPuck( secondColor, 0 ) );
#endif
}

TEST( setPuckOnRing, shouldCrash )
{
  Board b;
  b.setRing( defaultColor, 0 );
#ifndef NDEBUG
  EXPECT_DEATH( b.setPuck( defaultColor, 0 ), "" );
#else
  b.setPuck( defaultColor, 0 );
  EXPECT_TRUE( b.hasPuck( defaultColor, 0 ) );
#endif
}

TEST( setEvenRing, asExpected )
{
  Board b;
  b.setRing( defaultColor, 0 );
  EXPECT_TRUE( b.hasRing( defaultColor, 0 ) );

  for( int i = 1; i < Board::num_pos; ++i )
  {
    EXPECT_FALSE( b.hasRing( i ) );
  }
}

TEST( setOddRing, asExpected )
{
  const int oddPos = 7;
  Board b;
  b.setRing( defaultColor, oddPos );
  EXPECT_TRUE( b.hasRing( defaultColor, oddPos ) );

  for( int i = 1; i < Board::num_pos; ++i )
  {
    if( i == oddPos ) continue;
    EXPECT_FALSE( b.hasRing( i ) );
  }
}

TEST( setRingWithColor, asExpected )
{
  Board b;
  b.setRing( defaultColor, 0 );
  b.setRing( secondColor, 1 );

  EXPECT_TRUE( b.hasRing( defaultColor, 0 ) );
  EXPECT_TRUE( b.hasRing( secondColor, 1 ) );

  for( int i = 2; i < Board::num_pos; ++i )
  {
    EXPECT_FALSE( b.hasRing( i ) );
  }
}

TEST( setEvenAndOddRingSameByte, asExpected )
{
  const int evenPos = 72;
  const int oddPos = 73;
  Board b;
  b.setRing( defaultColor, evenPos );
  b.setRing( defaultColor, oddPos );
  EXPECT_TRUE( b.hasRing( defaultColor, evenPos ) );
  EXPECT_TRUE( b.hasRing( defaultColor, oddPos ) );

  for( int i = 0; i < Board::num_pos; ++i )
  {
    if( i == evenPos || i == oddPos ) continue;
    EXPECT_FALSE( b.hasRing( i ) );
  }
}

TEST( removeRingOdd, asExpected )
{
  Board b;
  b.setRing( defaultColor, 0 );
  EXPECT_TRUE( b.hasRing( defaultColor, 0 ) );
  b.removeRing( 0 );
  EXPECT_FALSE( b.hasRing( 0 ) );
}

TEST( setRingOnPuck, shouldCrash )
{
  Board b;
  b.setPuck( defaultColor, 60 );
#ifndef NDEBUG
  EXPECT_DEATH( b.setRing( defaultColor, 60 ), "" );
#else
  b.setRing( defaultColor, 60 );
  EXPECT_TRUE( b.hasRing( defaultColor, 60 ) );
#endif
}

TEST( setRingOnRing, shouldCrash )
{
  Board b;
  b.setRing( defaultColor, 60 );
#ifndef NDEBUG
  EXPECT_DEATH( b.setRing( secondColor, 60 ), "" );
#else
  b.setRing( defaultColor, 60 );
  EXPECT_TRUE( b.hasRing( defaultColor, 60 ) );
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

TEST( hasSeriesWhenNoSeries, asExpected )
{
  Board b;
  for( int i = 0; i < Board::num_pos; ++i )
  {
    EXPECT_FALSE( b.hasSeries( i ) );
  }
}

TEST( hasSeriesWhenSinglePuck, asExpected )
{
  Board b;
  b.setPuck( true, 50 );
  EXPECT_FALSE( b.hasSeries( 50 ) );
}

TEST( hasSeriesWhenThereIsOne, asExpected )
{
  Board b;
  b.setPuck(true, 42);
  b.setPuck(true, 41);
  b.setPuck(true, 40);
  b.setPuck(true, 39);
  b.setPuck(true, 38);

  EXPECT_TRUE( b.hasSeries(true, 42) );
  EXPECT_TRUE( b.hasSeries(true, 41) );
  EXPECT_TRUE( b.hasSeries(true, 40) );
  EXPECT_TRUE( b.hasSeries(true, 39) );
  EXPECT_TRUE( b.hasSeries(true, 38) );
}

TEST( flipPuck, asExpected )
{
  Board b;
  b.setPuck( defaultColor, 10 );
  b.flipPuck( 10 );
  EXPECT_TRUE( b.hasPuck( secondColor, 10 ) );
  b.flipPuck( 10 );
  EXPECT_TRUE( b.hasPuck( defaultColor, 10 ) );
}

int main( int argc, char* argv[] )
{
  ::testing::InitGoogleTest( &argc, argv );
  return RUN_ALL_TESTS();
}

