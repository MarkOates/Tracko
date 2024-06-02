

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
   auto &identifier = board_identifier;

   static float UPDATE_RATE_DENOMINATOR_ULTRA_EASY = 9.0f;
   static float UPDATE_RATE_DENOMINATOR_EASY = 8.0f;
   static float UPDATE_RATE_DENOMINATOR_MEDIUM = 4.0f;
   static float UPDATE_RATE_DENOMINATOR_HARD = 2.0f;

   // TODO: Add board names
   std::map<std::string, std::function<Tracko::Board*()>> factory = {

      // Levels 1-3 (Easy)

      { "level_1", [](){ return create_board(
            5, 3,
            { 0, 1 }, Tracko::Piece::ConnectingPosition::CONNECTING_POSITION_LEFT,
            { 4, 1 }, Tracko::Piece::ConnectingPosition::CONNECTING_POSITION_RIGHT,
            UPDATE_RATE_DENOMINATOR_ULTRA_EASY,
            1 // 1 approved
         );
      }},
      { "level_2", [](){ return create_board(
            5, 3,
            { 0, 0 }, Tracko::Piece::ConnectingPosition::CONNECTING_POSITION_LEFT,
            { 4, 2 }, Tracko::Piece::ConnectingPosition::CONNECTING_POSITION_RIGHT,
            UPDATE_RATE_DENOMINATOR_EASY,
            2
         );
      }},
      { "level_3", [](){ return create_board(
            6, 4,
            { 0, 2 }, Tracko::Piece::ConnectingPosition::CONNECTING_POSITION_LEFT,
            { 5, 1 }, Tracko::Piece::ConnectingPosition::CONNECTING_POSITION_RIGHT,
            UPDATE_RATE_DENOMINATOR_EASY,
            4
         );
      }},


      // Levels 10-12 (Hardest)

      { "level_12", [](){ return create_board(
            7, 5,
            { 0, 2 }, Tracko::Piece::ConnectingPosition::CONNECTING_POSITION_LEFT,
            { 6, 3 }, Tracko::Piece::ConnectingPosition::CONNECTING_POSITION_RIGHT,
            UPDATE_RATE_DENOMINATOR_HARD,
            123
         );
      }},
   };


   if (factory.count(identifier) == 0)
   {
      //bool item_handled = false;
      //if (unrecognized_key_callback_func)
      //{
         //item_handled = unrecognized_key_callback_func();
      //}

      //if (!item_handled)
      //{
         // item not found
         std::stringstream error_message;
         error_message << "[CubeShooter::LevelFactory::load_level]: error: Cannot load the item with the board_identifier \""
                       << identifier << "\", it does not exist.";
         throw std::runtime_error(error_message.str());
      //}
   }
   else
   {
      // call the item
      return factory[identifier]();
   }


   /*
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
   */
   return nullptr;
}

Tracko::Board* BoardFactory::create_board(int num_columns, int num_rows, AllegroFlare::Int2D start_coordinate, Tracko::Piece::ConnectingPosition start_connecting_position, AllegroFlare::Int2D end_coordinate, Tracko::Piece::ConnectingPosition end_connecting_position, float update_rate_denominator, int seed)
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
   board->set_update_rate_denominator(update_rate_denominator);
   board->initialize_pieces();
   Tracko::Piece *start_piece = board->get_piece(
         board->get_start_tile_coordinates().x,
         board->get_start_tile_coordinates().y
      );
   start_piece->reveal();
   return board;
}


} // namespace Tracko


