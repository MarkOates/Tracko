

#include <Tracko/SharedForeground.hpp>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>


namespace Tracko
{


SharedForeground::SharedForeground(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin)
   : AllegroFlare::Elements::Backgrounds::Base(Tracko::SharedForeground::TYPE)
   , event_emitter(event_emitter)
   , bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , curtain_position(0.0f)
   , curtain_state(CURTAIN_STATE_UNDEF)
   , curtain_state_is_busy(false)
   , curtain_state_changed_at(0.0f)
   , initialized(false)
{
}


SharedForeground::~SharedForeground()
{
}


void SharedForeground::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   if (get_initialized()) throw std::runtime_error("[SharedForeground::set_event_emitter]: error: guard \"get_initialized()\" not met.");
   this->event_emitter = event_emitter;
}


void SharedForeground::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   if (get_initialized()) throw std::runtime_error("[SharedForeground::set_bitmap_bin]: error: guard \"get_initialized()\" not met.");
   this->bitmap_bin = bitmap_bin;
}


void SharedForeground::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (get_initialized()) throw std::runtime_error("[SharedForeground::set_font_bin]: error: guard \"get_initialized()\" not met.");
   this->font_bin = font_bin;
}


AllegroFlare::EventEmitter* SharedForeground::get_event_emitter() const
{
   return event_emitter;
}


AllegroFlare::BitmapBin* SharedForeground::get_bitmap_bin() const
{
   return bitmap_bin;
}


AllegroFlare::FontBin* SharedForeground::get_font_bin() const
{
   return font_bin;
}


float SharedForeground::get_curtain_position() const
{
   return curtain_position;
}


uint32_t SharedForeground::get_curtain_state() const
{
   return curtain_state;
}


bool SharedForeground::get_initialized() const
{
   return initialized;
}


void SharedForeground::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[SharedForeground::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SharedForeground::initialize: error: guard \"(!initialized)\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[SharedForeground::initialize]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SharedForeground::initialize: error: guard \"event_emitter\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[SharedForeground::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SharedForeground::initialize: error: guard \"font_bin\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[SharedForeground::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SharedForeground::initialize: error: guard \"bitmap_bin\" not met");
   }
   set_curtain_state(CURTAIN_STATE_OPEN);
   initialized = true;
   return;
}

void SharedForeground::open_curtain()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[SharedForeground::open_curtain]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SharedForeground::open_curtain: error: guard \"initialized\" not met");
   }
   if (is_curtain_state(CURTAIN_STATE_OPENING) || is_curtain_state(CURTAIN_STATE_OPEN)) return;
   set_curtain_state(CURTAIN_STATE_OPENING);
   return;
}

void SharedForeground::close_curtain()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[SharedForeground::close_curtain]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SharedForeground::close_curtain: error: guard \"initialized\" not met");
   }
   if (is_curtain_state(CURTAIN_STATE_CLOSING) || is_curtain_state(CURTAIN_STATE_CLOSED)) return;
   set_curtain_state(CURTAIN_STATE_CLOSING);
   return;
}

bool SharedForeground::curtain_is_open()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[SharedForeground::curtain_is_open]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SharedForeground::curtain_is_open: error: guard \"initialized\" not met");
   }
   return is_curtain_state(CURTAIN_STATE_OPEN);
}

bool SharedForeground::curtain_is_closed()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[SharedForeground::curtain_is_closed]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SharedForeground::curtain_is_closed: error: guard \"initialized\" not met");
   }
   return is_curtain_state(CURTAIN_STATE_CLOSED);
}

void SharedForeground::activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[SharedForeground::activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SharedForeground::activate: error: guard \"initialized\" not met");
   }
   return;
}

void SharedForeground::deactivate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[SharedForeground::deactivate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SharedForeground::deactivate: error: guard \"initialized\" not met");
   }
   return;
}

void SharedForeground::update()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[SharedForeground::update]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SharedForeground::update: error: guard \"initialized\" not met");
   }
   // TODO: Consider a proper time-step
   update_curtain_state();
   return;
}

void SharedForeground::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[SharedForeground::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SharedForeground::render: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[SharedForeground::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SharedForeground::render: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[SharedForeground::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SharedForeground::render: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[SharedForeground::render]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SharedForeground::render: error: guard \"font_bin\" not met");
   }
   // TODO: Fix initialization requirements here and in tests
   render_curtains();
   return;
}

void SharedForeground::render_curtains()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[SharedForeground::render_curtains]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SharedForeground::render_curtains: error: guard \"initialized\" not met");
   }
   if (is_curtain_state(CURTAIN_STATE_OPEN)) return;

   //ALLEGRO_COLOR color = ALLEGRO_COLOR{0, 0.3, 0, 0.5};
   ALLEGRO_COLOR color = ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 1.0f}; // Consider a different color
   float width = 1920;
   float height = 1080;
   float curtain_size = width/2*curtain_position;

   // left_curtain
   al_draw_filled_rectangle(0, 0, curtain_size, height, color);

   // right_curtain
   al_draw_filled_rectangle(width-curtain_size, 0, width, height, color);
   return;
}

void SharedForeground::show()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[SharedForeground::show]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SharedForeground::show: error: guard \"initialized\" not met");
   }
   return;
}

void SharedForeground::hide()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[SharedForeground::hide]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SharedForeground::hide: error: guard \"initialized\" not met");
   }
   return;
}

void SharedForeground::set_curtain_state(uint32_t curtain_state, bool override_if_busy)
{
   if (!(is_valid_curtain_state(curtain_state)))
   {
      std::stringstream error_message;
      error_message << "[SharedForeground::set_curtain_state]: error: guard \"is_valid_curtain_state(curtain_state)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SharedForeground::set_curtain_state: error: guard \"is_valid_curtain_state(curtain_state)\" not met");
   }
   if (this->curtain_state == curtain_state) return;
   if (!override_if_busy && curtain_state_is_busy) return;
   uint32_t previous_curtain_state = this->curtain_state;

   switch (curtain_state)
   {
      case CURTAIN_STATE_OPENING:
         // Nothing to do
      break;

      case CURTAIN_STATE_OPEN:
         curtain_position = 0.0f;
      break;

      case CURTAIN_STATE_CLOSING:
         // Nothing to do
      break;

      case CURTAIN_STATE_CLOSED:
         curtain_position = 1.0f;
      break;

      default:
         throw std::runtime_error("weird error");
      break;
   }

   this->curtain_state = curtain_state;
   curtain_state_changed_at = al_get_time();

   return;
}

void SharedForeground::update_curtain_state(float time_now)
{
   if (!(is_valid_curtain_state(curtain_state)))
   {
      std::stringstream error_message;
      error_message << "[SharedForeground::update_curtain_state]: error: guard \"is_valid_curtain_state(curtain_state)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SharedForeground::update_curtain_state: error: guard \"is_valid_curtain_state(curtain_state)\" not met");
   }
   float age = infer_current_curtain_state_age(time_now);

   switch (curtain_state)
   {
      case CURTAIN_STATE_OPENING:
         curtain_position -= 0.04;
         if (curtain_position < 0.0f)
         {
            curtain_position = 0.0f;
            set_curtain_state(CURTAIN_STATE_OPEN);
            emit_curtain_opened_event();
         }
      break;

      case CURTAIN_STATE_OPEN:
         // Nothing to do
      break;

      case CURTAIN_STATE_CLOSING:
         curtain_position += 0.04f;
         if (curtain_position > 1.0f)
         {
            curtain_position = 1.0f;
            set_curtain_state(CURTAIN_STATE_CLOSED);
            emit_curtain_closed_event();
         }
      break;

      case CURTAIN_STATE_CLOSED:
         // Nothing to do
      break;

      default:
         throw std::runtime_error("weird error");
      break;
   }

   return;
}

void SharedForeground::emit_curtain_opened_event()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[SharedForeground::emit_curtain_opened_event]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SharedForeground::emit_curtain_opened_event: error: guard \"initialized\" not met");
   }
   event_emitter->emit_game_event(AllegroFlare::GameEvent(CURTAIN_OPENED_GAME_EVENT_NAME));
   return;
}

void SharedForeground::emit_curtain_closed_event()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[SharedForeground::emit_curtain_closed_event]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SharedForeground::emit_curtain_closed_event: error: guard \"initialized\" not met");
   }
   event_emitter->emit_game_event(AllegroFlare::GameEvent(CURTAIN_CLOSED_GAME_EVENT_NAME));
   return;
}

bool SharedForeground::is_valid_curtain_state(uint32_t curtain_state)
{
   std::set<uint32_t> valid_curtain_states =
   {
      CURTAIN_STATE_OPENING,
      CURTAIN_STATE_OPEN,
      CURTAIN_STATE_CLOSING,
      CURTAIN_STATE_CLOSED,
   };
   return (valid_curtain_states.count(curtain_state) > 0);
}

bool SharedForeground::is_curtain_state(uint32_t possible_curtain_state)
{
   return (curtain_state == possible_curtain_state);
}

float SharedForeground::infer_current_curtain_state_age(float time_now)
{
   return (time_now - curtain_state_changed_at);
}


} // namespace Tracko


