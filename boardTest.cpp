
#include <gtest/gtest.h>
#include <board.h>

TEST( emptyBoard, shouldBeEmpty )
{
  Board board;
  for( int i = 0; i < Board::num_pos; ++i )
  {
    EXPECT_FALSE( board.hasPuck( i ) );
    EXPECT_FALSE( board.hasRing( i ) );
  }
}

TEST( setEvenPuck, asExpected )
{
  Board b;
  b.setPuck( 0 );
  EXPECT_TRUE( b.hasPuck( 0 ) );

  for( int i = 1; i < Board::num_pos; ++i )
  {
    EXPECT_FALSE( b.hasPuck( i ) );
  }
}

TEST( setOddPuck, asExpected )
{
  Board b;
  b.setPuck( 1 );
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
  b.setPuck( 1 );
  b.setPuck( 0 );
  EXPECT_TRUE( b.hasPuck( 1 ) );
  EXPECT_TRUE( b.hasPuck( 0 ) );

  for( int i = 0; i < Board::num_pos; ++i )
  {
    if( i == 0 || i == 1 ) continue;
    EXPECT_FALSE( b.hasPuck( i ) );
  }
}

TEST( setEvenRing, asExpected )
{
  Board b;
  b.setRing( 0 );
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
  b.setRing( oddPos );
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
  b.setRing( evenPos );
  b.setRing( oddPos );
  EXPECT_TRUE( b.hasRing( evenPos ) );
  EXPECT_TRUE( b.hasRing( oddPos ) );

  for( int i = 0; i < Board::num_pos; ++i )
  {
    if( i == evenPos || i == oddPos ) continue;
    EXPECT_FALSE( b.hasRing( i ) );
  }
}

int main( int argc, char* argv[] )
{
  ::testing::InitGoogleTest( &argc, argv );
  return RUN_ALL_TESTS();
}

