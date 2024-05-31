
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
   Tracko::Piece piece;
   piece.fill_with_amount(0.2);
   EXPECT_EQ(0.2f, piece.get_fill_counter());
}


