

#include <Tracko/Visuals/TrackPath.hpp>

#include <AllegroFlare/Vec2D.hpp>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Tracko
{
namespace Visuals
{


TrackPath::TrackPath(AllegroFlare::Path2D path)
   : path(path)
{
}


TrackPath::~TrackPath()
{
}


void TrackPath::set_path(AllegroFlare::Path2D path)
{
   this->path = path;
}


AllegroFlare::Path2D TrackPath::get_path() const
{
   return path;
}


AllegroFlare::Path2D &TrackPath::get_path_ref()
{
   return path;
}


void TrackPath::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[TrackPath::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TrackPath::render: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[TrackPath::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TrackPath::render: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[TrackPath::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TrackPath::render: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   path.draw(true, true, true, true);
   /*
   float x = 1920/2;
   float y = 1080/3;
   ALLEGRO_FONT *font = obtain_font();
   float text_width = al_get_text_width(font, quote.c_str());
   float text_height = al_get_font_line_height(font);
   float h_text_width = text_width/2;
   float h_text_height = text_height/2;
   AllegroFlare::Vec2D padding = {30, 20};

   al_draw_rounded_rectangle(
      x-h_text_width - padding.x,
      y-h_text_height - padding.y,
      x+h_text_width + padding.x,
      y+h_text_height + padding.y,
      8.0f,
      8.0f,
      ALLEGRO_COLOR{1, 1, 1, 1},
      8.0f
   );
   al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, x, y-h_text_height, ALLEGRO_ALIGN_CENTER, quote.c_str());
   */
   return;
}


} // namespace Visuals
} // namespace Tracko


