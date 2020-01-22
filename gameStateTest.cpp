

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
  for( int i = 0; i < Board::num_pos; ++i )
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

TEST( createSeries, hasToRemoveSeries )
{
  GameState state = createGameState();

  const std::array<int, 5> puckPosWhite = {8, 15, 23, 32, 41};
  const std::array<int, 5> puckPosBlack = {9, 16, 24, 33, 42};
  EXPECT_TRUE( state.moveRing( true, puckPosWhite[0], puckPosWhite[1] ) );
  EXPECT_TRUE( state.moveRing( false, 9, 16 ) );

  EXPECT_TRUE( state.moveRing( true, puckPosWhite[1], puckPosWhite[2] ) );
  EXPECT_TRUE( state.moveRing( false, 16, 24 ) );

  EXPECT_TRUE( state.moveRing( true, puckPosWhite[2], puckPosWhite[3] ) );
  EXPECT_TRUE( state.moveRing( false, 24, 33 ) );

  EXPECT_TRUE( state.moveRing( true, puckPosWhite[3], puckPosWhite[4] ) );
  EXPECT_TRUE( state.moveRing( false, 33, 42 ) );

  EXPECT_TRUE( state.moveRing( true, puckPosWhite[4], 50 ) );

  EXPECT_FALSE( state.isWhiteTurn() );
  EXPECT_FALSE( state.isGameOver() );

  // White now has a series, black shouldn't be allowed to play
  EXPECT_FALSE( state.moveRing( false, 42, 51 ) );

  const int ringToRemoveIdxWhite = 0;
  EXPECT_TRUE( state.removeSeries( true, puckPosWhite, ringToRemoveIdxWhite ) );
  EXPECT_FALSE( state.hasRing( ringToRemoveIdxWhite ) );
  EXPECT_FALSE( state.isWhiteTurn() );
  for( int i : puckPosWhite )
  {
    EXPECT_FALSE( state.hasPuck( i ) );
  }

  EXPECT_TRUE( state.moveRing( false, 42, 51 ) );

  const int ringToRemoveIdxBlack = 1;
  EXPECT_TRUE(
      state.removeSeries( false, puckPosBlack, ringToRemoveIdxBlack ) );
  EXPECT_TRUE( state.isWhiteTurn() );
  EXPECT_FALSE( state.isGameOver() );
  for( int i : puckPosBlack )
  {
    EXPECT_FALSE( state.hasPuck( i ) );
  }
}

TEST( playFullGame3, asExpected )
{
  GameState state;
  EXPECT_TRUE( state.placeRing( true, 47 ) );
  EXPECT_TRUE( state.placeRing( false, 42 ) );
  EXPECT_TRUE( state.placeRing( true, 4 ) );
  EXPECT_TRUE( state.placeRing( false, 52 ) );
  EXPECT_TRUE( state.placeRing( true, 3 ) );
  EXPECT_TRUE( state.placeRing( false, 43 ) );
  EXPECT_TRUE( state.placeRing( true, 37 ) );
  EXPECT_TRUE( state.placeRing( false, 51 ) );
  EXPECT_TRUE( state.placeRing( true, 84 ) );
  EXPECT_TRUE( state.placeRing( false, 32 ) );
  EXPECT_FALSE( state.isRingPlacementPhase() );

  EXPECT_TRUE( state.moveRing( true, 4, 5 ) );
  EXPECT_TRUE( state.moveRing( false, 42, 33 ) );
  EXPECT_TRUE( state.moveRing( true, 5, 6 ) );
  EXPECT_TRUE( state.moveRing( false, 32, 8 ) );
  EXPECT_TRUE( state.moveRing( true, 3, 9 ) );
  EXPECT_TRUE( state.moveRing( false, 33, 24 ) );
  EXPECT_TRUE( state.moveRing( true, 47, 29 ) );
  EXPECT_TRUE( state.moveRing( false, 43, 34 ) );
  EXPECT_TRUE( state.moveRing( true, 29, 38 ) );
  EXPECT_TRUE( state.moveRing( false, 51, 41 ) );
  EXPECT_TRUE( state.moveRing( true, 6, 53 ) );
  EXPECT_TRUE( state.moveRing( false, 24, 16 ) );
  EXPECT_TRUE( state.moveRing( true, 38, 28 ) );
  EXPECT_TRUE( state.moveRing( false, 41, 59 ) );
  EXPECT_TRUE( state.moveRing( true, 84, 31 ) );
  EXPECT_TRUE( state.moveRing( false, 59, 19 ) );
  EXPECT_TRUE( state.moveRing( true, 31, 22 ) );
  EXPECT_TRUE( state.moveRing( false, 19, 21 ) );
  EXPECT_TRUE( state.moveRing( true, 22, 40 ) );
  EXPECT_TRUE( state.moveRing( false, 21, 30 ) );
  EXPECT_TRUE( state.moveRing( true, 28, 11 ) );
  EXPECT_TRUE( state.moveRing( false, 30, 20 ) );
  EXPECT_TRUE( state.moveRing( true, 11, 12 ) );
  EXPECT_TRUE( state.moveRing( false, 16, 60 ) );
  EXPECT_TRUE( state.removeSeries( false, {29, 30, 31, 32, 33}, 52 ) );

  EXPECT_TRUE( state.moveRing( true, 53, 33 ) );
  EXPECT_TRUE( state.moveRing( false, 8, 7 ) );
  EXPECT_TRUE( state.moveRing( true, 12, 17 ) );
  EXPECT_TRUE( state.moveRing( false, 7, 1 ) );
  EXPECT_TRUE( state.moveRing( true, 17, 15 ) );
  EXPECT_TRUE( state.moveRing( false, 1, 13 ) );
  EXPECT_TRUE( state.moveRing( true, 33, 29 ) );
  EXPECT_TRUE( state.moveRing( false, 20, 30 ) );
  EXPECT_TRUE( state.moveRing( true, 29, 39 ) );
  EXPECT_TRUE( state.moveRing( false, 13, 32 ) );
  EXPECT_TRUE( state.moveRing( true, 15, 23 ) );
  EXPECT_TRUE( state.moveRing( false, 30, 31 ) );
  EXPECT_TRUE( state.removeSeries( false, {30, 21, 13, 6, 1}, 60 ) );

  EXPECT_TRUE( state.moveRing( true, 39, 1 ) );
  EXPECT_TRUE( state.moveRing( false, 32, 52 ) );
  EXPECT_TRUE( state.moveRing( true, 9, 60 ) );
  EXPECT_TRUE( state.moveRing( false, 31, 61 ) );
  EXPECT_TRUE( state.moveRing( true, 23, 50 ) );
  EXPECT_TRUE( state.moveRing( false, 52, 13 ) );
  EXPECT_TRUE( state.moveRing( true, 37, 18 ) );
  EXPECT_TRUE( state.moveRing( false, 13, 21 ) );
  EXPECT_TRUE( state.moveRing( true, 40, 30 ) );
  EXPECT_TRUE( state.moveRing( false, 21, 25 ) );
  EXPECT_TRUE( state.removeSeries( false, {13, 22, 32, 42, 52}, 25 ) );

  EXPECT_TRUE( state.isGameOver() );
}

int main( int argc, char* argv[] )
{
  ::testing::InitGoogleTest( &argc, argv );
  return RUN_ALL_TESTS();
}

