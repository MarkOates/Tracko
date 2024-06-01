#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Camera2D.hpp>
#include <Tracko/BoardRenderer.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();


class Tracko_BoardRendererTest : public ::testing::Test {};
class Tracko_BoardRendererTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};



TEST_F(Tracko_BoardRendererTest, can_be_created_without_blowing_up)
{
   Tracko::BoardRenderer board_renderer;
}


TEST_F(Tracko_BoardRendererTest, render__without_allegro_initialized__raises_an_error)
{
   Tracko::BoardRenderer board_renderer;
   std::string expected_error_message =
      "BoardRenderer::render: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(board_renderer.render(), std::runtime_error, expected_error_message);
}


TEST_F(Tracko_BoardRendererTest, render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   Tracko::BoardRenderer board_renderer;
   std::string expected_error_message =
      "BoardRenderer::render: error: guard \"al_is_primitives_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(board_renderer.render(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(Tracko_BoardRendererTest, render__without_font_addon_initialized__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   Tracko::BoardRenderer board_renderer;
   std::string expected_error_message =
      "BoardRenderer::render: error: guard \"al_is_font_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(board_renderer.render(), std::runtime_error, expected_error_message);
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(Tracko_BoardRendererTest, render__without_a_font_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   Tracko::BoardRenderer board_renderer;
   std::string expected_error_message =
      "BoardRenderer::render: error: guard \"font_bin\" not met";
   EXPECT_THROW_WITH_MESSAGE(board_renderer.render(), std::runtime_error, expected_error_message);
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}   


TEST_F(Tracko_BoardRendererTestWithAllegroRenderingFixture, CAPTURE__render__with_pieces__will_not_blow_up)
{
   AllegroFlare::Camera2D camera;
   camera.size = { 1920, 1080 };
   Tracko::Board board;
   board.resize(7, 5);
   board.fill_with_random_types();
   board.set_start_tile_coordinates({ 0, 1 });
   board.set_start_tile_start_connecting_position(Tracko::Piece::ConnectingPosition::CONNECTING_POSITION_LEFT);
   board.set_exit_tile_coordinates({ 6, 3 });
   board.set_exit_tile_exit_connecting_position(Tracko::Piece::ConnectingPosition::CONNECTING_POSITION_RIGHT);
   board.initialize_pieces();

   camera.start_reverse_transform();
   Tracko::BoardRenderer board_renderer(&get_font_bin_ref(), &board);
   AllegroFlare::Placement2D subject_placement;
   subject_placement.size = { board_renderer.infer_width(), board_renderer.infer_height() };
   subject_placement.start_transform();
   board_renderer.render();
   subject_placement.restore_transform();
   camera.restore_transform();

   al_flip_display();
   sleep_for(1);
}


