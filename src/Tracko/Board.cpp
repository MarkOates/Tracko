

#include <Tracko/Board.hpp>

#include <AllegroFlare/Random.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Tracko
{


Board::Board()
   : pieces({})
   , num_rows(0)
   , num_columns(0)
{
}


Board::~Board()
{
}


void Board::set_pieces(std::vector<std::vector<Tracko::Piece>> pieces)
{
   this->pieces = pieces;
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


std::vector<std::vector<Tracko::Piece>> &Board::get_pieces_ref()
{
   return pieces;
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
   return;
}

void Board::random_fill_types(uint32_t seed)
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

   for (int x=0; x<num_columns; x++)
   {
      for (int y=0; y<num_rows; y++)
      {
         Tracko::Piece* piece = get_piece(x, y);
         piece->set_tile_type(random.get_random_element(tile_types));
      }
   }
   return;
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


} // namespace Tracko


