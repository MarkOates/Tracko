#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <Tracko/Board.hpp>
#include <allegro5/allegro_font.h>


namespace Tracko
{
   class BoardRenderer
   {
   private:
      AllegroFlare::BitmapBin* bitmap_bin;
      AllegroFlare::FontBin* font_bin;
      AllegroFlare::ModelBin* model_bin;
      Tracko::Board* board;
      float column_width;
      float row_height;
      ALLEGRO_FONT* obtain_font();

   protected:


   public:
      BoardRenderer(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::ModelBin* model_bin=nullptr, Tracko::Board* board=nullptr);
      ~BoardRenderer();

      void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
      void set_font_bin(AllegroFlare::FontBin* font_bin);
      void set_model_bin(AllegroFlare::ModelBin* model_bin);
      void set_board(Tracko::Board* board);
      void set_column_width(float column_width);
      void set_row_height(float row_height);
      AllegroFlare::BitmapBin* get_bitmap_bin() const;
      AllegroFlare::FontBin* get_font_bin() const;
      AllegroFlare::ModelBin* get_model_bin() const;
      Tracko::Board* get_board() const;
      float get_column_width() const;
      float get_row_height() const;
      float infer_width();
      float infer_height();
      void render();
   };
}



