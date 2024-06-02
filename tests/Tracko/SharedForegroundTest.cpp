#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <Tracko/SharedForeground.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();


class Tracko_SharedForegroundTest : public ::testing::Test {};
class Tracko_SharedForegroundTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};



TEST_F(Tracko_SharedForegroundTest, can_be_created_without_blowing_up)
{
   Tracko::SharedForeground shared_foreground;
}


TEST_F(Tracko_SharedForegroundTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "Tracko/SharedForeground",
     Tracko::SharedForeground::TYPE
   );
}


TEST_F(Tracko_SharedForegroundTest, type__has_the_expected_value_matching_TYPE)
{
   Tracko::SharedForeground shared_foreground;
   EXPECT_EQ(Tracko::SharedForeground::TYPE, shared_foreground.get_type());
}


TEST_F(Tracko_SharedForegroundTest, render__without_allegro_initialized__raises_an_error)
{
   Tracko::SharedForeground shared_foreground;
   std::string expected_error_message =
      "SharedForeground::render: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(shared_foreground.render(), std::runtime_error, expected_error_message);
}


TEST_F(Tracko_SharedForegroundTest, render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   Tracko::SharedForeground shared_foreground;
   std::string expected_error_message =
      "SharedForeground::render: error: guard \"al_is_primitives_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(shared_foreground.render(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(Tracko_SharedForegroundTest, render__without_font_addon_initialized__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   Tracko::SharedForeground shared_foreground;
   std::string expected_error_message =
      "SharedForeground::render: error: guard \"al_is_font_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(shared_foreground.render(), std::runtime_error, expected_error_message);
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(Tracko_SharedForegroundTest, render__without_a_font_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   Tracko::SharedForeground shared_foreground;
   std::string expected_error_message =
      "SharedForeground::render: error: guard \"font_bin\" not met";
   EXPECT_THROW_WITH_MESSAGE(shared_foreground.render(), std::runtime_error, expected_error_message);
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}   


TEST_F(Tracko_SharedForegroundTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::EventEmitter event_emitter;

   Tracko::SharedForeground shared_foreground;
   shared_foreground.set_event_emitter(&event_emitter);
   shared_foreground.set_bitmap_bin(&get_bitmap_bin_ref());
   shared_foreground.set_font_bin(&get_font_bin_ref());
   shared_foreground.initialize();

   shared_foreground.render();

   al_flip_display();
   sleep_for(1);
}


