

#include <Tracko/BoardRenderer.hpp>

#include <AllegroFlare/Vec2D.hpp>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Tracko
{


BoardRenderer::BoardRenderer(AllegroFlare::FontBin* font_bin, Tracko::Board* board)
   : font_bin(font_bin)
   , board(board)
{
}


BoardRenderer::~BoardRenderer()
{
}


void BoardRenderer::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[BoardRenderer::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BoardRenderer::render: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[BoardRenderer::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BoardRenderer::render: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[BoardRenderer::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BoardRenderer::render: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[BoardRenderer::render]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BoardRenderer::render: error: guard \"font_bin\" not met");
   }
   if (!(board))
   {
      std::stringstream error_message;
      error_message << "[BoardRenderer::render]: error: guard \"board\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BoardRenderer::render: error: guard \"board\" not met");
   }
   int num_rows = board->get_num_rows();
   int num_columns = board->get_num_columns();
   float row_height = 80;
   float column_width = 80;

   for (int row=0; row<num_rows; row++)
   {
      for (int column=0; column<num_columns; column++)
      {
         float x = row * row_height;
         float y = column * column_width;
         al_draw_filled_circle(x, y, 4, ALLEGRO_COLOR{0.2, 0.21, 0.22, 0.22});
      }
   }
   return;
}

ALLEGRO_FONT* BoardRenderer::obtain_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[BoardRenderer::obtain_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BoardRenderer::obtain_font: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Medium.ttf -52");
}


} // namespace Tracko


