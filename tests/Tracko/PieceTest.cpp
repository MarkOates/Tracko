
#include <gtest/gtest.h>

#include <Tracko/Piece.hpp>


TEST(Tracko_PieceTest, can_be_created_without_blowing_up)
{
   Tracko::Piece piece;
}


TEST(Tracko_PieceTest, run__returns_the_expected_response)
{
   Tracko::Piece piece;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, piece.run());
}


