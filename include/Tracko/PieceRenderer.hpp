#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <Tracko/Piece.hpp>
#include <allegro5/allegro_font.h>
#include <string>
#include <utility>


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
      static std::string get_model_identifier_for_type(Tracko::Piece::TileType tile_type=Tracko::Piece::TILE_TYPE_UNDEF);
      static std::pair<AllegroFlare::Vec2D, AllegroFlare::Vec2D> get_connecting_coords_for_type(Tracko::Piece::TileType tile_type=Tracko::Piece::TILE_TYPE_UNDEF);
      static AllegroFlare::Vec2D get_connecting_coords(Tracko::Piece::ConnectingPosition connecting_position=Tracko::Piece::CONNECTING_POSITION_UNDEF);
   };
}



