
#include <gtest/gtest.h>
#include <min_max.h>

TEST( evaluate, fiveRings_asExpected )
{
  Board2 b;
  b.setRing( 0, 0 );
  b.setRing( 1, 1 );
  b.setRing( 2, 2 );
  b.setRing( 3, 3 );
  b.setRing( 4, 4 );

  b.setRing( 5, 5 );
  b.setRing( 6, 6 );
  b.setRing( 7, 7 );
  b.setRing( 8, 8 );
  b.setRing( 9, 9 );

  EXPECT_EQ( ai::evaluate2( b, true ), 0 );
  EXPECT_EQ( ai::evaluate2( b, false ), 0 );
}

TEST( evaluate, fourWhiteRings_asExpected )
{
  Board2 b;
  b.setRing( 0, 0 );
  b.setRing( 1, 1 );
  b.setRing( 2, 2 );
  b.setRing( 3, 3 );

  b.setRing( 5, 5 );
  b.setRing( 6, 6 );
  b.setRing( 7, 7 );

  EXPECT_EQ( ai::evaluate2( b, true ), 10 );
  EXPECT_EQ( ai::evaluate2( b, false ), 20 );
}

TEST( evaluate, boardWithRings_asExpected )
{
  Board2 b;
  b.setRing( 0, 0 );
  b.setRing( 1, 1 );
  b.setRing( 2, 2 );
  b.setRing( 3, 3 );

  b.setRing( 5, 5 );
  b.setRing( 6, 6 );
  b.setRing( 7, 7 );

  b.setPuck( true, 15 );
  b.setPuck( true, 16 );
  b.setPuck( true, 17 );
  b.setPuck( true, 18 );

  b.setPuck( false, 19 );
  b.setPuck( false, 20 );
  b.setPuck( false, 21 );
  b.setPuck( false, 22 );
  b.setPuck( false, 23 );
  b.setPuck( false, 24 );

  EXPECT_EQ( ai::evaluate2( b, true ), 14 );
  EXPECT_EQ( ai::evaluate2( b, false ), 26 );
}

TEST( evaluate, boardWithRings2_asExpected )
{
  Board2 b;
  b.setRing( 0, 0 );
  b.setRing( 1, 1 );
  b.setRing( 2, 2 );
  b.setRing( 3, 3 );

  b.setRing( 5, 5 );
  b.setRing( 6, 6 );
  b.setRing( 7, 7 );

  b.setPuck( true, 15 );
  b.setPuck( true, 16 );
  b.setPuck( true, 17 );
  b.setPuck( true, 18 );
  b.setPuck( true, 83 );

  b.setPuck( false, 84 );

  EXPECT_EQ( ai::evaluate2( b, true ), 15 );
  EXPECT_EQ( ai::evaluate2( b, false ), 21 );
}

TEST( evaluate, boardWithRings3_asExpected )
{
  Board2 b;
  b.setRing( 0, 0 );
  b.setRing( 1, 1 );
  b.setRing( 2, 2 );
  b.setRing( 3, 3 );

  b.setRing( 5, 5 );
  b.setRing( 6, 6 );
  b.setRing( 7, 7 );

  b.setPuck( true, 15 );
  b.setPuck( true, 16 );
  b.setPuck( true, 17 );
  b.setPuck( true, 18 );
  b.setPuck( true, 78 );
  b.setPuck( true, 79 );
  b.setPuck( true, 80 );
  b.setPuck( true, 81 );
  b.setPuck( true, 82 );
  b.setPuck( true, 83 );

  b.setPuck( false, 72 );
  b.setPuck( false, 73 );
  b.setPuck( false, 74 );
  b.setPuck( false, 75 );
  b.setPuck( false, 76 );
  b.setPuck( false, 77 );
  b.setPuck( false, 84 );

  EXPECT_EQ( ai::evaluate2( b, true ), 20 );
  EXPECT_EQ( ai::evaluate2( b, false ), 27 );
}

TEST( evaluate, boardWithRings4_asExpected )
{
  Board2 b;
  b.setRing( 0, 0 );
  b.setRing( 1, 1 );
  b.setRing( 2, 2 );
  b.setRing( 3, 3 );
  b.setRing( 4, 4 );

  b.setRing( 5, 5 );
  b.setRing( 6, 6 );
  b.setRing( 7, 7 );
  b.setRing( 8, 8 );
  b.setRing( 9, 9 );

  for( int i = 10; i < 85; ++i )
  {
    b.setPuck( true, i );
  }

  EXPECT_EQ( ai::evaluate2( b, true ), 75 );
}

TEST( evaluate, boardWithRings5_asExpected )
{
  Board2 b;
  b.setRing( 0, 0 );
  b.setRing( 1, 1 );
  b.setRing( 2, 2 );
  b.setRing( 3, 3 );
  b.setRing( 4, 4 );

  b.setRing( 5, 5 );
  b.setRing( 6, 6 );
  b.setRing( 7, 7 );
  b.setRing( 8, 8 );
  b.setRing( 9, 9 );

  for( int i = 10; i < 85; ++i )
  {
    b.setPuck( true, i );
  }

  EXPECT_EQ( ai::evaluate2( b, true ), 75 );
}

TEST( evaluate, boardWithRings6_asExpected )
{
  Board2 b;
  b.setRing( 0, 0 );
  b.setRing( 1, 1 );
  b.setRing( 2, 2 );
  b.setRing( 3, 3 );
  b.setRing( 4, 4 );

  b.setRing( 5, 5 );
  b.setRing( 6, 6 );
  b.setRing( 7, 7 );
  b.setRing( 8, 8 );
  b.setRing( 9, 9 );

  for( int i = 10; i < 85; ++i )
  {
    b.setPuck( false, i );
  }

  EXPECT_EQ( ai::evaluate2( b, false ), 75 );
}

int main( int argc, char* argv[] )
{
  ::testing::InitGoogleTest( &argc, argv );
  return RUN_ALL_TESTS();
}