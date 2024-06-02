#pragma once


#include <AllegroFlare/Int2D.hpp>
#include <Tracko/Board.hpp>
#include <Tracko/Piece.hpp>
#include <string>


namespace Tracko
{
   class BoardFactory
   {
   private:

   protected:


   public:
      BoardFactory();
      ~BoardFactory();

      static Tracko::Board* create_board_by_identifier(std::string board_identifier="[unset-board_identifier]");
      static Tracko::Board* create_board(int num_columns=6, int num_rows=4, AllegroFlare::Int2D start_coordinate={ 0, 2 }, Tracko::Piece::ConnectingPosition start_connecting_position=Tracko::Piece::ConnectingPosition::CONNECTING_POSITION_LEFT, AllegroFlare::Int2D end_coordinate={ 5, 1 }, Tracko::Piece::ConnectingPosition end_connecting_position=Tracko::Piece::ConnectingPosition::CONNECTING_POSITION_RIGHT, float update_rate_denominator=8.0f, int seed=0);
   };
}



