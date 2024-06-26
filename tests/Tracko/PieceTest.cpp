
#include <gtest/gtest.h>

#include <Tracko/Piece.hpp>


TEST(Tracko_PieceTest, can_be_created_without_blowing_up)
{
   Tracko::Piece piece;
}


TEST(Tracko_PieceTest, fill_counter__initializes_with_zero)
{
   Tracko::Piece piece;
   EXPECT_EQ(0.0f, piece.get_fill_counter());
}


TEST(Tracko_PieceTest, fill_with_amount__will_fill_the_fill_counter_by_the_amount)
{
   al_init();
   Tracko::Piece piece;
   piece.set_tile_type(Tracko::Piece::TileType::TILE_TYPE_HORIZONTAL_BAR);
   piece.initialize();
   piece.reveal();
   piece.fill_with_amount(0.2);
   EXPECT_EQ(0.2f, piece.get_fill_counter());
   al_uninstall_system();
}


TEST(Tracko_PieceTest, fill_with_amount__when_the_fill_does_not_overflow__will_return_false_with_no_overflow_amount)
{
   al_init();
   Tracko::Piece piece;
   piece.set_tile_type(Tracko::Piece::TileType::TILE_TYPE_HORIZONTAL_BAR);
   piece.initialize();
   piece.reveal();

   bool was_filled = false;
   float overflow = 0.0f;
   Tracko::Piece::ConnectingPosition exit_connecting_position =
      Tracko::Piece::ConnectingPosition::CONNECTING_POSITION_UNDEF;
   std::tie(was_filled, overflow, exit_connecting_position) = piece.fill_with_amount(0.8);

   EXPECT_EQ(false, was_filled);
   EXPECT_FLOAT_EQ(0.0f, overflow);
   EXPECT_FLOAT_EQ(0.8f, piece.get_fill_counter());

   EXPECT_EQ(true, piece.is_partially_filled());
   EXPECT_EQ(false, piece.is_filled());
   al_uninstall_system();
}


TEST(Tracko_PieceTest, fill_with_amount__when_the_fill_amount_overflows__will_return_true_with_the_overflow_amount)
{
   al_init();
   Tracko::Piece piece;
   piece.set_tile_type(Tracko::Piece::TileType::TILE_TYPE_HORIZONTAL_BAR);
   piece.initialize();
   piece.reveal();

   piece.set_entrance_connecting_position(Tracko::Piece::ConnectingPosition::CONNECTING_POSITION_LEFT);

   bool was_filled = false;
   float overflow = 0.0f;
   Tracko::Piece::ConnectingPosition exit_connecting_position =
      Tracko::Piece::ConnectingPosition::CONNECTING_POSITION_UNDEF;
   std::tie(was_filled, overflow, exit_connecting_position) = piece.fill_with_amount(1.2);

   EXPECT_EQ(true, was_filled);
   EXPECT_FLOAT_EQ(0.2f, overflow);
   EXPECT_FLOAT_EQ(1.0f, piece.get_fill_counter());

   EXPECT_EQ(false, piece.is_partially_filled());
   EXPECT_EQ(true, piece.is_filled());
   al_uninstall_system();
}


