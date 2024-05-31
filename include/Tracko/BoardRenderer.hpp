#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <Tracko/Board.hpp>
#include <allegro5/allegro_font.h>


namespace Tracko
{
   class BoardRenderer
   {
   private:
      AllegroFlare::FontBin* font_bin;
      Tracko::Board* board;
      float column_width;
      float row_height;
      ALLEGRO_FONT* obtain_font();

   protected:


   public:
      BoardRenderer(AllegroFlare::FontBin* font_bin=nullptr, Tracko::Board* board=nullptr);
      ~BoardRenderer();

      void set_column_width(float column_width);
      void set_row_height(float row_height);
      float get_column_width() const;
      float get_row_height() const;
      float infer_width();
      float infer_height();
      void render();
   };
}



