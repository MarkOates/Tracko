

#include <Tracko/Visuals/TrackPath.hpp>

#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <Tracko/Piece.hpp>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <map>
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
   path.draw(true, true, false, true, line_color);
   return;
}

void TrackPath::reverse_points()
{
   path.reverse();
}

std::vector<AllegroFlare::Vec2D> TrackPath::build_points_for_tile_type(Tracko::Piece::TileType tile_type)
{
   if (!((tile_type != Tracko::Piece::TileType::TILE_TYPE_UNDEF)))
   {
      std::stringstream error_message;
      error_message << "[TrackPath::build_points_for_tile_type]: error: guard \"(tile_type != Tracko::Piece::TileType::TILE_TYPE_UNDEF)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TrackPath::build_points_for_tile_type: error: guard \"(tile_type != Tracko::Piece::TileType::TILE_TYPE_UNDEF)\" not met");
   }
   std::map<Tracko::Piece::TileType, std::vector<AllegroFlare::Vec2D>> path_coordinates = {
      { Piece::TILE_TYPE_HORIZONTAL_BAR, {
            { 0.0, 0.5 },
            { 1.0, 0.5 },
         },
      },
      { Piece::TILE_TYPE_VERTICAL_BAR, {
            { 0.5, 0.0 },
            { 0.5, 1.0 },
         },
      },
      { Piece::TILE_TYPE_TOP_RIGHT_CURVE, {
            { 0.5, 0.0 },
            { 0.5, 0.5 },
            { 1.0, 0.5 },
         },
      },
      { Piece::TILE_TYPE_RIGHT_BOTTOM_CURVE, {
            { 1.0, 0.5 },
            { 0.5, 0.5 },
            { 0.5, 1.0 },
         },
      },
      { Piece::TILE_TYPE_BOTTOM_LEFT_CURVE, {
            { 0.5, 1.0 },
            { 0.5, 0.5 },
            { 0.0, 0.5 },
         },
      },
      { Piece::TILE_TYPE_LEFT_TOP_CURVE, {
            { 0.0, 0.5 },
            { 0.5, 0.5 },
            { 0.5, 0.0 },
         },
      },
   };


   if (tile_type == Piece::TILE_TYPE_TOP_RIGHT_CURVE)
   {
      AllegroFlare::Path2D path;
      path.add_arc(0.0, 0.0, 0.5, 0.5, 0.5 * ALLEGRO_PI * 2, -0.25 * ALLEGRO_PI * 2, 24, false);
      path.scale(0.666666);
      path.move(1.0-0.5*0.333333, 0.5*0.333333);
      path.insert_point(0, 0.5, 0.0);
      path.add_point(1.0, 0.5);
      path.refresh_segment_info();
      return path.point;
   }
   else if (tile_type == Piece::TILE_TYPE_RIGHT_BOTTOM_CURVE)
   {
      AllegroFlare::Path2D path;
      path.add_arc(0.0, 0.0, 0.5, 0.5, 0.75 * ALLEGRO_PI * 2, -0.25 * ALLEGRO_PI * 2, 24, false);
      path.scale(0.666666);
      path.move(1.0-0.5*0.333333, 1.0-0.5*0.333333);
      path.insert_point(0, 1.0, 0.5);
      path.add_point(0.5, 1.0);
      path.refresh_segment_info();
      return path.point;
   }

   //path_coordinates[TILE_TYPE_TOP_RIGHT_CURVE] = {};
   //path_coordinates.add_point({ 0.5, 0.0 });
   //path_coordinates.push_back({ 0.5, 0.5 * 0.3333333 });
   //path_coordinates.push_back({ 0.5, 0.5 * 0.3333333 });

   //Path2D &add_arc(float center_x, float center_y, float radius_x, float radius_y, float start_theta,
   //float delta_theta, int num_segments, bool refresh=true);




   if (path_coordinates.find(tile_type) == path_coordinates.end())
   {
      AllegroFlare::Logger::throw_error(
         "Tracko::Visuals::TrackPath::build_points_for_tile_type",
         "Could not find path coordinates for tile type \"" + std::to_string(tile_type) + "\"."
      );
   }

   return path_coordinates[tile_type];
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


