
#include <gtest/gtest.h>

#include <Tracko/GameProgressAndStateInfo.hpp>


TEST(Tracko_GameProgressAndStateInfoTest, can_be_created_without_blowing_up)
{
   Tracko::GameProgressAndStateInfo game_progress_and_state_info;
}


TEST(Tracko_GameProgressAndStateInfoTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "Tracko/GameProgressAndStateInfo",
     Tracko::GameProgressAndStateInfo::TYPE
   );
}


TEST(Tracko_GameProgressAndStateInfoTest, type__has_the_expected_value_matching_TYPE)
{
   Tracko::GameProgressAndStateInfo game_progress_and_state_info;
   EXPECT_EQ(Tracko::GameProgressAndStateInfo::TYPE, game_progress_and_state_info.get_type());
}


