#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/Backgrounds/Base.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <cstdint>


namespace Tracko
{
   class SharedForeground : public AllegroFlare::Elements::Backgrounds::Base
   {
   public:
      static constexpr char* CURTAIN_OPENED_GAME_EVENT_NAME = (char*)"Tracko/SharedForeground::curtain_opened";
      static constexpr char* CURTAIN_CLOSED_GAME_EVENT_NAME = (char*)"Tracko/SharedForeground::curtain_closed";
      static constexpr char* TYPE = (char*)"Tracko/SharedForeground";

   private:
      enum CurtainState
      {
         CURTAIN_STATE_UNDEF = 0,
         CURTAIN_STATE_OPENING,
         CURTAIN_STATE_OPEN,
         CURTAIN_STATE_CLOSING,
         CURTAIN_STATE_CLOSED,
      };
      AllegroFlare::EventEmitter* event_emitter;
      AllegroFlare::BitmapBin* bitmap_bin;
      AllegroFlare::FontBin* font_bin;
      float curtain_position;
      uint32_t curtain_state;
      bool curtain_state_is_busy;
      float curtain_state_changed_at;
      bool initialized;
      void set_curtain_state(uint32_t curtain_state=CURTAIN_STATE_UNDEF, bool override_if_busy=false);
      void update_curtain_state(float time_now=al_get_time());
      void emit_curtain_opened_event();
      void emit_curtain_closed_event();

   protected:


   public:
      SharedForeground(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr);
      virtual ~SharedForeground();

      void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
      void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
      void set_font_bin(AllegroFlare::FontBin* font_bin);
      AllegroFlare::EventEmitter* get_event_emitter() const;
      AllegroFlare::BitmapBin* get_bitmap_bin() const;
      AllegroFlare::FontBin* get_font_bin() const;
      float get_curtain_position() const;
      uint32_t get_curtain_state() const;
      bool get_initialized() const;
      void initialize();
      void open_curtain();
      void close_curtain();
      bool curtain_is_open();
      bool curtain_is_closed();
      virtual void activate() override;
      virtual void deactivate() override;
      virtual void update() override;
      virtual void render() override;
      void render_curtains();
      virtual void show() override;
      virtual void hide() override;
      static bool is_valid_curtain_state(uint32_t curtain_state=CURTAIN_STATE_UNDEF);
      bool is_curtain_state(uint32_t possible_curtain_state=CURTAIN_STATE_UNDEF);
      float infer_current_curtain_state_age(float time_now=al_get_time());
   };
}



