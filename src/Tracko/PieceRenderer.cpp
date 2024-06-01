

#include <Tracko/PieceRenderer.hpp>

#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/Model3D.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>


namespace Tracko
{


PieceRenderer::PieceRenderer(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::ModelBin* model_bin, Tracko::Piece* piece)
   : bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , model_bin(model_bin)
   , piece(piece)
   , width(120.0f)
   , height(120.0f)
{
}


PieceRenderer::~PieceRenderer()
{
}


void PieceRenderer::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


void PieceRenderer::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void PieceRenderer::set_model_bin(AllegroFlare::ModelBin* model_bin)
{
   this->model_bin = model_bin;
}


void PieceRenderer::set_piece(Tracko::Piece* piece)
{
   this->piece = piece;
}


void PieceRenderer::set_width(float width)
{
   this->width = width;
}


void PieceRenderer::set_height(float height)
{
   this->height = height;
}


AllegroFlare::BitmapBin* PieceRenderer::get_bitmap_bin() const
{
   return bitmap_bin;
}


AllegroFlare::FontBin* PieceRenderer::get_font_bin() const
{
   return font_bin;
}


AllegroFlare::ModelBin* PieceRenderer::get_model_bin() const
{
   return model_bin;
}


Tracko::Piece* PieceRenderer::get_piece() const
{
   return piece;
}


float PieceRenderer::get_width() const
{
   return width;
}


float PieceRenderer::get_height() const
{
   return height;
}


void PieceRenderer::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[PieceRenderer::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PieceRenderer::render: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[PieceRenderer::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PieceRenderer::render: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[PieceRenderer::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PieceRenderer::render: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[PieceRenderer::render]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PieceRenderer::render: error: guard \"font_bin\" not met");
   }
   if (!(piece))
   {
      std::stringstream error_message;
      error_message << "[PieceRenderer::render]: error: guard \"piece\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PieceRenderer::render: error: guard \"piece\" not met");
   }
   if (!(piece->get_initialized()))
   {
      std::stringstream error_message;
      error_message << "[PieceRenderer::render]: error: guard \"piece->get_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PieceRenderer::render: error: guard \"piece->get_initialized()\" not met");
   }
   std::string quote = "piece";
   // float x = 1920/2;
   // float y = 1080/3;
   ALLEGRO_FONT *font = obtain_font();
   //float text_width = al_get_text_width(font, quote.c_str());
   //float text_height = al_get_font_line_height(font);
   //float h_text_width = width;
   //float h_text_height = height;
   AllegroFlare::Vec2D padding = {30, 20};

   // Draw the connection points
   float center_x = width * 0.5;
   float center_y = height * 0.5;
   float dist = width * 0.5 * 0.6;

   ALLEGRO_COLOR hidden_appearance_color = ALLEGRO_COLOR{0.2, 0.21, 0.22, 0.22};

   if (piece->is_hidden())
   {
      // Draw hidden appearance
      al_draw_rounded_rectangle(
         4,
         4,
         width-4,
         height-4,
         8.0f,
         8.0f,
         hidden_appearance_color,
         4.0f
      );

      int font_line_height = al_get_font_line_height(font);
      al_draw_text(font, hidden_appearance_color, center_x, center_y-font_line_height * 0.5f,
         ALLEGRO_ALIGN_CENTER, "?");
   }
   else
   {
      // Draw revealed appearance
      al_draw_rounded_rectangle(
         4,
         4,
         width-4,
         height-4,
         8.0f,
         8.0f,
         ALLEGRO_COLOR{1, 1, 1, 1},
         4.0f
      );

      // Draw connection points
      if (piece->get_tile_type() != Tracko::Piece::TILE_TYPE_UNDEF)
      {
         // DEVELOPMENT: Draw connection points
         std::pair<AllegroFlare::Vec2D, AllegroFlare::Vec2D> connection_coords =
            get_connecting_coords_for_type(piece->get_tile_type());

         std::vector<AllegroFlare::Vec2D> connection_coords_vec = { connection_coords.first, connection_coords.second };

         for (auto &connection_coord : connection_coords_vec)
         {
            float x = center_x + connection_coord.x * dist;
            float y = center_y + connection_coord.y * dist;
            al_draw_filled_circle(x, y, 8, ALLEGRO_COLOR{ 0.3, 0.4, 0.3, 0.4 });
         }

         if (bitmap_bin)
         {
            ALLEGRO_BITMAP *bitmap = bitmap_bin->auto_get(
                  get_bitmap_identifier_for_type(piece->get_tile_type())
               );
            AllegroFlare::Placement2D bitmap_placement;
            bitmap_placement.scale = { width / al_get_bitmap_width(bitmap), height / al_get_bitmap_height(bitmap) };
            bitmap_placement.start_transform();
            al_draw_bitmap(bitmap, 0, 0, 0);
            bitmap_placement.restore_transform();
         }

         
         //if (model_bin && bitmap_bin)
         //{
            //ALLEGRO_BITMAP *texture = bitmap_bin->auto_get("tiles_4x3-01-horizontal-01.png");
            //AllegroFlare::Model3D *model = model_bin->auto_get(
                  //get_model_identifier_for_type(piece->get_tile_type())
               //);
            //if (model)
            //{
               //model->set_texture(texture);
               //model->draw();
            //}
         //}
      }

      // Draw fill_counter
      ALLEGRO_COLOR dial_color = al_color_name("gray");
      if (piece->is_filled()) dial_color = al_color_name("forestgreen");
      if (piece->is_partially_filled()) dial_color = al_color_name("aquamarine");
      al_draw_arc(center_x, center_y, 20, 0, piece->get_fill_counter() * (ALLEGRO_PI * 2), dial_color, 12);
   }

   // Draw some tile type undefined warning
   if (piece->get_tile_type() == Tracko::Piece::TILE_TYPE_UNDEF)
   {
      int font_line_height = al_get_font_line_height(font);
      al_draw_text(font, ALLEGRO_COLOR{1, 1, 0.5, 1}, center_x, center_y-font_line_height * 0.5f, ALLEGRO_ALIGN_CENTER,
         "undefined type");
   }

   return;
}

std::string PieceRenderer::get_model_identifier_for_type(Tracko::Piece::TileType tile_type)
{
   std::map<Piece::TileType, std::string> model_identifiers = {
      { Piece::TILE_TYPE_HORIZONTAL_BAR,     "tiles_4x3-01-horizontal-01.obj" },
      { Piece::TILE_TYPE_VERTICAL_BAR,       "tiles_4x3-01-horizontal-01.obj" },
      { Piece::TILE_TYPE_TOP_RIGHT_CURVE,    "tiles_4x3-01-horizontal-01.obj" },
      { Piece::TILE_TYPE_RIGHT_BOTTOM_CURVE, "tiles_4x3-01-horizontal-01.obj" },
      { Piece::TILE_TYPE_BOTTOM_LEFT_CURVE,  "tiles_4x3-01-horizontal-01.obj" },
      { Piece::TILE_TYPE_LEFT_TOP_CURVE,     "tiles_4x3-01-horizontal-01.obj" },
   };

   if (model_identifiers.find(tile_type) == model_identifiers.end())
   {
      AllegroFlare::Logger::throw_error(
         "Tracko::PieceRenderer::get_model_identifier_for_type",
         "Unable to handle case for the Tracko::Piece::TileType \""
            + std::to_string(tile_type) + "\""
      );
   }

   return model_identifiers[tile_type];
}

std::string PieceRenderer::get_bitmap_identifier_for_type(Tracko::Piece::TileType tile_type)
{
   std::map<Piece::TileType, std::string> model_identifiers = {
      { Piece::TILE_TYPE_HORIZONTAL_BAR,     "horizontal-01.png" },
      { Piece::TILE_TYPE_VERTICAL_BAR,       "vertical-01.png" },
      { Piece::TILE_TYPE_TOP_RIGHT_CURVE,    "top_right-01.png" },
      { Piece::TILE_TYPE_RIGHT_BOTTOM_CURVE, "right_bottom-01.png" },
      { Piece::TILE_TYPE_BOTTOM_LEFT_CURVE,  "bottom_left-01.png" },
      { Piece::TILE_TYPE_LEFT_TOP_CURVE,     "left_top-01.png" },
   };

   if (model_identifiers.find(tile_type) == model_identifiers.end())
   {
      AllegroFlare::Logger::throw_error(
         "Tracko::PieceRenderer::get_bitmap_identifier_for_type",
         "Unable to handle case for the Tracko::Piece::TileType \""
            + std::to_string(tile_type) + "\""
      );
   }

   return model_identifiers[tile_type];
}

std::pair<AllegroFlare::Vec2D, AllegroFlare::Vec2D> PieceRenderer::get_connecting_coords_for_type(Tracko::Piece::TileType tile_type)
{
   std::pair<Tracko::Piece::ConnectingPosition, Tracko::Piece::ConnectingPosition> connecting_positions =
      Tracko::Piece::get_connecting_positions(tile_type);
   return { get_connecting_coords(connecting_positions.first), get_connecting_coords(connecting_positions.second) };
}

AllegroFlare::Vec2D PieceRenderer::get_connecting_coords(Tracko::Piece::ConnectingPosition connecting_position)
{
   std::map<Tracko::Piece::ConnectingPosition, AllegroFlare::Vec2D> connecting_position_coords = {
      { Tracko::Piece::CONNECTING_POSITION_LEFT, { -1.0, 0.0 } },
      { Tracko::Piece::CONNECTING_POSITION_TOP, { 0.0, -1.0 } },
      { Tracko::Piece::CONNECTING_POSITION_RIGHT, { 1.0, 0.0 } },
      { Tracko::Piece::CONNECTING_POSITION_BOTTOM, { 0.0, 1.0 } },
   };

   if (connecting_position_coords.find(connecting_position) == connecting_position_coords.end())
   {
      AllegroFlare::Logger::throw_error(
         "Tracko::PieceRenderer::get_connecting_coors",
         "Unable to handle case for the Tracko::Piece::ConnectingPosition \""
            + std::to_string(connecting_position) + "\""
      );
   }
   AllegroFlare::Vec2D connecting_coords = connecting_position_coords[connecting_position];

   return connecting_coords;
}

ALLEGRO_FONT* PieceRenderer::obtain_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[PieceRenderer::obtain_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PieceRenderer::obtain_font: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Medium.ttf -52");
}


} // namespace Tracko


