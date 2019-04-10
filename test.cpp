
#include <gtest/gtest.h>
#include <board.h>

TEST( emptyBoard, shouldBeEmpty )
{
  Board board;
  for( int i = 0; i < 85; ++i )
  {
    EXPECT_FALSE( board.hasPuck( i ) );
    EXPECT_FALSE( board.hasRing( i ) );
  }
}

TEST(setEvenPuck, asExpected)
{
  Board b;
  b.setPuck( 0 );
  EXPECT_TRUE(b.hasPuck(0));

  for (int i = 1; i < 85; ++i)
  {
    EXPECT_FALSE(b.hasPuck(i));
  }
}

TEST(setOddPuck, asExpected)
{
  Board b;
  b.setPuck( 1 );
  EXPECT_TRUE(b.hasPuck(1));


  for (int i = 0; i < 85; ++i)
  {
    if (i == 1) continue;
    EXPECT_FALSE(b.hasPuck(i));
  }

}


TEST( settingEvenAndOddPuckSameByte, setGetPuck_AsExpected )
{
  Board b;
  b.setPuck( 1 );
  b.setPuck( 0 );
  EXPECT_TRUE( b.hasPuck( 1 ) );
  EXPECT_TRUE( b.hasPuck( 0 ) );

  for (int i = 0; i < 85; ++i)
  {
    if (i == 0 || i == 1) continue;
    EXPECT_FALSE(b.hasPuck(i));
  }
}

int main( int argc, char* argv[] )
{
  ::testing::InitGoogleTest( &argc, argv );
  return RUN_ALL_TESTS();
}

TEST( removingPuck, removingPuck_AsExpected )
{
  Board b;
  b.setPuck( 0 );

  EXPECT_TRUE( b.hasPuck( 0 ) );
}

