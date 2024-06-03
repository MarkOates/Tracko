

#include <Tracko/BoardRenderer.hpp>

#include <AllegroFlare/Placement2D.hpp>
#include <AllegroFlare/Placement3D.hpp>
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


BoardRenderer::BoardRenderer(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::ModelBin* model_bin, Tracko::Board* board, std::string train_icon_bitmap_identifier)
   : bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , model_bin(model_bin)
   , board(board)
   , train_icon_bitmap_identifier(train_icon_bitmap_identifier)
   , column_width(120.0f)
   , row_height(120.0f)
{
}


BoardRenderer::~BoardRenderer()
{
}


void BoardRenderer::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


void BoardRenderer::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void BoardRenderer::set_model_bin(AllegroFlare::ModelBin* model_bin)
{
   this->model_bin = model_bin;
}


void BoardRenderer::set_board(Tracko::Board* board)
{
   this->board = board;
}


void BoardRenderer::set_train_icon_bitmap_identifier(std::string train_icon_bitmap_identifier)
{
   this->train_icon_bitmap_identifier = train_icon_bitmap_identifier;
}


void BoardRenderer::set_column_width(float column_width)
{
   this->column_width = column_width;
}


void BoardRenderer::set_row_height(float row_height)
{
   this->row_height = row_height;
}


AllegroFlare::BitmapBin* BoardRenderer::get_bitmap_bin() const
{
   return bitmap_bin;
}


AllegroFlare::FontBin* BoardRenderer::get_font_bin() const
{
   return font_bin;
}


AllegroFlare::ModelBin* BoardRenderer::get_model_bin() const
{
   return model_bin;
}


Tracko::Board* BoardRenderer::get_board() const
{
   return board;
}


std::string BoardRenderer::get_train_icon_bitmap_identifier() const
{
   return train_icon_bitmap_identifier;
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

void BoardRenderer::render_models()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[BoardRenderer::render_models]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BoardRenderer::render_models: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[BoardRenderer::render_models]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BoardRenderer::render_models: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[BoardRenderer::render_models]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BoardRenderer::render_models: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[BoardRenderer::render_models]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BoardRenderer::render_models: error: guard \"font_bin\" not met");
   }
   if (!(board))
   {
      std::stringstream error_message;
      error_message << "[BoardRenderer::render_models]: error: guard \"board\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BoardRenderer::render_models: error: guard \"board\" not met");
   }
   int num_rows = board->get_num_rows();
   int num_columns = board->get_num_columns();

   // Draw the 3D pieces
   if (model_bin && bitmap_bin)
   {
      AllegroFlare::Placement3D piece_placement_3d;
      for (int x=0; x<num_columns; x++)
      {
         for (int y=0; y<num_rows; y++)
         {
            Tracko::Piece* piece = board->get_piece(x, y);
            float center_x = x * column_width + column_width * 0.5;
            float center_y = y * row_height + row_height * 0.5;

            Tracko::PieceRenderer piece_renderer;//(font_bin, model_bin, piece);
            piece_renderer.set_bitmap_bin(bitmap_bin);
            piece_renderer.set_font_bin(font_bin);
            piece_renderer.set_model_bin(model_bin);
            piece_renderer.set_piece(piece);

            float scale = 0.25;
            //piece_placement.scale = { scale, scale, scale };
            piece_placement_3d.rotation += { 0.25, 0.0, 0.0 };

            piece_placement_3d.position = { center_x, center_y };
            //piece_placement_3d.size = { piece_renderer.get_width(), piece_renderer.get_height() };
            //piece_placement_3d.scale = { 0.3f, 0.3f, 0.3f };
            piece_placement_3d.start_transform();
            piece_renderer.render();
            piece_placement_3d.restore_transform();
         }
      }
   }
   return;
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
   bool train_is_on_board = false;
   AllegroFlare::Vec2D train_position;
   AllegroFlare::Int2D train_tile_xy;
   //get_path_pos

   int num_rows = board->get_num_rows();
   int num_columns = board->get_num_columns();
   ALLEGRO_COLOR grid_color = ALLEGRO_COLOR{0.2, 0.21, 0.22, 0.22};

   // Draw the empty board lines
   bool draw_board_grid_lines_and_cell_points = false;
   if (draw_board_grid_lines_and_cell_points)
   {
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
   }

   // Draw the actual pieces
   AllegroFlare::Placement2D piece_placement;
   for (int x=0; x<num_columns; x++)
   {
      for (int y=0; y<num_rows; y++)
      {
         bool train_is_on_this_piece = false;

         Tracko::Piece* piece = board->get_piece(x, y);
         float center_x = x * column_width + column_width * 0.5;
         float center_y = y * row_height + row_height * 0.5;

         if (piece->is_state(Piece::STATE_FILLING))
         {
            // Train is on this piece
            train_is_on_board = true;
            train_is_on_this_piece = true;
            bool is_on_path = false;
            AllegroFlare::Vec2D path_pos = { 0, 0 };
            std::tie(is_on_path, path_pos) = piece->get_path_pos();
            train_position.x = path_pos.x * column_width;
            train_position.y = path_pos.y * row_height;
            train_tile_xy = { x, y };
         }

         Tracko::PieceRenderer piece_renderer;//(font_bin, model_bin, piece);
         piece_renderer.set_bitmap_bin(bitmap_bin);
         piece_renderer.set_font_bin(font_bin);
         //piece_renderer.set_model_bin(model_bin);
         piece_renderer.set_piece(piece);

         piece_placement.position = { center_x, center_y };
         piece_placement.size = { piece_renderer.get_width(), piece_renderer.get_height() };
         piece_placement.start_transform();
         piece_renderer.render();
         bool render_train_on_piece = false;
         if (train_is_on_this_piece && render_train_on_piece)
         {
            al_draw_filled_circle(train_position.x, train_position.y, 6, ALLEGRO_COLOR{1.0, 0.8, 0.5, 1.0});
         }
         piece_placement.restore_transform();
      }
   }

   // Draw the entrance
   AllegroFlare::Int2D start_tile_coordinates = board->get_start_tile_coordinates();
   Tracko::Piece::ConnectingPosition start_tile_start_connecting_position = 
      board->get_start_tile_start_connecting_position();
   AllegroFlare::Vec2D start_tile_connecting_delta =
      Tracko::PieceRenderer::get_connecting_coords(start_tile_start_connecting_position);
   float entrance_tile_center_x = start_tile_coordinates.x * column_width + column_width * 0.5;
   float entrance_tile_center_y = start_tile_coordinates.y * row_height + row_height * 0.5;
   AllegroFlare::Vec2D start_tile_connecting_offset = start_tile_connecting_delta * row_height * 0.5;
   float start_tile_entrance_x = entrance_tile_center_x + start_tile_connecting_offset.x;
   float start_tile_entrance_y = entrance_tile_center_y + start_tile_connecting_offset.y;
   al_draw_filled_circle(start_tile_entrance_x, start_tile_entrance_y, 9, al_color_name("aliceblue"));

   // Draw the exit
   AllegroFlare::Int2D exit_tile_coordinates = board->get_exit_tile_coordinates();
   Tracko::Piece::ConnectingPosition exit_tile_exit_connecting_position = 
      board->get_exit_tile_exit_connecting_position();
   AllegroFlare::Vec2D exit_tile_connecting_delta =
      Tracko::PieceRenderer::get_connecting_coords(exit_tile_exit_connecting_position);
   float exit_tile_center_x = exit_tile_coordinates.x * column_width + column_width * 0.5;
   float exit_tile_center_y = exit_tile_coordinates.y * row_height + row_height * 0.5;
   AllegroFlare::Vec2D exit_tile_connecting_offset = exit_tile_connecting_delta * row_height * 0.5;
   float exit_tile_exit_x = exit_tile_center_x + exit_tile_connecting_offset.x;
   float exit_tile_exit_y = exit_tile_center_y + exit_tile_connecting_offset.y;
   al_draw_filled_circle(exit_tile_exit_x, exit_tile_exit_y, 9, al_color_name("aliceblue"));

   // Draw the train
   if (train_is_on_board)
   {
      ALLEGRO_BITMAP *train_icon_bitmap = bitmap_bin->auto_get(train_icon_bitmap_identifier);
      float train_x = train_tile_xy.x * column_width + train_position.x;
      float train_y = train_tile_xy.y * row_height + train_position.y;
      if (!train_icon_bitmap)
      {
         //float train_x = train_tile_xy.x * column_width + train_position.x;
         //float train_y = train_tile_xy.y * row_height + train_position.y;
         ALLEGRO_COLOR train_color = ALLEGRO_COLOR{ 1, 0, 1, 1 };
         al_draw_circle(train_x, train_y, 8, train_color, 2.0);
      }
      else
      {
         AllegroFlare::Placement2D train_icon_placement;
         train_icon_placement.scale = { 0.34, 0.34 };
         train_icon_placement.position = { train_x, train_y };
         train_icon_placement.size = {
               (float)al_get_bitmap_width(train_icon_bitmap),
               (float)al_get_bitmap_height(train_icon_bitmap)
            };
         train_icon_placement.start_transform();
         al_draw_bitmap(train_icon_bitmap, 0, 0, 0);
         train_icon_placement.restore_transform();
      }

      //ALLEGRO_BITMAP *bitmap = train_icon_bitmap_identifier

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


