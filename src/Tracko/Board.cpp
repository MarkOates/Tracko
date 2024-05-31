

#include <Tracko/Board.hpp>

#include <AllegroFlare/Random.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Tracko
{


Board::Board()
   : pieces({})
   , swap_piece({})
   , num_rows(0)
   , num_columns(0)
   , cursor_x(0)
   , cursor_y(0)
{
}


Board::~Board()
{
}


void Board::set_pieces(std::vector<std::vector<Tracko::Piece>> pieces)
{
   this->pieces = pieces;
}


void Board::set_swap_piece(Tracko::Piece swap_piece)
{
   this->swap_piece = swap_piece;
}


std::vector<std::vector<Tracko::Piece>> Board::get_pieces() const
{
   return pieces;
}


int Board::get_num_rows() const
{
   return num_rows;
}


int Board::get_num_columns() const
{
   return num_columns;
}


int Board::get_cursor_x() const
{
   return cursor_x;
}


int Board::get_cursor_y() const
{
   return cursor_y;
}


std::vector<std::vector<Tracko::Piece>> &Board::get_pieces_ref()
{
   return pieces;
}


void Board::move_cursor_up()
{
   cursor_y -= 1;
   if (cursor_y < 0) cursor_y = 0;
   return;
}

void Board::move_cursor_down()
{
   cursor_y += 1;
   if (cursor_y >= num_rows) cursor_y = (num_rows - 1);
   return;
}

void Board::move_cursor_left()
{
   cursor_x -= 1;
   if (cursor_x < 0) cursor_x = 0;
   return;
}

void Board::move_cursor_right()
{
   cursor_x += 1;
   if (cursor_x >= num_columns) cursor_x = (num_columns - 1);
   return;
}

void Board::swap()
{
   if (!(can_swap()))
   {
      std::stringstream error_message;
      error_message << "[Board::swap]: error: guard \"can_swap()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Board::swap: error: guard \"can_swap()\" not met");
   }
   // TODO: Test this
   Tracko::Piece *piece_at_cursor = get_piece_at_cursor();
   Tracko::Piece intermediate_piece = *piece_at_cursor;
   *piece_at_cursor = swap_piece;
   swap_piece = intermediate_piece;
   return;
}

bool Board::can_swap()
{
   if (!cursor_is_in_valid_position()) return false;
   Tracko::Piece *piece_at_cursor = get_piece_at_cursor();
   return piece_at_cursor->infer_can_swap();
}

bool Board::cursor_is_in_valid_position()
{
   if (cursor_x < 0) return false;
   if (cursor_y < 0) return false;
   if (cursor_x >= num_columns) return false;
   if (cursor_y >= num_rows) return false;
   return true;
}

void Board::resize(int num_columns, int num_rows)
{
   if (!((num_rows > 0)))
   {
      std::stringstream error_message;
      error_message << "[Board::resize]: error: guard \"(num_rows > 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Board::resize: error: guard \"(num_rows > 0)\" not met");
   }
   if (!((num_columns > 0)))
   {
      std::stringstream error_message;
      error_message << "[Board::resize]: error: guard \"(num_columns > 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Board::resize: error: guard \"(num_columns > 0)\" not met");
   }
   this->num_rows = num_rows;
   this->num_columns = num_columns;

   pieces.resize(num_columns);
   for (auto &piece : pieces) piece.resize(num_rows);

   swap_piece = Tracko::Piece();

   cursor_x = 0;
   cursor_y = 0;

   return;
}

void Board::fill_with_random_types(uint32_t seed)
{
   static AllegroFlare::Random random(seed);

   std::vector<Tracko::Piece::TileType> tile_types = {
      Tracko::Piece::TILE_TYPE_HORIZONTAL_BAR,
      Tracko::Piece::TILE_TYPE_VERTICAL_BAR,
      Tracko::Piece::TILE_TYPE_TOP_RIGHT_CURVE,
      Tracko::Piece::TILE_TYPE_RIGHT_BOTTOM_CURVE,
      Tracko::Piece::TILE_TYPE_BOTTOM_LEFT_CURVE,
      Tracko::Piece::TILE_TYPE_LEFT_TOP_CURVE,
   };

   // Fill the board with random pieces
   for (int x=0; x<num_columns; x++)
   {
      for (int y=0; y<num_rows; y++)
      {
         Tracko::Piece* piece = get_piece(x, y);
         piece->set_tile_type(random.get_random_element(tile_types));
      }
   }

   // Set the swap piece with a random piece
   swap_piece.set_tile_type(random.get_random_element(tile_types));

   return;
}

void Board::initialize_pieces()
{
   // Initialize the pieces on the board
   for (int x=0; x<num_columns; x++)
   {
      for (int y=0; y<num_rows; y++)
      {
         Tracko::Piece* piece = get_piece(x, y);
         piece->initialize();
      }
   }

   // Initialize the swap piece (and reveal it)
   swap_piece.initialize();
   swap_piece.reveal();
}

Tracko::Piece* Board::get_piece_at_cursor()
{
   if (!(cursor_is_in_valid_position()))
   {
      std::stringstream error_message;
      error_message << "[Board::get_piece_at_cursor]: error: guard \"cursor_is_in_valid_position()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Board::get_piece_at_cursor: error: guard \"cursor_is_in_valid_position()\" not met");
   }
   return get_piece(cursor_x, cursor_y);
}

Tracko::Piece* Board::get_piece(int x, int y)
{
   if (!((x >= 0)))
   {
      std::stringstream error_message;
      error_message << "[Board::get_piece]: error: guard \"(x >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Board::get_piece: error: guard \"(x >= 0)\" not met");
   }
   if (!((x < num_columns)))
   {
      std::stringstream error_message;
      error_message << "[Board::get_piece]: error: guard \"(x < num_columns)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Board::get_piece: error: guard \"(x < num_columns)\" not met");
   }
   if (!((y >= 0)))
   {
      std::stringstream error_message;
      error_message << "[Board::get_piece]: error: guard \"(y >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Board::get_piece: error: guard \"(y >= 0)\" not met");
   }
   if (!((y < num_rows)))
   {
      std::stringstream error_message;
      error_message << "[Board::get_piece]: error: guard \"(y < num_rows)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Board::get_piece: error: guard \"(y < num_rows)\" not met");
   }
   return &pieces[x][y];
}

Tracko::Piece* Board::get_swap_piece()
{
   return &swap_piece;
}


} // namespace Tracko


