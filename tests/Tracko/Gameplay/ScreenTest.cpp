
#include <gtest/gtest.h>

#include <Tracko/Gameplay/Screen.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/WithAllegroFlareFrameworksFullFixture.hpp>
//#include <AllegroFlare/Frameworks/Full.hpp>


// NOTE: Fully commented out
// NOTE: Fully commented out
// NOTE: Fully commented out
// NOTE: Fully commented out
// NOTE: Fully commented out
class TestGameConfiguration : public Tracko::GameConfigurations::Main
{
public:
   // TODO: Upgrade this out of void* to a level base class (once the upstream design is clear)
   virtual AllegroFlare::Levels::Base *load_level_by_identifier(std::string identifier) override
   {
      // NOTE: Not used in this test
      //RPG::Gameplay::Level *result = new RPG::Gameplay::Level();
      //if (identifier == "test_level")
      //{
         //result->set_background_image_identifier("maps/rpg-fit-backgrounds-x2-01.png");
      //}
      //return result;
      return nullptr;
   }
};


class Tracko_Gameplay_ScreenTest : public ::testing::Test {};
class Tracko_Gameplay_ScreenTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};
class Tracko_Gameplay_ScreenTestWithAllegroFrameworksFullFixture
   : public AllegroFlare::Testing::WithAllegroFlareFrameworksFullFixture
{};


/*

TEST_F(Tracko_Gameplay_ScreenTest, can_be_created_without_blowing_up)
{
   Tracko::Gameplay::Screen screen;
}


TEST_F(Tracko_Gameplay_ScreenTest, TYPE__has_the_expected_value)
{
   Tracko::Gameplay::Screen screen;
   EXPECT_EQ("Tracko/Gameplay/Screen", screen.get_type());
}


TEST_F(Tracko_Gameplay_ScreenTest, type__has_the_expected_value_matching_TYPE)
{
   Tracko::Gameplay::Screen screen;
   EXPECT_EQ(Tracko::Gameplay::Screen::TYPE, screen.get_type());
}


*/

TEST_F(Tracko_Gameplay_ScreenTestWithAllegroFrameworksFullFixture,
   CAPTURE__TIMED_INTERACTIVE__will_run_as_expected)
{
   TestGameConfiguration game_configuration;
   Tracko::Gameplay::Screen screen;
   screen.set_event_emitter(get_framework_event_emitter());
   screen.set_bitmap_bin(get_framework_bitmap_bin());
   screen.set_font_bin(get_framework_font_bin());
   screen.set_model_bin(get_framework_model_bin());
   screen.set_game_configuration(&game_configuration),
   screen.initialize();

   framework_register_and_activate_screen("screen", &screen);

   screen.load_level_by_identifier("level_1");

   framework_run_loop(-1);
}


