#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <Tracko/Visuals/TrackPath.hpp>
#include <AllegroFlare/Camera2D.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();


class Tracko_Visuals_TrackPathTest : public ::testing::Test {};
class Tracko_Visuals_TrackPathTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};



TEST_F(Tracko_Visuals_TrackPathTest, can_be_created_without_blowing_up)
{
   Tracko::Visuals::TrackPath track_path;
}


TEST_F(Tracko_Visuals_TrackPathTest, render__without_allegro_initialized__raises_an_error)
{
   Tracko::Visuals::TrackPath track_path;
   std::string expected_error_message =
      "TrackPath::render: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(track_path.render(), std::runtime_error, expected_error_message);
}


/*
TEST_F(Tracko_Visuals_TrackPathTest, render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   Tracko::Visuals::TrackPath track_path;
   std::string expected_error_message =
      "TrackPath::render: error: guard \"al_is_primitives_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(track_path.render(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(Tracko_Visuals_TrackPathTest, render__without_font_addon_initialized__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   Tracko::Visuals::TrackPath track_path;
   std::string expected_error_message =
      "TrackPath::render: error: guard \"al_is_font_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(track_path.render(), std::runtime_error, expected_error_message);
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(Tracko_Visuals_TrackPathTest, render__without_a_font_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   Tracko::Visuals::TrackPath track_path;
   std::string expected_error_message =
      "TrackPath::render: error: guard \"font_bin\" not met";
   EXPECT_THROW_WITH_MESSAGE(track_path.render(), std::runtime_error, expected_error_message);
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}   
*/


TEST_F(Tracko_Visuals_TrackPathTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::Camera2D camera;
   camera.size = { 1920, 1080 };
   Tracko::Visuals::TrackPath track_path;
   AllegroFlare::Path2D &path = track_path.get_path_ref();
   ALLEGRO_COLOR frame_color = ALLEGRO_COLOR{0.4, 0.41, 0.42, 0.42};

   path.add_point(0.0f, 0.5f);
   path.add_point(1.0f, 0.5f);

   float scale = 200.0f;

   camera.start_reverse_transform();
   al_draw_rectangle(0, 0, scale, scale, frame_color, 2.0f);
   path.scale(200); // For visual purposes
   track_path.render();
   track_path.render_point_at(0.2);
   camera.restore_transform();

   al_flip_display();
   sleep_for(1);
}


TEST_F(Tracko_Visuals_TrackPathTestWithAllegroRenderingFixture, CAPTURE__build_points_for_tile_type__will_return_\
points_for_the_path_shape)
{
   AllegroFlare::Camera2D camera;
   camera.size = { 1920, 1080 };

   std::vector<Tracko::Piece::TileType> tile_types_to_render = {
      //Tracko::Piece::TILE_TYPE_UNDEF,
      Tracko::Piece::TILE_TYPE_HORIZONTAL_BAR,
      Tracko::Piece::TILE_TYPE_VERTICAL_BAR,
      Tracko::Piece::TILE_TYPE_TOP_RIGHT_CURVE,
      Tracko::Piece::TILE_TYPE_RIGHT_BOTTOM_CURVE,
      Tracko::Piece::TILE_TYPE_BOTTOM_LEFT_CURVE,
      Tracko::Piece::TILE_TYPE_LEFT_TOP_CURVE,
   };

   camera.start_reverse_transform();

   float spacing = 200.0f;
   float scale = 180.0f;

   int num_subjects = tile_types_to_render.size();
   float x = -((num_subjects - 1) * spacing) * 0.5;
   for (auto &tile_type_to_render : tile_types_to_render)
   {
      // Build the piece
      //Tracko::Piece piece;
      //piece.set_tile_type(tile_type_to_render);
      //piece.initialize();
      //piece.reveal();

      // Build the placement
      AllegroFlare::Placement2D subject_placement;
      //Tracko::PieceRenderer piece_renderer(&get_font_bin_ref());
      //piece_renderer.set_piece(&piece);
      //subject_placement.size = { piece_renderer.get_width(), piece_renderer.get_height() };
      //subject_placement.position.x = x;

      // Render the subject
      //subject_placement.start_transform();
      //piece_renderer.render();
      //subject_placement.restore_transform();

      x += spacing;
   }

   camera.restore_transform();

   al_flip_display();

   sleep_for(1);
}


