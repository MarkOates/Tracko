
#include <gtest/gtest.h>

#include <Tracko/JSONLoaders/Tracko/GameProgressAndStateInfo.hpp>
#include <Tracko/Testing/Comparison/Tracko/GameProgressAndStateInfo.hpp>


TEST(Tracko_JSONLoaders_Tracko_GameProgressAndStateInfoTest,
   to_json__returns_the_object_as_json_with_the_expected_values)
{
   Tracko::GameProgressAndStateInfo game_progress_and_state_info;
   game_progress_and_state_info.set_player_inventory_items({ "fruit", "veggie", "fork" });

   nlohmann::json j = game_progress_and_state_info;

   std::string expected_values =
R"({
  "player_inventory_items": [
    "fruit",
    "veggie",
    "fork"
  ]
})";

   std::string actual_values = j.dump(2);
   EXPECT_EQ(expected_values, actual_values);
}


TEST(Tracko_JSONLoaders_Tracko_GameProgressAndStateInfoTest,
   from_json__loads_json_data_into_the_object)
{
   Tracko::GameProgressAndStateInfo game_progress_and_state_info;

   std::string json =
R"({
  "player_inventory_items": [
    "fruit",
    "veggie",
    "fork"
  ]
})";

   nlohmann::json parsed_json = nlohmann::json::parse(json);
   parsed_json.get_to(game_progress_and_state_info);

   Tracko::GameProgressAndStateInfo expected;
   expected.set_player_inventory_items({ "fruit", "veggie", "fork" });

   EXPECT_EQ(expected, game_progress_and_state_info);
}


