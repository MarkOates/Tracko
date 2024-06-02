

#include <Tracko/BoardFactory.hpp>

#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>


namespace Tracko
{


BoardFactory::BoardFactory()
{
}


BoardFactory::~BoardFactory()
{
}


Tracko::Board* BoardFactory::create_board_by_identifier(std::string board_identifier)
{
   // TODO: Add board names
   std::map<std::string, std::function<Tracko::Board*()>> factory = {
      { "level_1", [](){
         return create_board(
            6, 4,
            { 0, 2 }, Tracko::Piece::ConnectingPosition::CONNECTING_POSITION_LEFT,
            { 5, 1 }, Tracko::Piece::ConnectingPosition::CONNECTING_POSITION_RIGHT,
            4
         );
      }},
   };

   if (board_identifier == "")
   {
      throw std::runtime_error("missing level identifier");
   }
   else if (board_identifier == "level_1")
   {
      return create_board(
         6, 4,
         { 0, 2 }, Tracko::Piece::ConnectingPosition::CONNECTING_POSITION_LEFT,
         { 5, 1 }, Tracko::Piece::ConnectingPosition::CONNECTING_POSITION_RIGHT,
         4
      );
   }
   else if (board_identifier == "level_1234")
   {
      return create_board(
         7, 5,
         { 0, 2 }, Tracko::Piece::ConnectingPosition::CONNECTING_POSITION_LEFT,
         { 6, 3 }, Tracko::Piece::ConnectingPosition::CONNECTING_POSITION_RIGHT,
         123
      );
   }
   else
   {
      throw std::runtime_error("unfound level identifier");
   }
   return nullptr;
}

Tracko::Board* BoardFactory::create_board(int num_columns, int num_rows, AllegroFlare::Int2D start_coordinate, Tracko::Piece::ConnectingPosition start_connecting_position, AllegroFlare::Int2D end_coordinate, Tracko::Piece::ConnectingPosition end_connecting_position, int seed)
{
   if (!((num_columns >= 1)))
   {
      std::stringstream error_message;
      error_message << "[BoardFactory::create_board]: error: guard \"(num_columns >= 1)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BoardFactory::create_board: error: guard \"(num_columns >= 1)\" not met");
   }
   if (!((num_rows >= 1)))
   {
      std::stringstream error_message;
      error_message << "[BoardFactory::create_board]: error: guard \"(num_rows >= 1)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BoardFactory::create_board: error: guard \"(num_rows >= 1)\" not met");
   }
   if (!((seed != 0)))
   {
      std::stringstream error_message;
      error_message << "[BoardFactory::create_board]: error: guard \"(seed != 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BoardFactory::create_board: error: guard \"(seed != 0)\" not met");
   }
   Tracko::Board* board = new Tracko::Board;
   board->set_start_tile_coordinates(start_coordinate);
   //board->set_start_tile_start_connecting_position(Tracko::Piece::ConnectingPosition::CONNECTING_POSITION_LEFT);
   board->set_start_tile_start_connecting_position(start_connecting_position);
   board->set_exit_tile_coordinates(end_coordinate);
   //board->set_exit_tile_exit_connecting_position(Tracko::Piece::ConnectingPosition::CONNECTING_POSITION_RIGHT);
   board->set_exit_tile_exit_connecting_position(end_connecting_position);
   board->resize(num_columns, num_rows);
   board->fill_with_random_types(seed);
   board->set_random_tile_with_connection(
         board->get_start_tile_coordinates().x,
         board->get_start_tile_coordinates().y,
         start_connecting_position,
         //Tracko::Piece::ConnectingPosition::CONNECTING_POSITION_LEFT,
         seed
      );
   board->initialize_pieces();
   Tracko::Piece *start_piece = board->get_piece(
         board->get_start_tile_coordinates().x,
         board->get_start_tile_coordinates().y
      );
   start_piece->reveal();
   return board;
}


} // namespace Tracko


