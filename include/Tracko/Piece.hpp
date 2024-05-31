#pragma once


#include <Tracko/Piece.hpp>
#include <allegro5/allegro.h>
#include <cstdint>
#include <utility>


namespace Tracko
{
   class Piece
   {
   private:
      enum TileType
      {
         TILE_TYPE_UNDEF = 0,
         TILE_TYPE_HORIZONTAL_BAR,
         TILE_TYPE_VERTICAL_BAR,
         TILE_TYPE_TOP_RIGHT_CURVE,
         TILE_TYPE_RIGHT_BOTTOM_CURVE,
         TILE_TYPE_BOTTOM_LEFT_CURVE,
         TILE_TYPE_LEFT_TOP_CURVE,
      };
      enum State
      {
         STATE_UNDEF = 0,
         STATE_HIDDEN,
         STATE_REVEALED,
         STATE_FILLING,
         STATE_FILLED,
      };
      float fill_counter;
      uint32_t tile_type;
      uint32_t state;
      bool state_is_busy;
      float state_changed_at;

   protected:


   public:
      Piece();
      ~Piece();

      float get_fill_counter() const;
      uint32_t get_tile_type() const;
      uint32_t get_state() const;
      void set_tile_type(Tracko::Piece::TileType tile_type=TILE_TYPE_UNDEF);
      bool is_filled();
      std::pair<bool, float> fill_with_amount(float amount=0.025f);
      void set_state(uint32_t state=STATE_UNDEF, bool override_if_busy=false);
      void update_state(float time_now=al_get_time());
      static bool is_valid_state(uint32_t state=STATE_UNDEF);
      bool is_state(uint32_t possible_state=STATE_UNDEF);
      float infer_current_state_age(float time_now=al_get_time());
   };
}



