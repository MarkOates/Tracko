#pragma once


#include <AllegroFlare/Path2D.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <Tracko/Piece.hpp>
#include <vector>


namespace Tracko
{
   namespace Visuals
   {
      class TrackPath
      {
      private:
         AllegroFlare::Path2D path;

      protected:


      public:
         TrackPath(AllegroFlare::Path2D path={});
         ~TrackPath();

         void set_path(AllegroFlare::Path2D path);
         AllegroFlare::Path2D get_path() const;
         AllegroFlare::Path2D &get_path_ref();
         void render();
         void reverse_points();
         static std::vector<AllegroFlare::Vec2D> build_points_for_tile_type(Tracko::Piece::TileType tile_type=Tracko::Piece::TileType::TILE_TYPE_UNDEF);
         void render_point_at(float position=0.0f);
      };
   }
}



