#pragma once


#include <Tracko/Piece.hpp>
#include <cstdint>
#include <vector>


namespace Tracko
{
   class Board
   {
   private:
      std::vector<std::vector<Tracko::Piece>> pieces;
      Tracko::Piece swap_piece;
      int num_rows;
      int num_columns;
      int cursor_x;
      int cursor_y;

   protected:


   public:
      Board();
      ~Board();

      void set_pieces(std::vector<std::vector<Tracko::Piece>> pieces);
      void set_swap_piece(Tracko::Piece swap_piece);
      std::vector<std::vector<Tracko::Piece>> get_pieces() const;
      int get_num_rows() const;
      int get_num_columns() const;
      int get_cursor_x() const;
      int get_cursor_y() const;
      std::vector<std::vector<Tracko::Piece>> &get_pieces_ref();
      void swap();
      bool can_swap();
      bool cursor_is_in_valid_position();
      void resize(int num_columns=8, int num_rows=8);
      void fill_with_random_types(uint32_t seed=76414 /*TRAIN*/);
      Tracko::Piece* get_piece_at_cursor();
      Tracko::Piece* get_piece(int x=8, int y=8);
      Tracko::Piece* get_swap_piece();
   };
}



