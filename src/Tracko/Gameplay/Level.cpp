

#include <Tracko/Gameplay/Level.hpp>




namespace Tracko
{
namespace Gameplay
{


Level::Level()
   : AllegroFlare::Levels::Base(Tracko::Gameplay::Level::TYPE)
   , title("[unset-title]")
{
}


Level::~Level()
{
}


void Level::set_title(std::string title)
{
   this->title = title;
}


std::string Level::get_title() const
{
   return title;
}




} // namespace Gameplay
} // namespace Tracko


