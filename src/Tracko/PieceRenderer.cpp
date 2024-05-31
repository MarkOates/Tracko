

#include <Tracko/PieceRenderer.hpp>

#include <AllegroFlare/Vec2D.hpp>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Tracko
{


PieceRenderer::PieceRenderer(AllegroFlare::FontBin* font_bin, Tracko::Piece* piece)
   : font_bin(font_bin)
   , piece(piece)
   , width(120.0f)
   , height(120.0f)
{
}


PieceRenderer::~PieceRenderer()
{
}


void PieceRenderer::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
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


AllegroFlare::FontBin* PieceRenderer::get_font_bin() const
{
   return font_bin;
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
   std::string quote = "piece";
   // float x = 1920/2;
   // float y = 1080/3;
   ALLEGRO_FONT *font = obtain_font();
   //float text_width = al_get_text_width(font, quote.c_str());
   //float text_height = al_get_font_line_height(font);
   //float h_text_width = width;
   //float h_text_height = height;
   AllegroFlare::Vec2D padding = {30, 20};

   al_draw_rounded_rectangle(
      0,
      0,
      width,
      height,
      8.0f,
      8.0f,
      ALLEGRO_COLOR{1, 1, 1, 1},
      8.0f
   );
   //al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, 0, 0-h_text_height, ALLEGRO_ALIGN_CENTER, quote.c_str());
   return;
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


