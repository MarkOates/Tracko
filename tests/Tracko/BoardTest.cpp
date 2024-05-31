
#include <gtest/gtest.h>

#include <Tracko/Board.hpp>


TEST(Tracko_BoardTest, can_be_created_without_blowing_up)
{
   Tracko::Board board;
}


TEST(Tracko_BoardTest, resize__will_set_the_size_of_the_board)
{
   Tracko::Board board;
   board.resize(5, 7);
   EXPECT_EQ(5, board.get_num_columns());
   EXPECT_EQ(7, board.get_num_rows());
}


