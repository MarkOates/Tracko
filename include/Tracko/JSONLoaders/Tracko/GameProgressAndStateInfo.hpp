#pragma once


#include <lib/nlohmann/json.hpp>
#include <Tracko/GameProgressAndStateInfo.hpp>


namespace Tracko
{
  void to_json(nlohmann::json& j, const GameProgressAndStateInfo& object);
  void from_json(const nlohmann::json& j, GameProgressAndStateInfo& object);
}


