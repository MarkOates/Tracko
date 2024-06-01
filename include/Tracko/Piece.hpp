#pragma once


#include <Tracko/Piece.hpp>
#include <allegro5/allegro.h>
#include <cstdint>
#include <utility>
#include <vector>


namespace Tracko
{
   class Piece
   {
   public:

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
      enum ConnectingPosition
      {
         CONNECTING_POSITION_UNDEF = 0,
         CONNECTING_POSITION_LEFT,
         CONNECTING_POSITION_TOP,
         CONNECTING_POSITION_RIGHT,
         CONNECTING_POSITION_BOTTOM,
      };
      enum State
      {
         STATE_UNDEF = 0,
         STATE_HIDDEN,
         STATE_REVEALED,
         STATE_FILLING,
         STATE_FILLED,
      };
   private:
      float fill_counter;
      Tracko::Piece::TileType tile_type;
      uint32_t entrance_connecting_position;
      uint32_t state;
      bool state_is_busy;
      float state_changed_at;
      bool initialized;

   protected:


   public:
      Piece();
      ~Piece();

      float get_fill_counter() const;
      Tracko::Piece::TileType get_tile_type() const;
      uint32_t get_entrance_connecting_position() const;
      uint32_t get_state() const;
      bool get_initialized() const;
      void initialize();
      bool infer_can_swap();
      bool infer_can_fill();
      bool infer_can_reveal();
      void reveal();
      bool is_hidden();
      void set_tile_type(Tracko::Piece::TileType tile_type=TILE_TYPE_UNDEF);
      void set_entrance_connecting_position(Tracko::Piece::ConnectingPosition entrance_connecting_position=CONNECTING_POSITION_UNDEF);
      static std::pair<Tracko::Piece::ConnectingPosition, Tracko::Piece::ConnectingPosition> get_connecting_positions(Tracko::Piece::TileType tile_type=TILE_TYPE_UNDEF);
      static std::vector<Tracko::Piece::TileType> get_types_with_connecting_position(Tracko::Piece::ConnectingPosition connecting_position=CONNECTING_POSITION_UNDEF);
      Tracko::Piece::ConnectingPosition infer_exit_connecting_position();
      bool is_filled();
      std::pair<bool, float> fill_with_amount(float amount=0.025f);
      void set_state(uint32_t state=STATE_UNDEF, bool override_if_busy=false);
      void update_state(float time_now=al_get_time());
      static bool is_valid_state(uint32_t state=STATE_UNDEF);
      bool is_state(uint32_t possible_state=STATE_UNDEF);
      float infer_current_state_age(float time_now=al_get_time());
   };
}



