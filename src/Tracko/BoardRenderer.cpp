

#include <Tracko/BoardRenderer.hpp>

#include <AllegroFlare/Placement2D.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <Tracko/PieceRenderer.hpp>
#include <allegro5/allegro_color.h>
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
   , column_width(120.0f)
   , row_height(120.0f)
{
}


BoardRenderer::~BoardRenderer()
{
}


void BoardRenderer::set_column_width(float column_width)
{
   this->column_width = column_width;
}


void BoardRenderer::set_row_height(float row_height)
{
   this->row_height = row_height;
}


float BoardRenderer::get_column_width() const
{
   return column_width;
}


float BoardRenderer::get_row_height() const
{
   return row_height;
}


float BoardRenderer::infer_width()
{
   if (!(board))
   {
      std::stringstream error_message;
      error_message << "[BoardRenderer::infer_width]: error: guard \"board\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BoardRenderer::infer_width: error: guard \"board\" not met");
   }
   return board->get_num_columns() * column_width;
}

float BoardRenderer::infer_height()
{
   if (!(board))
   {
      std::stringstream error_message;
      error_message << "[BoardRenderer::infer_height]: error: guard \"board\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BoardRenderer::infer_height: error: guard \"board\" not met");
   }
   return board->get_num_rows() * row_height;
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
   ALLEGRO_COLOR grid_color = ALLEGRO_COLOR{0.2, 0.21, 0.22, 0.22};

   // Draw the empty board lines
   for (int column=0; column<num_columns; column++)
   {
      for (int row=0; row<num_rows; row++)
      {
         float x1 = column * column_width;
         float y1 = row * row_height;
         float x2 = column * column_width + column_width;
         float y2 = row * row_height + row_height;
         float center_x = x1 + column_width * 0.5;
         float center_y = y1 + row_height * 0.5;
         al_draw_filled_circle(center_x, center_y, 4, grid_color);
         al_draw_rectangle(x1, y1, x2, y2, grid_color, 1.0);
      }
   }

   // Draw the actual pieces
   AllegroFlare::Placement2D piece_placement;
   for (int x=0; x<num_columns; x++)
   {
      for (int y=0; y<num_rows; y++)
      {
         Tracko::Piece* piece = board->get_piece(x, y);
         float center_x = x * column_width + column_width * 0.5;
         float center_y = y * row_height + row_height * 0.5;

         Tracko::PieceRenderer piece_renderer(font_bin, piece);

         piece_placement.position = { center_x, center_y };
         piece_placement.size = { piece_renderer.get_width(), piece_renderer.get_height() };
         piece_placement.start_transform();
         piece_renderer.render();
         piece_placement.restore_transform();
      }
   }

   // Draw the position of the cursor
   float cursor_column = board->get_cursor_x();
   float cursor_row = board->get_cursor_y();
   float x1 = cursor_column * column_width;
   float y1 = cursor_row * row_height;
   float x2 = cursor_column * column_width + column_width;
   float y2 = cursor_row * row_height + row_height;
   float center_x = x1 + column_width * 0.5;
   float center_y = y1 + row_height * 0.5;
   al_draw_rectangle(x1, y1, x2, y2, al_color_name("dodgerblue"), 7.0);


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


