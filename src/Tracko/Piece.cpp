

#include <Tracko/Piece.hpp>

#include <AllegroFlare/Logger.hpp>
#include <allegro5/allegro.h>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <utility>


namespace Tracko
{


Piece::Piece()
   : fill_counter(0.0f)
   , tile_type(TILE_TYPE_UNDEF)
   , entrance_connecting_position(CONNECTING_POSITION_UNDEF)
   , state(STATE_UNDEF)
   , state_is_busy(false)
   , state_changed_at(0.0f)
{
}


Piece::~Piece()
{
}


float Piece::get_fill_counter() const
{
   return fill_counter;
}


Tracko::Piece::TileType Piece::get_tile_type() const
{
   return tile_type;
}


uint32_t Piece::get_entrance_connecting_position() const
{
   return entrance_connecting_position;
}


uint32_t Piece::get_state() const
{
   return state;
}


void Piece::set_tile_type(Tracko::Piece::TileType tile_type)
{
   if (!((tile_type != TILE_TYPE_UNDEF)))
   {
      std::stringstream error_message;
      error_message << "[Piece::set_tile_type]: error: guard \"(tile_type != TILE_TYPE_UNDEF)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Piece::set_tile_type: error: guard \"(tile_type != TILE_TYPE_UNDEF)\" not met");
   }
   if (!((is_state(STATE_UNDEF) || is_state(STATE_HIDDEN))))
   {
      std::stringstream error_message;
      error_message << "[Piece::set_tile_type]: error: guard \"(is_state(STATE_UNDEF) || is_state(STATE_HIDDEN))\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Piece::set_tile_type: error: guard \"(is_state(STATE_UNDEF) || is_state(STATE_HIDDEN))\" not met");
   }
   this->tile_type = tile_type;
   return;
}

void Piece::set_entrance_connecting_position(Tracko::Piece::ConnectingPosition entrance_connecting_position)
{
   if (!((entrance_connecting_position != CONNECTING_POSITION_UNDEF)))
   {
      std::stringstream error_message;
      error_message << "[Piece::set_entrance_connecting_position]: error: guard \"(entrance_connecting_position != CONNECTING_POSITION_UNDEF)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Piece::set_entrance_connecting_position: error: guard \"(entrance_connecting_position != CONNECTING_POSITION_UNDEF)\" not met");
   }
   if (!((is_state(STATE_UNDEF) || is_state(STATE_HIDDEN))))
   {
      std::stringstream error_message;
      error_message << "[Piece::set_entrance_connecting_position]: error: guard \"(is_state(STATE_UNDEF) || is_state(STATE_HIDDEN))\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Piece::set_entrance_connecting_position: error: guard \"(is_state(STATE_UNDEF) || is_state(STATE_HIDDEN))\" not met");
   }
   this->entrance_connecting_position = entrance_connecting_position;
   return;
}

Tracko::Piece::ConnectingPosition Piece::infer_exit_connecting_position()
{
   // TODO: Test this
   std::map<TileType, std::pair<ConnectingPosition, ConnectingPosition>> piece_connection_edges = {
      { TILE_TYPE_HORIZONTAL_BAR, { CONNECTING_POSITION_LEFT, CONNECTING_POSITION_RIGHT } },
      { TILE_TYPE_VERTICAL_BAR, { CONNECTING_POSITION_TOP, CONNECTING_POSITION_BOTTOM } },
      { TILE_TYPE_TOP_RIGHT_CURVE, { CONNECTING_POSITION_TOP, CONNECTING_POSITION_RIGHT } },
      { TILE_TYPE_RIGHT_BOTTOM_CURVE, { CONNECTING_POSITION_RIGHT, CONNECTING_POSITION_BOTTOM } },
      { TILE_TYPE_BOTTOM_LEFT_CURVE, { CONNECTING_POSITION_BOTTOM, CONNECTING_POSITION_LEFT } },
      { TILE_TYPE_LEFT_TOP_CURVE, { CONNECTING_POSITION_LEFT, CONNECTING_POSITION_TOP } },
   };

   // Lookup the connections on this piece type
   if (piece_connection_edges.find(tile_type) == piece_connection_edges.end())
   {
      AllegroFlare::Logger::throw_error(
         "Tracko::Piece::infer_exit_connection_position",
         "Unable to handle case for the tile_type \""
            + std::to_string(tile_type) + "\""
      );
   }
   std::pair<ConnectingPosition, ConnectingPosition> connections_on_this_piece = piece_connection_edges[tile_type];

   // Find the "other" connecting piece, given the entrance connecting position
   Tracko::Piece::ConnectingPosition inferred_exit_position = CONNECTING_POSITION_UNDEF;
   if (connections_on_this_piece.first == entrance_connecting_position)
   {
      inferred_exit_position = connections_on_this_piece.first;
   }
   else if (connections_on_this_piece.second == entrance_connecting_position)
   {
      inferred_exit_position = connections_on_this_piece.first;
   }

   if (inferred_exit_position == CONNECTING_POSITION_UNDEF)
   {
      AllegroFlare::Logger::throw_error(
         "Tracko::Piece::infer_exit_connection_position",
         "When looking at the connection pieces for this piece type \"" + std::to_string(tile_type) + "\", there "
            "was no connecting edge that matched the \"entrance_connecting_position\" of \""
            + std::to_string(entrance_connecting_position) + "\""
      );
   }

   return inferred_exit_position;
}

bool Piece::is_filled()
{
   return is_state(STATE_FILLED);
}

std::pair<bool, float> Piece::fill_with_amount(float amount)
{
   if (!((!is_filled())))
   {
      std::stringstream error_message;
      error_message << "[Piece::fill_with_amount]: error: guard \"(!is_filled())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Piece::fill_with_amount: error: guard \"(!is_filled())\" not met");
   }
   float remainder = 0.0f;
   bool was_filled = false;

   fill_counter += amount;
   if (fill_counter >= 1.0) 
   {
      remainder = (fill_counter - 1.0);
      was_filled = true;

      set_state(STATE_FILLED);
      fill_counter = 1.0f;
   }
   return { was_filled, remainder };
}

void Piece::set_state(uint32_t state, bool override_if_busy)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Piece::set_state]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Piece::set_state: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(is_valid_state(state)))
   {
      std::stringstream error_message;
      error_message << "[Piece::set_state]: error: guard \"is_valid_state(state)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Piece::set_state: error: guard \"is_valid_state(state)\" not met");
   }
   if (this->state == state) return;
   if (!override_if_busy && state_is_busy) return;
   uint32_t previous_state = this->state;

   switch (state)
   {
      case STATE_HIDDEN:
      break;

      case STATE_REVEALED:
      break;

      case STATE_FILLING:
      break;

      case STATE_FILLED:
      break;

      default:
         AllegroFlare::Logger::throw_error(
            "ClassName::set_state",
            "Unable to handle case for state \"" + std::to_string(state) + "\""
         );
      break;
   }

   this->state = state;
   state_changed_at = al_get_time();

   return;
}

void Piece::update_state(float time_now)
{
   if (!(is_valid_state(state)))
   {
      std::stringstream error_message;
      error_message << "[Piece::update_state]: error: guard \"is_valid_state(state)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Piece::update_state: error: guard \"is_valid_state(state)\" not met");
   }
   float age = infer_current_state_age(time_now);

   switch (state)
   {
      case STATE_HIDDEN:
      break;

      case STATE_REVEALED:
      break;

      case STATE_FILLING:
      break;

      case STATE_FILLED:
      break;

      default:
         AllegroFlare::Logger::throw_error(
            "ClassName::update_state",
            "Unable to handle case for state \"" + std::to_string(state) + "\""
         );
      break;
   }

   return;
}

bool Piece::is_valid_state(uint32_t state)
{
   std::set<uint32_t> valid_states =
   {
      STATE_HIDDEN,
      STATE_REVEALED,
      STATE_FILLING,
      STATE_FILLED,
   };
   return (valid_states.count(state) > 0);
}

bool Piece::is_state(uint32_t possible_state)
{
   return (state == possible_state);
}

float Piece::infer_current_state_age(float time_now)
{
   return (time_now - state_changed_at);
}


} // namespace Tracko


