

#include <Tracko/SharedBackground.hpp>

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Tracko
{


SharedBackground::SharedBackground(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, ALLEGRO_COLOR clear_color)
   : AllegroFlare::Elements::Backgrounds::Base(Tracko::SharedBackground::TYPE)
   , event_emitter(event_emitter)
   , bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , using_clear_color(false)
   , clear_color(clear_color)
   , using_parallax(false)
   , parallax()
   , using_fill_image(false)
   , fill_image_identifier("[unset-fill_image_identifier]")
   , initialized(false)
{
}


SharedBackground::~SharedBackground()
{
}


void SharedBackground::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   if (get_initialized()) throw std::runtime_error("[SharedBackground::set_event_emitter]: error: guard \"get_initialized()\" not met.");
   this->event_emitter = event_emitter;
}


void SharedBackground::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   if (get_initialized()) throw std::runtime_error("[SharedBackground::set_bitmap_bin]: error: guard \"get_initialized()\" not met.");
   this->bitmap_bin = bitmap_bin;
}


void SharedBackground::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (get_initialized()) throw std::runtime_error("[SharedBackground::set_font_bin]: error: guard \"get_initialized()\" not met.");
   this->font_bin = font_bin;
}


void SharedBackground::set_using_clear_color(bool using_clear_color)
{
   this->using_clear_color = using_clear_color;
}


void SharedBackground::set_clear_color(ALLEGRO_COLOR clear_color)
{
   this->clear_color = clear_color;
}


void SharedBackground::set_using_parallax(bool using_parallax)
{
   this->using_parallax = using_parallax;
}


void SharedBackground::set_using_fill_image(bool using_fill_image)
{
   this->using_fill_image = using_fill_image;
}


void SharedBackground::set_fill_image_identifier(std::string fill_image_identifier)
{
   this->fill_image_identifier = fill_image_identifier;
}


AllegroFlare::EventEmitter* SharedBackground::get_event_emitter() const
{
   return event_emitter;
}


AllegroFlare::BitmapBin* SharedBackground::get_bitmap_bin() const
{
   return bitmap_bin;
}


AllegroFlare::FontBin* SharedBackground::get_font_bin() const
{
   return font_bin;
}


bool SharedBackground::get_using_clear_color() const
{
   return using_clear_color;
}


ALLEGRO_COLOR SharedBackground::get_clear_color() const
{
   return clear_color;
}


bool SharedBackground::get_using_parallax() const
{
   return using_parallax;
}


bool SharedBackground::get_using_fill_image() const
{
   return using_fill_image;
}


std::string SharedBackground::get_fill_image_identifier() const
{
   return fill_image_identifier;
}


bool SharedBackground::get_initialized() const
{
   return initialized;
}


void SharedBackground::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[SharedBackground::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SharedBackground::initialize: error: guard \"(!initialized)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[SharedBackground::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SharedBackground::initialize: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[SharedBackground::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SharedBackground::initialize: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[SharedBackground::initialize]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SharedBackground::initialize: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[SharedBackground::initialize]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SharedBackground::initialize: error: guard \"event_emitter\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[SharedBackground::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SharedBackground::initialize: error: guard \"font_bin\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[SharedBackground::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SharedBackground::initialize: error: guard \"bitmap_bin\" not met");
   }
   initialized = true;
   return;
}

void SharedBackground::clear_all_usings()
{
   using_clear_color = false;
   using_fill_image = false;
   using_parallax = false;
   return;
}

void SharedBackground::activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[SharedBackground::activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SharedBackground::activate: error: guard \"initialized\" not met");
   }
   return;
}

void SharedBackground::deactivate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[SharedBackground::deactivate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SharedBackground::deactivate: error: guard \"initialized\" not met");
   }
   return;
}

void SharedBackground::update()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[SharedBackground::update]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SharedBackground::update: error: guard \"initialized\" not met");
   }
   // TODO: Consider a proper time-step
   return;
}

void SharedBackground::set_parallax_offset(float offset_x, float offset_y)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[SharedBackground::set_parallax_offset]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SharedBackground::set_parallax_offset: error: guard \"initialized\" not met");
   }
   parallax.set_offset_x(offset_x);
   parallax.set_offset_y(offset_y);
   return;
}

void SharedBackground::set_parallax_layers(std::vector<AllegroFlare::Elements::Backgrounds::ParallaxLayer> parallax_layers)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[SharedBackground::set_parallax_layers]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SharedBackground::set_parallax_layers: error: guard \"initialized\" not met");
   }
   parallax.set_layers(parallax_layers);
   // NOTE: Example
   //parallax.set_layers({
      //{0, 0, 0.1, bitmap_bin->auto_get("backgrounds/Sky3.png") },
      //{0, 0, 0.4, bitmap_bin->auto_get("backgrounds/Cloud3a.png") },
      //{0, 0, 0.8, bitmap_bin->auto_get("backgrounds/Cloud3b.png") },
   //});
   return;
}

void SharedBackground::render()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[SharedBackground::render]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SharedBackground::render: error: guard \"initialized\" not met");
   }
   // TODO: Fix initialization requirements here and in tests
   if (using_clear_color)
   {
      al_clear_to_color(clear_color);
   }
   if (using_fill_image)
   {
      ALLEGRO_BITMAP *image = bitmap_bin->auto_get(fill_image_identifier);
      al_draw_bitmap(image, 0, 0, 0);
   }
   if (using_parallax)
   {
      //if (parallax_background_shader) parallax_background_shader->activate();
      parallax.render();
      //if (parallax_background_shader) parallax_background_shader->deactivate();
   }
   return;
}

void SharedBackground::show()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[SharedBackground::show]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SharedBackground::show: error: guard \"initialized\" not met");
   }
   return;
}

void SharedBackground::hide()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[SharedBackground::hide]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SharedBackground::hide: error: guard \"initialized\" not met");
   }
   return;
}

void SharedBackground::swap_to_title()
{
   clear_all_usings();
   set_using_fill_image(true);
   set_fill_image_identifier("metropolitan-title-01.jpg");
}

void SharedBackground::swap_to_level_select()
{
   clear_all_usings();
   set_using_fill_image(true);
   set_fill_image_identifier("level-select-bg-02.jpg");
}

void SharedBackground::swap_to_gameplay()
{
   clear_all_usings();
   clear_all_usings();
   set_using_fill_image(true);
   set_fill_image_identifier("level-select-bg.jpg");
}

void SharedBackground::swap_to_unknown()
{
   clear_all_usings();
   set_using_clear_color(true);
   set_clear_color(ALLEGRO_COLOR{0.2, 0.2, 0.21, 1.0});
}


} // namespace Tracko


