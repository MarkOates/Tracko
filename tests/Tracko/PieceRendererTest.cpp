#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <Tracko/PieceRenderer.hpp>
#include <AllegroFlare/Camera2D.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();


class Tracko_PieceRendererTest : public ::testing::Test {};
class Tracko_PieceRendererTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};



TEST_F(Tracko_PieceRendererTest, can_be_created_without_blowing_up)
{
   Tracko::PieceRenderer piece_renderer;
}


TEST_F(Tracko_PieceRendererTest, render__without_allegro_initialized__raises_an_error)
{
   Tracko::PieceRenderer piece_renderer;
   std::string expected_error_message =
      "PieceRenderer::render: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(piece_renderer.render(), std::runtime_error, expected_error_message);
}


TEST_F(Tracko_PieceRendererTest, render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   Tracko::PieceRenderer piece_renderer;
   std::string expected_error_message =
      "PieceRenderer::render: error: guard \"al_is_primitives_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(piece_renderer.render(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(Tracko_PieceRendererTest, render__without_font_addon_initialized__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   Tracko::PieceRenderer piece_renderer;
   std::string expected_error_message =
      "PieceRenderer::render: error: guard \"al_is_font_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(piece_renderer.render(), std::runtime_error, expected_error_message);
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(Tracko_PieceRendererTest, render__without_a_font_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   Tracko::PieceRenderer piece_renderer;
   std::string expected_error_message =
      "PieceRenderer::render: error: guard \"font_bin\" not met";
   EXPECT_THROW_WITH_MESSAGE(piece_renderer.render(), std::runtime_error, expected_error_message);
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}   


TEST_F(Tracko_PieceRendererTestWithAllegroRenderingFixture,
   CAPTURE__render__with_an_undefined_tile_type__will_render_as_expected)
{
   AllegroFlare::Camera2D camera;
   camera.size = { 1920, 1080 };
   Tracko::Piece piece;

   camera.start_reverse_transform();
   AllegroFlare::Placement2D subject_placement;
   Tracko::PieceRenderer piece_renderer(&get_font_bin_ref());
   piece_renderer.set_piece(&piece);

   subject_placement.size = { piece_renderer.get_width(), piece_renderer.get_height() };
   subject_placement.start_transform();
   piece_renderer.render();
   subject_placement.restore_transform();
   camera.restore_transform();

   al_flip_display();

   sleep_for(1);
}


TEST_F(Tracko_PieceRendererTestWithAllegroRenderingFixture,
   CAPTURE__render__on_the_defined_tile_types__will_render_as_expected)
{
   AllegroFlare::Camera2D camera;
   camera.size = { 1920, 1080 };
   Tracko::Piece piece;

   AllegroFlare::Placement2D subject_placement;
   Tracko::PieceRenderer piece_renderer(&get_font_bin_ref());
   piece_renderer.set_piece(&piece);
   subject_placement.size = { piece_renderer.get_width(), piece_renderer.get_height() };

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

   float spacing = 200;
   int num_subjects = tile_types_to_render.size();
   float x = -((num_subjects - 1) * spacing) * 0.5;
   for (auto &tile_type_to_render : tile_types_to_render)
   {
      piece.set_tile_type(tile_type_to_render);
      subject_placement.position.x = x;

      subject_placement.start_transform();
      piece_renderer.render();
      subject_placement.restore_transform();

      x += spacing;
   }

   camera.restore_transform();

   al_flip_display();

   sleep_for(1);
}


