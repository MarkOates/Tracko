

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
   ALLEGRO_COLOR line_color = ALLEGRO_COLOR{1, 1, 1, 1};
   path.draw(true, true, true, true, line_color);
   return;
}

void TrackPath::render_point_at(float position)
{
   if (position <= 0.0f) position = 0.0f;
   if (position >= 1.0f) position = 1.0f;

   ALLEGRO_COLOR point_color = ALLEGRO_COLOR{1.0, 0.6, 0.65, 1.0};

   float length = path.length();
   AllegroFlare::Vec2D position_along_path = path.coordinate_at(length * position);

   al_draw_filled_circle(position_along_path.x, position_along_path.y, 8, point_color);

   return;
}


} // namespace Visuals
} // namespace Tracko


