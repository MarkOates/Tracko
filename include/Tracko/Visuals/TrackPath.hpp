#pragma once


#include <AllegroFlare/Path2D.hpp>


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
      };
   }
}



