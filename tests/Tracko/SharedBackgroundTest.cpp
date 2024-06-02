
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <Tracko/SharedBackground.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();


class Tracko_SharedBackgroundTest : public ::testing::Test {};
class Tracko_SharedBackgroundTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};



TEST_F(Tracko_SharedBackgroundTest, can_be_created_without_blowing_up)
{
   Tracko::SharedBackground shared_foreground;
}


TEST_F(Tracko_SharedBackgroundTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "Tracko/SharedBackground",
     Tracko::SharedBackground::TYPE
   );
}


TEST_F(Tracko_SharedBackgroundTest, type__has_the_expected_value_matching_TYPE)
{
   Tracko::SharedBackground shared_foreground;
   EXPECT_EQ(Tracko::SharedBackground::TYPE, shared_foreground.get_type());
}


/*
TEST_F(Tracko_SharedBackgroundTest, render__without_allegro_initialized__raises_an_error)
{
   Tracko::SharedBackground shared_foreground;
   std::string expected_error_message =
      "SharedBackground::render: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(shared_foreground.render(), std::runtime_error, expected_error_message);
}


TEST_F(Tracko_SharedBackgroundTest, render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   Tracko::SharedBackground shared_foreground;
   std::string expected_error_message =
      "SharedBackground::render: error: guard \"al_is_primitives_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(shared_foreground.render(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(Tracko_SharedBackgroundTest, render__without_font_addon_initialized__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   Tracko::SharedBackground shared_foreground;
   std::string expected_error_message =
      "SharedBackground::render: error: guard \"al_is_font_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(shared_foreground.render(), std::runtime_error, expected_error_message);
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(Tracko_SharedBackgroundTest, render__without_a_font_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   Tracko::SharedBackground shared_foreground;
   std::string expected_error_message =
      "SharedBackground::render: error: guard \"font_bin\" not met";
   EXPECT_THROW_WITH_MESSAGE(shared_foreground.render(), std::runtime_error, expected_error_message);
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}   
*/


TEST_F(Tracko_SharedBackgroundTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::EventEmitter event_emitter;

   Tracko::SharedBackground shared_foreground;
   shared_foreground.set_event_emitter(&event_emitter);
   shared_foreground.set_bitmap_bin(&get_bitmap_bin_ref());
   shared_foreground.set_font_bin(&get_font_bin_ref());
   shared_foreground.initialize();

   shared_foreground.render();

   al_flip_display();
   sleep_for(1);
}


TEST_F(Tracko_SharedBackgroundTestWithAllegroRenderingFixture,
   CAPTURE__render__with_parallax__will_work_as_expected)
{
   AllegroFlare::EventEmitter event_emitter;
   AllegroFlare::BitmapBin *bitmap_bin = &get_bitmap_bin_ref();

   Tracko::SharedBackground shared_background;
   shared_background.set_event_emitter(&event_emitter);
   shared_background.set_bitmap_bin(bitmap_bin);
   shared_background.set_font_bin(&get_font_bin_ref());
   shared_background.initialize();

   shared_background.set_using_parallax(true);
   shared_background.set_parallax_layers({
      {0, 0, 0.1, bitmap_bin->auto_get("backgrounds/Sky3.png") },
      {0, 0, 0.4, bitmap_bin->auto_get("backgrounds/Cloud3a.png") },
      {0, 0, 0.8, bitmap_bin->auto_get("backgrounds/Cloud3b.png") },
   });

   //sin((float)i/passes * 6.28) * 100);
   shared_background.render();

   al_flip_display();
   sleep_for(1);
}


