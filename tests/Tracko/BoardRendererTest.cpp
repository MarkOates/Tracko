#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
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


TEST_F(Tracko_BoardRendererTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   Tracko::Board board;
   board.resize(7, 5);

   Tracko::BoardRenderer board_renderer(&get_font_bin_ref(), &board);
   board_renderer.render();
   al_flip_display();
   sleep_for(1);
}


