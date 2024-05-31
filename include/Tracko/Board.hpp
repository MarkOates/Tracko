#pragma once


#include <Tracko/Piece.hpp>
#include <vector>


namespace Tracko
{
   class Board
   {
   private:
      std::vector<std::vector<Tracko::Piece>> pieces;
      int num_rows;
      int num_columns;

   protected:


   public:
      Board();
      ~Board();

      void set_pieces(std::vector<std::vector<Tracko::Piece>> pieces);
      std::vector<std::vector<Tracko::Piece>> get_pieces() const;
      int get_num_rows() const;
      int get_num_columns() const;
      void resize(int num_columns=8, int num_rows=8);
      Tracko::Piece* get_piece(int x=8, int y=8);
   };
}



