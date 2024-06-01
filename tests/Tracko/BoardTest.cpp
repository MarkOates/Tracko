
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

   std::vector<std::pair<
      std::pair<std::pair<int, int>, Tracko::Piece::TileType>,
      std::pair<std::pair<int, int>, Tracko::Piece::TileType>
   >> valid_connections = {
      // Some simple vertical bars
      {
         { { 2, 3 }, Tracko::Piece::TILE_TYPE_HORIZONTAL_BAR },
         { { 3, 3 }, Tracko::Piece::TILE_TYPE_HORIZONTAL_BAR },
      },
      {
         { { 2, 3 }, Tracko::Piece::TILE_TYPE_HORIZONTAL_BAR },
         { { 1, 3 }, Tracko::Piece::TILE_TYPE_HORIZONTAL_BAR },
      },
      {
         { { 2, 1 }, Tracko::Piece::TILE_TYPE_VERTICAL_BAR },
         { { 2, 2 }, Tracko::Piece::TILE_TYPE_VERTICAL_BAR },
      },
      {
         { { 2, 2 }, Tracko::Piece::TILE_TYPE_VERTICAL_BAR },
         { { 2, 1 }, Tracko::Piece::TILE_TYPE_VERTICAL_BAR },
      },
      // Some curves
      {
         { { 2, 1 }, Tracko::Piece::TILE_TYPE_VERTICAL_BAR },
         { { 2, 2 }, Tracko::Piece::TILE_TYPE_TOP_RIGHT_CURVE },
      },
      {
         { { 2, 1 }, Tracko::Piece::TILE_TYPE_VERTICAL_BAR },
         { { 2, 2 }, Tracko::Piece::TILE_TYPE_LEFT_TOP_CURVE },
      },
   };

   for (auto &valid_connection : valid_connections)
   {
      std::pair<std::pair<int, int>, Tracko::Piece::TileType> &piece_a_data = valid_connection.first;
      std::pair<std::pair<int, int>, Tracko::Piece::TileType> &piece_b_data = valid_connection.second;
      float piece_a_x = piece_a_data.first.first;
      float piece_a_y = piece_a_data.first.second;
      float piece_b_x = piece_b_data.first.first;
      float piece_b_y = piece_b_data.first.second;

      Tracko::Board board;
      board.resize(5, 7);
      board.fill_with_random_types();

      Tracko::Piece* piece_a = board.get_piece(piece_a_x, piece_a_y);
      Tracko::Piece* piece_b = board.get_piece(piece_b_x, piece_b_y);
      ASSERT_NE(nullptr, piece_a);
      ASSERT_NE(nullptr, piece_b);
      piece_a->set_tile_type(piece_a_data.second);
      piece_b->set_tile_type(piece_b_data.second);

      board.initialize_pieces();

      EXPECT_EQ(true, board.have_connecting_edges(piece_a_x, piece_a_y, piece_b_x, piece_b_y));
   }

   al_uninstall_system();
}


TEST(Tracko_BoardTest, have_connecting_edges__will_return_false_if_the_pieces_between_the_two_coordinates_do_not_\
connect)
{
   al_init();

   std::vector<std::pair<
      std::pair<std::pair<int, int>, Tracko::Piece::TileType>,
      std::pair<std::pair<int, int>, Tracko::Piece::TileType>
   >> invalid_connections = {
      // Tile types that do not connect
      {
         { { 2, 3 }, Tracko::Piece::TILE_TYPE_HORIZONTAL_BAR },
         { { 3, 3 }, Tracko::Piece::TILE_TYPE_VERTICAL_BAR },
      },
      {
         { { 2, 3 }, Tracko::Piece::TILE_TYPE_VERTICAL_BAR },
         { { 3, 3 }, Tracko::Piece::TILE_TYPE_HORIZONTAL_BAR },
      },
      {
         { { 2, 1 }, Tracko::Piece::TILE_TYPE_VERTICAL_BAR },
         { { 2, 2 }, Tracko::Piece::TILE_TYPE_RIGHT_BOTTOM_CURVE },
      },
      {
         { { 2, 1 }, Tracko::Piece::TILE_TYPE_VERTICAL_BAR },
         { { 2, 2 }, Tracko::Piece::TILE_TYPE_BOTTOM_LEFT_CURVE },
      },
      // Same tile
      {
         { { 3, 3 }, Tracko::Piece::TILE_TYPE_TOP_RIGHT_CURVE },
         { { 3, 3 }, Tracko::Piece::TILE_TYPE_TOP_RIGHT_CURVE },
      },
      // Tiles that are not adjacent
      {
         { { 2, 3 }, Tracko::Piece::TILE_TYPE_HORIZONTAL_BAR },
         { { 4, 3 }, Tracko::Piece::TILE_TYPE_HORIZONTAL_BAR },
      },
      {
         { { 2, 1 }, Tracko::Piece::TILE_TYPE_VERTICAL_BAR },
         { { 2, 3 }, Tracko::Piece::TILE_TYPE_VERTICAL_BAR },
      },
      // Tiles that are off the edge of the board (TODO: this will need to be tested separately)
      //{
         //{ { 4, 0 }, Tracko::Piece::TILE_TYPE_HORIZONTAL_BAR },
         //{ { 5, 0 }, Tracko::Piece::TILE_TYPE_HORIZONTAL_BAR },
      //},
   };

   for (auto &invalid_connection : invalid_connections)
   {
      std::pair<std::pair<int, int>, Tracko::Piece::TileType> &piece_a_data = invalid_connection.first;
      std::pair<std::pair<int, int>, Tracko::Piece::TileType> &piece_b_data = invalid_connection.second;
      float piece_a_x = piece_a_data.first.first;
      float piece_a_y = piece_a_data.first.second;
      float piece_b_x = piece_b_data.first.first;
      float piece_b_y = piece_b_data.first.second;
      
      Tracko::Board board;
      board.resize(5, 7);
      board.fill_with_random_types();

      Tracko::Piece* piece_a = board.get_piece(piece_a_x, piece_a_y);
      Tracko::Piece* piece_b = board.get_piece(piece_b_x, piece_b_y);
      ASSERT_NE(nullptr, piece_a);
      ASSERT_NE(nullptr, piece_b);
      piece_a->set_tile_type(piece_a_data.second);
      piece_b->set_tile_type(piece_b_data.second);

      board.initialize_pieces();

      EXPECT_EQ(false, board.have_connecting_edges(piece_a_x, piece_a_y, piece_b_x, piece_b_y));
   }

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


