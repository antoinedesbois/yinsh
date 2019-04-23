

#include <gameState.h>
#include <gtest/gtest.h>

namespace
{
  constexpr bool white = true;
  constexpr bool black = false;

  // white rings -> [0,2,4,5,8]
  // black rings -> [1,3,5,7,9]
  GameState createGameState()
  {
    GameState state;
    EXPECT_TRUE( state.placeRing( true, 0 ) );
    EXPECT_TRUE( state.placeRing( false, 1 ) );
    EXPECT_TRUE( state.placeRing( true, 2 ) );
    EXPECT_TRUE( state.placeRing( false, 3 ) );
    EXPECT_TRUE( state.placeRing( true, 4 ) );
    EXPECT_TRUE( state.placeRing( false, 5 ) );
    EXPECT_TRUE( state.placeRing( true, 6 ) );
    EXPECT_TRUE( state.placeRing( false, 7 ) );
    EXPECT_TRUE( state.placeRing( true, 8 ) );
    EXPECT_TRUE( state.placeRing( false, 9 ) );
    EXPECT_FALSE( state.isRingPlacementPhase() );
    EXPECT_TRUE( state.isWhiteTurn() );

    return state;
  }
}  // namespace

TEST( defaultGameState, asExpected )
{
  const GameState defaultState;

  EXPECT_TRUE( defaultState.isWhiteTurn() );
  EXPECT_TRUE( defaultState.isRingPlacementPhase() );
  EXPECT_FALSE( defaultState.isGameOver() );

  // Make sure the board is empty
  for( int i = 0; i < Board::num_pos; ++i)
  {
    EXPECT_FALSE( defaultState.hasRing( i ) );
    EXPECT_FALSE( defaultState.hasPuck( i ) );
  }
}

TEST( placeRing, asExpected )
{
  GameState state;
  EXPECT_TRUE( state.placeRing( white, 0 ) );
  EXPECT_TRUE( state.placeRing( black, 1 ) );

  EXPECT_TRUE( state.hasRing( white, 0 ) );
  EXPECT_TRUE( state.hasRing( black, 1 ) );
}

TEST( placeWhiteRingTwice, shouldFail )
{
  GameState state;
  EXPECT_TRUE( state.placeRing( white, 0 ) );
  EXPECT_FALSE( state.placeRing( white, 0 ) );

  EXPECT_TRUE( state.hasRing( white, 0 ) );
}

TEST( placeTwoRingOnSameLocation, shouldFail )
{
  GameState state;

  EXPECT_TRUE( state.placeRing( white, 0 ) );
  EXPECT_FALSE( state.placeRing( black, 0 ) );

  EXPECT_TRUE( state.hasRing( white, 0 ) );
  EXPECT_FALSE( state.hasRing( black, 0 ) );
}

TEST( placeRingAfterPlacementPhase, shouldPhase )
{
  GameState state;
  for( int i = 0; i < 10; ++i )
  {
    EXPECT_TRUE( state.placeRing( i % 2 == 0, i ) );
  }

  EXPECT_FALSE( state.placeRing( white, 50 ) );
  EXPECT_FALSE( state.placeRing( black, 51 ) );

  EXPECT_FALSE( state.isRingPlacementPhase() );
}

TEST( moveRingNoCrossOver, asExpected )
{
  GameState state = createGameState();

  EXPECT_TRUE( state.moveRing( true, 8, 74 ) );
  EXPECT_TRUE( state.hasPuck( true, 8 ) );
  EXPECT_FALSE( state.hasRing( 8 ) );
  EXPECT_TRUE( state.hasRing( true, 74 ) );

  EXPECT_TRUE( state.moveRing( false, 9, 26 ) );
  EXPECT_TRUE( state.hasPuck( false, 9 ) );
  EXPECT_FALSE( state.hasRing( 9 ) );
  EXPECT_TRUE( state.hasRing( false, 26 ) );

  EXPECT_TRUE( state.moveRing( true, 74, 78 ) );
  EXPECT_TRUE( state.hasPuck( true, 74 ) );
  EXPECT_FALSE( state.hasRing( 74 ) );
  EXPECT_TRUE( state.hasRing( true, 78 ) );

  EXPECT_TRUE( state.moveRing( false, 26, 18 ) );
  EXPECT_TRUE( state.hasPuck( false, 26 ) );
  EXPECT_FALSE( state.hasRing( 26 ) );
  EXPECT_TRUE( state.hasRing( false, 18 ) );

  EXPECT_TRUE( state.moveRing( true, 78, 77 ) );
  EXPECT_TRUE( state.hasPuck( true, 78 ) );
  EXPECT_FALSE( state.hasRing( 78 ) );
  EXPECT_TRUE( state.hasRing( true, 77 ) );

  EXPECT_TRUE( state.moveRing( false, 18, 35 ) );
  EXPECT_TRUE( state.hasPuck( false, 18 ) );
  EXPECT_FALSE( state.hasRing( 18 ) );
  EXPECT_TRUE( state.hasRing( false, 35 ) );
}

TEST( moveRingAfterPucks, asExpected )
{
  GameState state = createGameState();

  // Create a line of white puck at [8, 16, 25]
  // We will move the white ring at 2 over that line
  // We expect the puck to change color
  EXPECT_TRUE( state.moveRing( true, 8, 16 ) );
  EXPECT_TRUE( state.moveRing( false, 9, 17 ) );

  EXPECT_TRUE( state.moveRing( true, 16, 25 ) );
  EXPECT_TRUE( state.moveRing( false, 17, 26 ) );

  EXPECT_TRUE( state.moveRing( true, 25, 19 ) );
  EXPECT_TRUE( state.moveRing( false, 26, 36 ) );

  EXPECT_TRUE( state.moveRing( true, 2, 35 ) );

  // Check that the puck have changed color
  EXPECT_TRUE( state.hasPuck( false, 8 ) );
  EXPECT_TRUE( state.hasPuck( false, 16 ) );
  EXPECT_TRUE( state.hasPuck( false, 25 ) );
}

TEST( moveRingTwoPositionAfterPucks, shouldFail )
{
  GameState state = createGameState();

  // Create a line of white puck at [8, 16, 25]
  // We will move the white ring at pos 2 over that line
  // We expect this operation to fail because it should only be permitted to
  // move 1 position after a puck
  EXPECT_TRUE( state.moveRing( true, 8, 16 ) );
  EXPECT_TRUE( state.moveRing( false, 9, 17 ) );

  EXPECT_TRUE( state.moveRing( true, 16, 25 ) );
  EXPECT_TRUE( state.moveRing( false, 17, 26 ) );

  EXPECT_TRUE( state.moveRing( true, 25, 19 ) );
  EXPECT_TRUE( state.moveRing( false, 26, 36 ) );

  EXPECT_FALSE( state.moveRing( true, 2, 45 ) );

  // Check that the pucks have not changed color
  EXPECT_TRUE( state.hasPuck( true, 8 ) );
  EXPECT_TRUE( state.hasPuck( true, 16 ) );
  EXPECT_TRUE( state.hasPuck( true, 25 ) );
}

TEST( createSeries, shouldHasToRemoveSeries )
{
}

int main( int argc, char* argv[] )
{
  ::testing::InitGoogleTest( &argc, argv );
  return RUN_ALL_TESTS();
}

