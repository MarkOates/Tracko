
#include <gtest/gtest.h>

#include <Tracko/GameConfigurations/Main.hpp>


TEST(Tracko_GameConfigurations_MainTest, can_be_created_without_blowing_up)
{
   Tracko::GameConfigurations::Main main_configuration;
}


TEST(Tracko_GameConfigurations_MainTest, load_level_by_identifier__will_not_blow_up)
{
   Tracko::GameConfigurations::Main main_configuration;
   AllegroFlare::Levels::Base* level = main_configuration.load_level_by_identifier("forest_village_1");
   EXPECT_NE(nullptr, level);
}


