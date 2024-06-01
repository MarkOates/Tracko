
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


TEST(Tracko_BoardTest, have_connecting_edges__will_return_true_if_the_pieces_between_the_two_coordinates_connect)
{
   al_init();
   Tracko::Board board;
   board.resize(5, 7);
   board.fill_with_random_types();
   Tracko::Piece* piece_a = board.get_piece(2, 3);
   Tracko::Piece* piece_b = board.get_piece(3, 3);
   ASSERT_NE(nullptr, piece_a);
   ASSERT_NE(nullptr, piece_b);

   piece_a->set_tile_type(Tracko::Piece::TILE_TYPE_HORIZONTAL_BAR);
   piece_b->set_tile_type(Tracko::Piece::TILE_TYPE_HORIZONTAL_BAR);

   board.initialize_pieces();

   EXPECT_EQ(true, board.have_connecting_edges(2, 3, 3, 3));

   al_uninstall_system();
}


TEST(Tracko_BoardTest, have_connecting_edges__will_return_false_if_the_pieces_between_the_two_coordinates_do_not_\
connect)
{
   al_init();
   Tracko::Board board;
   board.resize(5, 7);
   board.fill_with_random_types();
   Tracko::Piece* piece_a = board.get_piece(2, 3);
   Tracko::Piece* piece_b = board.get_piece(3, 3);
   ASSERT_NE(nullptr, piece_a);
   ASSERT_NE(nullptr, piece_b);

   piece_a->set_tile_type(Tracko::Piece::TILE_TYPE_HORIZONTAL_BAR);
   piece_b->set_tile_type(Tracko::Piece::TILE_TYPE_HORIZONTAL_BAR);

   board.initialize_pieces();

   EXPECT_EQ(false, board.have_connecting_edges(-1, 2, 0, 2));

   al_uninstall_system();
}


/*
  - name: TileType
    scope: public
    enumerators:
      - TILE_TYPE_UNDEF
      - TILE_TYPE_HORIZONTAL_BAR
      - TILE_TYPE_VERTICAL_BAR
      - TILE_TYPE_TOP_RIGHT_CURVE
      - TILE_TYPE_RIGHT_BOTTOM_CURVE
      - TILE_TYPE_BOTTOM_LEFT_CURVE
      - TILE_TYPE_LEFT_TOP_CURVE


  - name: ConnectingPosition
    scope: public
    enumerators:
      - CONNECTING_POSITION_UNDEF
      - CONNECTING_POSITION_LEFT
      - CONNECTING_POSITION_TOP
      - CONNECTING_POSITION_RIGHT
      - CONNECTING_POSITION_BOTTOM


  - name: State
    scope: public
    enumerators:
      - STATE_UNDEF
      - STATE_HIDDEN
      - STATE_REVEALED
      - STATE_FILLING
      - STATE_FILLED
*/


