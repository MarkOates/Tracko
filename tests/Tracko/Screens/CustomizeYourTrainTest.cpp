
#include <gtest/gtest.h>

#include <Tracko/Screens/CustomizeYourTrain.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/WithAllegroFlareFrameworksFullFixture.hpp>
//#include <AllegroFlare/Frameworks/Full.hpp>

class Tracko_Screens_CustomizeYourTrainTest : public ::testing::Test {};
class Tracko_Screens_CustomizeYourTrainTestWithAllegroRenderingFixture
   : public Tracko::Testing::WithAllegroRenderingFixture
{};
class Tracko_Screens_CustomizeYourTrainTestWithAllegroFrameworksFullFixture
   : public Tracko::Testing::WithAllegroFlareFrameworksFullFixture
{};



TEST_F(Tracko_Screens_CustomizeYourTrainTest, can_be_created_without_blowing_up)
{
   Tracko::Screens::CustomizeYourTrain level_select_screen;
}


TEST_F(Tracko_Screens_CustomizeYourTrainTest, TYPE__has_the_expected_value)
{
   Tracko::Screens::CustomizeYourTrain level_select_screen;
   EXPECT_EQ("Tracko/Screens/CustomizeYourTrain", level_select_screen.get_type());
}


TEST_F(Tracko_Screens_CustomizeYourTrainTest, type__has_the_expected_value_matching_TYPE)
{
   Tracko::Screens::CustomizeYourTrain level_select_screen;
   EXPECT_EQ(Tracko::Screens::CustomizeYourTrain::TYPE, level_select_screen.get_type());
}


TEST_F(Tracko_Screens_CustomizeYourTrainTest, set_levels_list__will_set_the_levels_list_on_the_element)
{
   Tracko::Screens::CustomizeYourTrain level_select_screen;
   std::vector<std::pair<std::string, std::string>> levels_list = {
      { "Candy Kingdom", "candy_kingdom" },
      { "Cherry Blossom Grove", "cherry_blossom_grove" },
      { "Bubble Pop Bay", "bubble_pop_bay" },
      { "Neon City Nights", "neon_city_nights" },
      { "Wonderland Woods", "wonderland_woods" },
   };

   level_select_screen.set_levels_list(levels_list);

   EXPECT_EQ(levels_list, level_select_screen.get_level_select_element_ref().get_levels_list());
}


TEST_F(Tracko_Screens_CustomizeYourTrainTestWithAllegroRenderingFixture,
   activate_selected_menu_option__when_an_on_menu_choice_callback_func_is_present__will_call_the_callback)
{
   Tracko::EventEmitter event_emitter;
   event_emitter.initialize();
   Tracko::Screens::CustomizeYourTrain level_select_screen;
   level_select_screen.set_event_emitter(&event_emitter);
   level_select_screen.set_font_bin(&get_font_bin_ref());
   level_select_screen.set_bitmap_bin(&get_bitmap_bin_ref());
   level_select_screen.set_levels_list({
      { "Candy Kingdom", "candy_kingdom" },
      { "Cherry Blossom Grove", "cherry_blossom_grove" },
      { "Bubble Pop Bay", "bubble_pop_bay" },
      { "Neon City Nights", "neon_city_nights" },
      { "Wonderland Woods", "wonderland_woods" },
   });
   level_select_screen.initialize();

   int my_callback_user_data_representing_num_callback_calls = 0;
   level_select_screen.set_on_menu_choice_callback_func([this](Tracko::Screens::CustomizeYourTrain*, void* data) {
      // Increment my_callback_user_data_representing_num_callback_calls
      (*(int*)data)++;
   });
   level_select_screen.set_on_menu_choice_callback_func_user_data(
      &my_callback_user_data_representing_num_callback_calls
   );

   level_select_screen.activate_selected_menu_option();

   EXPECT_EQ(1, my_callback_user_data_representing_num_callback_calls);
}


TEST_F(Tracko_Screens_CustomizeYourTrainTestWithAllegroFrameworksFullFixture,
   TIMED_INTERACTIVE__will_run_as_expected)
{
   Tracko::Screens::CustomizeYourTrain level_select_screen;
   level_select_screen.set_event_emitter(get_framework_event_emitter());
   level_select_screen.set_bitmap_bin(get_framework_bitmap_bin());
   level_select_screen.set_font_bin(get_framework_font_bin());
   // TODO: As alternative to creating this dummy callback, could (and and) set submit_on_activate_if_empty to false
   level_select_screen.set_on_menu_choice_callback_func(
      [this](Tracko::Screens::CustomizeYourTrain*, void* data) {} // Nothing to do
   );
   level_select_screen.initialize();

   framework_register_and_activate_screen("level_select_screen", &level_select_screen);

   framework_run_loop(3);
}


TEST_F(Tracko_Screens_CustomizeYourTrainTestWithAllegroFrameworksFullFixture,
   on_activate__when_no_levels_are_present__when_submit_on_activate_if_empty_is_true__\
will_call_on_menu_choice_callback_func)
{
   Tracko::Screens::CustomizeYourTrain level_select_screen;
   level_select_screen.set_event_emitter(get_framework_event_emitter());
   level_select_screen.set_bitmap_bin(get_framework_bitmap_bin());
   level_select_screen.set_font_bin(get_framework_font_bin());
   level_select_screen.initialize();

   int my_callback_user_data_representing_num_callback_calls = 0;
   level_select_screen.set_on_menu_choice_callback_func([this](Tracko::Screens::CustomizeYourTrain*, void* data) {
      // Increment my_callback_user_data_representing_num_callback_calls
      (*(int*)data)++;
   });
   level_select_screen.set_on_menu_choice_callback_func_user_data(
      &my_callback_user_data_representing_num_callback_calls
   );

   framework_register_and_activate_screen("level_select_screen", &level_select_screen);

   EXPECT_EQ(1, my_callback_user_data_representing_num_callback_calls);
}


TEST_F(Tracko_Screens_CustomizeYourTrainTestWithAllegroFrameworksFullFixture,
   on_activate__when_no_levels_are_present__when_submit_on_activate_if_empty_is_true__when_on_menu_choice_callback_func_\
is_not_present__will_throw_an_error)
{
   Tracko::Screens::CustomizeYourTrain level_select_screen;
   level_select_screen.set_event_emitter(get_framework_event_emitter());
   level_select_screen.set_bitmap_bin(get_framework_bitmap_bin());
   level_select_screen.set_font_bin(get_framework_font_bin());
   level_select_screen.initialize();

   ASSERT_THROW_WITH_MESSAGE(
      framework_register_and_activate_screen("level_select_screen", &level_select_screen),
      std::runtime_error,
      "[Tracko::Screens::CustomizeYourTrain]: error: \"submit_on_activate_if_empty\" is set to true, thus "
         "expecting an \"on_menu_choice_callback_func\"  to be present but it is not."
   );
}


