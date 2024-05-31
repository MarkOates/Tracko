

#include <Tracko/Piece.hpp>

#include <AllegroFlare/Logger.hpp>
#include <allegro5/allegro.h>
#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>


namespace Tracko
{


Piece::Piece()
   : state(STATE_UNDEF)
   , state_is_busy(false)
   , state_changed_at(0.0f)
{
}


Piece::~Piece()
{
}


uint32_t Piece::get_state() const
{
   return state;
}


void Piece::set_state(uint32_t state, bool override_if_busy)
{
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


