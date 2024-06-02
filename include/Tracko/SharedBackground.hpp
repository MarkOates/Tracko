#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/Backgrounds/Base.hpp>
#include <AllegroFlare/Elements/Backgrounds/Parallax.hpp>
#include <AllegroFlare/Elements/Backgrounds/ParallaxLayer.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
#include <vector>


namespace Tracko
{
   class SharedBackground : public AllegroFlare::Elements::Backgrounds::Base
   {
   public:
      static constexpr char* TYPE = (char*)"Tracko/SharedBackground";
      static constexpr ALLEGRO_COLOR DEFAULT_CLEAR_COLOR = ALLEGRO_COLOR{1, 1, 1, 1};

   private:
      AllegroFlare::EventEmitter* event_emitter;
      AllegroFlare::BitmapBin* bitmap_bin;
      AllegroFlare::FontBin* font_bin;
      bool using_clear_color;
      ALLEGRO_COLOR clear_color;
      bool using_parallax;
      AllegroFlare::Elements::Backgrounds::Parallax parallax;
      bool initialized;

   protected:


   public:
      SharedBackground(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, ALLEGRO_COLOR clear_color=DEFAULT_CLEAR_COLOR);
      virtual ~SharedBackground();

      void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
      void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
      void set_font_bin(AllegroFlare::FontBin* font_bin);
      void set_using_clear_color(bool using_clear_color);
      void set_clear_color(ALLEGRO_COLOR clear_color);
      void set_using_parallax(bool using_parallax);
      AllegroFlare::EventEmitter* get_event_emitter() const;
      AllegroFlare::BitmapBin* get_bitmap_bin() const;
      AllegroFlare::FontBin* get_font_bin() const;
      bool get_using_clear_color() const;
      ALLEGRO_COLOR get_clear_color() const;
      bool get_using_parallax() const;
      bool get_initialized() const;
      void initialize();
      virtual void activate() override;
      virtual void deactivate() override;
      virtual void update() override;
      void set_parallax_offset(float offset_x=0.0f, float offset_y=0.0f);
      void set_parallax_layers(std::vector<AllegroFlare::Elements::Backgrounds::ParallaxLayer> parallax_layers={});
      virtual void render() override;
      virtual void show() override;
      virtual void hide() override;
   };
}



