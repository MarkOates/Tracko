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
      ALLEGRO_FONT* obtain_font();

   protected:


   public:
      BoardRenderer(AllegroFlare::FontBin* font_bin=nullptr, Tracko::Board* board=nullptr);
      ~BoardRenderer();

      void render();
   };
}



