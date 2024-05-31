
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

   std::vector<std::vector<Tracko::Piece>> pieces = board.get_pieces();
   EXPECT_EQ(5, pieces.size());
   for (auto &piece : pieces) EXPECT_EQ(7, piece.size());
}


TEST(Tracko_BoardTest, get_piece__will_return_the_correct_piece)
{
   Tracko::Board board;
   board.resize(5, 7);
   Tracko::Piece* piece = board.get_piece(3, 4);
   ASSERT_NE(nullptr, piece);

   std::vector<std::vector<Tracko::Piece>> &pieces = board.get_pieces_ref();
   Tracko::Piece* expected_piece = &pieces[3][4];
   EXPECT_EQ(expected_piece, piece);
}


