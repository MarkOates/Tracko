#pragma once


#include <AllegroFlare/Int2D.hpp>
#include <Tracko/Piece.hpp>
#include <cstdint>
#include <utility>
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
      AllegroFlare::Int2D start_tile_coordinates;
      Tracko::Piece::ConnectingPosition start_tile_start_connecting_position;
      AllegroFlare::Int2D exit_tile_coordinates;
      Tracko::Piece::ConnectingPosition exit_tile_exit_connecting_position;
      float update_rate_denominator;
      int cursor_x;
      int cursor_y;

   protected:


   public:
      Board();
      ~Board();

      void set_pieces(std::vector<std::vector<Tracko::Piece>> pieces);
      void set_swap_piece(Tracko::Piece swap_piece);
      void set_start_tile_coordinates(AllegroFlare::Int2D start_tile_coordinates);
      void set_start_tile_start_connecting_position(Tracko::Piece::ConnectingPosition start_tile_start_connecting_position);
      void set_exit_tile_coordinates(AllegroFlare::Int2D exit_tile_coordinates);
      void set_exit_tile_exit_connecting_position(Tracko::Piece::ConnectingPosition exit_tile_exit_connecting_position);
      void set_update_rate_denominator(float update_rate_denominator);
      std::vector<std::vector<Tracko::Piece>> get_pieces() const;
      int get_num_rows() const;
      int get_num_columns() const;
      AllegroFlare::Int2D get_start_tile_coordinates() const;
      Tracko::Piece::ConnectingPosition get_start_tile_start_connecting_position() const;
      AllegroFlare::Int2D get_exit_tile_coordinates() const;
      Tracko::Piece::ConnectingPosition get_exit_tile_exit_connecting_position() const;
      float get_update_rate_denominator() const;
      int get_cursor_x() const;
      int get_cursor_y() const;
      std::vector<std::vector<Tracko::Piece>> &get_pieces_ref();
      void move_cursor_up();
      void move_cursor_down();
      void move_cursor_left();
      void move_cursor_right();
      void swap();
      bool can_swap();
      std::pair<bool, std::pair<int, int>> calculate_adjacency(int x1=0, int y1=0, int x2=0, int y2=0);
      static Tracko::Piece::ConnectingPosition get_inverse_connection_position(Tracko::Piece::ConnectingPosition connection_position=Tracko::Piece::ConnectingPosition::CONNECTING_POSITION_UNDEF);
      std::pair<Tracko::Piece*, std::pair<int, int>> get_connecting_to_piece(int from_piece_x=0, int from_piece_y=0, Tracko::Piece::ConnectingPosition exiting_connection_position=Tracko::Piece::ConnectingPosition::CONNECTING_POSITION_UNDEF);
      bool have_connecting_edges(int x1=0, int y1=0, int x2=0, int y2=0);
      bool cursor_is_in_valid_position();
      void resize(int num_columns=8, int num_rows=8);
      void fill_with_random_types(uint32_t seed=76414 /*TRAIN*/, bool always_random=false);
      void set_random_tile_with_connection(int x=0, int y=0, Tracko::Piece::ConnectingPosition connecting_position=Tracko::Piece::CONNECTING_POSITION_UNDEF, uint32_t seed=76414 /*TRAIN*/);
      void initialize_pieces();
      Tracko::Piece* get_piece_at_cursor();
      Tracko::Piece* get_piece(int x=8, int y=8);
      bool is_valid_tile_coordinate(int x=8, int y=8);
      Tracko::Piece* get_swap_piece();
   };
}



