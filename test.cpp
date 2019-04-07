
#include <gtest/gtest.h>
#include <board.h>

TEST( emptyBoard, shouldBeEmpty ) 
{
  Board board;
  for (int i = 0; i < 85; ++i)
  {
    EXPECT_FALSE(board.hasPuck(i));
    EXPECT_FALSE(board.hasRing(i));
  }
}

TEST( settingPuck, setGetPuck_AsExpected ) {}

int main( int argc, char* argv[] )
{
  ::testing::InitGoogleTest( &argc, argv );
  return RUN_ALL_TESTS();
}
