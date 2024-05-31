#pragma once


#include <allegro5/allegro.h>
#include <cstdint>


namespace Tracko
{
   class Piece
   {
   private:
      enum State
      {
         STATE_UNDEF = 0,
         STATE_HIDDEN,
         STATE_REVEALED,
         STATE_FILLING,
         STATE_FILLED,
      };
      uint32_t state;
      bool state_is_busy;
      float state_changed_at;

   protected:


   public:
      Piece();
      ~Piece();

      uint32_t get_state() const;
      void set_state(uint32_t state=STATE_UNDEF, bool override_if_busy=false);
      void update_state(float time_now=al_get_time());
      static bool is_valid_state(uint32_t state=STATE_UNDEF);
      bool is_state(uint32_t possible_state=STATE_UNDEF);
      float infer_current_state_age(float time_now=al_get_time());
   };
}



