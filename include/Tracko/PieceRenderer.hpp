#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <Tracko/Piece.hpp>
#include <allegro5/allegro_font.h>


namespace Tracko
{
   class PieceRenderer
   {
   private:
      AllegroFlare::FontBin* font_bin;
      Tracko::Piece* piece;
      float width;
      float height;
      ALLEGRO_FONT* obtain_font();

   protected:


   public:
      PieceRenderer(AllegroFlare::FontBin* font_bin=nullptr, Tracko::Piece* piece=nullptr);
      ~PieceRenderer();

      void set_font_bin(AllegroFlare::FontBin* font_bin);
      void set_piece(Tracko::Piece* piece);
      void set_width(float width);
      void set_height(float height);
      AllegroFlare::FontBin* get_font_bin() const;
      Tracko::Piece* get_piece() const;
      float get_width() const;
      float get_height() const;
      void render();
   };
}



