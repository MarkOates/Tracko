

#include <Tracko/Board.hpp>

#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/Random.hpp>
#include <iostream>
#include <map>
#include <set>
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

std::pair<bool, std::pair<int, int>> Board::calculate_adjacency(int x1, int y1, int x2, int y2)
{
   std::pair<int, int> difference = { x2 - x1, y2 - y1 };
   std::set<std::pair<int, int>> valid_adjacent_numbers = {
      { -1, 0 },
      { 0, -1 },
      { 1, 0 },
      { 0, 1 },
   };
   if (valid_adjacent_numbers.find(difference) == valid_adjacent_numbers.end()) return { false, difference };
   return { true, difference };
}

bool Board::have_connecting_edges(int x1, int y1, int x2, int y2)
{
   // Coordinates are on the board
   if (!is_valid_tile_coordinate(x1, y1)) return false;
   if (!is_valid_tile_coordinate(x2, y2)) return false;

   // Check if pieces are adjacent
   bool are_adjacent = false;
   std::pair<int, int> adjacency = { 0, 0 };
   std::tie(are_adjacent, adjacency) = calculate_adjacency(x1, y1, x2, y2);
   if (!are_adjacent) return false;

   // Pieces are in a connectable state
   Tracko::Piece* piece_a = get_piece(x1, y1);
   Tracko::Piece* piece_b = get_piece(x2, x2);

   std::pair<Tracko::Piece::ConnectingPosition, Tracko::Piece::ConnectingPosition> piece_a_connections =
      Tracko::Piece::get_connecting_positions(piece_a->get_tile_type());
   std::pair<Tracko::Piece::ConnectingPosition, Tracko::Piece::ConnectingPosition> piece_b_connections =
      Tracko::Piece::get_connecting_positions(piece_b->get_tile_type());

   // Get the connecting edges
   std::map<std::pair<int, int>, std::pair<Piece::ConnectingPosition, Piece::ConnectingPosition>> adjacency_connections = {
      { { -1, 0 }, { Piece::CONNECTING_POSITION_LEFT, Piece::CONNECTING_POSITION_RIGHT }, },
      { { 0, -1 }, { Piece::CONNECTING_POSITION_TOP, Piece::CONNECTING_POSITION_BOTTOM }, },
      { { 1, 0 }, { Piece::CONNECTING_POSITION_RIGHT, Piece::CONNECTING_POSITION_LEFT}, },
      { { 0, 1 }, { Piece::CONNECTING_POSITION_BOTTOM, Piece::CONNECTING_POSITION_TOP}, },
   };

   if (adjacency_connections.find(adjacency) == adjacency_connections.end())
   {
      AllegroFlare::Logger::throw_error(
         "Tracko::Piece::have_connecting_edges",
         "Unable to handle case for the adjacency coordinates { "
            + std::to_string(adjacency.first) + ", " + std::to_string(adjacency.second) + " }."
      );
   }

   std::pair<Piece::ConnectingPosition, Piece::ConnectingPosition> required_connections =
      adjacency_connections[adjacency];
   if (!piece_a->has_connecting_position(required_connections.first)) return false;
   if (!piece_b->has_connecting_position(required_connections.second)) return false;

   // HERE
   // TODO: This method, need to take into account if:
   // 1) piece is in a connectable state
   // 2) piece has the matching connection
   // 3) source's connection does not match to edge of map
   // 4) other stuff
   //CONNECTING_POSITION_LEFT
   //CONNECTING_POSITION_TOP
   //CONNECTING_POSITION_RIGHT
   //CONNECTING_POSITION_BOTTOM
   //throw std::runtime_error("Tracko::Board HERE");
   return true;
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

void Board::set_random_tile_with_connection(int x, int y, Tracko::Piece::ConnectingPosition connecting_position, uint32_t seed)
{
   if (!((connecting_position != Tracko::Piece::CONNECTING_POSITION_UNDEF)))
   {
      std::stringstream error_message;
      error_message << "[Board::set_random_tile_with_connection]: error: guard \"(connecting_position != Tracko::Piece::CONNECTING_POSITION_UNDEF)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Board::set_random_tile_with_connection: error: guard \"(connecting_position != Tracko::Piece::CONNECTING_POSITION_UNDEF)\" not met");
   }
   static AllegroFlare::Random random(seed);

   Tracko::Piece *piece = get_piece(x, y);
   std::vector<Tracko::Piece::TileType> tile_types_with_connecting_position =
      piece->get_types_with_connecting_position(connecting_position);

   Tracko::Piece::TileType selected_type_with_connection = random.get_random_element(
         tile_types_with_connecting_position
      );

   piece->set_tile_type(selected_type_with_connection);
   ////Tracko::Piece::ConnectingPosition::CONNECTING_POSITION_LEFT
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

bool Board::is_valid_tile_coordinate(int x, int y)
{
   return (x >= 0) && (x < num_columns) && (y >= 0) && (y < num_rows);
}

Tracko::Piece* Board::get_swap_piece()
{
   return &swap_piece;
}


} // namespace Tracko


